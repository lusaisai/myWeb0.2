#! /bin/bash -e

######################################################################
# Initialize the parameters
######################################################################
mysql_host="localhost"
mysql_user="myweb"
mysql_pass="myweb"
mysql_db="myweb01"
gen_home_dir="/home/lusaisai/wwwLearning/myWeb0.2/genTool"
bin_dir=$gen_home_dir/bin/HTMLParsing/bin
tmp_dir=$gen_home_dir/tmp
cfg_dir=$gen_home_dir/cfg
last_extract_file=$cfg_dir/song_info.last_extract_value.dat
last_extract_value=$( < $last_extract_file )
input_file=$tmp_dir/song_id.txt
output_file=$tmp_dir/song_info.txt
mysql_connect_str="mysql --host=$mysql_host --user=$mysql_user --password=$mysql_pass --skip-column-names $mysql_db"
query="select
music_id
from d_id_map
where insert_ts >= '$last_extract_value'
;
"


######################################################################
# Export new song ids
######################################################################
echo "Get latest song ids ..."
$mysql_connect_str --execute="$query" > $input_file


######################################################################
# Get info from xiami.com
######################################################################
cd $bin_dir
java -cp "/home/lusaisai/jars/jsoup-1.7.1.jar:." com.im633.FetchSongInfo $input_file $output_file

######################################################################
# load into database
######################################################################
echo "Loading ..."
query="delete from stg_f_song_info_w;
LOAD DATA LOCAL INFILE '$output_file' INTO TABLE stg_f_song_info_w character set UTF8 FIELDS TERMINATED BY 0x07;
delete t from f_song_info t join stg_f_song_info_w w where w.song_id = t.song_id; 
insert into f_song_info(song_id, title, artist, album, lyric) select song_id, title, artist, album, lyric from stg_f_song_info_w;"
$mysql_connect_str  --local-infile=1 --execute="$query"


######################################################################
# Send to Remote
######################################################################
#echo "Sending to remote ..."
#query="delete from imsixthr_myweb01.stg_d_id_map_w; 
#LOAD DATA LOCAL INFILE '/home7/imsixthr/public_html/${output_file##*/}' INTO TABLE imsixthr_myweb01.std_d_id_map_w FIELDS TERMINATED BY ' ';
#delete t from imsixthr_myweb01.d_id_map t join imsixthr_myweb01.stg_d_id_map_w w where w.music_id = t.music_id; 
#insert into imsixthr_myweb01.d_id_map(list_id, music_id) select list_id, music_id from imsixthr_myweb01.stg_d_id_map_w;
#"
#gzip -f $output_file
#scp $output_file.gz imsixthr@im633.com:/home7/imsixthr/public_html
#ssh imsixthr@im633.com "cd /home7/imsixthr/public_html;gunzip -f ${output_file##*/}.gz; echo \"$query\" | mysql --database=imsixthr_myweb01 -u imsixthr_myweb -pimsixthr_myweb"

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

