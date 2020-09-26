<?php
namespace app\index\controller;
use think\Controller;
use app\common\model\Teacher;

//use think\Db;

/*
class TeacherController
{
    public function index()
    {			
		$Teacher = new Teacher;
		$teachers = $Teacher->select();
		
		$teacher = $teachers[0];
		
		var_dump($teacher->getData('name'));
		echo $teacher->getData('name');
		//echo 'hello teacher';
    }

}
*/

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

}

