/*
 * topic.cpp
 *
 *  Created on: Jan 24, 2013
 *      Author: lusaisai
 */

#include "topic.hpp"
#include "topictype.hpp"
#include <string>

using namespace Im633;

// Constructor
topic::topic(unsigned int topic_id, unsigned int topic_type_id, std::string name, std::string tags, std::string recom_flag):
	id(topic_id), topic_name(name),  topic_recom_flag(recom_flag), topic_tags(tags) {
	topic_type = &topictype::get_topictype(topic_type_id);
}

topic::topic(unsigned int topic_id, unsigned int topic_type_id):
	id(topic_id){
	topic_type = &topictype::get_topictype(topic_type_id);
}

// operators
bool operator==(const topic &lhs, const topic &rhs) {
	return lhs.get_id() == rhs.get_id();
}

bool operator!=(const topic &lhs, const topic &rhs) {
	return lhs.get_id() != rhs.get_id();
}

bool operator<(const topic &lhs, const topic &rhs) {
	return lhs.get_id() < rhs.get_id();
}


// various getters and setters
unsigned int topic::get_id() const {
	return id;
}

void topic::set_id(unsigned int id) {
	this->id = id;
}

const std::string& topic::get_topic_name() const {
	return topic_name;
}

void topic::set_topic_name(const std::string& topic_name) {
	this->topic_name = topic_name;
}

const std::string& topic::get_topic_recom_flag() const {
	return topic_recom_flag;
}

void topic::set_topic_recom_flag(const std::string& topic_recom_flag) {
	this->topic_recom_flag = topic_recom_flag;
}

const std::string& topic::get_topic_tags() const {
	return topic_tags;
}

void topic::set_topic_tags(const std::string& topic_tags) {
	this->topic_tags = topic_tags;
}

const topictype& topic::get_topic_type() const
{
	return *topic_type;
}

