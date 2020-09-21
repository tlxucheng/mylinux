<?php
function insert($tableName, $column = array())
{
    $columnName = "";
    $columnValue = "";
    foreach ($column as $key => $value) {
		$columnName .= $key . ",";
		$columnValue .= "'" . $value . "',";
    }
	
	$columnName = substr($columnName, 0, strlen($columnName) - 1);
    $columnValue = substr($columnValue, 0, strlen($columnValue) - 1);
    $sql = "INSERT INTO $tableName($columnName) VALUES($columnValue)";
	
	echo $sql;
}

$userInfo = array('username'=>'system', 'password' => "123456");
insert("user", $userInfo);

/*
$userInfo2 = array('username'=>'system', 'password' => 123456);
insert("user", $userInfo2);
*/

?>