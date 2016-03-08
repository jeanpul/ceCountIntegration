<?php

include_once("BluePHP/Application.inc");
require_once("Config.inc");
require_once("StatusHTML.inc");

$status = new StatusHTML($_GET);
$app = new Application($status);
$app->render();

?>