#pragma once

#include "./file.hpp"

#include <fstream>

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

	std::vector<uint8_t> read(uint64_t pos, uint32_t size) override {
		if (_file_size > 0 && pos >= _file_size) {
			return {};
		}

		// TODO: error check
		_file.seekg(pos);

		// TODO: optimize
		std::vector<uint8_t> chunk;
		int read_char;
		for (size_t i = 0; i < size && (_file_size == 0 || i+pos < _file_size) && (read_char = _file.get()) != std::ifstream::traits_type::eof(); i++) {
			chunk.push_back(read_char);
		}

		_bytes_read += chunk.size();

		return chunk;
	}

	// read only
	bool write(uint64_t, const std::vector<uint8_t>&) override { return false; }
};

