#include "lrucache.h"

#include <iostream>

LRUCache::LRUCache(size_t maxLen)
    : m_maxLen(maxLen)
{
    if (m_maxLen <= 0)
    {
        std::cerr << "Invalid cache size, resetting to size: 1";
        m_maxLen = maxLen;
    }
}

void LRUCache::add(const int &key, const int &val)
{
    if (m_cache.contains(key))
    {
        m_cache[key]->second = val;
        m_list.splice(m_list.begin(), m_list, m_cache[key]);
        return;
    }
    m_list.push_front({key, val});
    m_cache[key] = m_list.begin();
    if (m_list.size() > m_maxLen)
    {
        auto last = std::prev(m_list.end());
        m_cache.erase(last->first);
        m_list.pop_back();
    }
}

int LRUCache::get(const int &key)
{
    if (!m_cache.contains(key))
        return -1;

    m_list.splice(m_list.begin(), m_list, m_cache[key]);

    return m_list.front().second;
}
