 // open.cpp: Open Addressing Map

#include "map.h"
#include "utility"

#include <stdexcept>

// If you are bored try figuring this message out ^_^
// Ly8gICAgICAgICAgICAgIF9fICAgICANCi8vICAod29vZikgLS0gPChvIClfX18gDQovLyAgICAgICAgICAgICAoIC5fPiAvIA0KLy8gICAgICAgICAgICAgIGAtLS0nICAg 

OpenMap::OpenMap(){
    hash_table = new Entry [DEFAULT_TABLE_SIZE];
    table_size = DEFAULT_TABLE_SIZE;
    nitems = 0;
    load_factor = 0;
    load_limit = DEFAULT_LOAD_FACTOR; 
    for(size_t i = 0; i < table_size; i ++){
        // Initialzes everything to NONE 
        hash_table[i] = NONE; 
    }
}

// Initialized with values
OpenMap::OpenMap(double limit){ 
    hash_table = new Entry [DEFAULT_TABLE_SIZE];
    table_size = DEFAULT_TABLE_SIZE;
    nitems = 0;
    load_factor = 0;
    load_limit = limit; 
    for(size_t i = 0; i < table_size; i ++){
        // Initialzes everything to NONE 
        hash_table[i] = NONE; 
    } 
}

OpenMap::OpenMap(double limit, size_t sz){
    hash_table = new Entry [sz];
    table_size = sz;
    nitems = 0;
    load_factor = 0; 
    load_limit = limit; 
    for(size_t i = 0; i < table_size; i ++){
        // Initialzes everything to NONE 
        hash_table[i] = NONE; 
    }
}

OpenMap::~OpenMap(){
    delete[] hash_table;
}
// Methods --------------------------------------------------------------------

void OpenMap::insert(const std::string &key, const std::string &value) {
    size_t hash_key = locate(key); 
    hash_table[hash_key] = std::make_pair(key, value);
    
    // Calculates the load factor 
    load_factor = ((double) ++nitems) / ((double) table_size);

    if (load_factor > load_limit)
        resize(table_size * 2);
}

const Entry OpenMap::search(const std::string &key) {
    size_t i = locate(key); 
    
    if(hash_table[i].first == key) return hash_table[i]; 

    return NONE;
}

void OpenMap::dump(std::ostream &os, DumpFlag flag) {
    for(size_t i = 0; i < table_size; i ++){
        if(hash_table[i] != NONE) {
            switch (flag){
                case(DUMP_KEY):
                    os << hash_table[i].first << '\n';
                    break;
                case(DUMP_VALUE):
                    os << hash_table[i].second << '\n';
                    break;
                case(DUMP_KEY_VALUE):
                    os << hash_table[i].first << '\t' << hash_table[i].second << '\n';
                    break;
                case(DUMP_VALUE_KEY):
                    os << hash_table[i].second << '\t' << hash_table[i].first << '\n';
                    break;
            }
        }
    }
    
}

size_t OpenMap::locate(const std::string &key) {
    // Returns the index where a key is stored 
    size_t hash_key = hash_function(key) % table_size;

    while(hash_table[hash_key] != NONE){
        // Found the key you were looking for 
        if(hash_table[hash_key].first == key) return hash_key;  
        
        hash_key ++; 
        if(hash_key >= table_size) hash_key = 0; 
    }

    // Otherwise we found the next NONE contining bucket, returns that index 
    return hash_key;
}

void OpenMap::resize(const size_t new_size) {
    size_t old_size = table_size; 
    table_size = new_size;
    
    load_factor = ((double) nitems) / ((double) table_size);
    
    auto old_table = hash_table;
    hash_table = new Entry [table_size];

    // Initialzes everything in the table to NONE 
    for(size_t i = 0; i < table_size; i ++)
        hash_table[i] = NONE; 

    for(size_t i = 0; i < old_size; i ++){
        if(old_table[i] != NONE)
            insert(old_table[i].first, old_table[i].second);
    }

    delete[] old_table;
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
