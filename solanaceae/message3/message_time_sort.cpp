#include "./message_time_sort.hpp"

#include <solanaceae/registry_message_model/components.hpp>

MessageTimeSort::MessageTimeSort(RegistryMessageModel& rmm) : _rmm(rmm) {
	_rmm.subscribe(this, RegistryMessageModel_Event::message_construct);
	_rmm.subscribe(this, RegistryMessageModel_Event::message_updated);
}

void MessageTimeSort::iterate(void) {
	// TODO: maybe only every x for updated
	for (auto* reg : _to_sort) {
		reg->sort<Message::Components::Timestamp>([](const auto& lhs, const auto& rhs) -> bool {
			return lhs.ts < rhs.ts;
		}, entt::insertion_sort{});
	}
	_to_sort.clear();
}

bool MessageTimeSort::onEvent(const Message::Events::MessageConstruct& e) {
	_to_sort.emplace(e.e.registry());
	return false;
}

bool MessageTimeSort::onEvent(const Message::Events::MessageUpdated& e) {
	_to_sort.emplace(e.e.registry());
	return false;
}

