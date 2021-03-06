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
			switch($Nursing->project_type)
			{
				case "0":
					$History->breast_milk_number = $historys[0]->breast_milk_number + $postdata['project_number'];
					$update_array = [
					'project_date' => $History->project_date,
					'breast_milk_number' => $History->breast_milk_number
		            ];
					break;
				case "1":
					$History->formula_number = $historys[0]->formula_number + $postdata['project_number'];
					$update_array = [
					'project_date' => $History->project_date,
					'formula_number' => $History->formula_number
		            ];
					break;
				case "2":
					$History->boiling_water_number = $historys[0]->boiling_water_number + $postdata['project_number'];
				    $update_array = [
					'project_date' => $History->project_date,
					'boiling_water_number' => $History->boiling_water_number
		            ];
					break;
				case "3":
					$History->shit_number = $historys[0]->shit_number + $postdata['project_number'];
					$update_array = [
					'project_date' => $History->project_date,
					'shit_number' => $History->shit_number
		            ];
					break;
				default:
					break;
			}	
			
			$History->save($update_array, ['project_date' => $postdata['project_date']]);
	    }
		else
	    {
			switch($Nursing->project_type)
			{
				case 0:
					$History->breast_milk_number = $postdata['project_number'];
					break;
				case 1:
					$History->formula_number = $postdata['project_number'];
					break;
				case 2:
					$History->boiling_water_number = $postdata['project_number'];
					break;
				case 3:
					$History->shit_number = $postdata['project_number'];
					break;
				default:
					break;
			}
			$History->save();
		}

		return '新增成功';
	}
	
	public function statistics()
	{		
		$Nursing = new Nursing;
		
		$getdate = Request::instance()->param('project_date');
		$nursings = $Nursing->where('project_date',$getdate)->select();		
		for($i = 0; $i < count($nursings); $i++)
		{
			switch($nursings[$i]->project_type)
			{
				case 0:
					$nursings[$i]->project_type = '母乳';
					break;
				case 1:
					$nursings[$i]->project_type = '配方奶';
					break;
				case 2:
					$nursings[$i]->project_type = '开水';
					break;
				case 3:
					$nursings[$i]->project_type = '便便';
					break;
				default:
					break;
			}
		}
		$this->assign('nursings', $nursings);			
	    $htmls = $this->fetch();
		
		return $htmls;
	}
	
	public function add()
	{
		$htmls = $this->fetch();		
		return $htmls;
	}

	public function delete()
	{
	    $id = (Request::instance()->param('id/d'));
		
		if(is_null($id) || 0 == $id)
		{
			return $this->error('未获取到ID信息');
		}
		
		$Nursing = Nursing::get($id);
		
		if(is_null($Nursing))
		{
			return $this->error('不存在id为' . $id . '的记录，删除失败');
		}
		
		if(!$Nursing->delete())
		{
			return $this->error('删除失败:' . $Nursing->getError());
		}
		
		/* 还需要删除历史表 */
		
		//return $this->success('删除成功', url('index'));
	    //return $this->success('删除成功');
		return '删除成功';
	}
	
}
