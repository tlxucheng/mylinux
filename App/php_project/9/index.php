<form name="form1" method="post" action="">
	<table width="300" border="0" cellpadding="0" cellspacing="0">
		<tr>
			<td height="30">&nbsp;&nbsp;订单号:
			 <input type="text" name="user" size="20">
			 <input name="submit" type="submit" id = "submit" value="提交">
			</td>
		</tr>
	</table>
</form>

<?php
// if($_POST["submit"]=="提交"){
if (isset($_POST['submit']) && $_POST['submit']) {
	echo "提交成功";
}
?>