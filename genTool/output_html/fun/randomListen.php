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
	$title_query = " case when locate('$keyword_list[0]', title) > 0 then 1";
	$artist_query = " case when locate('$keyword_list[0]', artist)  > 0  then 1";
	$album_query = " case when locate('$keyword_list[0]', album) > 0 then 1";
	$lyric_query = " case when locate('$keyword_list[0]', lyric) > 0 then 1";
	$from_query = " from f_song_info";

	$where_query = " where locate('$keyword_list[0]', concat(title,artist,album,lyric)) > 0";


	for ( $i=1; $i < count($keyword_list); $i++ ) {
	$where_query .= " and locate( '$keyword_list[$i]', concat(title,artist,album,lyric) ) > 0 ";
	$title_query .= " when locate('$keyword_list[$i]', title) > 0 then 1";
	$artist_query .= " when locate('$keyword_list[$i]',  artist)  > 0  then 1";
	$album_query .= " when locate('$keyword_list[$i]', album) > 0 then 1";
	$lyric_query .= " when locate('$keyword_list[$i]', lyric) > 0 then 1";
}
	$title_query .= " else 0 end as title_rank, ";
	$artist_query .= " else 0 end as artist_rank, ";
	$album_query .= " else 0 end as album_rank, ";
	$lyric_query .= " else 0 end as lyric_rank";

	$query = "select song_id from (select song_id, " . $title_query . $artist_query . $album_query . $lyric_query . $from_query . $where_query. ") c group by 1 order by sum(title_rank) desc, sum(artist_rank) desc, sum(album_rank) desc, sum(lyric_rank) desc limit 15";
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
