<?php
header("Last-Modified: " . gmdate("D, d M Y H:i:s") . " GMT");
header("Cache-Control: no-store, no-cache, must-revalidate");
header("Cache-Control: post-check=0, pre-check=0", false);
header("Pragma: no-cache");
$embed_pre='<embed src="http://www.xiami.com/widget/4097932_';

if(!isset($_GET["autoplay"])) {
	$autoplay = '0';
} else {
	$autoplay = $_GET["autoplay"];
}

if(!isset($_GET["search_word"])) {
	$query = "select song_id from f_song_info order by rand() limit 15;";
} else {
	$search_word = $_GET["search_word"];
	if (trim($search_word) == "") {$query = "select song_id from f_song_info order by rand() limit 15;";} else {
		
	// Search the info
	$search_word = addslashes($search_word);
	$keyword_list = split(' ', $search_word, 20);
	$from_query = " from f_song_info";
	$where_query = " where locate('$keyword_list[0]', concat(title,artist,album,lyric)) > 0";


	for ( $i=1; $i < count($keyword_list); $i++ ) {
	$where_query .= " or locate( '$keyword_list[$i]', concat(title,artist,album,lyric) ) > 0 ";
}

	$query = "select song_id  " . $from_query . $where_query. " group by 1 order by rand() limit 15";
}
}
$embed_suf='_235_346_000000_494949_' . $autoplay . '/multiPlayer.swf" type="application/x-shockwave-flash" width="235" height="346" wmode="opaque"></embed>';

$mysqli = new mysqli('localhost','imsixthr_myweb','imsixthr_myweb','imsixthr_myweb02');
$mysqli->set_charset("utf8");
$result = $mysqli->query($query);
$song_ids = '';

while( $row = $result->fetch_object()) {
	$song_ids = $song_ids . "," . $row->song_id;
}

echo '<h3>推荐我喜欢的音乐 ...</h3>' . $embed_pre . $song_ids . $embed_suf;
$mysqli->close();
?>
