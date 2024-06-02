#ifndef JSONCARRIENDERIAREVIEWHANDLER_H
#define JSONCARRIENDERIAREVIEWHANDLER_H

#include "json.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;
using ordered_json = nlohmann::ordered_json;

class JSONCarrienderiaReviewHandler
{
public:
    JSONCarrienderiaReviewHandler();

    void receiveReview(const std::string user, const std::string review);
    void editReview(const std::string user, std::string name);
    void deleteReview(const std::string user);

    bool findCarrienderiaByName(const ordered_json& jsonArray, const std::string& name, ordered_json& carrienderia);
    bool load(const std::string& name);
    void save();

    ordered_json jsonArray; // Buffers for each category as well as counters and items
private:
    void initializeBuffers();

    ordered_json carrienderia;
};


#endif // JSONCARRIENDERIAREVIEWHANDLER_H
