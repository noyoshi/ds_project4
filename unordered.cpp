// unordered.cpp: Unordered Map

#include "map.h"

#include <algorithm>

// Methods --------------------------------------------------------------------

void            UnorderedMap::insert(const std::string &key, const std::string &value) {
    entries[key] = value;
}

const Entry     UnorderedMap::search(const std::string &key) {
    auto item = entries.find(key);
    if(item != entries.end())
        return *item;
    return NONE;
}

void            UnorderedMap::dump(std::ostream &os, DumpFlag flag) {
    for(auto it = entries.begin(); it != entries.end(); it++){
        switch (flag){
            case(DUMP_KEY):
                os << it->first << '\n';
                break;
            case(DUMP_VALUE):
                os <<  it->second << '\n';
                break;
            case(DUMP_KEY_VALUE):
                os << it->first << '\t' << it->second << '\n';
                break;
            case(DUMP_VALUE_KEY):
                os << it->second << '\t' << it->first << '\n';
                break;
        }
    }
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
