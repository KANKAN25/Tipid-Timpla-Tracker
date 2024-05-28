#ifndef JSONCARRIENDERIAMENUHANDLER_H
#define JSONCARRIENDERIAMENUHANDLER_H

#include "json.hpp"
#include <vector>
#include <string>

using ordered_json = nlohmann::ordered_json;

class JSONCarrienderiaMenuHandler
{
public:
    JSONCarrienderiaMenuHandler();

    void addItem(const std::string& category, const ordered_json& item);
    void editItem(const std::string& category, size_t index, const ordered_json& item);
    void deleteItem(const std::string& category, size_t index);
    void save(const std::string& filename);

    const ordered_json& getItems(const std::string& category) const;

private:
    ordered_json carrienderia;
    std::unordered_map<std::string, ordered_json> buffers;
    std::unordered_map<std::string, int> counters;

    void initializeBuffers();
};

#endif // JSONCARRIENDERIAMENUHANDLER_H
