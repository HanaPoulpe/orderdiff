#ifndef __ORDERDIFF_H
#define __ORDERDIFF_H

#include <string>
#include <ostream>

namespace orderdiff {
	const std::string VERSION{ "orderdiff/0.0/20200801" };

	void print_usage(std::ostream& out, std::istream& i1, std::istream& i2);
	void print_version(std::ostream& out, std::istream& i1, std::istream& i2);
	void print_diff(std::ostream&, std::istream&, std::istream&);
	void print_none(std::ostream&, std::istream&, std::istream&);

	bool redirected_cin();
}

#endif