#pragma once

#include "./registry_message_model.hpp"

#include <entt/entity/registry.hpp>
#include <entt/entity/handle.hpp>
#include <entt/container/dense_map.hpp>

#include <memory>

class RegistryMessageModelImpl : public RegistryMessageModelI {
	protected:
		Contact3Registry& _cr;

		entt::dense_map<Contact3, std::unique_ptr<Message3Registry>> _contact_messages;

		bool _update_in_progess {false};
		std::vector<Message3Handle> _update_queue {};

	public:
		RegistryMessageModelImpl(Contact3Registry& cr) : _cr(cr) {}
		virtual ~RegistryMessageModelImpl(void) {}

		// TODO: iterate?

	public:
		Message3Registry* get(Contact3 c) override;
		Message3Registry* get(Contact3 c) const override;

	public: // dispatcher
		// !!! remember to manually throw these externally
		void throwEventConstruct(Message3Registry& reg, Message3 e) override;
		void throwEventUpdate(Message3Registry& reg, Message3 e) override;
		void throwEventDestroy(Message3Registry& reg, Message3 e) override;

		void throwEventConstruct(const Contact3 c, Message3 e) override;
		void throwEventUpdate(const Contact3 c, Message3 e) override;
		void throwEventDestroy(const Contact3 c, Message3 e) override;

	public: // mm3
		bool sendText(const Contact3 c, std::string_view message, bool action = false) override;
		bool sendFilePath(const Contact3 c, std::string_view file_name, std::string_view file_path) override;
};

