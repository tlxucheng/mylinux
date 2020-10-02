<?php
namespace app\index\controller;
use think\Controller;
use think\Request;
use app\common\model\Nursing;

class NursingController extends Controller
{
	public function index()
    {			
		$Nursing = new Nursing;
		$nursings = $Nursing->select();
		
        $this->assign('nursings', $nursings);		
	    $htmls = $this->fetch();
		
		return $htmls;
    }
	
	public function insert()
	{
		$postdata = Request::instance()->post();
		
		$Nursing = new Nursing();
		
		//$Nursing->project_type = $postdata['project_type'];
		$Nursing->project_number = $postdata['project_number'];
		$Nursing->project_date = $postdata['project_date'];
		$Nursing->project_time = $postdata['project_time'];
		$Nursing->project_comments = $postdata['project_comments'];
		
		$Nursing->save();
		
		return '新增成功。新增ID为:' . $Nursing->id;
	}
	
	public function history()
	{		
	    $htmls = $this->fetch();
		
		return $htmls;
	}
	
	public function add()
	{
		$htmls = $this->fetch();		
		return $htmls;
	}

}

