<?php
namespace app\index\controller;
use think\Controller;
use think\Request;
use app\common\model\History;

class HistoryController extends Controller
{
	public function history()
    {		     	
		$History = new History;
		$historys = $History->select();
					
		$this->assign('historys', $historys);		
	    $htmls = $this->fetch();
		
		return $htmls;
    }
}

