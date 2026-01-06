cmake_minimum_required(VERSION 3.18...3.24 FATAL_ERROR)

include(FetchContent)

if (NOT TARGET solanaceae_contact)
	FetchContent_Declare(solanaceae_contact
		GIT_REPOSITORY https://github.com/Green-Sky/solanaceae_contact.git
		GIT_TAG master
		EXCLUDE_FROM_ALL
	)
	FetchContent_MakeAvailable(solanaceae_contact)
endif()

if (NOT TARGET solanaceae_util)
	FetchContent_Declare(solanaceae_util
		GIT_REPOSITORY https://github.com/Green-Sky/solanaceae_util.git
		GIT_TAG master
		EXCLUDE_FROM_ALL
	)
	FetchContent_MakeAvailable(solanaceae_util)
endif()

if (NOT TARGET solanaceae_object_store)
	FetchContent_Declare(solanaceae_object_store
		GIT_REPOSITORY https://github.com/Green-Sky/solanaceae_object_store.git
		GIT_TAG master
		EXCLUDE_FROM_ALL
	)
	FetchContent_MakeAvailable(solanaceae_object_store)
endif()

