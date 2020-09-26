<?php
class MyDB
{	
    const MYSQL_DEFAULT_PORT = 3306; 

	public function __construct($host, $port, $ip)
	{
	    $this->host = $host;
		$this->port = $port;
		$this->ip = $ip;
	}
	
	public function init($para_host, $para_port, $para_ip)
	{
		$this->host = $para_host;
		$this->port = $para_port;
		$this->ip = $para_ip;
	}
	
	public function show_init_info()
	{
		echo $this->host."<br>";
		echo $this->port."<br>";
		echo $this->ip."<br>";
	}

	public function show()
	{
		echo "MyDB class print."."<br>";
	}
	
	public function __destruct()
	{
	    echo "call destruct function."."<br>";
	}
	
	private $host;
	private $port;
	private $ip;
}

$test_my_db = new MyDB("cc.com", 5076, "192.168.0.112");
$test_my_db->show();

//$test_my_db->init("cc.com", 5076, "192.168.0.111");
$test_my_db->show_init_info();

echo MyDB::MYSQL_DEFAULT_PORT."<br>";

?>