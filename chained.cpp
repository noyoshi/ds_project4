// chained.cpp: Separate Chaining Map

#include "map.h"

#include <stdexcept>


ChainedMap::ChainedMap(){
    hash_table = new std::map<std::string, std::string>[1<<10];
    table_size = 1<<10;
    nitems = 0;
    load_factor = 0;
}

ChainedMap::~ChainedMap(){
    delete[] hash_table;
}

// Methods --------------------------------------------------------------------

void            ChainedMap::insert(const std::string &key, const std::string &value) {
    size_t hash_key = hash_function(key) % table_size;
    auto bucket = hash_table + sizeof(*hash_table) * hash_key;
    (*bucket)[key] = value;

    load_factor = ++nitems / (double) table_size;

    if (load_factor > DEFAULT_LOAD_FACTOR){
        table_size = table_size * 2;
        // Segfaults here?
        resize(table_size);
        load_factor = nitems / table_size;
    }

    /*
    0: map = {'noah': 'danica', 'tim' : 'sami's girlfriend who likes musicals'}
    1: map = {}
    2: map = {}
    3:
    4:
    */
}

const Entry     ChainedMap::search(const std::string &key) {
    size_t hash_key = hash_function(key) % table_size;
    auto bucket = hash_table + (sizeof(*hash_table) * hash_key);
    if(bucket->empty()) return NONE;

    auto   it = bucket->find(key);
    if(it != bucket->end()) return *it;

    if(bucket->size() == 1) {
        if(it->first == key){
            return *it;
        }
    }

    return NONE;
}

void            ChainedMap::dump(std::ostream &os, DumpFlag flag) {
    for(size_t i = 0; i < table_size; i ++){
        auto bucket = hash_table + (sizeof(*hash_table) * i);
        for(auto it = bucket->begin(); it !=bucket->end(); it++){
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
}

void            ChainedMap::resize(const size_t new_size) {
    auto old_size = table_size;
    auto old_table = hash_table;

    hash_table = new std::map<std::string, std::string>[new_size];
    table_size = new_size;

    load_factor = ++nitems / new_size;

    for(size_t i = 0; i < old_size; i ++){
        auto bucket = hash_table + (sizeof(*hash_table) * i);
        for(auto it = bucket->begin(); it != bucket->end(); it++){
            insert(it->first, it->second);
        }
    }
    delete[] old_table;
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
