<?php
namespace app\index\controller;
use think\Controller;
use think\Request;
use app\common\model\Teacher;

class TeacherController extends Controller
{
    public function index()
    {			
		$Teacher = new Teacher;
		$teachers = $Teacher->select();
		
        $this->assign('teachers', $teachers);		
	    $htmls = $this->fetch();
		
		return $htmls;
    }
	
	public function insert()
	{
		$postdata = Request::instance()->post();
		
		$Teacher = new Teacher();
		
		$Teacher->name = $postdata['name'];
		$Teacher->username = $postdata['username'];
		$Teacher->sex = $postdata['sex'];
		$Teacher->email = $postdata['email'];
		
		$Teacher->save();
		
		return '�����ɹ�������IDΪ:' . $Teacher->id;
	}
	
	public function add()
	{
		$htmls = $this->fetch();		
		return $htmls;
	}

}

