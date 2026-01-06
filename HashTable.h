#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "TableEntry.h"

#include "ListLinked.h"

template <typename V>
class HashTable : public Dict<V> {

    private:
        int n;
        int max;
        ListLinked<TableEntry<V>>* table;

        int h(std::string key) {
            int sum = 0;
            for (int i = 0; i < key.length(); i++) {
                sum += int(key.at(i));
            }
            return sum % max;
        }

    public:
        HashTable(int size) {
            n = 0;
            max = size;
            table = new ListLinked<TableEntry<V>>[size];
        }

        ~HashTable() {
            delete[] table;
        }

        int capacity() {
            return max;
        }

        void insert(std::string key, V value) override {
            int bucket = h(key);
            TableEntry<V> entry(key, value);
            
            if (table[bucket].search(entry) != -1) {
                throw std::runtime_error("Key already exists in HashTable");
            }

            table[bucket].prepend(entry);
            n++;
        }

        V search(std::string key) override {
            int bucket = h(key);
            TableEntry<V> entry(key);
            
            int pos = table[bucket].search(entry);
            
            if (pos == -1) {
                throw std::runtime_error("Key not found in HashTable");
            }

            return table[bucket].get(pos).value;
        }

        V remove(std::string key) override {
            int bucket = h(key);
            TableEntry<V> entry(key);

            int pos = table[bucket].search(entry);
            
            if (pos == -1) {
                throw std::runtime_error("Key not found in HashTable");
            }

            V val = table[bucket].get(pos).value;
            
            table[bucket].remove(pos);
            n--;
            
            return val;
        }

        int entries() override {
            return n;
        }

        V operator[](std::string key) {
            return search(key);
        }

        friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th) {
            out << "HashTable [entries: " << th.n << ", capacity: " << th.max << "]" << std::endl;
            out << "================" << std::endl;
            
            for (int i = 0; i < th.max; i++) {
                out << "== Bucket " << i << " ==" << std::endl;
                out << th.table[i] << std::endl;
            }
            
            out << "================" << std::endl;
            return out;
        }
};

#endif
