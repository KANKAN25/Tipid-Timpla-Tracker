#ifndef JSONCARRIENDERIAHANDLER_H
#define JSONCARRIENDERIAHANDLER_H

// This header and associated function list is for dealing with the initialization of a carrienderia into a list, or editing of a existing carrienderia

#include "json.hpp"
#include <iostream>
#include <fstream>

using namespace std;
using ordered_json = nlohmann::ordered_json;

class JSONCarrienderiaHandler
{
public:
    JSONCarrienderiaHandler();

    // Edit, delete eateries
    bool editEatery(const std::string& name);
    bool deleteEatery(const std::string& name);
    bool deleteEatery(size_t index);

    // Load and Save functions that happened at start and beginning
    void addEatery();
    bool load(const std::string& name);
    bool load(size_t index);
    void save();

    // Receive data from external sources and create an item JSON object
    void receiveAttribute(const std::string key, const std::string value);
    void receiveAttribute(const std::string key, const float value); // This is for the input for average rating
    void receiveAttribute(const std::string key, const float value1, const float value2); // This is for the average price range, two float values of a minimum and a maximum tied into an array

    ordered_json jsonArray;

private:

    // Search for a carrienderia by name
    bool findCarrienderiaByName(const ordered_json& jsonArray, const std::string& name, ordered_json& carrienderia);

    void initializeBuffers();

    ordered_json carrienderia;


};


#endif // JSONCARRIENDERIAHANDLER_H
