#include <iostream>
#include "orderdiff.h"
#include "config.h"
#include <vector>
#include <string_view>

int main(int argc, char* argv[])
{
	orderdiff::config c{ argc, argv };

	c.print();

	if (!c.getErrorList().empty()) c.printError();

	return 0;
}

namespace orderdiff {


	void print_usage(std::ostream& out, std::istream& i1, std::istream& i2) {
		out << "orderdiff [options] <file1> <file2>" << '\n'
			<< " - file1: First list" << '\n'
			<< "     Input redirections are considered as file1" << '\n'
			<< '\n'
			<< " - file2: Second list" << '\n'
			<< '\n'
			<< "Options:" << '\n'
			<< " -o<file> | --output=<file>: Writes output in file" << '\n'
			<< " -h |--help: Displays this menu" << '\n'
			<< " --version : Displays tool version" << '\n';
	}

	void print_version(std::ostream& out, std::istream& i1, std::istream& i2) {
		out << VERSION << '\n';
	}

	void print_none(std::ostream& out, std::istream& i1, std::istream& i2) {}

	void print_diff(std::ostream& out, std::istream& i1, std::istream& i2) {
		std::vector<std::string> ilist1{};
		size_t last_found_pos{};
		std::string last_found{};
		bool first_found{ false };
		std::string l{};

		while(!i1.eof()) {
			std::getline(i1, l);
			ilist1.push_back(l);
		}

		while (!i2.eof()) {
			std::getline(i2, l);

			for (size_t i{0}; i < ilist1.size(); i++) {
				if (ilist1[i] == l) {
					if (first_found && (i < last_found_pos)) {
						out << last_found << "\t>\t" << l << '\n';
					}
					else {
						last_found = l;
						last_found_pos = i;
						first_found = true;
					}
				}
			}
		}
	}

	bool redirected_cin() {
		//TODO:Implement
		return false;
	}
}
