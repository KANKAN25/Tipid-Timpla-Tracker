#ifndef JSONFILEINITIALIZER_H
#define JSONFILEINITIALIZER_H

#include "json.hpp"
#include <fstream>
#include <iostream>
#include <string>

using ordered_json = nlohmann::ordered_json;

class JSONFileInitializer {
public:
    JSONFileInitializer(const std::string& filename);
    bool initialize();
    const ordered_json& getData() const;

private:
    std::string filename;
    ordered_json jsonData;
    bool load();
    bool createFile();
};

#endif // JSONFILEINITIALIZER_H
