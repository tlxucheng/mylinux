<?php
$conn = mysqli_connect("localhost", "root", "");
$db_selected = mysqli_select_db($conn, "test_db");
if($db_selected)
{
	echo "数据库连接成功";
}

$sql_statement = "insert student(name, age) values('xucheng', 34)";
if($conn->query($sql_statement) == TRUE)
{
	echo "插入记录成功";
}
else 
{
	echo "插入记录失败";
}
?>