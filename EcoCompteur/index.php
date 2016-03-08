<?php

include_once("BluePHP/Window.inc");
include_once("BluePHP/Application.inc");
include_once("Config.inc");

$app = new Application(new Window(_("EcoCompteur configuration"), "index"));
$app->render();

?>
