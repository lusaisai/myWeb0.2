/*
 * list.cpp
 *
 *  Created on: Jan 24, 2013
 *      Author: lusaisai
 */

#include "list.hpp"
#include <string>
#include <iostream>

using namespace Im633;

/*
 * The constructor
 * */
list::list(unsigned int id, unsigned int topic_id, std::string list_name, std::string list_desc,
	std::string list_image_loc, std::string list_outer_link, std::string list_other_link):
	id(id), topic_id(topic_id), list_name(list_name), list_desc(list_desc),
	list_image_loc(list_image_loc), list_outer_link(list_outer_link), list_other_link(list_other_link){

}

list::list(unsigned int id, unsigned int topic_id):
		id(id), topic_id(topic_id) {

}

void list::print_data() const {
	std::cout << "list id: " << id << std::endl;
	std::cout << "topic id: " << topic_id << std::endl;
	std::cout << "list name: " << list_name << std::endl;
	std::cout << "list description: " << list_desc << std::endl;
	std::cout << "list image: " << list_image_loc << std::endl;
	std::cout << "list outer link: " << list_outer_link << std::endl;
	std::cout << "list other link: " << list_other_link << std::endl;
}

/*
 * The operators
 * */
bool Im633::operator==(const list &lhs, const list &rhs) {
	return lhs.get_id() == rhs.get_id();
}

bool Im633::operator!=(const list &lhs, const list &rhs) {
	return lhs.get_id() != rhs.get_id();
}

bool Im633::operator<(const list &lhs, const list &rhs) {
	return lhs.get_id() < rhs.get_id();
}


/*
 * The getters and setters
 * */
unsigned int list::get_id() const {
	return id;
}

void list::set_id(unsigned int id) {
	this->id = id;
}

const std::string& list::get_list_desc() const {
	return list_desc;
}

void list::set_list_desc(const std::string& list_desc) {
	this->list_desc = list_desc;
}

const std::string& list::get_list_image_loc() const {
	return list_image_loc;
}

void list::set_list_image_loc(const std::string& list_image_loc) {
	this->list_image_loc = list_image_loc;
}

const std::string& list::get_list_name() const {
	return list_name;
}

void list::set_list_name(const std::string& list_name) {
	this->list_name = list_name;
}

const std::string& list::get_list_other_link() const {
	return list_other_link;
}

void list::set_list_other_link(const std::string& list_other_link) {
	this->list_other_link = list_other_link;
}

const std::string& list::get_list_outer_link() const {
	return list_outer_link;
}

void list::set_list_outer_link(const std::string& list_outer_link) {
	this->list_outer_link = list_outer_link;
}

unsigned int list::get_topic_id() const {
	return topic_id;
}

void list::set_topic_id(unsigned int topic_id) {
	this->topic_id = topic_id;
}

