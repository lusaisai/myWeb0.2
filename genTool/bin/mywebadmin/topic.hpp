/*
 * topic.hpp
 *
 *  Created on: Jan 24, 2013
 *      Author: lusaisai
 */

#ifndef TOPIC_HPP_
#define TOPIC_HPP_

#include "topictype.hpp"
#include <string>

namespace Im633 {

class topic {
private:
	unsigned int id;
	const topictype * topic_type;
	std::string topic_name;
	std::string topic_tags;
	std::string topic_recom_flag = "N";

public:
	topic(unsigned int topic_id, unsigned int topic_type_id, std::string name, std::string tags = "", std::string recom_flag = "N");
	~topic() = default;
	topic(unsigned int topic_id, unsigned int topic_type_id);

	unsigned int get_id() const;
	void set_id(unsigned int id);
	const std::string& get_topic_name() const;
	void set_topic_name(const std::string& topic_name);
	const std::string& get_topic_recom_flag() const;
	void set_topic_recom_flag(const std::string& _topic_recom_flag);
	const std::string& get_topic_tags() const;
	void set_topic_tags(const std::string& topic_tags);
	const topictype& get_topic_type() const;
};

bool operator==(const topic &lhs, const topic &rhs);
bool operator!=(const topic &lhs, const topic &rhs);
bool operator<(const topic &lhs, const topic &rhs);
}


#endif /* TOPIC_HPP_ */
