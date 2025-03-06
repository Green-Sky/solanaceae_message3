#include "./registry_message_model_impl.hpp"

#include <solanaceae/contact/components.hpp>
#include <solanaceae/contact/contact_store_i.hpp>

#include <iostream>

Message3Registry* RegistryMessageModelImpl::get(Contact4 c) {
	const auto& reg = _cs.registry();
	if (reg.valid(c) && !reg.all_of<Contact::Components::TagBig>(c)) {
		// TODO: loop upwards
		if (!reg.all_of<Contact::Components::Parent>(c)) {
			return nullptr;
		}
		c = reg.get<Contact::Components::Parent>(c).parent;
	}

	if (!reg.valid(c)) {
		// TODO: throw error
		return nullptr;
	}

	const auto it = _contact_messages.find(c);
	if (it != _contact_messages.end()) {
		return it->second.get();
	}

	auto& reg_sh = _contact_messages[c] = std::make_unique<Message3Registry>();
	reg_sh->ctx().emplace<Contact4>(c);
	return reg_sh.get();
}

Message3Registry* RegistryMessageModelImpl::get(Contact4 c) const {
	const auto& reg = _cs.registry();
	if (reg.valid(c) && !reg.all_of<Contact::Components::TagBig>(c)) {
		// TODO: loop upwards
		if (!reg.all_of<Contact::Components::Parent>(c)) {
			return nullptr;
		}
		c = reg.get<Contact::Components::Parent>(c).parent;
	}

	if (!reg.valid(c)) {
		// TODO: throw error
		return nullptr;
	}

	const auto it = _contact_messages.find(c);
	if (it != _contact_messages.cend()) {
		return it->second.get();
	}

	return nullptr;
}

void RegistryMessageModelImpl::throwEventConstruct(Message3Registry& reg, Message3 e) {
	std::cout << "RMM debug: event construct " << entt::to_integral(e) << "\n";
	dispatch(
		RegistryMessageModel_Event::message_construct,
		Message::Events::MessageConstruct{
			Message3Handle{reg, e}
		}
	);
}

void RegistryMessageModelImpl::throwEventUpdate(Message3Registry& reg, Message3 e) {
	// the update while update lock is hacky
	_update_queue.push_back({reg, e});
	if (!_update_in_progess) {
		_update_in_progess = true;
		for (size_t i = 0; i < _update_queue.size(); i++) {
			// WAY too spammy
			//std::cout << "RMM debug: event update " << entt::to_integral(e) << "\n";
			dispatch(
				RegistryMessageModel_Event::message_updated,
				Message::Events::MessageUpdated{
					_update_queue.at(i)
				}
			);
		}
		_update_queue.clear();
		_update_in_progess = false;
	}
}

void RegistryMessageModelImpl::throwEventDestroy(Message3Registry& reg, Message3 e) {
	std::cout << "RMM debug: event destroy " << entt::to_integral(e) << "\n";
	dispatch(
		RegistryMessageModel_Event::message_destroy,
		Message::Events::MessageDestory{
			Message3Handle{reg, e}
		}
	);
}

void RegistryMessageModelImpl::throwEventConstruct(const Contact4 c, Message3 e) {
	if (auto* reg_ptr = get(c); reg_ptr) {
		throwEventConstruct(*reg_ptr, e);
	}
}

void RegistryMessageModelImpl::throwEventUpdate(const Contact4 c, Message3 e) {
	if (auto* reg_ptr = get(c); reg_ptr) {
		throwEventUpdate(*reg_ptr, e);
	}
}

void RegistryMessageModelImpl::throwEventDestroy(const Contact4 c, Message3 e) {
	if (auto* reg_ptr = get(c); reg_ptr) {
		throwEventDestroy(*reg_ptr, e);
	}
}

bool RegistryMessageModelImpl::sendText(const Contact4 c, std::string_view message, bool action) {
	std::cout << "RMM debug: event send text\n";

	// manual, bc its not an "event"
	for (auto* zei : _subscribers.at(size_t(RegistryMessageModel_Event::send_text))) {
		if (zei->sendText(c, message, action)) {
			return true;
		}
	}

	std::cerr << "RMM error: event send text unhandled\n";

	return false;
}

bool RegistryMessageModelImpl::sendFilePath(const Contact4 c, std::string_view file_name, std::string_view file_path) {
	std::cout << "RMM debug: event send file path\n";

	// manual, bc its not an "event"
	for (auto* zei : _subscribers.at(size_t(RegistryMessageModel_Event::send_file_path))) {
		if (zei->sendFilePath(c, file_name, file_path)) {
			return true;
		}
	}

	std::cerr << "RMM error: event send file path unhandled\n";

	return false;
}

