<?php

require_once("BluePHP/Window.inc");
require_once("BluePHP/ModuleInterface.inc");
require_once("Forms.inc");
require_once("EcoCompteurs.inc");

class EcoCompteursHTML extends ModuleInterface
{
  function EcoCompteursHTML($params)
  {
    parent::setName(_("EcoCompteurs"));
    parent::setModule(new EcoCompteurs());
    $this->setWindow($params);
  }

  function setWindow($params)
  {
    $params = array_merge( array( "action" => "list"), 
			   $params );

    $winTitle = "";
    $winContent = "";
    if($params["action"] == "list")
      {
	$winTitle = _("EcoCompteurs configuration");
	$winContent = "EcoCompteurs"; 
      }
    else
      {    
	$winTitle = _("EcoCompteurs configuration");
	$winContent = "EcoCompteursEdit"; 
      }
    parent::setTitle($winTitle);
    parent::setContent($winContent);
    parent::setParams($params);
  }

  protected function getTableInput($params)
  {
    $colList = array( array( "id" => "E1" ), array( "id" => "S1" ),
		      array( "id" => "E2" ), array( "id" => "S2" ),
		      array( "id" => "E3" ), array( "id" => "S3" ),
		      array( "id" => "E4" ), array( "id" => "S4" ),
		      array( "id" => "E5" ), array( "id" => "S5" ),
		      array( "id" => "E6" ), array( "id" => "S6" ),
		      array( "id" => "E7" ), array( "id" => "S7" ),
		      array( "id" => "E8" ), array( "id" => "S8" ) );

    $str = "<table>\n";    
    $str .= get2CellsRow(_("ClientId"), getInputText($params["clientId"],
					      array( "name" => "clientId",
						     "readonly" => false,
						     "extra" => false )));

    $str .= get2CellsRow(_("ColCounter0"), getSelectTemplate($colList,
							     array( "value" => "id",
								    "name" => "colCounter0",
								    "key" => "id",
								    "default" => $params["colCounter0"],
								    "extra" => false )));

    $str .= get2CellsRow(_("ColCounter1"), getSelectTemplate($colList,
							     array( "value" => "id",
								    "name" => "colCounter1",
								    "key" => "id",
								    "default" => $params["colCounter1"],
								    "extra" => false )));

    $str .= get2CellsRow(_("Range"), getSelectTemplate( array( array( "key" => "1", "value" => "1 minute" ),
							       array( "key" => "15", "value" => "15 minutes" ),
							       array( "key" => "60", "value" => "1 hour" ) ),
							array( "value" => "value",
							       "name" => "range",
							       "key" => "key",
							       "default" => $params["range"],
							       "extra" => false )));

    $str .= get2CellsRow(_("TimeZone"), getSelectTemplate(timezone_identifiers_list(),
							  array( "value" => false,
								 "name" => "tz",
								 "key" => false,
								 "default" => $params["tz"],
								 "extra" => false )));

    $str .= get2CellsRow(_("ftp_server"), getInputText($params["ftp_server"],
					      array( "name" => "ftp_server",
						     "readonly" => false,
						     "extra" => false )));

    $str .= get2CellsRow(_("ftp_port"), getInputText($params["ftp_port"],
					      array( "name" => "ftp_port",
						     "readonly" => false,
						     "extra" => false )));

    $str .= get2CellsRow(_("ftp_login"), getInputText($params["ftp_login"],
					      array( "name" => "ftp_login",
						     "readonly" => false,
						     "extra" => false )));

    $str .= get2CellsRow(_("ftp_passwd"), getInputText($params["ftp_passwd"],
					      array( "name" => "ftp_passwd",
						     "readonly" => false,
						     "extra" => false )));

    $str .= get2CellsRow(_("ftp_dir"), getInputText($params["ftp_dir"],
						    array( "name" => "ftp_dir",
							   "readonly" => false,
							   "extra" => false )));

    $str .= get2CellsRow(_("bluehttp_server"), getInputText($params["bluehttp_server"],
					      array( "name" => "bluehttp_server",
						     "readonly" => false,
						     "extra" => false )));

    $str .= get2CellsRow(_("bluehttp_port"), getInputText($params["bluehttp_port"],
					      array( "name" => "bluehttp_port",
						     "readonly" => false,
						     "extra" => false )));

    $str .= get2CellsRow(_("bluehttp_script"), getInputText($params["bluehttp_script"],
					      array( "name" => "bluehttp_script",
						     "readonly" => false,
						     "extra" => false )));

    $str .= get2CellsRow(_("Comment"), getInputTextArea($params["comment"],
							 array( "name" => "comment",
								"rows" => 4,
								"cols" => 40,
								"extra" => false )));    
    $str .= "</table>\n";
    return $str;
  }

  function getTableList($pagename)
  {
    return parent::getModuleTableList(array("ctitle" => _("Add a new EcoCompteur"),
					    "titles" => array( _("ClientId"), _("ColCounter0"), _("ColCounter1"), 
							       _("Ftp"), _("Range"), _("TimeZone"), _("BlueHTTP") ),
					    "cols" => array( "clientId", "colCounter0", "colCounter1", 
							     "ftp_server", "range", "tz", "bluehttp_server" ) ),
				      $pagename);
  }
  
}


?>
