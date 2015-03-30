
#include <stdlib.h>  
#include <sys/types.h>  
#include <stdio.h>  
#include <sys/socket.h>  
#include <linux/in.h>  
#include <string.h>  



int main ( int argc , char **argv  )
{
	if(argc !=2)
	{
		printf("please enter the portnum\n");
		return -1;
	}

	unsigned short portnum=atoi(argv[argc-1]);

	int i=0;
	int sockfd;
	int nfd;
	unsigned char receipt[]={};
	unsigned char ok_receipt[]={0x55,0x00,0x00,0xAA};
	unsigned int  len  = sizeof(struct sockaddr_in);
	
	struct sockaddr_in servaddr;
	struct sockaddr_in clienaddr;
	bzero(&servaddr,sizeof(struct sockaddr_in)); 
	servaddr.sin_family=AF_INET;  
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(portnum); 
	
	int recbytes;
	unsigned char buffer[1024]={0};
	unsigned value = 1;
	struct timeval tv;
	
	while(1)
	{
		if((sockfd = socket(AF_INET, SOCK_DGRAM, 0))<0)
		{
			printf("socket fail\n");
			return 0;
		}
		setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value));
	
		if(-1 == bind(sockfd,(struct sockaddr *)(&servaddr), sizeof(struct sockaddr)))  
		{  
	 		  printf("bind fail !\n");  
	 		  return -1;  
		}  		
	
		//if(-1 == listen(sockfd,5))  
		{  
	 	//	 printf("portnum:%d  listen fail !\n",portnum);  
	    //		 return -1;  
		}  
		printf("portnum:%d listen ok!\n",portnum);  
		
		
		//nfd=accept(sockfd, (struct sockaddr *)(&clienaddr), &len);
		//if(nfd == -1)  
		//{  
	 	//	 printf("accept fail !\r\n");  
	 	//	 return -1;  
		//}  
		printf("portnum:%d accept ok!\n",portnum);  
		nfd = sockfd;
		while ( 1 )
		{	
			recbytes = read(nfd,buffer,1024);
			if(-1 ==recbytes )  
			{  
	  			  printf("read data fail !\r\n");  
	  			  break ;
			}  
			for(i=0;i<recbytes;i++)
			{
				printf("0x%1x,",buffer[i]);
			}
			printf("\n");

			printf("send recv:%d", sizeof(ok_receipt));
			if( 0 == recbytes)  
			{  
				 if(-1 == write(nfd,ok_receipt,sizeof(ok_receipt)))  
				 {  
	   				 printf("write fail!\r\n");  
				 }  
				 printf("over!\r\n");  
				 break ;
			} 

                        gettimeofday(&tv , NULL);
			printf("portnum:%d read data %d byte SEC:%lu, USEC:%lu \n",portnum,recbytes, (unsigned long)tv.tv_sec, (unsigned long)tv.tv_usec);
			if(-1 == write(nfd,ok_receipt,sizeof(ok_receipt)))  
			{  
	   				 printf("write fail!\r\n"); 
	   				 //break ; 
			}   
		}
		close(nfd); 
		close(sockfd); 
	}
	return 1;
}

