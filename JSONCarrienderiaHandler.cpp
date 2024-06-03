#include "JSONCarrienderiaHandler.h"
#include "json.hpp"
#include <fstream>
#include <iostream>

using ordered_json = nlohmann::ordered_json;

// This is a constructor, thus would mean that anything made by the class would then have the buffers be initialized.
JSONCarrienderiaHandler::JSONCarrienderiaHandler()
{
    initializeBuffers();
}

void JSONCarrienderiaHandler::initializeBuffers()
{
    carrienderia["Name"] = "";
    carrienderia["Status"] = "";
    carrienderia["Average Rating"] = 0.0;
    carrienderia["Average Price Range"] = ordered_json::array();
    carrienderia["Address"] = "";
    carrienderia["Landmarks"] = "";
    carrienderia["Dining Accomodations"] = "";
    carrienderia["Menu Offerings"] = ordered_json::array({{{"Category", "Meals"}, {"Items", ordered_json::array()}}, {{"Category", "Drinks"}, {"Items", ordered_json::array()}}});
    carrienderia["User Reviews"] = ordered_json::array();

    ifstream file("CarriendariaList.json");
    file >> jsonArray;
    file.close();
}

// Function overloading can be done for the following to not have
void JSONCarrienderiaHandler::receiveAttribute(const std::string key, const std::string value)
{
    carrienderia[key] = value;
}

// This is for the ratings
void JSONCarrienderiaHandler::receiveAttribute(const std::string key, const float value)
{
    carrienderia[key] = value;
}

// This is for the price range since the price range would accep two values of
void JSONCarrienderiaHandler::receiveAttribute(const std::string key, const float value1, const float value2)
{
    carrienderia[key] = ordered_json::array({value1,value2});;
}

void JSONCarrienderiaHandler::addEatery()
{
    jsonArray.push_back(carrienderia);
}

bool JSONCarrienderiaHandler::editEatery(const std::string& name)
{
    for (auto& item : jsonArray)
    {
        if (item["Name"] == name)
        {
            item = carrienderia;
            save();
            return true;
        }
    }

    std::cerr << "Carrienderia with name " << name << " not found for editing." << std::endl;
    return false;
}
// Delete an eatery by name
bool JSONCarrienderiaHandler::deleteEatery(const std::string& name)
{
    for (auto it = jsonArray.begin(); it != jsonArray.end(); ++it)
    {
        if ((*it)["Name"] == name)
        {
            jsonArray.erase(it);
            save();
            return true;
        }
    }

    std::cerr << "Carrienderia with name " << name << " not found for deletion." << std::endl;
    return false;
}

// Delete an eatery by index
bool JSONCarrienderiaHandler::deleteEatery(size_t index)
{
    if (index < jsonArray.size())
    {
        jsonArray.erase(jsonArray.begin() + index);
        save();
        return true;
    }

    std::cerr << "Index out of range for deletion." << std::endl;
    return false;
}

bool JSONCarrienderiaHandler::findCarrienderiaByName(const ordered_json& jsonArray, const std::string& name, ordered_json& carrienderia)
{
    for (const auto& item : jsonArray)
    {
        if (item["Name"] == name)
        {
            carrienderia = item;
            return true;
        }
    }
    return false;
}

// Load carrienderia list from file
// This function is used by the eatery manipulation functions
// Essentially adding into
// Load a carrienderia by name
bool JSONCarrienderiaHandler::load(const std::string& name)
{
    if (!findCarrienderiaByName(jsonArray, name, carrienderia))
    {
        // std::cerr << "Carrienderia with name " << name << " not found." << std::endl;
        return false;
    }
    return true;
}

// Load a carrienderia by index
bool JSONCarrienderiaHandler::load(size_t index)
{
    if (index >= jsonArray.size())
    {
        std::cerr << "Index out of range." << std::endl;
        return false;
    }

    carrienderia = jsonArray[index];
    return true;
}

// Save carrienderia changes
void JSONCarrienderiaHandler::save()
{
    std::ofstream outFile("CarriendariaList.json");
    if (!outFile.is_open())
    {
        std::cerr << "Unable to open file CarriendariaList.json" << std::endl;
        return;
    }
    outFile << jsonArray.dump(4);
    outFile.close();
}

std::vector<ordered_json> JSONCarrienderiaHandler::getAllEateries() const
{
    return jsonArray;
}
