/*
 * topictype.hpp
 *
 *  Created on: Jan 24, 2013
 *      Author: lusaisai
 */

#ifndef TOPICTYPE_HPP_
#define TOPICTYPE_HPP_

#include <string>

namespace Im633 {

class topictype {
	private:
		const unsigned int id;
		const std::string type_name;
		static topictype music;
		static topictype video;
		static topictype soccer;
		static topictype fun;
		static topictype software;
		static topictype blog;
		static topictype others;

		// private constructor prevents new instances
		topictype( unsigned int id, const std::string & type_name);

	public:

		~topictype() = default;
		topictype(topictype & another) = delete;

		// methods to get the fields
		const unsigned int get_id() const;
		const std::string& get_type_name() const;

		// methods to get the static members
		static const topictype& get_topictype(unsigned int id) ;
};

bool operator==(const topictype &lhs, const topictype &rhs);
bool operator!=(const topictype &lhs, const topictype &rhs);

}


#endif /* TOPICTYPE_HPP_ */
