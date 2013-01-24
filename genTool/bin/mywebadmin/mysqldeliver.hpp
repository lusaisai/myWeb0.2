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
	void topic_insert(const topic & topic);
	void topic_delete(const topic & topic);
	void topic_update(const topic & topic);

	// Operations on list table
	void list_insert(const list & list);
	void list_delete(const list & list);
	void list_update(const list & list);

	// member setters and getters
	const mysqlpp::Connection& get_conn() const;
	const std::string& get_list_table_name() const;
	void set_list_table_name(const std::string& list_table_name);
	const std::string& get_topic_table_name() const;
	void set_topic_table_name(const std::string& topic_table_name);
};

}



#endif /* MYSQLDELIVER_HPP_ */
