#ifndef JSONCARRIENDERIAREVIEWHANDLER_H
#define JSONCARRIENDERIAREVIEWHANDLER_H

#include "json.hpp"
#include <vector>
#include <string>

using namespace std;
using ordered_json = nlohmann::ordered_json;

// Work in progress header file for carrienderia review handling
// Treat header files as the same as the prototype functions done in C for better understanding

using ordered_json = nlohmann::ordered_json;

class JSONCarrienderiaReviewHandler
{
public:
    JSONCarrienderiaReviewHandler();

    void addReview(const std::string& category, const ordered_json& item);
    void editReview(const std::string& category, size_t index, const ordered_json& item);
    void deleteReview(const std::string& category, size_t index);
    void save(const std::string& filename);

    void receiveReview(const std::string user, const std::string name, const std::string review);

    const ordered_json& getItems(const std::string& category) const;

private:
    void initializeBuffers();

    ordered_json carrienderia;
    ordered_json jsonArray;

    std::unordered_map<std::string, ordered_json> buffers; // Buffers for each category as well as counters and items.
};

#endif // JSONCARRIENDERIAREVIEWHANDLER_H
