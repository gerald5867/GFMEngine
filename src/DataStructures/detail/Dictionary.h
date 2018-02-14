#pragma once
/*
#ifndef DICTIONARY_H
#define DICTIONARY_H
namespace gfm {
namespace detail {
	// !!! THIS CLASS IS ABSOLUTELY GARBAGE AT THE MOMENT IT DOES ALL ITS STUFF LINERALLY!!! //
	// !!! THIS WILL BE REPLACED IN THE FUTURE !!!!!!!!!!!!!!!!!!!!!!!! //

	template<typename KeyT, typename ValueT>
	struct KeyValuePair {
		KeyT key;
		ValueT value;

		bool operator == (const KeyValuePair<KeyT, ValueT>& other) {
			return other.key == key && value == other.value;
		}
	};

	template<typename KeyT, typename ValueT>
	class Dictionary {
		public:
			Dictionary() = default;
			Dictionary(utils::uint32 size) {

			}
		public:
			void Insert(KeyT&& key, ValueT&& value) {
				m_map.insert(std::make_pair(std::move(key), std::move(value));
			}

			bool Remove(KeyT&& key) {
				auto iter = m_map.erase(key);
				return iter != m_map.end();
			}

			KeyValuePair<KeyT, ValueT>& operator [](utils::uint32 index) {
				return m_map[index];
			}

			const KeyValuePair<KeyT, ValueT>& operator [](utils::uint32 index) const {
				return m_map[index];
			}

			utils::uint32 Length() const noexcept {
				return m_map.size();
			}

			
		private:
			utils::uint32 m_size;
			KeyValuePair m_data;
	};

}//detail
}//gfm

#endif // DICTIONARY_H
*/