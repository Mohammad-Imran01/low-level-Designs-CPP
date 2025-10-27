#pragma once

#include <list>
#include <unordered_map>
#include <utility>

class LRUCache
{
public:
    LRUCache(size_t maxLen);
    void add(const int &key, const int &val);
    int get(const int &key);

private:
    size_t m_maxLen;
    std::list<std::pair<int, int>> m_list;
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> m_cache;
};