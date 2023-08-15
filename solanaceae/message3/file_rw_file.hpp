#pragma once

#include "./file.hpp"

#include <fstream>
#include <limits>

struct FileRWFile : public FileI {
	std::fstream _file;

	//FileWFile(std::string_view file_path, uint64_t file_size) : _file(static_cast<std::string>(file_path), std::ios::binary) {
		//_file_size = file_size;

		//if (!_file.is_open()) {
			//return; // TODO: error
		//}
	//}

	virtual ~FileRWFile(void) {}

	bool isGood(void) override {
		return _file.is_open() && _file.good();
	}

	std::vector<uint8_t> read(uint64_t pos, uint32_t size) override {
		if (pos >= _file_size) {
			return {};
		}

		// TODO: error check
		_file.seekg(pos);

#if 0
		std::vector<uint8_t> chunk;
		int read_char;
		for (size_t i = 0; i < size && (_file_size == 0 || i+pos < _file_size) && (read_char = _file.get()) != std::ifstream::traits_type::eof(); i++) {
			chunk.push_back(read_char);
		}
#else
		std::vector<uint8_t> chunk(size);
		const auto nread = _file.read(reinterpret_cast<char*>(chunk.data()), chunk.size()).gcount();
		if (nread != std::numeric_limits<std::streamsize>::max()) {
			chunk.resize(nread); // usually a noop
		} else {
			chunk.clear();
		}
#endif

		_bytes_read += chunk.size();

		return chunk;
	}

	bool write(uint64_t pos, const std::vector<uint8_t>& data) override {
		if (pos >= _file_size) {
			return false;
		}

		// if out-of-order, seek
		if (_file.tellp() != int64_t(pos)) {
			// TODO: error check
			_file.seekp(pos);
		}

		_file.write(reinterpret_cast<const char*>(data.data()), data.size());

		return _file.good();
	}
};

