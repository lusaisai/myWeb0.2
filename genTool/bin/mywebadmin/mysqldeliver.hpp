/*
 * mysqldeliver.hpp
 *
 *  Created on: Jan 24, 2013
 *      Author: lusaisai
 */

#ifndef MYSQLDELIVER_HPP_
#define MYSQLDELIVER_HPP_

#define MYSQLPP_MYSQL_HEADERS_BURIED

#include "topic.hpp"
#include "list.hpp"
#include <string>
#include <set>
#include <mysql++/mysql++.h>


namespace Im633 {

class mysqldeliver {
private:
	mysqlpp::Connection conn;
	std::string topic_table_name;
	std::string list_table_name;

public:
	mysqldeliver(const char * db, std::string topic_table_name, std::string list_table_name, const char * user, const char * password, const char * server = 0, unsigned int port = 0);
	~mysqldeliver() = default;

	// Operations on topic table
	void topic_insert(const topic & topic); // insert into database
	void topic_delete(const topic & topic); // delete from database
	void topic_update(const topic & topic); // update into database
	unsigned int max_topic_id();
	topic fetch_topic(const unsigned int topic_id); //fetch data from database and constructs an topic object
	std::set<topic> fetch_topic(const topictype & tt); // Given a topic type, constructs a set of topic objects
	std::set<topic> fetch_topic(); // Constructs a set of all existing topic objects
	topic new_topic(const topictype & tt); // create a new topic, the topic id will be max + 1

	// Operations on list table
	void list_insert(const list & list);
	void list_delete(const list & list);
	void list_update(const list & list);
	unsigned int max_list_id();
	list fetch_list(const unsigned int list_id); //fetch data from database and constructs an list object
	std::set<list> fetch_list(const topic & topic); // Given a topic, fetch data from database and constructs a set of list objects
	list new_list(const topic & topic); // create a new list, the list_id is max + 1

	// The normal method to run any query and handle the result by yourself
	mysqlpp::StoreQueryResult query(std::string text);

	// member setters and getters
	const mysqlpp::Connection& get_conn() const;
	const std::string& get_list_table_name() const;
	void set_list_table_name(const std::string& list_table_name);
	const std::string& get_topic_table_name() const;
	void set_topic_table_name(const std::string& topic_table_name);
};

}



#endif /* MYSQLDELIVER_HPP_ */
