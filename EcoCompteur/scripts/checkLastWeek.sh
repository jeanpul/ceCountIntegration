#!/bin/bash

. /etc/BEV/scripts/BlueSystem/Logs.inc

CLIENTBLUEPORTAIL=$1

DATE=$(date +%Y%m%d)
HISTORY=2
CMD=checkLastWeek

if [ $(ps -e | grep -c $CMD) -gt 2 ]; then
    Logs_add $0 "Instance already running cannot perform check for date $DATE and $HISTORY days"
    exit -1;
fi

php /var/www/EcoCompteur/CheckLastDays.php $DATE $HISTORY $CLIENTBLUEPORTAIL > /tmp/lastWeekConvertOutput

