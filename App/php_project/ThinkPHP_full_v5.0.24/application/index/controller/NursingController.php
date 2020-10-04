<?php
namespace app\index\controller;
use think\Controller;
use think\Request;
use app\common\model\Nursing;
use app\common\model\History;

class NursingController extends Controller
{
	public function history()
    {		     	
		$Nursing = new Nursing;
		$nursings = $Nursing->field('project_type, project_date, sum(project_number) as project_number,project_time,project_comments')
		            ->group('project_date, project_type')->select();
					
		$this->assign('nursings', $nursings);		
	    $htmls = $this->fetch();
		
		return $htmls;
    }
	
	public function insert()
	{
		$postdata = Request::instance()->post();
		
		$Nursing = new Nursing();

		$Nursing->project_type = $postdata['project_type'];
		$Nursing->project_number = $postdata['project_number'];
		$Nursing->project_date = $postdata['project_date'];
		$Nursing->project_time = $postdata['project_time'];
		$Nursing->project_comments = $postdata['project_comments'];
		
		$Nursing->save();
		
		$History = new History();
		$historys = $History->where('project_date',$Nursing->project_date)->select();
		
		$History->project_date = $postdata['project_date'];
		if(!empty($historys))
	    {
			$History->breast_milk_number = $historys[0]->breast_milk_number + $postdata['project_number'];
			
			$update_array = [
				'project_date' => $History->project_date,
				'breast_milk_number' => $History->breast_milk_number
		    ];
			$History->save($update_array, ['project_date' => $postdata['project_date']]);
	    }
		else
	    {
	        $History->breast_milk_number = $postdata['project_number'];
			$History->save();
		}

		return '新增成功';
	}
	
	public function statistics()
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

