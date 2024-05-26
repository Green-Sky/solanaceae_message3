#pragma once

#include "./file.hpp"

#include <fstream>
#include <ios>
#include <limits>

struct FileRFile : public FileI {
	std::ifstream _file;

	FileRFile(std::string_view file_path) : _file(static_cast<std::string>(file_path), std::ios::binary) {
		if (!_file.is_open()) {
			return; // TODO: error
		}

		// figure out size
		_file.seekg(0, _file.end);
		_file_size = _file.tellg();
		_file.seekg(0, _file.beg);
	}

	//FileRFile(std::ifstream&& other_file) : _file(std::move(other_file)) {}
	//FileRFile(std::ifstream&& other_file, size_t file_size) : _file(std::move(other_file)), _file_size(file_size) {}

	virtual ~FileRFile(void) {}

	bool isGood(void) override {
		return _file.is_open() && _file.good();
	}

	std::vector<uint8_t> read(uint64_t pos, uint64_t size) override {
		if (_file_size > 0 && pos >= _file_size) {
			return {};
		}

		// TODO: error check
		_file.seekg(pos);

		std::vector<uint8_t> chunk(size);
		const auto nread = _file.read(reinterpret_cast<char*>(chunk.data()), chunk.size()).gcount();
		if (nread != std::numeric_limits<std::streamsize>::max()) {
			chunk.resize(nread); // usually a noop
		} else {
			chunk.clear();
		}

		_bytes_read += chunk.size();

		return chunk;
	}

	// read only
	bool write(uint64_t, const std::vector<uint8_t>&) override { return false; }
};

