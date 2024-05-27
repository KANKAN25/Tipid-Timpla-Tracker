#include "JSONFileInitializer.h"

JSONFileInitializer::JSONFileInitializer(const std::string& filename) : filename(filename) {}

bool JSONFileInitializer::initialize() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        if (!createFile()) {
            std::cerr << "Failed to create file " << filename << std::endl;
            return false;
        }
        file.open(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open file " << filename << " after creation" << std::endl;
            return false;
        }
    }
    file >> jsonData;
    file.close();
    return true;
}

bool JSONFileInitializer::createFile() {
    std::ofstream newfile(filename);
    if (!newfile.is_open()) {
        std::cerr << "Unable to create file " << filename << std::endl;
        return false;
    }
    ordered_json jsonfile = ordered_json::array();
    newfile << jsonfile.dump(4);
    newfile.close();
    return true;
}

const ordered_json& JSONFileInitializer::getData() const {
    return jsonData;
}
