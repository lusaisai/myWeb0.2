#! /bin/bash -eu

mysql_host="localhost"
mysql_user="imsixthr_myweb"
mysql_pass="imsixthr_myweb"
mysql_db="imsixthr_myweb02"
mysql_connect_str="mysql --host=$mysql_host --user=$mysql_user --password=$mysql_pass --skip-column-names $mysql_db"
new_data_query="
select
concat_ws( 0x07, l.list_id, l.topic_id, l.list_name, l.list_desc, l.list_image_loc, l.list_outer_link, l.list_other_link, t.topic_type_id, t.topic_name, d.topic_type_desc)
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
order by l.topic_id, l.list_id
;
"

all_topic_query="
select
concat_ws( 0x07, t.topic_id, d.topic_type_id, greatest(t.modified_ts, l.modified_ts), t.topic_name, l.char_length, l.byte_length )
from f_topic t
join d_topic_type d
on   t.topic_type_id = d.topic_type_id
join ( select topic_id, max(modified_ts) as modified_ts, max(char_length(list_name)) as char_length, max(length(list_name)) as byte_length from f_topic_list group by 1 ) l
on t.topic_id = l.topic_id
order by greatest(t.modified_ts, l.modified_ts) desc, t.topic_id desc
"

$mysql_connect_str --execute="$new_data_query" > $new_data_file
$mysql_connect_str --execute="$all_topic_query" > $all_topic_file

