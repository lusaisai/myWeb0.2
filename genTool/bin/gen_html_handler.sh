#! /bin/bash -eu

######################################################################
# Parameters
######################################################################
export gen_home_dir=/home/lusaisai/wwwLearning/myWeb0.2/genTool
export bin_dir=$gen_home_dir/bin
export output_dir=$gen_home_dir/output_html
export output_css=$output_dir/css
export output_img=$output_dir/images
export output_js=$output_dir/js
export output_php=$output_dir/php
export cfg_dir=$gen_home_dir/cfg
export tmp_dir=$gen_home_dir/tmp
export last_extract_file=$cfg_dir/gen_html.last_extract_value.dat
export last_extract_value=$( < $cfg_dir/gen_html.last_extract_value.dat )
export new_data_file=$tmp_dir/new_data.txt
export all_topic_file=$tmp_dir/all_topic.txt


######################################################################
# Call mysql to export latest data and all the topic list
######################################################################
$bin_dir/data_export.sh

######################################################################
# Call C core to generate the html files
######################################################################
#$bin_dir/genhtml $new_data_file $all_topic_file $output_dir $tmp_dir

