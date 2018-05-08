<?php
/*
if($db = sqlite_open('../lesson12.sqlite3', 0666, $sqliteerror)){
	$result = sqlite_array_query($db, 'select id, strTitle from table_article', SQLITE_ASSOC);
	echo 'table_article 表查询\n';
	echo 'id, strTitle\n';
	foreach( $result as $entry){
		echo ' '.$entry['id'].' '.$entry['strTitle'].'\n';
	}
	sqlite_close($db);
}else{
	die($sqliteerror);
}
*/

class SQLite3DB extends SQLite3{
	//		 __construct
	function __construct(){
		//$this->open('../lesson12.sqlite3');
		$this->open('E:\\PASCAL\\sys\\public\\Users\\PASCAL\\DESK\\f\\CODE\\CODE-asp.net\\lesson12\\App_Data\\lesson12.sqlite3');
	}
}

$strCrlf = "\r\n";

//echo 'lesson12-sqlite3-db-php.php'.$strCrlf;

$db = new SQLite3DB();

if(!$db){
	echo $db->lastErrorMsg();
}else{
	//echo 'Opened databases successfully!'.$strCrlf;
}

echo '<!DOCTYPE html>'.$strCrlf;
echo '<html xmlns="http://www.w3.org/1999/xhtml">'.$strCrlf;
echo '<head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" /><title>'.$strCrlf;
echo '	sqlite3-db--lesson12--php.php'.$strCrlf;
echo '</title>'.$strCrlf;
echo '	<style type="text/css">#GridView1{font-size:12px;}</style>'.$strCrlf;
echo '</head>'.$strCrlf;
echo '<body>'.$strCrlf;
echo '	<h1>lesson12-sqlite3-db-php.php</h1>'.$strCrlf;
echo '	<div>'.$strCrlf;
echo '	<table cellspacing="0" cellpadding="3" rules="all" border="1" id="GridView1" style="border-collapse:collapse;">'.$strCrlf;
echo '		<tr>'.$strCrlf;
echo '			<th scope="col">id</th><th scope="col">标题</th><th scope="col">时间</th><th scope="col">分类ID</th><th scope="col">分类</th><th scope="col">浏览数</th><th scope="col">备注</th>'.$strCrlf;
echo '		</tr>'.$strCrlf;


$sql = 'select id, strTitle, strDate, nTypeID, strTypeName, nCount, strMemo from table_article';
$ret = $db->query($sql);
while($row = $ret->fetchArray(SQLITE3_ASSOC)){
	//echo 'id = '.$row['id'].$strCrlf;
	//echo 'title = '.$row['strTitle'].$strCrlf;
	echo $strCrlf;
	echo "\t\t".'<tr>'.$strCrlf;
	echo "\t\t\t".'<td>'.$row['id'].'</td><td>'.$row['strTitle'].'</td><td>'.$row['strDate'].'</td><td align="center">'.$row['nTypeID'].'</td><td>'.$row['strTypeName'].'</td><td align="center">'.$row['nCount'].'</td><td>'.$row['strMemo'].'</td>'.$strCrlf;
	echo "\t\t".'</tr>'.$strCrlf;
	echo $strCrlf;

}

echo $strCrlf;
echo '	</table>'.$strCrlf;
echo '</div>'.$strCrlf;
echo $strCrlf;
echo '	Exists 14'.$strCrlf;
echo $strCrlf;
echo '	<p><font color="red"><em style="font-size:16px;">总结 sqlite3 写入的时候不管什么情况下都必须 2016-01-01 00:00:00 的格式写，否则会出现非标准数据。至于显示规则，有些情况下系统会缩略输出，例如 2016-1-1 0:00:00 月、日、时 三部分显示可能会省去前缀0</em></font></p>'.$strCrlf;
echo ''.$strCrlf;

echo '</body>'.$strCrlf;
echo '</html>'.$strCrlf;


$db->close();
?>
