#include "config.h"
#include "orderdiff.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <deque>

namespace orderdiff {

	void config::parseLongOption(const std::string param) {
		size_t equal_pos = param.find("=");
		std::string_view p_view{ param };
		std::string_view option_name{ p_view };
		std::string_view option_param{};

		if (equal_pos != std::string::npos) {
			option_param = p_view.substr(equal_pos + 1);
			option_name = p_view.substr(0, equal_pos - 1);
		}

		if (option_name == "--output") {
			setOutput(std::string{ option_param });
		}
		else if (option_name == "--help") {
			__print = print_usage;
		}
		else if (option_name == "--version") {
			__print = print_version;
		}
		else {
			__error_stack.push_back("Invalid option: " + std::string{ p_view });
			__print = print_none;
		}
	}

	void config::parseShortOption(const std::string param) {
		size_t i{};

		for (i = 0; param[i] != '\0'; i++);
		if (i < 1) {
			__error_stack.push_back(std::string{ "Invalid options " } +param);
			return;
		}

		switch (param[1]) {
		case 'h':
			__print = print_usage;
			return;
		case 'o':
			if (i < 2) {
				setOutput(param.substr(2));
				return;
			}
			else {
				__error_stack.push_back("Error with param " + param);
				__error_stack.push_back("-o must specify a  outpur file");
			}
		default:
			__error_stack.push_back("Invalid option " + param);
			__print = print_none;
		}
	}

	///! Creates a config from c main args
	config::config(int argc, char* argv[]) {
		config();

		if (argc < 2) {
			__error_stack.push_back("No parametters found");
			__print = print_usage;
			return;
		}

		int input_count{ 0 };

		if (redirected_cin()) input_count = 1;

		for (int i{ 1 }; i < argc && input_count < 2; i++) {
			if (argv[i][0] == '-') {
				if (argv[i][1] == '-') {
					parseLongOption(argv[i]);
				}
				else {
					parseShortOption(argv[i]);
				}
			}
			else {
				if (input_count == 0) {
					input_count = 1;
					setInput1(argv[i]);
				}
				else {
					input_count = 2;
					setInput2(argv[i]);
				}
			}
		}
	}

	config::~config() {
		closeInput1();
		closeInput2();
		closeOutput();
	}

	///! Access input1

	///! Set input1 from file name
	///! \param filename input file name
	void config::setInput1(const std::string filename) {
		closeInput1();
		__input1 = new std::ifstream(filename);
		__close_input1 = true;
	}

	///! Set input1 from istream
	void config::setInput1(std::istream& i) {
		closeInput1();
		__input1 = &i;
	}

	///! Close input1
	void config::closeInput1() {
		if (__close_input1) {
			((std::ofstream*)__input1)->close();
			delete __input1;
			__input1 = nullptr;
			__close_input1 = false;
		}
	}

	///!Access input2

	///! Set input2 from file name
	///! \param filename input file name
	void config::setInput2(const std::string filename) {
		closeInput2();
		__input2 = new std::ifstream(filename);
		__close_input2 = true;
	}

	///! Set input2 from istream
	void config::setInput2(std::istream& i) {
		closeInput2();
		__input2 = &i;
	}

	///! Close input2
	void config::closeInput2() {
		if (__close_input2) {
			((std::ifstream*)__input2)->close();
			delete __input2;
			__input2 = nullptr;
			__close_input2 = false;
		}
	}

	///! Access output

	///! Set ouput from file name
	///! \param filename Output file name
	void config::setOutput(const std::string filename) {
		closeOutput();
		__output = new std::ofstream(filename);
		__close_ouput = true;
	}

	///! Set output from ostream
	void config::setOutput(std::ostream& o) {
		closeOutput();
		__output = &o;
	}

	///! Close output
	void config::closeOutput() {
		if (__close_ouput) {
			((std::ofstream*)__output)->close();
			delete __output;
			__output = nullptr;
			__close_ouput = false;
		}
	}

	void config::print() {
		__print(*__output, *__input1, *__input2);
	}

	bool config::hasError()
	{
		return !__error_stack.empty();
	}

	void config::printError()
	{
		while (!__error_stack.empty()) {
			std::string e = __error_stack[0];
			std::cerr << e << '\n';
			__error_stack.pop_front();
		}
	}

	std::deque<std::string> config::getErrorList()
	{
		return __error_stack;
	}

}