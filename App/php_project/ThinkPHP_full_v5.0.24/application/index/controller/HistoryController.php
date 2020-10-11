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
		$historys = $History->order('project_date')->select();
										
		$this->assign('historys', $historys);		
	    $htmls = $this->fetch();
		
		return $htmls;
    }
	
	/*
	public function statistics()
    {		     		
	    $htmls = $this->fetch();
		
		return $htmls;
    }
	*/
	
	public function statistics()
    {		     	
		$History = new History;
		$today_date = date('Y-m-d', time());
        $latest7date = date('Y-m-d', time()-6*24*60*60);	
		$map['project_date'] = array(array('egt',$latest7date),array('elt',$today_date));
		$historys = $History->where($map)->order('project_date desc')->select();
					
		$this->assign('historys', $historys);		
	    $htmls = $this->fetch();
		
		return $htmls;
    }
	
	
}

