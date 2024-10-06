#include "./registry_message_model.hpp"

#include <chrono>
#include <iostream>

uint64_t Message::getTimeMS(void) {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

