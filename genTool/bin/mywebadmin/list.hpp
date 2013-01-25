/*
 * list.hpp
 *
 *  Created on: Jan 24, 2013
 *      Author: lusaisai
 */

#ifndef LIST_HPP_
#define LIST_HPP_


#include <string>

namespace Im633 {

class list {
private:
	unsigned int id;
	unsigned int topic_id;
	std::string list_name;
	std::string list_desc;
	std::string list_image_loc;
	std::string list_outer_link;
	std::string list_other_link;

public:
	list(unsigned int id, unsigned int topic_id, std::string list_name, std::string list_desc,
			std::string list_image_loc, std::string list_outer_link, std::string list_other_link);
	list(unsigned int id, unsigned int topic_id);
	~list() = default;

	// print what the list looks like
	void print_data() const;

	unsigned int get_id() const;
	void set_id(unsigned int id);
	const std::string& get_list_desc() const;
	void set_list_desc(const std::string& list_desc);
	const std::string& get_list_image_loc() const;
	void set_list_image_loc(const std::string& list_image_loc);
	const std::string& get_list_name() const;
	void set_list_name(const std::string& list_name);
	const std::string& get_list_other_link() const;
	void set_list_other_link(const std::string& list_other_link);
	const std::string& get_list_outer_link() const;
	void set_list_outer_link(const std::string& list_outer_link);
	unsigned int get_topic_id() const;
	void set_topic_id(unsigned int topic_id);
};

bool operator==(const list &lhs, const list &rhs);
bool operator!=(const list &lhs, const list &rhs);
bool operator<(const list &lhs, const list &rhs);

}


#endif /* LIST_HPP_ */
