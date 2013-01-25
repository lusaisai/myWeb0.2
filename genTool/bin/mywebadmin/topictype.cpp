/*
 * topictype.cpp
 *
 *  Created on: Jan 24, 2013
 *      Author: lusaisai
 */


#include "topictype.hpp"
#include <stdexcept>

using namespace Im633;

//The constructor
topictype::topictype( unsigned int id, const std::string & type_name) :
	id(id), type_name(type_name) { }

// static members initialization
topictype topictype::music(1,"music");
topictype topictype::video(2,"video");
topictype topictype::soccer(3,"soccer");
topictype topictype::fun(4,"fun");
topictype topictype::software(5,"software");
topictype topictype::blog(6,"blog");
topictype topictype::others(7,"others");

// The equality operator
bool Im633::operator==(const topictype &lhs, const topictype &rhs){
	return lhs.get_id() == rhs.get_id();
}

bool Im633::operator!=(const topictype &lhs, const topictype &rhs){
	return lhs.get_id() != rhs.get_id();
}


// the various member functions

const topictype& topictype::get_topictype(unsigned int id)  {
	switch (id) {
		case 1: return music;
		case 2: return video;
		case 3: return soccer;
		case 4: return fun;
		case 5: return software;
		case 6: return blog;
		case 7: return others;
		default: throw std::invalid_argument("Unknown topic type");
	}

}

const std::string& topictype::get_type_name() const {
	return type_name;
}

const unsigned int topictype::get_id() const {
	return id;
}
