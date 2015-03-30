#!/bin/sh 

get_config_ini_value()
{
	if [ -f $1 ];then
		awk -F= -v tmpkey="$2"  ' $1==tmpkey {print $2} '  $1  ;
	else 
		echo NULL ;
	fi
}

TEST_CONIFG=./config.ini
led_type=`get_config_ini_value $TEST_CONIFG "led_type"`
count=`get_config_ini_value $TEST_CONIFG "count"`
star_portnum=`get_config_ini_value $TEST_CONIFG "star_portnum"`

for (( i=0; i<$count; i++)); do
	./$led_type $(($star_portnum+$i)) &
done