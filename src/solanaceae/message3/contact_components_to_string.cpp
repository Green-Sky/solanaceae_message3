#include "./contact_components_to_string.hpp"

#include "./contact_components.hpp"

#include <entt/entity/registry.hpp>
#include <entt/entity/handle.hpp>

#include <string>

namespace Contact {

void registerMessageComponents2Str(ContactStore4I& cs) {
	cs.registerComponentToString(
		entt::type_id<Contact::Components::MessageIsSame>().hash(),
		+[](ContactHandle4 c, bool) -> std::string {
			return "";
		},
		"Message",
		"IsSame",
		entt::type_id<Contact::Components::MessageIsSame>().name(),
		true
	);

	cs.registerComponentToString(
		entt::type_id<Contact::Components::MessageLengths>().hash(),
		+[](ContactHandle4 c, bool) -> std::string {
			const auto& comp = c.get<Contact::Components::MessageLengths>();
			return "max_atomic:" + std::to_string(comp.max_atomic) + ",max_extended:" + std::to_string(comp.max_extended);
		},
		"Message",
		"Lengths",
		entt::type_id<Contact::Components::MessageLengths>().name(),
		true
	);
}

} // Contact
