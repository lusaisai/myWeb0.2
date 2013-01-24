/*
 * mysqldeliver.cpp
 *
 *  Created on: Jan 24, 2013
 *      Author: lusaisai
 */

#include "mysqldeliver.hpp"

using namespace Im633;


/*
 * The constructor
 * */
mysqldeliver::mysqldeliver(const char * db, std::string topic_table_name, std::string list_table_name,
		const char * user, const char * password, const char * server, unsigned int port):
			conn(db,server,user,password,port), topic_table_name(topic_table_name), list_table_name(list_table_name) {

}

/*
 * The various mysql operations
 * */
// Operations on topic table
void mysqldeliver::topic_insert(const topic & topic) {
	mysqlpp::Query query = conn.query();
	query << "insert into " << topic_table_name << " values (%0,%1,%2q,%3q,%4q,CURRENT_TIMESTAMP);";
	query.parse();
	mysqlpp::SimpleResult res = query.execute(topic.get_id(), topic.get_topic_type().get_id(), topic.get_topic_name(), topic.get_topic_tags(), topic.get_topic_recom_flag());
	std::cout << res.rows() << " record inserted." << std::endl;
}

void mysqldeliver::topic_delete(const topic & topic){
	mysqlpp::Query query = conn.query();
	query << "delete from " << topic_table_name << " where topic_id = " << topic.get_id() << ";";
	mysqlpp::SimpleResult res = query.execute();
	std::cout << res.rows() << " record deleted." << std::endl;
}

void mysqldeliver::topic_update(const topic & topic){
	mysqlpp::Query query = conn.query();
	query << "update " << topic_table_name << " set "
			"topic_type_id = %1,"
			"topic_name = %2q,"
			"topic_tags = %3q,"
			"topic_recom_flag = %4q,"
			"modified_ts = CURRENT_TIMESTAMP "
			"where topic_id = %0;";
	query.parse();
	mysqlpp::SimpleResult res = query.execute(topic.get_id(), topic.get_topic_type().get_id(), topic.get_topic_name(), topic.get_topic_tags(), topic.get_topic_recom_flag());
	std::cout << res.rows() << " record updated." << std::endl;
}

// Operations on list table
void mysqldeliver::list_insert(const list & list){
	mysqlpp::Query query = conn.query();
	query << "insert into " << list_table_name << " values (%0,%1,%2q,%3q,%4q,%5q,%6q,CURRENT_TIMESTAMP);";
	query.parse();
	mysqlpp::SimpleResult res = query.execute(list.get_id(),list.get_topic_id(),list.get_list_name(), list.get_list_desc(), list.get_list_image_loc(), list.get_list_outer_link(), list.get_list_other_link());
	std::cout << res.rows() << " record inserted." << std::endl;
}
void mysqldeliver::list_delete(const list & list){
	mysqlpp::Query query = conn.query();
	query << "delete from " << list_table_name << " where list_id = " << list.get_id() << ";";
	mysqlpp::SimpleResult res = query.execute();
	std::cout << res.rows() << " record deleted." << std::endl;
}
void mysqldeliver::list_update(const list & list){
	mysqlpp::Query query = conn.query();
	query << "update " << list_table_name << " set "
			"topic_id = %1,"
			"list_name = %2q,"
			"list_desc = %3q,"
			"list_image_loc = %4q,"
			"list_outer_link = %5q,"
			"list_other_link = %6q,"
			"modified_ts = CURRENT_TIMESTAMP "
			"where list_id = %0;";
	query.parse();
	mysqlpp::SimpleResult res = query.execute(list.get_id(),list.get_topic_id(),list.get_list_name(), list.get_list_desc(), list.get_list_image_loc(), list.get_list_outer_link(), list.get_list_other_link());
	std::cout << res.rows() << " record updated." << std::endl;
}


/*
 * The setters and getters
 * */
const mysqlpp::Connection& mysqldeliver::get_conn() const {
	return conn;
}

const std::string& mysqldeliver::get_list_table_name() const {
	return list_table_name;
}

void mysqldeliver::set_list_table_name(const std::string& list_table_name) {
	this->list_table_name = list_table_name;
}

const std::string& mysqldeliver::get_topic_table_name() const {
	return topic_table_name;
}

void mysqldeliver::set_topic_table_name(const std::string& topic_table_name) {
	this->topic_table_name = topic_table_name;
}
