<?php

include_once("BluePHP/Application.inc");
require_once("Config.inc");
require_once("EcoCompteursHTML.inc");

$counters = new EcoCompteursHTML($_GET);
$app = new Application($counters);
$app->render();

?>
