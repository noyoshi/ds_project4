// chained.cpp: Separate Chaining Map

#include "map.h"
#include <vector>

#include <stdexcept>

//              __
//  (woof) -- <(o )___
//             ( ._> /
//              `---'   

ChainedMap::ChainedMap(){
    hash_table = new std::map<std::string, std::string>[DEFAULT_TABLE_SIZE];
    table_size = DEFAULT_TABLE_SIZE;
    nitems = 0;
    load_limit = DEFAULT_LOAD_FACTOR;
    load_factor = 0;
}

// Initialized with values 
ChainedMap::ChainedMap(double limit){ 
    hash_table = new std::map<std::string, std::string>[DEFAULT_TABLE_SIZE];
    table_size = DEFAULT_TABLE_SIZE;
    nitems = 0;
    load_limit = limit;
    load_factor = 0;  
}

// Initializes with custom load limit and custom size 
ChainedMap::ChainedMap(double limit, size_t sz){
    hash_table = new std::map<std::string, std::string>[sz];
    table_size = sz;
    nitems = 0;
    load_limit = limit; 
    load_factor = 0;
}

ChainedMap::~ChainedMap(){
    delete[] hash_table;
}

// Methods --------------------------------------------------------------------

void            ChainedMap::insert(const std::string &key, const std::string &value) {
    size_t hash_key = hash_function(key) % table_size;
    hash_table[hash_key][key] = value;    

    load_factor = ((double) ++nitems) / ((double) table_size);

    if (load_factor > load_limit)
        resize(table_size * 2);
}

const Entry     ChainedMap::search(const std::string &key) {
    size_t hash_key = hash_function(key) % table_size;

    // Bucket corresponding to the key is empty 
    if(hash_table[hash_key].empty()) return NONE;

    // Finding if the key is in that bucket 
    auto   it = hash_table[hash_key].find(key);
    if(it != hash_table[hash_key].end()) return *it;

    return NONE;
}

void            ChainedMap::dump(std::ostream &os, DumpFlag flag) {
    for(size_t i = 0; i < table_size; i ++){
        for(auto it = hash_table[i].begin(); it !=hash_table[i].end(); it++){
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
    size_t old_size = table_size;
    table_size = new_size;
    
    load_factor = ((double) nitems) / ((double) table_size);

    auto old_table = hash_table;
    hash_table = new std::map<std::string, std::string>[table_size];

    // Copies over values from the old table into the new table 
    for(size_t i = 0; i < old_size; i ++){
        for(auto it = old_table[i].begin(); it != old_table[i].end(); it++){
            insert(it->first, it->second);
        }
    }

    delete[] old_table;
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
