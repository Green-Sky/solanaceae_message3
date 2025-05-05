#pragma once

#include <solanaceae/util/event_provider.hpp>

#include "./message.hpp"
#include "./message_model3.hpp"

#include <entt/entity/registry.hpp>
#include <entt/entity/handle.hpp>

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

} // Message

enum class RegistryMessageModel_Event : uint32_t {
	message_construct,
	message_updated,
	message_destroy,

	//???
	send_text,
	send_file_path,
	send_file_obj,

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
	// send file obj
};
using RegistryMessageModelEventProviderI = EventProviderI<RegistryMessageModelEventI>;

class RegistryMessageModelI : public RegistryMessageModelEventProviderI, public MessageModel3I {
	public:
		static constexpr const char* version {"5"};

	// rmm interface
	public:
		virtual Message3Registry* get(Contact4 c) = 0;
		virtual Message3Registry* get(Contact4 c) const = 0;

	public: // dispatcher
		// !!! remember to manually throw these externally
		virtual void throwEventConstruct(Message3Registry& reg, Message3 e) = 0;
		virtual void throwEventUpdate(Message3Registry& reg, Message3 e) = 0;
		virtual void throwEventDestroy(Message3Registry& reg, Message3 e) = 0;

		void throwEventConstruct(Message3Handle h) { throwEventConstruct(*h.registry(), h.entity()); }
		void throwEventUpdate(Message3Handle h) { throwEventUpdate(*h.registry(), h.entity()); }
		void throwEventDestroy(Message3Handle h) { throwEventDestroy(*h.registry(), h.entity()); }

		virtual void throwEventConstruct(const Contact4 c, Message3 e) = 0;
		virtual void throwEventUpdate(const Contact4 c, Message3 e) = 0;
		virtual void throwEventDestroy(const Contact4 c, Message3 e) = 0;
};

template<>
struct std::hash<Message3Handle> {
	std::size_t operator()(Message3Handle const& m) const noexcept {
		const std::size_t h1 = reinterpret_cast<std::size_t>(m.registry());
		const std::size_t h2 = entt::to_integral(m.entity());
		return (h1 << 3) ^ (h2 * 11400714819323198485llu);
	}
};

