<?php

include_once("DBConnect.inc");

class ModuleProcessing
{
  var $con = false;
  var $conParams = false;
  var $enquote = false;

  var $params = array( "name" => null,
		       "keyname" => null );

  function getEntries()
  {
    return $this->getModuleEntries($this->params);
  }

  function getEntry($params)
  {
    return $this->getModuleEntry($params);
  }

  function getKey()
  {
    return $this->params["keyname"];
  }

  function enquoteKey($v)
  {
    $this->enquote = $v;
  }

  function getKeys()
  {
    return explode(",", $this->params["keyname"]);
  }

  function getName()
  {
    return $this->params["name"];
  }

  function newEntry($params)
  {
    return $this->newModuleEntry($params);
  }

  function setEntry($params)
  {
    return $this->setModuleEntry($params);
  }

  function delEntry($params)
  {
    return $this->delModuleEntry($params);
  }

  function setConParams($params)
  {
    $this->conParams = $params;
  }

  function getKeyCond($params, $sep = " AND ", $checkNum = true)
  {
    $str = "";
    $keyList = $this->getKeys();
    $lastKey = end($keyList);
    foreach($keyList as $k => $v)
      {
	$curKey = $params[$v];
	if($checkNum)
	  {
	    $str .= $v . "=" . (is_numeric($curKey) ? $curKey : "\"$curKey\"");
	  }
	else
	  {
	    $str .= $v . "=" . $curKey;
	  }
	if($v != $lastKey)
	  {
	    $str .= $sep;
	  }
      }
    return $str;
  }

  function haveKey($params)
  {
    $keyList = $this->getKeys();
    foreach($keyList as $k => $v)
      {
	if(!array_key_exists($v, $params))
	  {
	    return false;
	  }
      }
    return true;
  }

  protected function getParams()
  {
    return $this->params;
  }

  protected function setParams($params)
  {
    $this->params = $params;
  }

  protected function Select($query)
  {
    $res = array();
    $this->connect();
    $result = $this->con->query("select " . $query);
    while($obj = $result->nextAssoc())
      {
	$res[] = $obj;
      }
    $result->freeResult();
    return $res;    
  }  

  protected function connect()
  {
    if(!$this->con)
      {
	if(!$this->conParams)
	  {
	    $this->con = new DBConnect(DATADBTYPE, 
				       DATADBHOST, 
				       DATADBNAME,
				       DATADBUSER, 
				       DATADBPASSWD);
	  }
	else
	  {
	    $this->con = new DBConnect($this->conParams["type"],
				       $this->conParams["host"],
				       $this->conParams["name"],
				       $this->conParams["user"],
				       $this->conParams["passwd"]);
	  }
	$this->con->connectToDB();
      }
    return $this->con;
  }

  private function getModuleEntries($params)
  {
    $res = array();
    $query = "select ";
    if(isset($params["fields"]) and $params["fields"])
      {
	$query .= $params["fields"];
      }
    else
      {
	$query .= "*";
      }

    $query .= " from " . $this->getName();
    if(isset($params["sort"]) and $params["sort"])
      {
	$query .= " order by " . $params["sort"];
      }   
    $this->connect();
    $result = $this->con->query($query);
    while($obj = $result->nextAssoc())
      {
	$res[] = $obj;
      }
    $result->freeResult();
    
    return $res;    
  }

  private function getModuleEntry($params)
  {
      $res = array();
      if($this->haveKey($params))
          {
              $query = "SELECT * FROM " . $this->getName() . 
                  " WHERE " . $this->getKeyCond($params);             
              $this->connect();
              $result = $this->con->query($query);
              $res = $result->nextAssoc();
              $result->freeResult();
          }
      else
          {
              $res = array_merge($this->getModuleParams($params),
              $params);
              $res = array_merge($res, $params);
          }
      return $res;
  }

  private function getModuleParams($params)
  {
    $res = array();
    $this->connect();
    $data = $this->con->describes($this->getName());
    foreach($data as $k => $v)
      {
	$res[$v["Field"]] = null; // empty parameter
      }
    return $res;
  }
    
  private function newModuleEntry($params)
  {
    $data = array_intersect_key($params,
				$this->getModuleParams( array( "name" => $this->getName() )));
    $this->connect();
    return $this->con->insert($this->getName(), $data);
  }

  private function setModuleEntry($params)
  {
    $data = array_intersect_key($params,
				$this->getModuleParams( array( "name" => $this->getName() )));
    $this->connect();
    return $this->con->update($this->getName(),
			      $this->getKeys(),
			      $data);
  }

  private function delModuleEntry($params)
  {
    $this->connect();
    return $this->con->delete($this->getName(),
			      $this->getKeys(),
			      $params);
  }
  
}

?>