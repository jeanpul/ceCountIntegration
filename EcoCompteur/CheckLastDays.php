<?php

if($argc < 2)
  {
    ?>
Check and convert EcoCompteur csv file from n days
in the past of the specified date. The specified date
will not be considered.
Usage : CheckLastDays.php YYMMDD ndays [clientBluePortail]
<?php
    exit(-1);
  }

$date = $argv[1];
$ndays = $argv[2];
$clientBluePortail="";
if(isset($argv[3]))
  {
    $clientBluePortail = $argv[3];
  }

for($i = 1; $i <= $ndays; ++$i)
  {
    $prevDate = strftime("%Y%m%d", mktime( 0, 0, 0,
					   substr($date, 4, 2),
					   substr($date, 6, 2) - $i,
					   substr($date, 0, 4)));
    echo "*** CheckLastDays check date $prevDate for $clientBluePortail\n";
    passthru("php /var/www/EcoCompteur/ConvertBlueHTTP.php " . $prevDate 
	      . " " . $clientBluePortail);
  }

?>
