/*
 * File:   main.c
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
#define DOMAIN "im633.com"
#define NORMALLEN 1000     //used for normal string, filenames, etc.
#define DESCLEN 100000     //used for list description
#define ARGSCNT 4          //4 arguments are required
#define INVALID_TOPICID -1 //used to determine the start of processing
#define DELIMITER 0x07       //the delimiter in the new data file
#define NEW_DATA_FIELDSNUM  10 //number of fields in the new data file
#define ALL_TOPIC_FIELDSNUM 3  //number of fields in the all topic file
#define NORMAL_COLOR "#000000" //nomal color of a list
#define CURRENT_COLOR "#CC0052" //color of the current playing list
 
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
 
/* Function prototypes */
void usage(char * filename);
void gen_html_block( FILE * new_data_fp, const char * tmp_dir);
void pop_record(char * line, list_info_t * list);
void print_block_head( FILE * block_fp, list_info_t * list );
void print_block_list( FILE * block_fp, list_info_t * list );
void print_block_tail( FILE * block_fp );
void print_js_head( FILE * js_fp, list_info_t * list );
void print_js_list( FILE * js_fp, list_info_t * list );
void print_js_tail( FILE * js_fp );
void replace_quotes (char * target, char * source);
 
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
    gen_html_block(new_data_fp, tmp_dir);
   
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
void gen_html_block( FILE * new_data_fp, const char * tmp_dir){
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
        pop_record(line, &list);
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
            print_block_head( block_fp, &list );
            print_js_head( js_fp, &list ); //Blog don't need 
           
            /* Update the previous topic id */
            prev_topic_id = curr_topic_id;
        }
       
        /* For the same topic */
        print_block_list( block_fp, &list );
        print_js_list( js_fp, &list );
    }
    /* Close the lat file */
    print_block_tail( block_fp);
    print_js_tail( js_fp );
    fclose(block_fp);
    fclose(js_fp);
}
 
/*
* The pop_record function
* The function get the data from a line in the new data file
* and populate the structure variable
*/
void pop_record(char * line, list_info_t * list){
    /* strtok has issue with empty strings, use strchr and replace DELIMITER with null character */
    char * all_field[NEW_DATA_FIELDSNUM];
    char * single_field = line;
    int i;
    for ( i = 0; i < NEW_DATA_FIELDSNUM; i++,single_field++ ) {
        all_field[i] = single_field;
        single_field = strchr(all_field[i], DELIMITER);
        if ( single_field != NULL )  {
            *single_field = '\0';
        } else {
            single_field = strchr(all_field[i], '\n');
            *single_field = '\0'; //For the last field, it has newline brought in by fgets, replace it with string terminator
        }
    }
   
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
}
 
/*
* The print_block_head function
* for each topic, this function will print the head html code for topic and list
* the block data can be used later to pile up the html documents
*/
void print_block_head( FILE * block_fp, list_info_t * list ){
    fprintf(block_fp, "<div id=\"topic%d\" class=\"topic\">\n", list->topic_id);
    fprintf(block_fp, "<span class=\"time\"></span>\n");
    fprintf(block_fp, "<a href=\"/topics/topic_%d.html\" class=\"topicTitle\" target=\"_blank\"><h3>%s</h3></a>\n", list->topic_id, list->topic_name);
    switch ( list->topic_type_id ) {
        case 1://音乐
            fprintf(block_fp, "<div class=\"albumImageWrapper\"><img src=\"%s\" class=\"albumImage\"></div>\n", list->list_image_loc);
            fprintf(block_fp, "<span class=\"music listtxt\">%s</span>\n", list->list_desc);
            fprintf(block_fp, "<ul class=\"list\">\n", list->list_id);
            break;
        case 6://博客
            fprintf(block_fp, "<span class=\"listtxt\">%s</span>\n", list->list_desc);
            break;
        default:
            fprintf(block_fp, "<span class=\"listtxt\">%s</span>%s\n", list->list_desc, list->list_outer_link);
            fprintf(block_fp, "<ul class=\"list\">\n", list->list_id);
            break;
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
            fprintf(js_fp, "$('#list%d').click(function() {$('#musicPlayer h3').html('%s');$('#musicPlayer embed').replaceWith('%s');$('#topic%d li').css('color', '%s');$('#list%d').css('color', '%s');});"
                    , list->list_id, new_list_name, new_list_outer_link, list->topic_id,  NORMAL_COLOR, list->list_id, CURRENT_COLOR );
            break;
        case 7://其他
            fprintf(js_fp, "$('#list%d').click(function() {$('#topic%d li').css('color', '%s');$('#list%d').css('color', '%s');$('#topic%d span.listtxt').load(\"getListDesc.php\", \"list_id=%d\");$('#topic%d').animate({scrollTop:0}, 'slow');});\n"
                    , list->list_id, list->topic_id, NORMAL_COLOR, list->list_id, CURRENT_COLOR, list->topic_id, list->list_id, list->topic_id );
            break;
        default:
            fprintf(js_fp, "$('#list%d').click(function() {$('#topic%d span.listtxt').html('%s');$('#topic%d embed').wrap('<div class=\"videoWrapper\" />');$('#topic%d embed').replaceWith('%s');$('#topic%d li').css('color', '%s');$('#list%d').css('color', '%s');});\n"
                    , list->list_id, list->topic_id, new_list_desc, list->topic_id, list->topic_id, new_list_outer_link, list->topic_id, NORMAL_COLOR, list->list_id, CURRENT_COLOR  );
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
    while ( ( ch = source[i]) != '\0' ) {
        if ( ch == '\'' ) {
            target[j] = '\\';
            target[j] = '\'';
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

