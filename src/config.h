#ifndef __CONFIG_H
#define __CONFIG_H

#include <iostream>
#include <deque>
#include "orderdiff.h"

namespace orderdiff {
	
	///! Configuration holder
	class config {

	private:
		std::istream* __input1{ nullptr };
		bool __close_input1{ false };
		std::istream* __input2{ nullptr };
		bool __close_input2{ false };
		std::ostream* __output{ &std::cout };
		bool __close_ouput{ false };
		void (*__print)(std::ostream&, std::istream&, std::istream&) { print_diff };
		std::deque<std::string> __error_stack{};

		void parseLongOption(const std::string param);

		void parseShortOption(const std::string param);
		

	public:
		config() = default;

		///! Creates a config from c main args
		config(int argc, char* argv[]);

		config(const config&) = default;
		~config();

		///! Access input1

		///! Set input1 from file name
		///! \param filename input file name
		void setInput1(const std::string filename);

		///! Set input1 from istream
		void setInput1(std::istream& i);

		///! Close input1
		void closeInput1();

		///!Access input2

		///! Set input2 from file name
		///! \param filename input file name
		void setInput2(const std::string filename);

		///! Set input2 from istream
		void setInput2(std::istream& i);

		///! Close input2
		void closeInput2();

		///! Access output

		///! Set ouput from file name
		///! \param filename Output file name
		void setOutput(const std::string filename);

		///! Set output from ostream
		void setOutput(std::ostream& o);

		///! Close output
		void closeOutput();

		///! Displays what should be displayed
		void print();

		///! Tells if there are config errors
		bool hasError();

		///! Print errors in std::cerr
		void printError();

		///! Gives the stack of errors
		std::deque<std::string> getErrorList();
	};
}

#endif
