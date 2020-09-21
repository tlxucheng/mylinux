<?php
$lang_php = array("c", "cpp", "java", "c#", "php");
print_r($lang_php);
echo "<br>";

$test_array = array("c", "cpp", "java", "c#", 10);
print_r($test_array);
echo "<br>";
print($test_array[0]);
echo "<br>";
print($test_array[4]);
echo "<br>";

$test_ass_array = array("first"=>"cpp", "second"=>"java", "third"=>100);
print_r($test_ass_array);
echo "<br>";
print($test_ass_array["first"]);
echo "<br>";
print($test_ass_array["third"]);
echo "<br>";

$matrix = array("1"=>array(1,2,3),"2"=>array(4,5,6),"3"=>array(7,8,9));
print_r($matrix);
echo "<br>.<br>";

foreach($test_ass_array as $elem)
{
	echo $elem.'<br>';
}

foreach($matrix as $row)
{
	foreach($row as $rol)
	{
		echo $rol.' ';
	}
    echo '<br>';
}

?>