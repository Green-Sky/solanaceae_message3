cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(solanaceae)

add_library(solanaceae_message3
	./solanaceae/message3/file.hpp
	./solanaceae/message3/file_r_mem.hpp
	./solanaceae/message3/file_r_file.hpp
	./solanaceae/message3/file_w_file.hpp
	./solanaceae/message3/file_rw_file.hpp

	./solanaceae/message3/components.hpp
	./solanaceae/message3/components_id.inl

	./solanaceae/message3/message_model3.hpp

	./solanaceae/message3/registry_message_model.hpp
	./solanaceae/message3/registry_message_model.cpp

	./solanaceae/message3/message_time_sort.hpp
	./solanaceae/message3/message_time_sort.cpp
)

target_include_directories(solanaceae_message3 PUBLIC .)
target_compile_features(solanaceae_message3 PUBLIC cxx_std_17)
target_link_libraries(solanaceae_message3 PUBLIC
	solanaceae_util
	solanaceae_contact
	EnTT::EnTT
)

