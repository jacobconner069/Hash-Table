#include "passserver.h"
#include <fstream>
#include <iostream>
#include<unistd.h>
#include<crypt.h>


PassServer::PassServer(size_t size) : table(size) {}

PassServer::~PassServer() {
    table.clear();
}

bool PassServer::load(const char* filename) {
    return table.load(filename);
}

bool PassServer::addUser(std::pair<std::string, std::string> & kv) {
    kv.second = encrypt(kv.second);
    return table.insert(kv);
}

bool PassServer::addUser(std::pair<std::string, std::string> && kv) {
    kv.second = encrypt(kv.second);
    return table.insert(std::move(kv));
}

bool PassServer::removeUser(const std::string & k) {
    return table.remove(k);
}

bool PassServer::changePassword(const std::pair<std::string, std::string> &p, const std::string & newpassword) {
    if (!table.contains(p.first)){
        return false;
    }
    std::string encryptedNewPassword = encrypt(newpassword);
    if(encryptedNewPassword == encrypt(p.second)){
        return false; 
    }
    if (table.match(std::make_pair(p.first, encrypt(p.second)))){
        return table.insert(std::make_pair(p.first, encryptedNewPassword));
    }
    return false;
}

bool PassServer::find(const std::string & k) const {
    return table.contains(k);
}

void PassServer::dump() const {
    table.dump();
}

size_t PassServer::size() const {
    return table.size();
}

bool PassServer::write_to_file(const char* filename) const {
    return table.write_to_file(filename);
}

std::string PassServer::encrypt(const std::string & str) const {
    char salt[] = "$1$########";
    char* encrypted = crypt(str.c_str(), salt);
    std::string encryptedStr(encrypted);
    size_t pos = 0;
    int count = 0;
    for(size_t i = 0; i < encryptedStr.size(); ++i){
        if (encryptedStr[i] == '$'){
            ++count;
            if (count == 3){
                pos = i+1;
                break;
            }
        }
    }
    return encryptedStr.substr(pos);
}