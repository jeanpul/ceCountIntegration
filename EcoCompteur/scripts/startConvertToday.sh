#!/bin/bash

. /etc/BEV/scripts/BlueSystem/Logs.inc

CLIENTBLUEPORTAIL=$1

DATE=$(date +%Y%m%d)

if [ $(ps -ef | grep -v grep | grep -c startConvertToday) -gt 2 ]; then
    Logs_add $0 "$0 already running cannot perform check for date $DATE"
    exit -1;
fi

if [ $(ps -ef | grep ConvertBlueHTTP | grep -c $CLIENTBLUEPORTAIL) -eq 1 ]; then
    Logs_add $0 "Conversion already running on $CLIENTBLUEPORTAIL cannot perform check for date $DATE"
    exit -1
fi

php /var/www/EcoCompteur/ConvertBlueHTTP.php $DATE $CLIENTBLUEPORTAIL > /tmp/lastConvertOutput

