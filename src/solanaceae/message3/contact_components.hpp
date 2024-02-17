#pragma once

#include <solanaceae/message3/registry_message_model.hpp>

#include <functional>

namespace Contact::Components {

	struct MessageIsSame {
		std::function<bool(Message3Handle lh, Message3Handle rh)> comp;
	};

} // Contact::Components

