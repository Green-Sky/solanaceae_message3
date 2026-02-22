#pragma once

#include <solanaceae/message3/registry_message_model.hpp>

#include <functional>

namespace Contact::Components {

	struct MessageIsSame {
		std::function<bool(Message3Handle lh, Message3Handle rh)> comp;
	};

	struct MessageLengths {
		// if message is split, how small do we need to go to not get split
		uint64_t max_atomic {0};

		// the longest a message can be so that the mm can handle it
		uint64_t max_extended {0};
	};

} // Contact::Components

#include "./contact_components_id.inl"

