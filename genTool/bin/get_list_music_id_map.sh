#! /bin/bash -e

######################################################################
# Initialize the parameters
######################################################################
mysql_host="localhost"
mysql_user="imsixthr_myweb"
mysql_pass="imsixthr_myweb"
mysql_db="imsixthr_myweb02"
gen_home_dir="/home/lusaisai/wwwLearning/myWeb0.2/genTool"
tmp_dir="$gen_home_dir/tmp"
cfg_dir=$gen_home_dir/cfg
last_extract_file=$cfg_dir/list_music_map.last_extract_value.dat
last_extract_value=$( < $last_extract_file )
original_file="$tmp_dir/list_embed_map.txt"
output_file="$tmp_dir/list_music_id_map.txt"
mysql_connect_str="mysql --host=$mysql_host --user=$mysql_user --password=$mysql_pass --skip-column-names $mysql_db"
query="select
concat_ws( 0x07, l.list_id, l.list_outer_link)
from f_topic t
join (
select
t.topic_id
from f_topic t
join ( select topic_id, max(modified_ts) as modified_ts from f_topic_list group by 1 ) l
on    t.topic_id = l.topic_id
where greatest(t.modified_ts, l.modified_ts) >= '$last_extract_value'
) n
on   t.topic_id = n.topic_id
join d_topic_type d
on   t.topic_type_id = d.topic_type_id
join f_topic_list l
on   t.topic_id = l.topic_id
where d.topic_type_desc = '音乐'
;
"


######################################################################
# Process the data
######################################################################
echo "Parsing ..."
$mysql_connect_str --execute="$query" > $original_file
> $output_file

while read _line
do
   list_id=$(echo $_line | awk -F"\007" '{print $1}')
   list_outer_link=$(echo $_line | awk -F"\007" '{print $2}')
   music_ids=$(echo $list_outer_link|sed -e 's:^.*4097932_::' -e 's:,_235_346_000000_494949_0.*$::')
   echo $music_ids | awk -F"," '{ for(i=1;i<=NF;i++) print '$list_id', $i }' >> $output_file
done < $original_file


######################################################################
# Load into Database
######################################################################
echo "Loading ..."
query="delete from stg_d_id_map_w;
LOAD DATA LOCAL INFILE '$output_file' INTO TABLE stg_d_id_map_w FIELDS TERMINATED BY ' ';
delete t from d_id_map t join stg_d_id_map_w w where w.music_id = t.music_id; 
insert into d_id_map(list_id, music_id) select list_id, music_id from stg_d_id_map_w;"
$mysql_connect_str  --local-infile=1 --execute="$query"

######################################################################
# Send to Remote
######################################################################
echo "Sending to remote ..."
query="delete from stg_d_id_map_w; 
LOAD DATA LOCAL INFILE '/home7/imsixthr/public_html/${output_file##*/}' INTO TABLE stg_d_id_map_w FIELDS TERMINATED BY ' ';
delete t from d_id_map t join stg_d_id_map_w w where w.music_id = t.music_id; 
insert into d_id_map(list_id, music_id) select list_id, music_id from stg_d_id_map_w;
"
gzip -f $output_file
scp $output_file.gz imsixthr@im633.com:/home7/imsixthr/public_html
ssh imsixthr@im633.com "cd /home7/imsixthr/public_html;gunzip -f ${output_file##*/}.gz; echo \"$query\" | $mysql_connect_str"

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

