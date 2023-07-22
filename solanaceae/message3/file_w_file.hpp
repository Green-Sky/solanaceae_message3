#pragma once

#include "./file.hpp"

#include <string_view>
#include <fstream>

struct FileWFile : public FileI {
	std::ofstream _file;

	FileWFile(std::string_view file_path, uint64_t file_size) : _file(static_cast<std::string>(file_path), std::ios::binary) {
		_file_size = file_size;

		if (!_file.is_open()) {
			return; // TODO: error
		}
	}

	virtual ~FileWFile(void) {}

	bool isGood(void) override {
		return _file.is_open() && _file.good();
	}

	// write only
	std::vector<uint8_t> read(uint64_t, uint32_t) override { return {}; }

	bool write(uint64_t pos, const std::vector<uint8_t>& data) override {
		if (_file_size > 0 && pos >= _file_size) {
			return false;
		}

		// if out-of-order, seek
		if (_file.tellp() != int64_t(pos)) {
			// TODO: error check
			_file.seekp(pos);
		}

		_file.write(reinterpret_cast<const char*>(data.data()), data.size());

		_bytes_written += data.size();

		return _file.good();
	}
};

