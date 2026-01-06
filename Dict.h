#ifndef DICT_H
#define DICT_H
#include <string>

template <typename V>

class Dict {

    public:
        virtual int entries () = 0;
        virtual void insert (std::string key, V Value) = 0;
        virtual V search (std:: string key) = 0;
        virtual V remove (std:: string Key) = 0;

};
#endif
