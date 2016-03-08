#!/bin/bash

CLIENTBLUEPORTAIL=$1

php /var/www/EcoCompteur/ConvertBlueHTTP.php $(date +%Y%m%d) $CLIENTBLUEPORTAIL > /tmp/lastConvertOutput

