#pragma once

#include <string>
#include <fstream>

static std::string read_file(const std::string &filename) {
	std::string line, text;
	std::fstream file(filename);

	while (std::getline(file, line)) text += (line + '\n');

	file.close();

	return text;
}

static void write_file(const std::string &filename, std::string &data) {
	std::string line, text;
	std::fstream file(filename);

	file << data;

	file.close();
}