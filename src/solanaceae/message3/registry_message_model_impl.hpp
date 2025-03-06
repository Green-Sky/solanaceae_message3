#pragma once

#include "./registry_message_model.hpp"

#include <entt/container/dense_map.hpp>

#include <memory>

class RegistryMessageModelImpl : public RegistryMessageModelI {
	protected:
		ContactStore4I& _cs;

		entt::dense_map<Contact4, std::unique_ptr<Message3Registry>> _contact_messages;

		bool _update_in_progess {false};
		std::vector<Message3Handle> _update_queue {};

	public:
		RegistryMessageModelImpl(ContactStore4I& cs) : _cs(cs) {}
		virtual ~RegistryMessageModelImpl(void) {}

		// TODO: iterate?

	public:
		Message3Registry* get(Contact4 c) override;
		Message3Registry* get(Contact4 c) const override;

	public: // dispatcher
		// !!! remember to manually throw these externally
		void throwEventConstruct(Message3Registry& reg, Message3 e) override;
		void throwEventUpdate(Message3Registry& reg, Message3 e) override;
		void throwEventDestroy(Message3Registry& reg, Message3 e) override;

		void throwEventConstruct(const Contact4 c, Message3 e) override;
		void throwEventUpdate(const Contact4 c, Message3 e) override;
		void throwEventDestroy(const Contact4 c, Message3 e) override;

	public: // mm3
		bool sendText(const Contact4 c, std::string_view message, bool action = false) override;
		bool sendFilePath(const Contact4 c, std::string_view file_name, std::string_view file_path) override;
};

