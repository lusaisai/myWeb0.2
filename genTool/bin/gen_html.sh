#! /bin/bash -e

######################################################################
# Initialize the parameters
######################################################################
mysql_host="localhost"
mysql_user="myweb"
mysql_pass="myweb"
mysql_db="myweb01"
gen_home_dir="/home/lusaisai/wwwLearning/myweb0.1/genTool"
output_dir="$gen_home_dir/output_html"
output_css="$output_dir/css"
output_img="$output_dir/images"
output_js="$output_dir/js"
output_php="$output_dir/php"
cfg_dir="$gen_home_dir/cfg"
sql_dir="$gen_home_dir/sql"
tmp_dir="$gen_home_dir/tmp"
last_extract_file=$cfg_dir/gen_html.last_extract_value.dat
last_extract_value=$(cat $cfg_dir/gen_html.last_extract_value.dat)
mysql_connect_str="mysql --host=$mysql_host --user=$mysql_user --password=$mysql_pass --skip-column-names $mysql_db"
count_in_onepage=5
default_page_title="陆赛赛的网络小屋"
if [[ "$1" == "prod" ]]; then
	domain="http://im633.com"
elif [[ "$1" == "qa" ]]; then
	domain="http://localhost/output_html"
else
	domain=$output_dir
fi

######################################################################
# Functions
######################################################################
# Generate the html head
function gen_html_head {
cat << EOF
<!DOCTYPE html>
<html>
<head>
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Expires" CONTENT="-1">
<meta charset="utf-8" />
<title>$html_title</title>
<link rel="shortcut icon" href="$domain/favicon.ico">
<script type="text/javascript" src="$domain/js/jquery-1.8.0.min.js"></script>
<script type="text/javascript" src="$domain/js/navigation.js"></script>
<script type="text/javascript" src="$domain/js/logo.js"></script>
<script type="text/javascript" src="$domain/js/search_keyword.js"></script>
<link href="$domain/css/main.css" type="text/css" rel="stylesheet" />
$special_css
$player_js
</head>

<body>
<ul id="nav">
<li><a href="$domain" >首页</a></li>
<li><a href="$domain/music" >音乐</a></li>
<li><a href="$domain/mv" >影音</a></li>
<li><a href="$domain/soccer" >足球</a></li>
<li><a href="$domain/fun" >有趣</a></li>
<li><a href="$domain/software" >软件</a></li>
<li><a href="$domain/blog" >博客</a></li>
<li><a href="$domain/others" >其他</a></li>
</ul>

<div id="main">

<div id="header">
<canvas id="logo" width="380" height="100"><img src="$domain/images/logo.png" alt="im633" ></canvas>
<div id="bwBox">
<h3 id="bw"><?php include("$domain/php/getPoem.php"); ?></h3>
</div>
</div>

<div id="bdy">
<div id="left_panel">
<div id="musicPlayer">
<h3>推荐我喜欢的音乐...</h3>
$default_music_loc
</div>
<ul id="randomListen"><li>随便听听</li></ul>
<div id="searchBox">
<form id="searchForm">
<input type="search" name="search_word" maxlength="2048" size="28"/>
<select name="search_type">
<option>全部</option>
<option>音乐</option>
<option>影音</option>
<option>足球</option>
<option>有趣</option>
<option>软件</option>
<option>博客</option>
<option>其他</option>
</select>
<input type="submit" name="submit_search" value="搜索" />
</form>
</div>
<div id="searchResult">
</div>
</div>
<div id="topicBox">
EOF
}

# Generate the html head
function gen_html_tail {
cat << EOF
</div>
</div>
<div id="contact">
<span>订阅网站的RSS:</span>
<a target="_blank" href="$domain/feed/rss.xml" ><img src="$domain/images/rss.png" alt="RSS" ></a>
<br />
<span>我的Email和QQ:</span>
<a href="mailto:lusaisai@im633.com" ><img src="$domain/images/email.png" alt="mail" ></a>
<a target="_blank" href="http://sighttp.qq.com/authd?IDKEY=e0c250b3b6e8a43afa5e1813f64a68d8d90f2e532bef8936"><img border="0"  src="http://wpa.qq.com/imgd?IDKEY=e0c250b3b6e8a43afa5e1813f64a68d8d90f2e532bef8936&pic=41" alt="与我交流" title="与我交流"></a>
</div>
</div>
</body>
</html>
EOF
}

#Generate the page links
function gen_page_links {
i=1
middle_start_point=$((current_page - 5))
middle_end_point=$((current_page + 5))
while [ $i -le $page_count ]
do
if [[ $i == 1 && $current_page == 1 ]]; then
cat << EOF
<div>
<a id="currentpagelinks" class="pagelinks" href="$domain/${page_dir}index.html" >$i</a>
EOF

elif [[ $i == 1 && $current_page != 1 ]]; then
cat << EOF
<div>
<a class="pagelinks" href="$domain/${page_dir}index.html" >$i</a>
EOF

else

	if [[ $middle_start_point -gt 2 && $i -lt $middle_start_point ]]; then
cat << EOF
<span class="pagelinks">...</span>
EOF
   i=$middle_start_point
	fi

	if [ $((middle_end_point + 1)) -lt $page_count ];then
		 if [ $i -eq $((middle_end_point + 1)) ];then
cat << EOF
<span class="pagelinks">...</span>
EOF
		 i=$page_count
		 fi
	fi

	if [[ $i == $current_page ]]; then
cat << EOF
<a id="currentpagelinks" class="pagelinks" href="$domain/${page_dir}${page_dir%%/}_$i.html" >$i</a>
EOF
	else
cat << EOF
<a class="pagelinks" href="$domain/${page_dir}${page_dir%%/}_$i.html" >$i</a>
EOF
	fi

fi

((i+=1))
done
echo "</div>"
}


# Generate the topic division
function gen_topic_div {
cat <<EOF
<div id="topic$topic_id" class="topic">
<span class="time">$modified_date</span>
<a href="$domain/topics/topic_$topic_id.html" class="topicTitle" target="_blank"><h3>$topic_name</h3></a>
EOF
}

# Generate the list division and enclose the topic division
function gen_list_div_head {
	case $topic_type_desc in
	'音乐')
cat << EOF
<div class="albumImageWrapper">
<img src="$list_image_loc" class="albumImage">
</div>
<span class="music listtxt">$list_desc</span>
<ul class="list">
<li id="list$list_id">$list_name</li>
EOF
	;;

	'博客')
cat << EOF
<span class="listtxt">$list_desc</span>
EOF
	;;

	*)
	if [[ $_list_count -gt 1 ]]; then
cat << EOF
<span class="listtxt">$list_desc</span>
$list_outer_link
<ul class="list">
<li id="list$list_id">$list_name</li>
EOF
	else
cat << EOF
<span class="listtxt">$list_desc</span>
$list_outer_link
EOF
	fi
	;;
	esac
}

function gen_list_div_middle {
cat << EOF
<li id="list$list_id">$list_name</li>
EOF
}


function gen_list_div_tail {
case $topic_type_desc in
	'音乐')
cat << EOF
</ul>
</div>
EOF
	;;

	*)
if [[ $_list_count -gt 1 ]]; then
	echo '</ul>'
fi
cat << EOF
</div>
EOF
	;;
	esac
}


# Generate the javascript to changing the player
function gen_js_head {
	list_name=$(echo $list_name | sed s/\'/\\\\\'/g)
	list_desc=$(echo $list_desc | sed s/\'/\\\\\'/g)
	case $topic_type_desc in
	'音乐')
	list_outer_link=$(echo $list_outer_link | sed 's:_0/:_1/:')
cat << EOF
\$( function() {

\$('#list$list_id').mouseover(function() {
	\$('#topic$topic_id img').attr('src', '$list_image_loc');
	\$('#topic$topic_id span.listtxt').html('$list_desc');
	});
\$('#list$list_id').click(function() {
	\$('#musicPlayer h3').html('$list_name');
	\$('#musicPlayer embed').replaceWith('$list_outer_link');
	\$('#topic$topic_id li').css('color', '#000000');
	\$('#list$list_id').css('color', '#CC0052');
	});

EOF
	;;

	'影音'|'足球'|'有趣')
	if [[ $_list_count -gt 1 ]]; then
cat << EOF
\$( function() {

\$('#list$list_id').click(function() {
	\$('#topic$topic_id span.listtxt').html('$list_desc');
	\$('#topic$topic_id embed').wrap('<div class="videoWrapper" />');
	\$('#topic$topic_id embed').replaceWith('$list_outer_link');
	\$('#topic$topic_id li').css('color', '#000000');
	\$('#list$list_id').css('color', '#CC0052');
	});
EOF
	fi
	;;

	'其他'|'软件')
	if [[ $_list_count -gt 1 ]]; then
cat << EOF
\$( function() {

\$('#list$list_id').click(function() {
	\$('#topic$topic_id li').css('color', '#000000');
	\$('#list$list_id').css('color', '#CC0052');
	\$('#topic$topic_id span.listtxt').load("getListDesc.php", "list_id=$list_id");
	\$('#topic$topic_id').animate({scrollTop:0}, 'slow');
	});
EOF
	fi
	;;

	*)
	;;
	esac
}

function gen_js_middle {
	list_name=$(echo $list_name | sed s/\'/\\\\\'/g)
	list_desc=$(echo $list_desc | sed s/\'/\\\\\'/g)
if [[ $topic_type_desc == '音乐' ]]; then
list_outer_link=$(echo $list_outer_link | sed 's:_0/:_1/:')
cat << EOF
\$('#list$list_id').mouseover(function() {
	\$('#topic$topic_id img').attr('src', '$list_image_loc');
	\$('#topic$topic_id span.listtxt').html('$list_desc');
	});
\$('#list$list_id').click(function() {
	\$('#musicPlayer h3').html('$list_name');
	\$('#musicPlayer embed').replaceWith('$list_outer_link');
	\$('#topic$topic_id li').css('color', '#000000');
	\$('#list$list_id').css('color', '#CC0052');
	});
EOF
elif [[ $topic_type_desc == '其他' ]]; then
cat << EOF
\$('#list$list_id').click(function() {
	\$('#topic$topic_id li').css('color', '#000000');
	\$('#list$list_id').css('color', '#CC0052');
	\$('#topic$topic_id span.listtxt').load("getListDesc.php", "list_id=$list_id");
	\$('#topic$topic_id').animate({scrollTop:0}, 'slow');
	});
EOF
else
cat << EOF
\$('#list$list_id').click(function() {
	\$('#topic$topic_id span.listtxt').html('$list_desc');
	\$('#topic$topic_id embed').wrap('<div class="videoWrapper" />');
	\$('#topic$topic_id embed').replaceWith('$list_outer_link');
	\$('#topic$topic_id li').css('color', '#000000');
	\$('#list$list_id').css('color', '#CC0052');
	});
EOF
fi
}


function gen_js_tail {
case $topic_type_desc in
	'音乐')
cat << EOF
}
)
;
EOF
	;;

	'影音'|'足球'|'有趣'|'其他'|'软件')
if [[ $_list_count -gt 1 ]]; then
cat << EOF
}
)
;
EOF
fi
	;;

	*)
	;;
	esac
}

# Generate topic division based on topic_id
function gen_topic_div_box {
   _topic_id=$1
   modified_date=$2
   get_data_query="select
   concat_ws( 0x07, l.list_id, l.topic_id, l.list_name, l.list_desc, l.list_image_loc, l.list_outer_link, l.list_other_link,
   t.topic_type_id, t.topic_name, d.topic_type_desc)
   from f_topic t
   join d_topic_type d
   on   t.topic_type_id = d.topic_type_id
   join f_topic_list l
   on   t.topic_id = l.topic_id
   where t.topic_id = $_topic_id
   ;"

   $mysql_connect_str --execute="$get_data_query" > $tmp_dir/topic_$_topic_id.info.txt

	#Generate special css
   get_max_list_name_byte_length="select max(length(list_name)) from f_topic_list where topic_id = $_topic_id;"
   get_max_list_name_char_length="select max(char_length(list_name)) from f_topic_list where topic_id = $_topic_id;"
   get_max_list_desc_length="select max(char_length(list_desc)) from f_topic_list where topic_id = $_topic_id;"
   list_name_byte_length=$($mysql_connect_str --execute="$get_max_list_name_byte_length")
   list_name_char_length=$($mysql_connect_str --execute="$get_max_list_name_char_length")
   list_name_length=$( echo "($list_name_byte_length - $list_name_char_length) / 2 + (3 * $list_name_char_length - $list_name_byte_length) / 2 * 0.5 + 1" | bc )
   list_desc_length=$($mysql_connect_str --execute="$get_max_list_desc_length")
   echo "#topic$_topic_id li {width: ${list_name_length}em}" > $output_css/topic_$_topic_id.css
   if [ $list_desc_length -gt 1000 ]; then
		echo "#topic$_topic_id {max-height:700px;overflow:scroll;}" >> $output_css/topic_$_topic_id.css
	fi

   topic_content_file=$tmp_dir/topic_$_topic_id.html
   > $topic_content_file
   topic_js_file=$tmp_dir/topic_$_topic_id.js
   > $topic_js_file
   _list_count=$(wc -l $tmp_dir/topic_$_topic_id.info.txt|awk '{print $1}')
   i=1
   while read _line
   do
      list_id=$(echo $_line | awk -F"\007" '{print $1}')
      topic_id=$(echo $_line | awk -F"\007" '{print $2}')
      list_name="$(echo $_line | awk -F"\007" '{print $3}')"
      list_desc="$(echo $_line | awk -F"\007" '{print $4}')"
      list_image_loc="$(echo $_line | awk -F"\007" '{print $5}')"
      list_other_link="$(echo $_line | awk -F"\007" '{print $7}')"
      topic_type_id=$(echo $_line | awk -F"\007" '{print $8}')
      topic_name="$(echo $_line | awk -F"\007" '{print $9}')"
      topic_type_desc="$(echo $_line | awk -F"\007" '{print $10}')"
		if [[ $topic_type_desc == "音乐" || $topic_type_desc == "其他" ]]; then
      	list_outer_link="$(echo $_line | awk -F"\007" '{print $6}')"
      else
      	list_outer_link="$(echo $_line | awk -F"\007" '{print $6}' | sed 's/width="[0-9]*"/width="680"/;s/height="[0-9]*"/height="480"/')"
      	set +e
      	echo $list_outer_link | grep allowFullscreen > /dev/null
      	rcode=$?
      	set -e
      	if [[ $rcode == 0 ]]; then
      		list_outer_link=$(echo $list_outer_link|sed 's/allowFullscreen=[^ 	]*//')
      	fi
      	list_outer_link=$(echo $list_outer_link | sed 's/embed/embed allowFullscreen="true"/1')
      fi

      if [[ $i == 1  ]]; then #gen the topic data only once
			gen_topic_div >> $topic_content_file
			gen_list_div_head >> $topic_content_file
			gen_js_head >> $topic_js_file
			if [[ $_list_count == 1 ]]; then
				gen_list_div_tail >> $topic_content_file
				gen_js_tail >> $topic_js_file
			fi
		elif [[ $i == $_list_count ]]; then
		   gen_list_div_middle >> $topic_content_file
			gen_list_div_tail >> $topic_content_file
			gen_js_middle >> $topic_js_file
			gen_js_tail >> $topic_js_file
		else
			gen_list_div_middle >> $topic_content_file
			gen_js_middle >> $topic_js_file
      fi
      ((i+=1))
   done < $tmp_dir/topic_$_topic_id.info.txt
}


# Generate default music player division
function gen_default_music_palyer {
	_topic_id_list=$1
	get_latest_list_query="select
l.list_outer_link
from f_topic t
join d_topic_type d
on   t.topic_type_id = d.topic_type_id
join f_topic_list l
on   t.topic_id = l.topic_id
where d.topic_type_desc = '音乐'
order by rand()
limit 1
;
"
	get_latest_list_query_using_topic_id="select
l.list_outer_link
from f_topic_list l
join 
(
select
t.topic_id
from f_topic t
join d_topic_type d
on   t.topic_type_id = d.topic_type_id
join f_topic_list l
on   t.topic_id = l.topic_id
where d.topic_type_desc in ( '音乐', '博客')
and t.topic_id in ( $_topic_id_list )
order by l.modified_ts desc
limit 1
) as tmp
on l.topic_id = tmp.topic_id
order by l.list_id
limit 1
;
"


	default_music_loc="$($mysql_connect_str --execute="$get_latest_list_query_using_topic_id")"
	if [[ "$default_music_loc" == "" ]]; then
		default_music_loc="$($mysql_connect_str --execute="$get_latest_list_query")"
	fi
}
######################################################################
# Generate RSS Feed
######################################################################
function gen_rss_head {
cat << EOF
<?xml version="1.0" encoding="utf8" ?>
<rss version="2.0">
<channel>
  <title>陆赛赛的网络小屋</title>
  <link>http://www.im633.com</link>
  <description>音乐，影音，足球，软件...一切值得珍藏的</description>
EOF
}


function gen_rss_middle {
cat << EOF
  <item>
    <title>$topic_name</title>
    <link>$domain/topics/topic_$topic_id.html</link>
    <description>$topic_name</description>
    <guid>$domain/topics/topic_$topic_id.html</guid>
  </item>
EOF
}

function gen_rss_tail {
cat << EOF
</channel>
</rss>
EOF
}



######################################################################
# Main Generating Processes
######################################################################
echo "Copying common use files"
mkdir -p $output_dir
cd $output_dir
mkdir -p blog css feed fun images js music mv others php soccer software topics
cp $cfg_dir/*png $output_img
cp $cfg_dir/*ico $output_dir
cp $cfg_dir/*php $output_php
cp $cfg_dir/*.php $output_dir
cp $cfg_dir/*.php $output_dir/blog
cp $cfg_dir/*.php $output_dir/fun
cp $cfg_dir/*.php $output_dir/music
cp $cfg_dir/*.php $output_dir/mv
cp $cfg_dir/*.php $output_dir/others
cp $cfg_dir/*.php $output_dir/soccer
cp $cfg_dir/*.php $output_dir/software
cp $cfg_dir/*.php $output_dir/topics
cp $cfg_dir/*js $output_js
cp $cfg_dir/*css $output_css

######################################################################
# Generate the html block files to be used later and the RSS Feed
# Only generate newly updated topics/lists
######################################################################
echo "Generating html blocks"
get_topic_seq_query="select
t.topic_id, greatest(t.modified_ts, l.modified_ts)
from f_topic t
join ( select topic_id, max(modified_ts) as modified_ts from f_topic_list group by 1 ) l
on t.topic_id = l.topic_id
where greatest(t.modified_ts, l.modified_ts) >= '$last_extract_value'
order by 2 desc, 1 desc
;
"

$mysql_connect_str --execute="$get_topic_seq_query" > $tmp_dir/all_topic_id.txt
all_count=$(wc -l $tmp_dir/all_topic_id.txt | awk '{print $1}')
count_index=1


while [ $count_index -le $all_count ]
do
	gen_topic_div_box $(sed ''$count_index' !d' $tmp_dir/all_topic_id.txt)
	((count_index+=1))
done


# The RSS Feed
get_rss_query="select
t.topic_id,
t.topic_name
from f_topic t
join ( select topic_id, max(modified_ts) as modified_ts from f_topic_list group by 1 ) l
on t.topic_id = l.topic_id
order by greatest(t.modified_ts, l.modified_ts) desc, t.topic_id desc
limit 10
;"
$mysql_connect_str --execute="$get_rss_query" > $tmp_dir/rss_data.txt

rss_count=1
gen_rss_head > $output_dir/feed/rss.xml
while [ $rss_count -le 10 ]
do
	topic_id=$(sed ''$rss_count' !d' $tmp_dir/rss_data.txt | awk -F"	" '{print $1}')
	topic_name=$(sed ''$rss_count' !d' $tmp_dir/rss_data.txt | awk -F"	" '{print $2}')
	gen_rss_middle >> $output_dir/feed/rss.xml
	((rss_count+=1))
done
gen_rss_tail >> $output_dir/feed/rss.xml

######################################################################
# Generate individual pages
######################################################################
page_index=1
while [ $page_index -le $all_count ]
do
	page_dir="topics/"
	topic_id=$(sed ''$page_index' !d' $tmp_dir/all_topic_id.txt | awk '{print $1}')
	gen_default_music_palyer $topic_id
	html_title=$(sed '1 !d' $tmp_dir/topic_$topic_id.info.txt | awk -F"\007" '{print $9}' )
	if [ -n $tmp_dir/topic_$topic_id.js ];then
		player_js='<script type="text/javascript" src="'$domain'/js/topic_'$topic_id'.js"></script>'
		cp $tmp_dir/topic_$topic_id.js $output_js
	else
		player_js=""
	fi
	special_css='<link href="'$domain'/css/topic_'$topic_id'.css" type="text/css" rel="stylesheet" />'
	gen_html_head > $output_dir/${page_dir}topic_$topic_id.html
	cat $tmp_dir/topic_$topic_id.html >> $output_dir/${page_dir}topic_$topic_id.html
	gen_html_tail >> $output_dir/${page_dir}topic_$topic_id.html
	((page_index+=1))
done


######################################################################
# Generate Main pages
######################################################################
function gen_main_page {
	page_type=$1
	page_dir=$2
	get_topics_query="select
t.topic_id, greatest(t.modified_ts, l.modified_ts)
from f_topic t
join d_topic_type d
on   t.topic_type_id = d.topic_type_id
and  d.topic_type_desc like '%$page_type%'
join ( select topic_id, max(modified_ts) as modified_ts from f_topic_list group by 1 ) l
on t.topic_id = l.topic_id
order by 2 desc, 1 desc
;"

	mkdir -p $tmp_dir/${page_dir}
	$mysql_connect_str --execute="$get_topics_query" > $tmp_dir/${page_dir}_topic_id.txt
	topic_count=$(wc -l $tmp_dir/${page_dir}_topic_id.txt | awk '{print $1}')
	page_count=$(((topic_count-1)/count_in_onepage + 1))
	count_id=1
	page_index=1
	player_js=""
	current_div_all=""
	special_css=""
	topic_id_list="-1" #dummy data


	while [ $count_id -le $topic_count ]
	do
		topic_id=$(sed ''$count_id' !d' $tmp_dir/${page_dir}_topic_id.txt | awk '{print $1}')
		topic_id_list="$topic_id_list"",$topic_id"


		if [ -s $tmp_dir/topic_$topic_id.js ];then
			player_js="$player_js"'<script type="text/javascript" src="'$domain'/js/topic_'$topic_id'.js"></script>'
			cp $tmp_dir/topic_$topic_id.js $output_js
		fi

		special_css="$special_css"'<link href="'$domain'/css/topic_'$topic_id'.css" type="text/css" rel="stylesheet" />'

		current_div_all="$current_div_all"$(cat $tmp_dir/topic_$topic_id.html)


		if [ $((count_id % 5)) -eq 0 -o $count_id -eq $topic_count ];then
			current_page=$page_index
			gen_default_music_palyer $topic_id_list
			html_title=$default_page_title
			if [[ $page_index == 1 ]]; then
				gen_html_head > $output_dir/${page_dir}index.html
				echo $current_div_all >> $output_dir/${page_dir}index.html
				gen_page_links >> $output_dir/${page_dir}index.html
				gen_html_tail >> $output_dir/${page_dir}index.html
			else
				gen_html_head > $output_dir/${page_dir}${page_dir%%/}_$page_index.html
				echo $current_div_all >> $output_dir/${page_dir}${page_dir%%/}_$page_index.html
				gen_page_links >> $output_dir/${page_dir}${page_dir%%/}_$page_index.html
				gen_html_tail >> $output_dir/${page_dir}${page_dir%%/}_$page_index.html
			fi
			player_js=""
			special_css=""
			current_div_all=""
			topic_id_list="-1"
			((page_index+=1))
		fi
		((count_id+=1))
	done
}

echo "Generating main pages..."
gen_main_page "" ""

echo "Generating music pages..."
gen_main_page "音乐" "music/"

echo "Generating soccer pages..."
gen_main_page "足球" "soccer/"

echo "Generating mv pages..."
gen_main_page "影音" "mv/"

echo "Generating others pages..."
gen_main_page "其他" "others/"

echo "Generating fun pages..."
gen_main_page "有趣" "fun/"

echo "Generating software pages..."
gen_main_page "软件" "software/"

echo "Generating blog pages..."
gen_main_page "博客" "blog/"

######################################################################
# Post Jobs
######################################################################
# Update last extract value
echo "Complete!
Update the last extract value?(Y/y)"
read x
if [ "$x" = "y" -o "$x" = "Y" ]; then
	date +'%F %R:%S' > $last_extract_file
	echo "Updated!"
fi


exit 0
