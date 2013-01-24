/*
 * clienttest.cpp
 *
 *  Created on: Jan 24, 2013
 *      Author: lusaisai
 */

/*
 * testclient.cpp
 *
 *  Created on: Jan 24, 2013
 *      Author: lusaisai
 */

#include "topictype.hpp"
#include "topic.hpp"
#include "list.hpp"
#include "mysqldeliver.hpp"
#include <iostream>

using namespace Im633;

int main(int argc, char *argv[]) {
	unsigned int id(5);
	//std::cout << "Please enter a number between 1 and 7: ";
	//std::cin >> id;
	const topictype & tt = topictype::get_topictype(id);
	std::cout << tt.get_type_name() << std::endl;

	topic a(108, 2);
	topic b(101, 1);
	a.set_topic_name("Sam");
	std::cout << a.get_topic_name() << std::endl;
	a.set_topic_recom_flag("Y");
	a.set_topic_tags("it's another test");

	list l(500, 1);
	std::cout << l.get_list_name() << std::endl;
	l.set_list_name("this list");
	l.set_list_desc("it's a test");
	l.set_list_image_loc("a.png");
	l.set_list_other_link("http://aaaa/");
	std::cout << l.get_list_name() << std::endl;

	mysqldeliver md("myweb01","f_topic","f_topic_list","myweb","myweb");
	md.topic_delete(a);
	md.topic_insert(a);
	a.set_topic_name("sam_updated");
	md.topic_delete(b);
	md.topic_update(a);
	md.list_delete(l);
	md.list_insert(l);
	l.set_list_name("ah ha, updated");
	md.list_update(l);
	md.list_delete(l);
}

