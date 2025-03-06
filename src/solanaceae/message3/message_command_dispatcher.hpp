#pragma once

#include <solanaceae/contact/fwd.hpp>
#include <solanaceae/message3/registry_message_model.hpp>

#include <deque>
#include <string>
#include <string_view>
#include <functional>
#include <unordered_map>

// fwd
struct ConfigModelI;

class MessageCommandDispatcher : public RegistryMessageModelEventI {
	ContactStore4I& _cs;
	RegistryMessageModelI& _rmm;
	ConfigModelI& _conf;

	public:
		static constexpr const char* version {"1"};

		enum Perms {
			BLACKLIST = 1 << 0,
			WHITELIST = 1 << 1,

			// can only be trumped by blacklist
			EVERYONE = 1 << 2,

			// can only be trumped by blacklist
			// TODO: replace with groups?
			ADMIN = 1 << 3,
			MODERATOR = 1 << 4,
		};

	private:
		struct Command {
			std::string m; // module
			std::string m_prefix; // module prefix (if any)
			std::string command; // command
			std::function<bool(std::string_view params, Message3Handle m)> fn;
			std::string help_text;

			Perms perms = Perms::ADMIN; // default to highest

			//Command(const Command&) = delete;
		};
		std::unordered_map<std::string, Command> _command_map;

		struct QueuedMessage {
			Contact4 to;
			std::string message;
		};
		std::deque<QueuedMessage> _message_queue;

		uint64_t _program_started_at {0};

	public:
		MessageCommandDispatcher(ContactStore4I& cs, RegistryMessageModelI& rmm, ConfigModelI& conf);
		~MessageCommandDispatcher(void);

		float iterate(float time_delta);

		// TODO: think more about permissions?
		//  - user(s)
		//  - group(s)
		//  - everyone else?

		void registerCommand(
			std::string_view m, // module
			std::string_view m_prefix, // module prefix (if any)
			std::string_view command, // command
			std::function<bool(std::string_view params, Message3Handle m)>&& fn,
			std::string_view help_text,
			Perms perms = Perms::ADMIN
		);

		// generates a help
		bool helpCommand(std::string_view params, Message3Handle m);

		bool hasPermission(const Command& cmd, const Contact4 contact);

	protected: // mm
		bool onEvent(const Message::Events::MessageConstruct& e) override;
		bool onEvent(const Message::Events::MessageUpdated& e) override;
};

