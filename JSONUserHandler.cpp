#include "JSONUserHandler.h"

JSONUserHandler::JSONUserHandler(const std::string& filename)  : filename(filename), founduser(false), foundpass(false) {}

bool JSONUserHandler::load() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file " << filename << std::endl;
        return false;
    }
    file >> jsonData;
    file.close();
    return true;
}

bool JSONUserHandler::save() {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Unable to open file " << filename << std::endl;
        return false;
    }
    outfile << jsonData.dump(4);
    outfile.close();
    return true;
}

bool JSONUserHandler::deleteUser(const std::string& username) {
    bool found = false;
    for (auto it = jsonData.begin(); it != jsonData.end(); ++it) {
        if ((*it)["Username"] == username) {
            jsonData.erase(it);
            found = true;
            break;
        }
    }
    if (!found) {
        std::cout << "No such username" << std::endl;
    }
    return found;
}

bool JSONUserHandler::addUser(const std::string& username, const std::string& password) {
    ordered_json newUser;
    newUser["Username"] = username;
    newUser["Password"] = password;
    jsonData.push_back(newUser);
    return true;
}

bool JSONUserHandler::findUser(const std::string& username, const std::string& password) {
    founduser = false;
    foundpass = false;

    for (auto& it : jsonData) {
        if (it["Username"] == username) {
            founduser = true;
            if (it["Password"] == password) {
                foundpass = true;
                curusername = username;
                curpassword = password;
                break;
            }
        }
    }
    return founduser && foundpass;
}

std::string JSONUserHandler::getCurrentUsername() const {
    return curusername;
}

std::string JSONUserHandler::getCurrentPassword() const {
    return curpassword;
}
