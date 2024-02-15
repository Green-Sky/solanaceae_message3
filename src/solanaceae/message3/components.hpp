#pragma once

#include <solanaceae/contact/contact_model3.hpp>

//fwd
struct FileI;

#include <entt/container/dense_map.hpp>

#include <memory>
#include <string>
#include <vector>

namespace Message::Components {

	struct ContactFrom {
		Contact3 c;
	};

	struct ContactTo {
		Contact3 c;
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

	namespace Remote {
		// TODO: milliseconds sound excessive

		struct TimestampReceived {
			// Due to a lack of info with most protocols,
			// this is often the timestamp we heard they already have the message.
			entt::dense_map<Contact3, uint64_t> ts;
		};

		struct TimestampRead {
			// Due to a lack of info with most protocols,
			// this is often the timestamp we heard they have read it the message.
			entt::dense_map<Contact3, uint64_t> ts;
		};

	} // Remote

	struct SyncedBy {
		// ts is not updated once set
		entt::dense_map<Contact3, uint64_t> ts;
	};

	struct MessageText {
		std::string text;
		MessageText(const std::string& view) : text(view) {}
		MessageText(const std::string_view& view) : text(view) {}
	};

	struct TagMessageIsAction {};

	namespace Transfer {

		//struct TransferState {
			//enum State {
				//running,
				//paused,
				//finished,
				//failed,
			//} state = paused;
		//};
		struct TagHaveAll {};

		struct BytesSent {
			uint64_t total {0u};
		};

		struct BytesReceived {
			uint64_t total {0u};
		};

		// TODO: rename to stream?
		using File = std::unique_ptr<FileI>;

		struct TagReceiving {};
		struct TagSending {};
		// TODO: add both?

		// convert to enum?
		// TODO: local/remote
		// TODO: invert?
		struct TagPaused {};

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

		struct FileInfo {
			struct FileDirEntry {
				std::string file_name; // full path relative to base
				uint64_t file_size {0};
			};
			std::vector<FileDirEntry> file_list;
			uint64_t total_size {0};
		};

		// describes the files locally
		// filename might be different to non local FileInfo
		// order is the same
		struct FileInfoLocal {
			std::vector<std::string> file_list;
		};

		// TODO: rename to start? or set or ...
		struct ActionAccept {
			std::string save_to_path;
			bool path_is_file = false; // if the path is not the folder to place the file into, overwrites the name
		};

	} // Transfer

} // Message::Components

#include "./components_id.inl"

