#ifndef PASSSERVER_H
#define PASSSERVER_H

#include<vector>
#include<string>
#include <unistd.h>
#include <crypt.h>
#include "hashtable.h"

class PassServer
{
    public:
        PassServer(size_t size = 101);
        ~PassServer();
        bool load(const char* filename);
        bool addUser(std::pair<std::string, std::string> & kv);
        bool addUser(std::pair<std::string, std::string> && kv);
        bool removeUser(const std::string & k);
        bool changePassword(const std::pair<std::string, std::string> &p, const std::string & newpassword);
        bool find(const std::string & k) const;
        void dump() const;
        size_t size() const;
        bool write_to_file(const char* filename) const;

    private:
        std::string encrypt(const std::string & str) const;
        cop4530::HashTable<std::string, std::string> table;
};

#endif


 