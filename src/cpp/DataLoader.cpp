#include "DataLoader.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace expertake {

DataLoader::DataLoader() {
}

DailyData DataLoader::LoadData(const std::string& date) {
	std::stringstream fileName;
	fileName << "data/" << date << ".json";
	std::ifstream is(fileName.str().c_str(), std::ifstream::binary);
	std::string result;
	if (is) {
		is.seekg(0, is.end);
		int length = is.tellg();
		is.seekg(0, is.beg);

		char* buffer = new char[length];
		is.read(buffer, length);

		if (!is) {
			std::cout << "Error: only " << is.gcount() << " could be read from " << fileName.str() << std::endl;
		}

		is.close();

		result.append(buffer, length);

		delete[] buffer;
	} else {
		std::cout << "Error opening file " << fileName.str() << std::endl;
	}

	return DailyData(result);
}

} // expertake
