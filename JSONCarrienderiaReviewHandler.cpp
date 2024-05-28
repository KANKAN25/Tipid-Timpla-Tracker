#include "JSONCarrienderiaReviewHandler.h"
#include <fstream>
#include <iostream>

// To be polished and made

void JSONCarrienderiaReviewHandler::addReview(const std::string& category, const ordered_json& item)
{
    // if (buffers.find(category) != buffers.end())
    // {
    //     buffers[category].push_back(item);
    //     counters[category]++;
    // }
}

void JSONCarrienderiaReviewHandler::editReview(const std::string& category, size_t index, const ordered_json& item)
{
    // if (buffers.find(category) != buffers.end() && index < buffers[category].size())
    // {
    //     buffers[category][index] = item;
    // }
}

void JSONCarrienderiaReviewHandler::deleteReview(const std::string& category, size_t index)
{
    // if (buffers.find(category) != buffers.end() && index < buffers[category].size())
    // {
    //     buffers[category].erase(buffers[category].begin() + index);
    //     counters[category]--;
    // }
}

void JSONCarrienderiaReviewHandler::save(const std::string& filename)
{
    // for (const auto& pair : buffers)
    // {
    //     carrienderia["Menu Offerings"][pair.first] = pair.second;
    // }

    // std::ofstream file(filename);
    // if (!file.is_open())
    // {
    //     std::cerr << "Unable to open file " << filename << std::endl;
    //     return;
    // }
    // file << carrienderia.dump(4);
    // file.close();
}

const ordered_json& JSONCarrienderiaReviewHandler::getItems(const std::string& category) const {
    // return buffers.at(category);
}
