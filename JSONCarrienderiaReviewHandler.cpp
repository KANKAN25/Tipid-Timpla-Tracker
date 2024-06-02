#include "JSONCarrienderiaReviewHandler.h"
#include <fstream>
#include <iostream>

JSONCarrienderiaReviewHandler::JSONCarrienderiaReviewHandler()
{
    initializeBuffers();
}

void JSONCarrienderiaReviewHandler::initializeBuffers()
{

    carrienderia["User Reviews"] = ordered_json::array();

    ifstream file("CarriendariaList.json");
    file >> jsonArray;
    file.close();
}

void JSONCarrienderiaReviewHandler::receiveReview(const std::string user, const std::string review)
{
    carrienderia["User Reviews"].push_back({{"User", user}, {"Review", review}});
}

// This function would use the user input as the search condition, and then replaces that review with the entered review
void JSONCarrienderiaReviewHandler::editReview(const std::string user, const std::string review)
{
    auto& itemsArray = carrienderia["User Reviews"];

    // Iterate over the items array using an iterator
    for (auto it = itemsArray.begin(); it != itemsArray.end(); it++)
    {
        if ((*it)["User"] == user)
        {
            (*it)["Review"] = review; // Erase the item and get the next iterator
            break;
        }
    }
}

void JSONCarrienderiaReviewHandler::deleteReview(const std::string user)
{
    auto& itemsArray = carrienderia["User Reviews"];

    // Iterate over the items array using an iterator
    for (auto it = itemsArray.begin(); it != itemsArray.end(); it++)
    {
        if ((*it)["User"] == user)
        {
            it = itemsArray.erase(it); // Erase the item and get the next iterator
            break;
        }
    }
}

bool JSONCarrienderiaReviewHandler::findCarrienderiaByName(const ordered_json& jsonArray, const std::string& name, ordered_json& carrienderia)
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


bool JSONCarrienderiaReviewHandler::load(const std::string& name)
{
    ifstream file("CarriendariaList.json");
    if (!file.is_open())
    {
        std::cerr << "Unable to open file CarriendariaList.json" << std::endl;
        return false;
    }

    file >> jsonArray;
    file.close();

    if (!findCarrienderiaByName(jsonArray, name, carrienderia))
    {
        std::cerr << "Carrienderia with name " << name << " not found." << std::endl;
        return false;
    }
    return true;
}

void JSONCarrienderiaReviewHandler::save()
{

    for (auto& item : jsonArray)
    {
        if (item["Name"] == carrienderia["Name"])
        {
            item = carrienderia;
            break;
        }
    }

    std::ofstream outfile("CarriendariaList.json");
    if (!outfile.is_open())
    {
        std::cerr << "Unable to open file CarriendariaList.json" << std::endl;
        return;
    }
    outfile << jsonArray.dump(4);
    outfile.close();
}
