// map.h

#pragma once

// Includes --------------------------------------------------------------------

#include <iostream>
#include <functional>
#include <map>
#include <unordered_map>
#include <string>
#include <utility>
#include <vector>

//              __     
//  (woof) -- <(o )___ 
//             ( ._> / 
//              `---'   

// Type definitions ------------------------------------------------------------

typedef enum {
    DUMP_KEY,
    DUMP_VALUE,
    DUMP_KEY_VALUE,
    DUMP_VALUE_KEY,
} DumpFlag;

typedef std::pair<std::string, std::string> Entry;
typedef std::hash<std::string>              StringHasher;

// Constants -------------------------------------------------------------------

extern const Entry  NONE;
extern const double DEFAULT_LOAD_FACTOR;
extern const size_t DEFAULT_TABLE_SIZE;

// Structures ------------------------------------------------------------------

struct Node {
    Entry entry;
    int   priority;
    Node *left;
    Node *right;

    ~Node() {
        delete left;
        delete right;
    }
};

// Classes ---------------------------------------------------------------------

class Map {
public:
    virtual void            insert(const std::string &key, const std::string &value) {}
    virtual const Entry     search(const std::string &key) { return NONE; }
    virtual void            dump(std::ostream &os, DumpFlag flag) {}
    virtual                ~Map() {}
};

class UnsortedMap : public Map {
public:
            void            insert(const std::string &key, const std::string &value);
            const Entry     search(const std::string &key);
            void            dump(std::ostream &os, DumpFlag flag);
private:
            std::vector<Entry>    entries;
};

class SortedMap : public Map {
public:
            void            insert(const std::string &key, const std::string &value);
            const Entry     search(const std::string &key);
            void            dump(std::ostream &os, DumpFlag flag);
private:
            std::vector<Entry>    entries;
};

class BSTMap : public Map {
public:
            void            insert(const std::string &key, const std::string &value);
            const Entry     search(const std::string &key);
            void            dump(std::ostream &os, DumpFlag flag);
                           ~BSTMap() { delete root; }
private:
            Node    *root = nullptr;
};

class RBTreeMap : public Map {
public:
            void            insert(const std::string &key, const std::string &value);
            const Entry     search(const std::string &key);
            void            dump(std::ostream &os, DumpFlag flag);
private:
            std::map<std::string, std::string> entries;
};

class TreapMap : public Map {
public:
            void            insert(const std::string &key, const std::string &value);
            const Entry     search(const std::string &key);
            void            dump(std::ostream &os, DumpFlag flag);
                           ~TreapMap() { delete root; }
private:
            Node    *root = nullptr;
};

class UnorderedMap : public Map {
public:
            void            insert(const std::string &key, const std::string &value);
            const Entry     search(const std::string &key);
            void            dump(std::ostream &os, DumpFlag flag);
private:
            std::unordered_map<std::string, std::string> entries;
};

class ChainedMap : public Map {
public:
            void            insert(const std::string &key, const std::string &value);
            const Entry     search(const std::string &key);
            void            dump(std::ostream &os, DumpFlag flag);
            ChainedMap();
            ChainedMap(double); 
            ChainedMap(double, size_t); 
            ~ChainedMap();


private:
            void            resize(const size_t new_size);
            double          nitems;
            size_t          table_size;
            double          load_factor;
            std::map<std::string, std::string> *hash_table;
            StringHasher    hash_function;
            double          load_limit; 
};

class OpenMap : public Map {
public:
            void            insert(const std::string &key, const std::string &value);
            const Entry     search(const std::string &key);
            void            dump(std::ostream &os, DumpFlag flag);
            OpenMap();
            OpenMap(double); 
            OpenMap(double, size_t); 
            ~OpenMap();

private:
            size_t          locate(const std::string &key);
            void            resize(const size_t new_size);
            double          nitems;
            size_t          table_size;
            double          load_factor;
            Entry           *hash_table;
            StringHasher    hash_function;
            double          load_limit; 
};

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
