#pragma once

#include "./registry_message_model.hpp"

#include <entt/container/dense_set.hpp>

class MessageTimeSort : public RegistryMessageModelEventI {
	RegistryMessageModelI& _rmm;

	// TODO: use contact instead
	entt::dense_set<Message3Registry*> _to_sort;

	public:
		MessageTimeSort(RegistryMessageModelI& rmm);

		// do the sorting
		void iterate(void);

	protected: // mm
		bool onEvent(const Message::Events::MessageConstruct& e) override;
		bool onEvent(const Message::Events::MessageUpdated& e) override;
		bool onEvent(const Message::Events::MessageDestory& e) override;
};

