add_library(solanaceae_message3
	./solanaceae/message3/message.hpp
	./solanaceae/message3/components.hpp
	./solanaceae/message3/components_id.inl

	./solanaceae/message3/message_model3.hpp

	./solanaceae/message3/registry_message_model.hpp
	./solanaceae/message3/registry_message_model.cpp
	./solanaceae/message3/registry_message_model_impl.hpp
	./solanaceae/message3/registry_message_model_impl.cpp

	./solanaceae/message3/contact_components.hpp

	./solanaceae/message3/message_time_sort.hpp
	./solanaceae/message3/message_time_sort.cpp

	./solanaceae/message3/message_command_dispatcher.hpp
	./solanaceae/message3/message_command_dispatcher.cpp
)

target_include_directories(solanaceae_message3 PUBLIC .)
target_compile_features(solanaceae_message3 PUBLIC cxx_std_17)
target_link_libraries(solanaceae_message3 PUBLIC
	solanaceae_util
	solanaceae_contact
	solanaceae_object_store # for fwd.hpp
	EnTT::EnTT
)

