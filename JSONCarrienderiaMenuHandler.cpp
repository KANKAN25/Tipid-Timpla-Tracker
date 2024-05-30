#include "JSONCarrienderiaMenuHandler.h"
#include <fstream>
#include <iostream>

// Not yet complete as it simply deals with the addition of objects of the menu, not the details yet.
//

JSONCarrienderiaMenuHandler::JSONCarrienderiaMenuHandler()
{
    initializeBuffers();
}

void JSONCarrienderiaMenuHandler::initializeBuffers()
{
    buffers["Meals"] = ordered_json::array();
    buffers["Drinks"] = ordered_json::array();
    counters["Meals"] = 0;
    counters["Drinks"] = 0;
}

// recieves the details from an external source for an object, therefore should be in the same line as addItem function
// void JSONCarrienderiaMenuHandler::recieveItem(ordered_json& item, const std::string& category, const std::string& category, const int& price)
/*





 */

void JSONCarrienderiaMenuHandler::addItem(const std::string& category, const ordered_json& item)
{
    if (buffers.find(category) != buffers.end())
    {
        buffers[category].push_back(item);
        counters[category]++;
    }
}

void JSONCarrienderiaMenuHandler::editItem(const std::string& category, size_t index, const ordered_json& item)
{
    if (buffers.find(category) != buffers.end() && index < buffers[category].size())
    {
        buffers[category][index] = item;
    }
}

void JSONCarrienderiaMenuHandler::deleteItem(const std::string& category, size_t index)
{
    if (buffers.find(category) != buffers.end() && index < buffers[category].size())
    {
        buffers[category].erase(buffers[category].begin() + index);
        counters[category]--;
    }
}

void JSONCarrienderiaMenuHandler::save(const std::string& filename)
{
    for (const auto& pair : buffers)
    {
        carrienderia["Menu Offerings"][pair.first] = pair.second;
    }

    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Unable to open file " << filename << std::endl;
        return;
    }
    file << carrienderia.dump(4);
    file.close();
}

const ordered_json& JSONCarrienderiaMenuHandler::getItems(const std::string& category) const {
    return buffers.at(category);
}
