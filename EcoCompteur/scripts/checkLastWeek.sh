#!/bin/bash

CLIENTBLUEPORTAIL=$1

php /var/www/EcoCompteur/CheckLastDays.php $(date +%Y%m%d) 20 $CLIENTBLUEPORTAIL > /tmp/lastWeekConvertOutput

