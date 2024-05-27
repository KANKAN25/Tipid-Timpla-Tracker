#ifndef JSONUSERHANDLER_H
#define JSONUSERHANDLER_H

#include "json.hpp"
#include <fstream>
#include <iostream>
#include <string>

using ordered_json = nlohmann::ordered_json;

class JSONUserHandler {
public:
    JSONUserHandler(const std::string& filename);
    bool load();
    bool save();
    bool deleteUser(const std::string& username);
    bool addUser(const std::string& username, const std::string& password);
    bool findUser(const std::string& username, const std::string& password);

    std::string getCurrentUsername() const;
    std::string getCurrentPassword() const;

private:
    std::string filename;
    ordered_json jsonData;
    std::string curusername;
    std::string curpassword;
    bool founduser;
    bool foundpass;
};

#endif // JSONUSERHANDLER_H
