#ifndef JSONCARRIENDERIAREVIEWHANDLER_H
#define JSONCARRIENDERIAREVIEWHANDLER_H

#include "json.hpp"
#include <vector>
#include <string>

// Work in progress header file for carrienderia review handling
// Treat header files as the same as the prototype functions done in C

using ordered_json = nlohmann::ordered_json;

class JSONCarrienderiaReviewHandler
{
public:
    JSONCarrienderiaReviewHandler();

    void addReview(const std::string& category, const ordered_json& item);
    void editReview(const std::string& category, size_t index, const ordered_json& item);
    void deleteReview(const std::string& category, size_t index);
    void save(const std::string& filename);

    const ordered_json& getItems(const std::string& category) const;

private:
    ordered_json carrienderia;
};

#endif // JSONCARRIENDERIAREVIEWHANDLER_H
