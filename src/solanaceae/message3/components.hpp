#pragma once

#include <solanaceae/contact/fwd.hpp>

#include "./message.hpp"

#include <solanaceae/object_store/fwd.hpp>

#include <entt/container/dense_map.hpp>

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>
#include <entt/entity/handle.hpp>

#include <string>

namespace Message::Components {

	struct ContactFrom {
		Contact4 c{entt::null};
	};

	struct ContactTo {
		Contact4 c{entt::null};
	};

	// best guess as to how this should be displayed in the global order
	struct Timestamp {
		uint64_t ts {0};
	};

	struct TimestampWritten {
		uint64_t ts {0};
	};

	// local start TODO: namespace ?
	struct TimestampProcessed {
		uint64_t ts {0};
	};

	struct TagUnread {};

	struct Read {
		// TODO: too much?
		uint64_t ts {0};
	};
	// local end

	// TODO: milliseconds sound excessive
	struct ReceivedBy {
		// Due to a lack of info with some protocols,
		// this is often the timestamp we heard they already have the message.
		entt::dense_map<Contact4, uint64_t> ts;
	};

	struct ReadBy {
		entt::dense_map<Contact4, uint64_t> ts;
	};

	// similar to ReceivedBy, but only set when they sent the message
	// (efficent protocols have 1 contact in here)
	struct SyncedBy {
		// ts is not updated once set
		entt::dense_map<Contact4, uint64_t> ts;
	};

	struct MessageText {
		std::string text;
		MessageText(void) = default;
		MessageText(const std::string& view) : text(view) {}
		MessageText(const std::string_view& view) : text(view) {}
	};

	struct TagMessageIsAction {};

	// points to the object providing the file for this message
	struct MessageFileObject {
		ObjectHandle o;
	};

#if 0
	namespace Transfer {

		//struct TransferState {
			//enum State {
				//running,
				//paused,
				//finished,
				//failed,
			//} state = paused;
		//};

		struct TagReceiving {};
		struct TagSending {};
		// TODO: add both?

		struct StateCanceled {
			enum Reason {
				disconnected,
				remote_canceld,
				local_canceld,
			} reason = disconnected;
		};

#if 0
		struct FileID {
			// persistent ID
			// sometimes called file_id or hash
			ToxKey id;
			// TODO: variable length
		};

		struct FileKind {
			// TODO: use tox file kind
			uint64_t kind {0};
		};
#endif

	} // Transfer
#endif

	// points to the front/newer message
	// together they define a range that is,
	// eg the first(end) and last(begin) message being eg. rendered
	// MFS requires there to be atleast one other fragment after/before,
	// if not loaded fragment with fitting tsrange(direction) available
	// uses fragmentAfter/Before()
	// they can exist standalone (wip)
	// if they are a pair, the inside is filled first
	struct ViewCurserBegin {
		Message3 curser_end{entt::null};
	};
	struct ViewCurserEnd {
		Message3 curser_begin{entt::null};
	};

} // Message::Components

#include "./components_id.inl"

