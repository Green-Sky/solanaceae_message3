#pragma once

#include <solanaceae/contact/fwd.hpp>
#include <solanaceae/object_store/fwd.hpp>

#include <entt/entity/registry.hpp>
#include <entt/entity/handle.hpp>

// TODO: move, rename, do something?, change in favor of tox?
//enum class FileKind : uint32_t {
	//file = 0u,
	//avatar = 1u,
//};

// interface to send messages
struct MessageModel3I {
	virtual ~MessageModel3I(void) {}

	// return true if a handler was found for the contact

	virtual bool sendText(const Contact4 c, std::string_view message, bool action = false) { (void)c,(void)message,(void)action; return false; }

	//virtual bool sendFile(const Contact& c, std::string_view file_name, std::unique_ptr<FileI> file) { (void)c,(void)message,(void)action; return false; }
	virtual bool sendFilePath(const Contact4 c, std::string_view file_name, std::string_view file_path) { (void)c,(void)file_name,(void)file_path; return false; }
	virtual bool sendFileObj(const Contact4 c, ObjectHandle o) { (void)c,(void)o; return false; } // ideal for forwarding, Obj is not copied!

	// we want this back :) - nope, obj only (not sorry)
	//virtual bool sendFileMem(const Contact& c, std::string_view file_name, const std::vector<uint8_t>& file) = 0;
};

