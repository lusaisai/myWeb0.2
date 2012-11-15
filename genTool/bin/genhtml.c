/*
* File: main.c
* Author: lusaisai
*
* Created on November 1, 2012, 8:38 AM
* This program generates the html files of my website im633.com
* The input is four files:
* 1. The latest data file containing the detailed information of each topic
* 2. The all topic file containing all the topic id in a descending order
* 3. The output directory
* 4. The temporary working directory
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NORMALLEN 1000 //used for normal string, filenames, etc.
#define DESCLEN 100000 //used for list description
#define ARGSCNT 4 //4 arguments are required
#define INVALID_TOPICID -1 //used to determine the start of processing
#define DELIMITER 0x07 //the delimiter in the new data file
#define NEW_DATA_FIELDSNUM 10 //number of fields in the new data file
#define ALL_TOPIC_FIELDSNUM 6 //number of fields in the all topic file
#define NORMAL_COLOR "#000000" //nomal color of a list
#define CURRENT_COLOR "#CC0052" //color of the current playing list
#define DEFAULT_PAGE_TITLE "陆赛赛的网络小屋"
#define TOPIC_KIND_CNT (7+1)    //7 kind of pages + the main page
#define ONEPAGE_TOPIC_CNT 5     //topic count in a single page
#define DOMAIN "http://im633.com" // my website
#define RSS_CNT 10 // The topic count the RSS feed
 
/* The type represents a record of a single list, one line in the new data file */
typedef struct list_info_s {
    int  list_id;
    int  topic_id;
    char list_name[NORMALLEN];
    char list_desc[DESCLEN];
    char list_image_loc[NORMALLEN];
    char list_outer_link[NORMALLEN];
    char list_other_link[NORMALLEN];
    int  topic_type_id;
    char topic_name[NORMALLEN];
    char topic_type_desc[NORMALLEN];
} list_info_t;
 
/* The type represents a record of a single topic, one line in the all topic file */
typedef struct topic_info_s {
    int  topic_id;
    int  topic_type_id;
    char topic_post_time[NORMALLEN];
    char topic_name[NORMALLEN];
    int  max_char_length;
    int  max_byte_length;
} topic_info_t;
 
/* Function prototypes */
void usage(char * filename);
void gen_html_block( FILE * new_data_fp, FILE * all_topic_fp, const char * tmp_dir);
void pop_list_record(char * line, list_info_t * list);
void print_block_head( FILE * block_fp, FILE * all_topic_fp, list_info_t * list );
void print_block_list( FILE * block_fp, list_info_t * list );
void print_block_tail( FILE * block_fp );
void print_js_head( FILE * js_fp, list_info_t * list );
void print_js_list( FILE * js_fp, list_info_t * list );
void print_js_tail( FILE * js_fp );
void replace_quotes(char * target, char * source);
void search_post_time( FILE * all_topic_fp, list_info_t * list, char * time );
void split_line( char * line, int fieldnum, char ** all_field );
void gen_html_page( FILE * all_topic_fp, char * output_dir, char * tmp_dir);
void get_topic_count( FILE * all_topic_fp, int topic_count[], int topic_seq[][NORMALLEN] );
void pop_topic_record(char * line, topic_info_t * topic);
void create_pages( topic_info_t * topic, int * topic_count, int * single_page_index, FILE ** output_file, char ** page_dir, char * output_dir, int topic_seq[][NORMALLEN], char * tmp );
void print_doc_content( FILE * target, int topic_id, char * tmp_dir );
void print_doc_head( FILE ** output_file, int topic_type_id, char * html_title, int * single_page_index, int topic_seq[][NORMALLEN] );
void print_page_links ( FILE * target, int total_cnt, int this_topic, char * dir );
void print_doc_tail( FILE * target );

/*
* The main function
*/
int main(int argc, char** argv) {
    /* Parameter declarations */
    FILE * new_data_fp;
    FILE * all_topic_fp;
    char * new_data_file;
    char * all_topic_file;
    char * output_dir;
    char * tmp_dir;
 
    /* Verify the parameters */
    if ( argc != ARGSCNT + 1 ) {
        usage(argv[0]);
    }
 
    /* Parameters initialization and file opening */
    new_data_file = argv[1];
    all_topic_file = argv[2];
    output_dir = argv[3];
    tmp_dir = argv[4];
    if ( (new_data_fp = fopen(new_data_file, "r")) == NULL ) {
        fprintf(stderr, "Failed to open file %s\n", new_data_file);
        usage(argv[0]);
    }
    if ( (all_topic_fp = fopen(all_topic_file, "r")) == NULL ) {
        fprintf(stderr, "Failed to open file %s\n", all_topic_file);
        usage(argv[0]);
    }
 
    /* Generating single html blocks */
    gen_html_block(new_data_fp, all_topic_fp, tmp_dir);
 
    /* Generating html pages */
    gen_html_page( all_topic_fp, output_dir, tmp_dir);
 
    return (EXIT_SUCCESS);
}
 
/*
* The usage function, showing how to call the program
*/
void usage(char * filename) {
    char * basename;
    if( (basename = strrchr( filename, '/' )) == NULL ) {
        basename = filename;
    } else {
        basename++;
    }
    fprintf(stderr, "Usage: %s <new data file> <all topic file> <output dir> <tmp dir>\n", basename);
    exit(EXIT_FAILURE);
}
 
/*
* The gen_html_block function
* for each topic, this function will create it's own block of html code
* the block data can be used later to pile up the html documents
*/
void gen_html_block( FILE * new_data_fp, FILE * all_topic_fp, const char * tmp_dir){
    char line[DESCLEN * 2];
    list_info_t list;
    int prev_topic_id = INVALID_TOPICID;
    int curr_topic_id;
    /* html block file and its pointer */
    FILE * block_fp;
    char blockfile[NORMALLEN];
    /* javascript file and its pointer */
    FILE * js_fp;
    char jsfile[NORMALLEN];
 
    // Each topic has multiple lines, loop thru to handle it
    while ( fgets(line, DESCLEN * 2, new_data_fp ) != NULL ) {
        pop_list_record(line, &list);
        curr_topic_id = list.topic_id;
        /* For new topic */
        if ( curr_topic_id != prev_topic_id ) {
            /* Close the previous file except the first run */
            if ( prev_topic_id != INVALID_TOPICID ) {
                print_block_tail( block_fp );
                print_js_tail( js_fp );
                fclose(block_fp);
                fclose(js_fp);
            }
 
            /* creating file for this topic */
            sprintf(blockfile, "%s/topic_%d.html", tmp_dir, curr_topic_id);
            sprintf(jsfile, "%s/topic_%d.js", tmp_dir, curr_topic_id);
            if ((block_fp = fopen(blockfile, "w")) == NULL ) {
                fprintf(stderr, "Cannot create file %s", blockfile);
                exit(EXIT_FAILURE);
            }
            if ((js_fp = fopen(jsfile, "w")) == NULL ) {
                fprintf(stderr, "Cannot create file %s", jsfile);
                exit(EXIT_FAILURE);
            }
            /* Print the block html head and javascript file */
            print_block_head( block_fp, all_topic_fp, &list );
            print_js_head( js_fp, &list ); //Blog don't need
 
            /* Update the previous topic id */
            prev_topic_id = curr_topic_id;
        }
 
        /* For the same topic */
        print_block_list( block_fp, &list );
        print_js_list( js_fp, &list );
    }
    /* Close the last file */
    print_block_tail( block_fp);
    print_js_tail( js_fp );
    fclose(block_fp);
    fclose(js_fp);
}
 
/*
* The pop_list_record function
* The function get the data from a line in the new data file
* and populate the structure variable
*/
void pop_list_record(char * line, list_info_t * list){
    char * all_field[NEW_DATA_FIELDSNUM];
    split_line(line, NEW_DATA_FIELDSNUM, all_field);
    char * chp;
 
    list->list_id = atoi(all_field[0]);
    list->topic_id = atoi(all_field[1]);
    memcpy(list->list_name, all_field[2], strlen(all_field[2]) + 1);
    memcpy(list->list_desc, all_field[3], strlen(all_field[3]) + 1);
    memcpy(list->list_image_loc, all_field[4], strlen(all_field[4]) + 1);
    memcpy(list->list_outer_link, all_field[5], strlen(all_field[5]) + 1);
    memcpy(list->list_other_link, all_field[6], strlen(all_field[6]) + 1);
    list->topic_type_id = atoi(all_field[7]);
    memcpy(list->topic_name, all_field[8], strlen(all_field[8]) + 1);
    memcpy(list->topic_type_desc, all_field[9], strlen(all_field[9]) + 1);
    
    /* Change video/audio length */
    if ( list->topic_type_id >= 2 && list->topic_type_id <= 4 ) {
        if ( (chp = strstr(list->list_outer_link, "width=")) != NULL ) {
                *(chp+7) = '6' ;
                *(chp+8) = '8' ;
                *(chp+9) = '0' ;
        }
        if ( (chp = strstr(list->list_outer_link, "height=")) != NULL ) {
                *(chp+8) = '4' ;
                *(chp+9) = '8' ;
                *(chp+10) = '0' ;
        }
    }
}
 
/*
* The split_line function
* This function tokenlizes a record and store in an array since strtok cannot handle empty string.
*/
void split_line( char * line, int fieldnum, char ** all_field ) {
    char * single_field = line;
    int i;
    for ( i = 0; i < fieldnum; i++,single_field++ ) {
        all_field[i] = single_field;
        single_field = strchr(all_field[i], DELIMITER);
        if ( single_field != NULL ) {
            *single_field = '\0';
        } else {
            single_field = strchr(all_field[i], '\n');
            *single_field = '\0'; //For the last field, it has newline brought in by fgets, replace it with string terminator
        }
    }
}
 
 
/*
* The print_block_head function
* for each topic, this function will print the head html code for topic and list
* the block data can be used later to pile up the html documents
* pointer all_topic_fp is to used to serach topic level information that all_topic_file provides
*/
void print_block_head( FILE * block_fp, FILE * all_topic_fp, list_info_t * list ){
    char time[NORMALLEN];
    
    search_post_time( all_topic_fp, list, time );
    fprintf(block_fp, "<div id=\"topic%d\" class=\"topic\">\n", list->topic_id);
    fprintf(block_fp, "<span class=\"time\">%s</span>\n", time);
    fprintf(block_fp, "<a href=\"/topics/topic_%d.html\" class=\"topicTitle\" target=\"_blank\"><h3>%s</h3></a>\n", list->topic_id, list->topic_name);
    switch ( list->topic_type_id ) {
        case 1://音乐
            fprintf(block_fp, "<div class=\"albumImageWrapper\"><img src=\"%s\" class=\"albumImage\"></div>\n", list->list_image_loc);
            fprintf(block_fp, "<span class=\"music listtxt\">%s</span>\n", list->list_desc);
            fprintf(block_fp, "<ul class=\"list\">\n");
            break;
        case 6://博客
            fprintf(block_fp, "<span class=\"listtxt\">%s</span>\n", list->list_desc);
            break;
        default:

            fprintf(block_fp, "<span class=\"listtxt\">%s</span>%s\n", list->list_desc, list->list_outer_link);
            fprintf(block_fp, "<ul class=\"list\">\n");
            break;
    }
}
 
/*
* The search_post_time function
* Input the file pointer to search and provide the list information
* Output the blog post time of the topic
*/
void search_post_time( FILE * all_topic_fp, list_info_t * list, char * time ) {
    char line[NORMALLEN];
    char * single_topic_data[ALL_TOPIC_FIELDSNUM];
    rewind(all_topic_fp);
    while ( fgets(line, NORMALLEN, all_topic_fp ) != NULL ) {
        split_line(line, ALL_TOPIC_FIELDSNUM, single_topic_data);
        if (atoi(single_topic_data[0]) == list->topic_id) {
            memcpy( time, single_topic_data[2], strlen(single_topic_data[2]) + 1 );
            break;
        }
    }
}
 
/*
* The print_block_list function
* generate the html list tag for each list
*/
void print_block_list( FILE * block_fp, list_info_t * list ){
    if ( list->topic_type_id != 6 ) {
        fprintf(block_fp, "<li id=\"list%d\">%s</li>\n", list->list_id, list->list_name);
    }
}
 
/*
* The print_block_tail function
* close the html block
*/
void print_block_tail( FILE * block_fp ){
     fprintf(block_fp, "</ul></div>\n");
}
 
 
/*
* The print_js_head function
* Create the javascript header
*/
void print_js_head( FILE * js_fp, list_info_t * list ){
    fprintf(js_fp, "$( function() {\n");
}
 
/*
* The print_js_list function
* Create the javascript code of manipulating each list
*/
void print_js_list( FILE * js_fp, list_info_t * list ){
    char new_list_name[NORMALLEN];
    char new_list_desc[DESCLEN];
    char new_list_outer_link[NORMALLEN];
    char * chp;
    replace_quotes(new_list_name, list->list_name);
    replace_quotes(new_list_desc, list->list_desc);
    switch ( list->topic_type_id ) {
        case 1://音乐
            strcpy(new_list_outer_link,list->list_outer_link);
            chp = strstr(new_list_outer_link, "_0/");
            *(chp+1) = '1'; //This replacement make the player start to play automatically
            fprintf(js_fp, "$('#list%d').mouseover(function() {$('#topic%d img').attr('src', '%s');$('#topic%d span.listtxt').html('%s');});\n"
                    , list->list_id, list->topic_id, list->list_image_loc, list->topic_id, new_list_desc );
            fprintf(js_fp, "$('#list%d').click(function() {$('#musicPlayer').html('<h3>%s</h3>%s');$('#topic%d li').css('color', '%s');$('#list%d').css('color', '%s');});"
                    , list->list_id, new_list_name, new_list_outer_link, list->topic_id, NORMAL_COLOR, list->list_id, CURRENT_COLOR );
            break;
        case 7://其他
            fprintf(js_fp, "$('#list%d').click(function() {$('#topic%d li').css('color', '%s');$('#list%d').css('color', '%s');$('#topic%d span.listtxt').load(\"getListDesc.php\", \"list_id=%d\");$('#topic%d').animate({scrollTop:0}, 'slow');});\n"
                    , list->list_id, list->topic_id, NORMAL_COLOR, list->list_id, CURRENT_COLOR, list->topic_id, list->list_id, list->topic_id );
            break;
        default:
            fprintf(js_fp, "$('#list%d').click(function() {$('#topic%d span.listtxt').html('%s');$('#topic%d embed').wrap('<div class=\"videoWrapper\" />');$('#topic%d embed').replaceWith('%s');$('#topic%d li').css('color', '%s');$('#list%d').css('color', '%s');});\n"
                    , list->list_id, list->topic_id, new_list_desc, list->topic_id, list->topic_id, list->list_outer_link, list->topic_id, NORMAL_COLOR, list->list_id, CURRENT_COLOR );
            break;
    }
 
}
 
/*
* The replace_quotes function
* Replace ' to \' so that javascript can use it
*/
void replace_quotes (char * target, char * source) {
    char ch;
    int i = 0;
    int j = 0;
    while ( ( ch = source[i] ) != '\0' ) {
        if ( ch == '\'' ) {
            target[j] = '\\';
            target[j+1] = '\'';
            j += 2;
        } else {
            target[j] = ch;
            j++;
        }
        i++;
    }
    target[j] = '\0';
}
 
/*
* The print_js_tail function
* Close the javascript file
*/
void print_js_tail( FILE * js_fp ) {
    fprintf(js_fp, "});\n");
}
 
/*
* The gen_html_page function
* It will generate all the html pages for all kind of topics
*/
void gen_html_page( FILE * all_topic_fp, char * output_dir, char * tmp_dir) {
    int topic_count[TOPIC_KIND_CNT] = {0}; //0-main page,1-music,2-mv,3-soccer,4-fun,5-sofware,6-blog,7-other
    int single_page_index[TOPIC_KIND_CNT] = {1,1,1,1,1,1,1,1}; // there're total ONEPAGE_TOPIC_CNT topics in a single page, it will tell when to create/close new pages
    FILE * output_file[TOPIC_KIND_CNT];         // The output html pages
    char * page_dir[TOPIC_KIND_CNT] = {"", "music/", "mv/", "soccer/", "fun/", "software/", "blog/", "others/"}; // The sub-page names
    char line[NORMALLEN];
    int topic_seq[TOPIC_KIND_CNT][NORMALLEN]; //This two-dimension array will have a sequence of the topic id
    topic_info_t topic;
    char css_fn[NORMALLEN]; //css file for all the topics
    FILE * css_fp;
    char rss_fn[NORMALLEN]; // The feed
    FILE * rss_fp;
    int rss_index = 0;
    int css_len;
    
    /* Calculate the count */
    get_topic_count( all_topic_fp, topic_count, topic_seq );
    
    /* Open the css file */
    sprintf(css_fn, "%s/css/topics.css", output_dir);
    if ( ( css_fp = fopen(css_fn, "w") ) == NULL ) {
        fprintf(stderr, "Failed to open file %s\n", css_fn);
    }
    
    /* Open the rss file */
    sprintf(rss_fn, "%s/feed/rss.xml", output_dir);
    if ( ( rss_fp = fopen(rss_fn, "w") ) == NULL ) {
        fprintf(stderr, "Failed to open file %s\n", rss_fn);
    } else { // Print the rss feed html header
        fprintf(rss_fp, "<?xml version=\"1.0\" encoding=\"utf8\" ?><rss version=\"2.0\"><channel><title>陆赛赛的网络小屋</title><link>http://www.im633.com</link><description>音乐，影音，足球，软件...一切值得珍藏的</description>\n");
    }
    
    
    /* Read each line and create pages  */
    rewind(all_topic_fp);
    while ( fgets(line, NORMALLEN, all_topic_fp ) != NULL ) {
        pop_topic_record(line, &topic);
        create_pages( &topic, topic_count, single_page_index, output_file, page_dir, output_dir, topic_seq, tmp_dir );
        // Generate the css file
        css_len = (topic.max_byte_length - topic.max_char_length) / 2 + (3 * topic.max_char_length - topic.max_byte_length) / 2 * 0.5 + 2;
        fprintf(css_fp, "#topic%d li {width: %dem}\n", topic.topic_id, css_len);
        if ( topic.topic_type_id >= 5 ) {
            fprintf(css_fp, "#topic%d {max-height:700px;overflow:scroll;}\n", topic.topic_id);
        }
        // Generate the rss file
        if ( rss_index < RSS_CNT ) {
            fprintf(rss_fp, "<item><title>%s</title><link>%s/topics/topic_%d.html</link><description>%s</description><guid>%s/topics/topic_%d.html</guid></item>\n",
                    topic.topic_name, DOMAIN, topic.topic_id, topic.topic_name, DOMAIN, topic.topic_id  );
            rss_index++;
        }
    }
    
    //close the css file
    fclose(css_fp);
    //close the rss feed
    fprintf(rss_fp, "</channel></rss>");
    fclose(rss_fp);
}

/*
* The create_pages function
* The main function will create pages for all different kinds of pages
 * The input is one topic
*/
void create_pages( topic_info_t * topic, int * topic_count, int * single_page_index, FILE ** output_file, char ** page_dir, char * output_dir, int topic_seq[][NORMALLEN], char * tmp_dir ){
    char filename[NORMALLEN];
    FILE * single_fp;
    int page_cnt;
    
    /* Open file for main pages */
    if (single_page_index[0] % ONEPAGE_TOPIC_CNT == 1) {
        page_cnt = (single_page_index[0] - 1) / ONEPAGE_TOPIC_CNT;
        if ( page_cnt == 0 ) {
            sprintf(filename, "%s/%sindex.html", output_dir, page_dir[0]);
        } else {
            sprintf(filename, "%s/%s%d.html", output_dir, page_dir[0], page_cnt );
        }
        if ((output_file[0] = fopen(filename, "w")) == NULL) {
            fprintf(stderr, "Failed to open file %s\n", filename);
        }
        print_doc_head(  output_file,  0, DEFAULT_PAGE_TITLE, single_page_index, topic_seq );
    }
    
    /* open file for other pages */
    if (single_page_index[topic->topic_type_id] % ONEPAGE_TOPIC_CNT == 1) {
        page_cnt = (single_page_index[topic->topic_type_id] - 1) / ONEPAGE_TOPIC_CNT;
        if ( page_cnt == 0 ) {
            sprintf(filename, "%s/%sindex.html", output_dir, page_dir[topic->topic_type_id]);
        } else {
            sprintf(filename, "%s/%s%d.html", output_dir, page_dir[topic->topic_type_id], page_cnt );
        }
        if ((output_file[topic->topic_type_id] = fopen(filename, "w")) == NULL) {
            fprintf(stderr, "Failed to open file %s\n", filename);
        }
        print_doc_head(  output_file,  topic->topic_type_id, DEFAULT_PAGE_TITLE, single_page_index, topic_seq );
    }
    
    /* For single page */
    sprintf(filename, "%s/topics/topic_%d.html", output_dir, topic->topic_id );
    if ((single_fp = fopen(filename, "w")) == NULL) {
        fprintf(stderr, "Failed to open file %s\n", filename);
    }
    print_doc_head(  &single_fp,  0, topic->topic_name, single_page_index, topic_seq );
    
    
    // Append the contents
    print_doc_content( output_file[0], topic->topic_id, tmp_dir );
    print_doc_content( output_file[topic->topic_type_id], topic->topic_id, tmp_dir );
    print_doc_content( single_fp, topic->topic_id, tmp_dir );
    
    // Print page link and tail informations
    if ( (single_page_index[0] % ONEPAGE_TOPIC_CNT == 0) || (single_page_index[0] == topic_count[0]) ) {
        print_page_links( output_file[0], topic_count[0], single_page_index[0], page_dir[0] );
        print_doc_tail( output_file[0] );
    }
    if ( (single_page_index[topic->topic_type_id] % ONEPAGE_TOPIC_CNT == 0) || (single_page_index[topic->topic_type_id] == topic_count[topic->topic_type_id]) ) {
        print_page_links( output_file[topic->topic_type_id], topic_count[topic->topic_type_id], single_page_index[topic->topic_type_id], page_dir[topic->topic_type_id] );
        print_doc_tail( output_file[topic->topic_type_id] );
    }
    print_doc_tail( single_fp );
    
    // indexes updating
    single_page_index[0]++;
    single_page_index[topic->topic_type_id]++;
}

/*
* The print_doc_tail function
* It will print contact info.
*/
void print_doc_tail( FILE * target ){
    fprintf(target, "</div></div><div id=\"contact\"><span>订阅网站的RSS:</span><a target=\"_blank\" href=\"/feed/rss.xml\" ><img src=\"/images/rss.png\" alt=\"RSS\"></a><br /><span>我的Email和QQ:</span>\n");
    fprintf(target, "<a href=\"mailto:lusaisai@163.com\" ><img src=\"/images/email.png\" alt=\"mail\" ></a><a target=\"_blank\" href=\"http://sighttp.qq.com/authd?IDKEY=e0c250b3b6e8a43afa5e1813f64a68d8d90f2e532bef8936\"><img border=\"0\"  src=\"http://wpa.qq.com/imgd?IDKEY=e0c250b3b6e8a43afa5e1813f64a68d8d90f2e532bef8936&pic=41\" alt=\"与我交流\" title=\"与我交流\"></a></div></div></body></html>\n");
    fclose(target);
}

/*
* The print_page_links function
* It will create the navigation links.
*/
void print_page_links ( FILE * target, int total_cnt, int this_topic, char * dir ) {
    int total_page_cnt;
    int this_page;
    const int SHOW_PAGE_CNT = 10;
    int start_point;
    int end_point;
    int pagenum = 1;
    
    total_page_cnt = (total_cnt - 1) / ONEPAGE_TOPIC_CNT + 1;
    this_page = (this_topic - 1) / ONEPAGE_TOPIC_CNT + 1;
    start_point = this_page - SHOW_PAGE_CNT;
    end_point = this_page + SHOW_PAGE_CNT;
    
    
    /* printing the div tag */
    fprintf(target, "<div>\n");
    
    
    // The first page
    if ( this_page == 1 ) {
        fprintf(target, "<a id=\"currentpagelinks\" class=\"pagelinks\" href=\"/%sindex.html\" >1</a>\n", dir);
    } else {
        fprintf(target, "<a class=\"pagelinks\" href=\"/%sindex.html\" >1</a>\n", dir);
    }
    pagenum++;
    
    // If the second page should be ...
    if ( start_point > 2 ) {
        fprintf(target, "<span class=\"pagelinks\">...</span>\n");
        pagenum = start_point;
    }
    
    
    /* Print page links */
    while ( pagenum < this_page ) {
        fprintf(target, "<a class=\"pagelinks\" href=\"/%s%d.html\" >%d</a>\n", dir, pagenum - 1, pagenum );
        pagenum++; 
    }
    
    /* Print this page */
    if ( this_page != 1 ) {
        fprintf(target, "<a id=\"currentpagelinks\" class=\"pagelinks\" href=\"/%s%d.html\" >%d</a>\n", dir, pagenum - 1, pagenum );
        pagenum++;
    }
    
    /* print following pages */
    while ( pagenum <= (end_point <= total_page_cnt ? end_point : total_page_cnt ) ) {
        fprintf(target, "<a class=\"pagelinks\" href=\"/%s%d.html\" >%d</a>\n", dir, pagenum - 1, pagenum );
        pagenum++; 
    }
    
    /* If another ... needed */
    if( end_point < total_page_cnt - 1 ) {
        fprintf(target, "<span class=\"pagelinks\">...</span>\n");
        pagenum = total_page_cnt;
        fprintf(target, "<a class=\"pagelinks\" href=\"/%s%d.html\" >%d</a>\n", dir, pagenum - 1, pagenum );
    }
    
    /* close the div tag */
    fprintf(target, "</div>\n");  
}

/*
* The print_doc_content function
* Append that html block file into the target file.
*/
void print_doc_content( FILE * target, int topic_id, char * tmp_dir ) {
    FILE * source;
    char filename[NORMALLEN];
    char ch;
    
    sprintf(filename,"%s/topic_%d.html", tmp_dir, topic_id );
    
    if ((source = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Failed to open file %s\n", filename);
    }
    
    // Copy the source content into target
    while ( (ch = fgetc(source)) != EOF ) {
        fputc(ch, target);
    }
}


/*
* The print_doc_head function
* Print the head of html document.
*/
void print_doc_head( FILE ** output_file, int topic_type_id, char * html_title, int * single_page_index, int topic_seq[][NORMALLEN] ) {
    char jss[NORMALLEN]; //The combining string of the js files
    char tmp_jss[NORMALLEN];
    int i;
    jss[0] = '\0';
    
    /* Concatenate the js file strings */
    for ( i = 0; i < ONEPAGE_TOPIC_CNT; i++ ) {
        if ( topic_seq[topic_type_id][single_page_index[topic_type_id] - 1 + i] == INVALID_TOPICID ) break;
        sprintf(tmp_jss, "<script type=\"text/javascript\" src=\"/js/topic_%d.js\"></script>", topic_seq[topic_type_id][single_page_index[topic_type_id] - 1 + i]);
        strcat(jss,tmp_jss);
    }
    
    /* Print html tags */
    fprintf(output_file[topic_type_id], "<!DOCTYPE html><html><head><META HTTP-EQUIV=\"Pragma\" CONTENT=\"no-cache\"><META HTTP-EQUIV=\"Expires\" CONTENT=\"-1\"><meta charset=\"utf-8\" />\n");
    fprintf(output_file[topic_type_id], "<title>%s</title><link rel=\"shortcut icon\" href=\"/favicon.ico\">\n", html_title);
    fprintf(output_file[topic_type_id], "<script type=\"text/javascript\" src=\"/js/jquery-1.8.0.min.js\"></script><script type=\"text/javascript\" src=\"/js/navigation.js\"></script><script type=\"text/javascript\" src=\"/js/logo.js\"></script>\n");
    fprintf(output_file[topic_type_id], "<script type=\"text/javascript\" src=\"/js/search_keyword.js\"></script><link href=\"/css/main.css\" type=\"text/css\" rel=\"stylesheet\" />\n");
    fprintf(output_file[topic_type_id], "<link href=\"/css/topics.css?<?php echo time();?>\" type=\"text/css\" rel=\"stylesheet\" />%s</head><body>\n", jss);
    fprintf(output_file[topic_type_id], "<ul id=\"nav\"><li><a href=\"/\" >首页</a></li><li><a href=\"/music\" >音乐</a></li><li><a href=\"/mv\" >影音</a></li><li><a href=\"/soccer\" >足球</a></li><li><a href=\"/fun\" >有趣</a></li><li><a href=\"/software\" >软件</a></li><li><a href=\"/blog\" >博客</a></li><li><a href=\"/others\" >其他</a></li></ul>\n");
    fprintf(output_file[topic_type_id], "<div id=\"main\"><div id=\"header\"><canvas id=\"logo\" width=\"380\" height=\"100\"><img src=\"/images/logo.png\" alt=\"im633\" ></canvas><div id=\"bwBox\"><h3 id=\"bw\"><?php include(\"getPoem.php\"); ?></h3></div></div>\n");
    fprintf(output_file[topic_type_id], "<div id=\"bdy\"><div id=\"left_panel\"><div id=\"musicPlayer\"><?php include(\"randomListen.php\");?></div><ul id=\"randomListen\"><li>随便听听</li></ul>\n");
    fprintf(output_file[topic_type_id], "<div id=\"searchBox\"><form id=\"searchForm\"><input type=\"search\" name=\"search_word\" placeholder=\"输入关键字搜索或随便听听\" maxlength=\"2048\" size=\"20\"/>\n");
    fprintf(output_file[topic_type_id], "<input type=\"submit\" name=\"submit_search\" value=\"搜索\" /></form></div><div id=\"searchResult\"></div></div><div id=\"topicBox\">\n");
}

 
/*
* The get_topic_count function
* For each kind of topic, it will tell how many topics there are.
*/
void get_topic_count( FILE * all_topic_fp, int topic_count[], int topic_seq[][NORMALLEN] ){
    topic_info_t atopic;
    char line[NORMALLEN];
    int i;
    int index[TOPIC_KIND_CNT] = {0};
   
    rewind(all_topic_fp);
    while ( fgets(line, NORMALLEN, all_topic_fp ) != NULL ) {
        pop_topic_record(line, &atopic);
        for ( i = 0; i < TOPIC_KIND_CNT; i ++ ){
            if ( i == 0 || i == atopic.topic_type_id ) {
                topic_count[i]++;
                topic_seq[i][index[i]] = atopic.topic_id;
                index[i]++;
            }
        }
    }
    /* Close the sequence */
    for ( i = 0; i < TOPIC_KIND_CNT; i ++ ){
        topic_seq[i][index[i]] = INVALID_TOPICID;
    }
}
 
 
void pop_topic_record(char * line, topic_info_t * topic) {
    char * all_field[ALL_TOPIC_FIELDSNUM];
    split_line(line, ALL_TOPIC_FIELDSNUM, all_field);
   
    topic->topic_id = atoi(all_field[0]);
    topic->topic_type_id = atoi(all_field[1]);
    memcpy( topic->topic_post_time, all_field[2], strlen(all_field[2]) + 1);
    memcpy( topic->topic_name, all_field[3], strlen(all_field[3]) + 1);
    topic->max_char_length = atoi(all_field[4]);
    topic->max_byte_length = atoi(all_field[5]);
}
