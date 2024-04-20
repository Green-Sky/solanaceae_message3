#pragma once

#include "./components.hpp"

#include <entt/core/type_info.hpp>

// TODO: move more central
#define DEFINE_COMP_ID(x) \
template<> \
constexpr entt::id_type entt::type_hash<x>::value() noexcept { \
	using namespace entt::literals; \
	return #x##_hs; \
} \
template<> \
constexpr std::string_view entt::type_name<x>::value() noexcept { \
	return #x; \
}

// cross compile(r) stable ids

DEFINE_COMP_ID(Message::Components::ContactFrom)
DEFINE_COMP_ID(Message::Components::ContactTo)
DEFINE_COMP_ID(Message::Components::Timestamp)
DEFINE_COMP_ID(Message::Components::TimestampProcessed)
DEFINE_COMP_ID(Message::Components::TimestampWritten)
DEFINE_COMP_ID(Message::Components::TagUnread)
DEFINE_COMP_ID(Message::Components::Read)
DEFINE_COMP_ID(Message::Components::ReceivedBy)
DEFINE_COMP_ID(Message::Components::ReadBy)
DEFINE_COMP_ID(Message::Components::SyncedBy)
DEFINE_COMP_ID(Message::Components::MessageText)
DEFINE_COMP_ID(Message::Components::TagMessageIsAction)

DEFINE_COMP_ID(Message::Components::Transfer::TagHaveAll)
DEFINE_COMP_ID(Message::Components::Transfer::BytesSent)
DEFINE_COMP_ID(Message::Components::Transfer::BytesReceived)
DEFINE_COMP_ID(Message::Components::Transfer::File)
DEFINE_COMP_ID(Message::Components::Transfer::TagReceiving)
DEFINE_COMP_ID(Message::Components::Transfer::TagSending)
DEFINE_COMP_ID(Message::Components::Transfer::TagPaused)
DEFINE_COMP_ID(Message::Components::Transfer::StateCanceled)
DEFINE_COMP_ID(Message::Components::Transfer::FileInfo)
DEFINE_COMP_ID(Message::Components::Transfer::FileInfoLocal)
DEFINE_COMP_ID(Message::Components::Transfer::ActionAccept)

#undef DEFINE_COMP_ID

