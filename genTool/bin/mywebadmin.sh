#! /bin/bash -e

######################################################################
# Initialize the parameters
######################################################################
user="imsixthr_myweb"
passwd="imsixthr_myweb"
db="imsixthr_myweb02"
topic_table="f_topic"
list_table="f_topic_list"
myweb_admin_dir="/home/lusaisai/wwwLearning/myWeb0.2/genTool/bin/mywebadmin/Release"


######################################################################
# Ask user for input
######################################################################
$myweb_admin_dir/mywebadmin $db $topic_table $list_table $user $passwd

