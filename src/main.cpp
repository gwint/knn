#include <iostream>

#include "dataparser.hpp"

int main(int argc, char** argv) {
	std::cout << "Hello" << '\n';

	Data data = Data::retrieveFromCSVFile("breast-cancer-wisconsin.data");
	return 0;
}
