#include "Utilities/Utilities.h"
#include "Utilities/Log.h"
#include <fstream>

char* Utilities::ReadFile(std::string path)
{
	std::ifstream file;

	file.open(path);
	if (!file.is_open()) {
		Log::Error("[Utilities::ReadFile]\nCouldn't open file: " + path);
	}
	file.seekg(0, std::ios::end);
	const int len = file.tellg();
	file.seekg(0, std::ios::beg);
	char* buffer = new char[len + 1];
	file.read(buffer, len);
	buffer[len] = '\0';
	file.close();
	return (buffer);
}