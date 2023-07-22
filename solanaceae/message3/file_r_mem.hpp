#pragma once

#include "./file.hpp"

struct FileRMem : public FileI {
	std::vector<uint8_t> _data;

	FileRMem(void) = delete;
	FileRMem(const std::vector<uint8_t>& data) : _data(data) {
		_file_size = _data.size();
	}
	virtual ~FileRMem(void) {}

	bool isGood(void) override {
		return true;
	}

	std::vector<uint8_t> read(uint64_t pos, uint32_t size) override {
		if (_file_size > 0 && pos >= _data.size()) {
			return {};
		}

		// TODO: optimize
		std::vector<uint8_t> chunk;
		for (size_t i = 0; i < size && i+pos < _data.size(); i++) {
			chunk.push_back(_data[pos+i]);
		}
		//chunk.insert(chunk.begin(), _data.cbegin()+pos, _data.cbegin()+pos+size);

		_bytes_read += chunk.size();

		return chunk;
	}

	// read only
	bool write(uint64_t, const std::vector<uint8_t>&) override { return false; }
};

