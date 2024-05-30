#ifndef JSONCARRIENDERIAMENUHANDLER_H
#define JSONCARRIENDERIAMENUHANDLER_H

#include "json.hpp"
#include <vector>
#include <string>

// Check file to determine if fully complete

using ordered_json = nlohmann::ordered_json;

class JSONCarrienderiaMenuHandler
{
public:
    JSONCarrienderiaMenuHandler();

    // this is what will 'recieve' the data from the external sources
    // void recieveItem(ordered_json& item, const std::string& category, const std::string& category, const int& price)

    // should be the one to count the existing items for each category using the private counters variable
    // void counterItem()

    // each category will have its own counter as they are separate
    // therefore the respective category will be paired with its own function call to
    // the counterItem function for its respective items, if there are any.
    void addItem(const std::string& category, const ordered_json& item);
    void editItem(const std::string& category, size_t index, const ordered_json& item);
    void deleteItem(const std::string& category, size_t index);
    void save(const std::string& filename);


    const ordered_json& getItems(const std::string& category) const;

private:
    ordered_json carrienderia;
    std::unordered_map<std::string, ordered_json> buffers;
    std::unordered_map<std::string, int> counters; // used to describe the size of the json sub-object, serves as the basis for editing/adding

    void initializeBuffers();
};

#endif // JSONCARRIENDERIAMENUHANDLER_H
