#pragma once

#include <cstdint>
#include <vector>

struct FileI {
	uint64_t _file_size {0};
	// TODO: remove?
	uint64_t _bytes_read {0};
	uint64_t _bytes_written {0};

	virtual ~FileI(void) {}

	virtual bool isGood(void) = 0;

	// TODO: move to owning/nonowning pointers
	virtual std::vector<uint8_t> read(uint64_t pos, uint32_t size) = 0;
	virtual bool write(uint64_t pos, const std::vector<uint8_t>& data) = 0;
};

