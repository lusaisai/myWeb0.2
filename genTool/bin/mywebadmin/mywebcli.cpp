/*
 * mywebcli.cpp
 *
 *  Created on: Jan 25, 2013
 *      Author: lusaisai
 */

#include "topictype.hpp"
#include "topic.hpp"
#include "list.hpp"
#include "mysqldeliver.hpp"
#include <iostream>

void usage(int rcode);
unsigned int ask_options();
void option_handle(const unsigned int option,  Im633::mysqldeliver & md);
void add_new_topic( Im633::mysqldeliver & md);
void add_new_list( Im633::mysqldeliver & md, unsigned int topic_id);

/*
 * The main function
 * */
int main( int argc, char *argv[] ) {
	if ( argc < 6 ) {
		usage(1);
	}

	Im633::mysqldeliver md(argv[1],argv[2],argv[3],argv[4],argv[5]);

	unsigned int option = 0; // see comments of ask_options()

	while ( true ) {
		option = ask_options();
		if (option == 0) exit(0);
		else if ( option != 1 && option != 2 ) {
			std::cout << "A wrong option, please re-choose." << std::endl;
			continue;
		}
		option_handle(option, md);
	}

}

/*
 * The usage function
 * */
void usage(int rcode) {
	std::cout << "mywebcli <database name> <topic table name> <list table name> <username> <password>" << std::endl;
	exit(rcode);
}

/*
 * Asking for options
 * 1 - new topic
 * 2 - add list into existing topic
 * 0 - exit
 * */
unsigned int ask_options() {
	unsigned int option;
	std::cout << "========================================================================" << std::endl;
	std::cout <<  "Welcome:), please choose the number to tell me what you want to do" << std::endl;
	std::cout <<  "1 - add a new topic" << std::endl;
	std::cout <<  "2 - add topic list for existing topic" << std::endl;
	std::cout <<  "0 - exit" << std::endl;
	std::cin >> option;
	return option;
}

/*
 * Handle the work of adding topic or list
 * */
void option_handle(const unsigned int option, Im633::mysqldeliver & md) {

	switch ( option ) {
	case 1:
		add_new_topic(md);
		break;
	case 2:
		unsigned int topic_id;
		std::cout << "Please Enter the existing topic id: ";
		std::cin >> topic_id;
		add_new_list(md, topic_id);
		break;
	default:
		break;
	}
}


void add_new_topic( Im633::mysqldeliver & md) {
	unsigned int topic_type_id;

	// a loop to choose the type
	while ( true ) {
		std::cout << "Please choose the topic you want to add: " << std::endl;
		std::cout << "1 - music; 2 - video; 3 - soccer; 4 - fun; 5 - software; 6 - blog; 7 - others " << std::endl;
		std::cin >> topic_type_id;
		if ( topic_type_id >= 1 && topic_type_id <= 7 ) break;
		else {
			std::cout << "Wrong choice, please re-choose " << std::endl;
		}
	}

	// Create a new topic
	Im633::topic new_topic( md.new_topic(Im633::topictype::get_topictype(topic_type_id)) );

	// Keep asking to provide topic info till the user confirms
	while ( true ) {
		std::string topic_name, topic_tags, topic_recom_flag;
		std::cin.ignore(100, '\n');// just clean the buffer
		std::cout << "Please input your topic name: " << std::endl;
		std::getline(std::cin, topic_name);
		std::cout << "Please give some tags for this topic: " << std::endl;
		std::getline(std::cin, topic_tags);
		std::cout << "Is this topic strongly recommended? (Y/N): " << std::endl;
		std::getline(std::cin, topic_recom_flag);

		new_topic.set_topic_name(topic_name);
		new_topic.set_topic_tags(topic_tags);
		new_topic.set_topic_recom_flag(topic_recom_flag);

		new_topic.print_data();
		std::cout << "Is the data above looks good, enter y to deploy to MYSQL, enter n to re-input: ";
		std::string answer;
		std::cin >> answer;

		if ( answer == "Y" || answer == "y" ) {
			md.topic_insert(new_topic);
			add_new_list(md, new_topic.get_id());
			break;
		} else {
			continue;
		}

	}
}

/*
 * Add lists to a topic
 * */
void add_new_list( Im633::mysqldeliver & md, unsigned int topic_id) {
	while (true) {
		Im633::list new_list( md.new_list( md.fetch_topic(topic_id) ) );
		std::string list_name, list_image_loc, list_outer_link, list_other_link, list_desc;
		std::cin.ignore(100, '\n');// just clean the buffer
		std::cout << "Please enter your list name: " << std::endl;
		std::getline(std::cin, list_name);
		std::cout << "Please enter the image link: " << std::endl;
		std::getline(std::cin, list_image_loc);
		std::cout << "Please enter the external embed link: " << std::endl;
		std::getline(std::cin, list_outer_link);
		std::cout << "Please enter any other link to be used for this topic/list: " << std::endl;
		std::getline(std::cin, list_other_link);
		std::cout << "Please enter your description of this list: " << std::endl;
		std::getline(std::cin, list_desc);

		new_list.set_list_desc(list_desc);
		new_list.set_list_image_loc(list_image_loc);
		new_list.set_list_name(list_name);
		new_list.set_list_other_link(list_other_link);
		new_list.set_list_outer_link(list_outer_link);

		new_list.print_data();
		std::cout << "Is the data above looks good, enter y to deploy to MYSQL, enter n to re-input: ";
		std::string answer;
		std::cin >> answer;

		if ( answer == "Y" || answer == "y" ) {
			md.list_insert(new_list);
			std::cout << "Add another list to this topic?(y/n): ";
			std::cin >> answer;
			if ( answer == "Y" || answer == "y" ) continue;
			else break;
		} else {
			continue;
		}

	}
}
