#ifndef JSONCARRIENDERIAMENUHANDLER_H
#define JSONCARRIENDERIAMENUHANDLER_H

#include "json.hpp"
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>

using namespace std;
using ordered_json = nlohmann::ordered_json;

class JSONCarrienderiaMenuHandler
{
public:
    JSONCarrienderiaMenuHandler();

    // Add, edit, delete items in the specified category
    void addItem(const std::string category, const std::string name, const std::string details, int price);
    bool editItem(const std::string category, const std::string name, const std::string details, int price, size_t index);
    void deleteItem(const std::string& category, const std::string name);
    void deleteItem(const std::string& category, size_t index);

    // Save the current state to a file
    void save();

    // Load an existing carrienderia for editing by name or index
    bool load(const std::string& name);
    bool load(size_t index);

    // Subfunction to load that distributes the contents of the menu objects
    void initializeBuffersAndCounters(const ordered_json& carrienderia);

    // This one is just to get the count of all existing carrienderias.
    // Use this as the basis of the error handling when there is zero carrienderias.
    size_t countCarrienderias(const ordered_json& jsonArray);

    ordered_json jsonArray;
    ordered_json carrienderia;  // The main JSON object representing the carrienderia

private:
    // Receive data from external sources and create an item JSON object
    void receiveItem(const std::string category, const std::string name, const std::string details, int price);

    // Search for a carrienderia by name
    bool findCarrienderiaByName(const ordered_json& jsonArray, const std::string& name, ordered_json& carrienderia);


    std::unordered_map<std::string, ordered_json> buffers; // Buffers for each category as well as counters and items.
    std::unordered_map<std::string, size_t> counters;  // Counters for each category
    ordered_json itemReceiver;

    // Helper method to initialize buffers and counters
    void initializeBuffers();
};

#endif // JSONCARRIENDERIAMENUHANDLER_H
