#ifndef __LISTINDEXER_H__
#define __LISTINDEXER_H__

#include <list>
#include <unordered_map>

template <class Key, class T>
class ListIndexer
{
public:
    using key_type = Key;
    using mapped_type = T;
    using value_type = std::pair<Key, T>;
    using reference = value_type&;

    // Iterators
    decltype(auto) begin()
        { return _list.begin(); }
    decltype(auto) end()
        { return _list.end(); }
    decltype(auto) cbegin() const
        { return _list.cbegin(); }
    decltype(auto) cend() const
        { return _list.cend(); }

    // Capacity
    bool empty() const
        { return _list.empty(); }
    std::size_t size() const
        { return _list.size(); }
    
    // Modifiers
    void clear() noexcept
        { _list.clear(); _map.clear(); }
    reference emplace_back(const Key& key, const T& item);
    reference emplace_front(const Key& key, const T& item);

    // Lookup
    T& at(const Key& key)
        { return *_map.at(key); }
    const T& at(const Key& key) const
        { return *_map.at(key); }
    bool contains(const Key& key) const
        { return _map.contains(key); }
    

private:
    std::list<std::pair<Key, T>> _list;
    std::unordered_map<Key, T*> _map;
};



template <class Key, class T>
ListIndexer<Key, T>::reference ListIndexer<Key, T>::emplace_back(const Key& key, const T& item)
{
    reference ref = _list.emplace_back(key, item);
    _map.emplace(key, &ref.second);
    return ref;
}

template <class Key, class T>
ListIndexer<Key, T>::reference ListIndexer<Key, T>::emplace_front(const Key& key, const T& item)
{
    reference ref = _list.emplace_front(key, item);
    _map.emplace(key, &ref.second);
    return ref;
}

#endif
