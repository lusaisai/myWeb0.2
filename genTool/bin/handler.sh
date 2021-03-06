#! /bin/bash -eu

######################################################################
# Parameters and initializing
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
mkdir -p $output_dir
cd $output_dir
mkdir -p blog css feed fun images js music mv others php soccer software topics

######################################################################
# Call mysql to export latest data and all the topic list
######################################################################
echo "Call MYSQL exporting ..."
$bin_dir/data_export.sh

######################################################################
# Call C core to generate the html files
######################################################################
echo "Call C Process ..."
if [ -s $new_data_file ]; then
    $bin_dir/genhtml $new_data_file $all_topic_file $output_dir $tmp_dir
fi


######################################################################
# File deploying
######################################################################
echo "File deploying"
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
cp $tmp_dir/*js $output_js

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

