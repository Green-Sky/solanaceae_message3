#pragma once

#include <solanaceae/util/event_provider.hpp>

#include "./message_model3.hpp"

#include <entt/entity/registry.hpp>
#include <entt/entity/handle.hpp>
#include <entt/container/dense_map.hpp>

#include <memory>

// strong typing
enum class Message3 : uint32_t {};
using Message3Registry = entt::basic_registry<Message3>;
using Message3Handle = entt::basic_handle<Message3Registry>;

namespace Message {

namespace Events {

	struct MessageConstruct {
		const Message3Handle e;
	};

	struct MessageUpdated {
		const Message3Handle e;
		// hint?
		// like component list?
	};

	struct MessageDestory {
		const Message3Handle e;
	};

} // Events

// get unix time in milliseconds
// TODO: move to util
uint64_t getTimeMS(void);

} // Message

enum class RegistryMessageModel_Event : uint32_t {
	message_construct,
	message_updated,
	message_destroy,

	send_text,
	send_file_path,

	MAX
};

// 2 in 1
struct RegistryMessageModelEventI : public MessageModel3I {
	using enumType = RegistryMessageModel_Event;

	virtual ~RegistryMessageModelEventI(void) {}

	virtual bool onEvent(const Message::Events::MessageConstruct&) { return false; }
	virtual bool onEvent(const Message::Events::MessageUpdated&) { return false; }
	virtual bool onEvent(const Message::Events::MessageDestory&) { return false; }

	// mm3
	// send text
	// send file path
};
using RegistryMessageModelEventProviderI = EventProviderI<RegistryMessageModelEventI>;

class RegistryMessageModel : public RegistryMessageModelEventProviderI, public MessageModel3I {
	protected:
		Contact3Registry& _cr;

		entt::dense_map<Contact3, std::unique_ptr<Message3Registry>> _contact_messages;

		bool _update_in_progess {false};
		std::vector<Message3Handle> _update_queue {};

	public:
		RegistryMessageModel(Contact3Registry& cr) : _cr(cr) {}
		virtual ~RegistryMessageModel(void) {}

		// TODO: iterate?

	public:
		Message3Registry* get(Contact3 c);
		Message3Registry* get(Contact3 c) const;

	public: // dispatcher
		// !!! remember to manually throw these externally
		void throwEventConstruct(Message3Registry& reg, Message3 e);
		void throwEventUpdate(Message3Registry& reg, Message3 e);
		void throwEventDestroy(Message3Registry& reg, Message3 e);

		void throwEventConstruct(Message3Handle h) { throwEventConstruct(*h.registry(), h.entity()); }
		void throwEventUpdate(Message3Handle h) { throwEventUpdate(*h.registry(), h.entity()); }
		void throwEventDestroy(Message3Handle h) { throwEventDestroy(*h.registry(), h.entity()); }

		void throwEventConstruct(const Contact3 c, Message3 e);
		void throwEventUpdate(const Contact3 c, Message3 e);
		void throwEventDestroy(const Contact3 c, Message3 e);

	public: // mm3
		bool sendText(const Contact3 c, std::string_view message, bool action = false) override;
		bool sendFilePath(const Contact3 c, std::string_view file_name, std::string_view file_path) override;
};

