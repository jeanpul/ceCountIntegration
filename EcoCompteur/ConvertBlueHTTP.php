<?php

if($argc < 2)
  {
    ?>
Read data from an EcoCompteur csv file and generate the BlueHTTP requests if
necessary.
Usage : ConvertBlueHTTP.php YYYMMDD [clientBluePortail]
<?php
    exit(-1);
  }

$file = $argv[1];

if(isset($argv[2]))
  {
    $_REQUEST["clientBluePortail"] = $argv[2];
  }

$params = array_merge( array( "date" => strftime("%Y%m%d") ),
		       $_GET );

include_once("BluePHP/Application.inc");
include_once("BluePHP/DateOps.inc");
require_once("Config.inc");
require_once("EcoCompteurs.inc");
require_once("Status.inc");

function getTimeRange($eco, $date)
{
  $res = array( "timeStart" => false, 
		"timeEnd" => false );
  $dateTime = new DateTime($date, new DateTimeZone($eco["tz"]));
  $dateTime->setTimeZone(new DateTimeZone("UTC"));  
  $res["timeStart"] = $dateTime->format("YmdHis");
  setLocale(LC_TIME, "UTC");
  $res["timeEnd"] = strftime("%Y%m%d%H%M%S", addTime(mkTimeFromString($res["timeStart"]), 
						     array( "hour" => 0, 
							    "minute" => $eco["range"], 
							    "second" => 0, "month" => 0, "day" => 0, "year" => 0)));
			     //  $res["timeEnd"] = $dateTime->add( DateInterval::createFromDateString("15 minute"))->format("YmdHis");
  return $res;
}

function Eco_getBlueHTTP($eco, $rowValue)
{
  // timezone conversion from Eco compteur to UTC
  $timeRange = getTimeRange($eco, $rowValue["date"]);
  return "http://" . $eco["bluehttp_server"] . ":" . $eco["bluehttp_port"] . "/" . 
    $eco["bluehttp_script"] . "?" . "client=" . $eco["clientId"] . 
    "&type=146&channel=0&timeStart=" . $timeRange["timeStart"] . 
    "&timeEnd=" . $timeRange["timeEnd"] . "&counter0=0&value0=" . $rowValue["value0"] .
    "&counter1=1&value1=" . $rowValue["value1"];
}

$emodule = new EcoCompteurs();
$entries = $emodule->getEntries();

foreach($entries as $ecoKey => $ecoObj)
  { 
    $values = $emodule->getFileContent($ecoObj, $file);
    $module = new Status();
    $status = $module->getEntry( array( "counters_id" => $ecoObj["id"],
					"file" => $file ));
    $isNewEntry = false;
    
    if(!$status)
      {
	$status = $module->getEntry( array() );
	$status["counters_id"] = $ecoObj["id"];
	$status["file"] = $file;
	$isNewEntry = true;
      }
    
    echo "<ConvertBlueHTTP> retrieve data from $file.csv for EcoCompteur " . $ecoObj["id"] . " / " . $ecoObj["clientId"] . "\n";
    
    $nbProcessed = 0;
    echo "<ConvertBlueHTTP> process ";
    foreach($values as $k => $v)
      {
	$processed = false;
	if($isNewEntry or ($status["lastDate"] < $v["date"]))
	  {
	    $blueHTTP =  Eco_getBlueHTTP($ecoObj, $v);
	    if(file_get_contents($blueHTTP))
	      {
		$status["lastDate"] = $v["date"];

		if($isNewEntry)
		  {
		    $module->newEntry($status);
		    $isNewEntry = false;
		  }
		else
		  {
		    $module->setEntry($status);
		  }
		
		$processed = "+";
		++$nbProcessed;
		usleep(250000);
	      }
	    else
	      {
		$processed = "-";
	      }
	  }
	else
	  {
	    $processed = ".";
	  }
	echo "$processed";
      }
    echo " $nbProcessed\n";

    echo "<ConvertBlueHTTP> status entry for EcoCompteur " . $ecoObj["id"] . " / " . $ecoObj["clientId"] . 
      " with file " . $status["file"] . " and last date processed " . $status["lastDate"] . "\n";
  }
?>
