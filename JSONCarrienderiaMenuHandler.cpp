#include "JSONCarrienderiaMenuHandler.h"
#include <fstream>
#include <iostream>

JSONCarrienderiaMenuHandler::JSONCarrienderiaMenuHandler()
{
    initializeBuffers();
}

// A function that initializes static variables accessible by the class
void JSONCarrienderiaMenuHandler::initializeBuffers()
{
    buffers["Meals"] = ordered_json::array();
    buffers["Drinks"] = ordered_json::array();
    counters["Meals"] = 0;  // These two takes the count of the number of existing items in the
    counters["Drinks"] = 0; // categories, hence please use this as the basis for the error handling
}                           // when there isn't any existing items to manipulate. Edit and Delete functions are noted for this

size_t JSONCarrienderiaMenuHandler::countCarrienderias(const ordered_json& jsonArray) {
    return jsonArray.size();
}

// This function is intended to receive data from external sources and create an item JSON object, coming from three UI input fields.
void JSONCarrienderiaMenuHandler::receiveItem(const std::string category, const std::string name, const std::string details, int price)
{
    ordered_json newItem;
    newItem["Name"] = name;
    newItem["Details"] = details;
    newItem["Price"] = price;
    itemReceiver = newItem;
}

// This function is called within the addItem function, intended to recieve the data from the external sources.
void JSONCarrienderiaMenuHandler::addItem(const std::string category, const std::string name, const std::string details, int price)
{
    receiveItem(category, name, details, price);

    if (buffers.find(category) != buffers.end())
    {
        buffers[category].push_back(itemReceiver);
        counters[category]++;
        itemReceiver.clear();
    }
}

/* The following is for visualization of what's being affected bythe addItem and other item manipulation functions
 * Essentially, each buffer[categoryname] has the items for the respective cetagory for each object of the menu offerings
"Menu Offerings":
    [
        { // The json array of Items goes to buffers["Meals"]
            "Category": "Meals",
            "Items": [
                {
                    "Name": "Mealname",
                    "Details": "Mealdetail",
                    "Price": 45
                }
            ]
        },
        { // And the items of this category goes to buffers["Drinks"]
            "Category": "Drinks",
            "Items": [
                {
                    "Name": "Drinkname",
                    "Details": "DrinkDetail",
                    "Price": 0
                }
            ]
        }
    ]
 */

// The logic for this is similar to addItem function, however instead of appending it to the json array
// it instead locates the chosen object via the index, and ovewrites it with the newly recieved object
// It will check if the index is within the bounds of the category.
// If it is, it will replace the item at the specified index with the new item.
// Index is a specific parameter that comes from button presses that equate to a number.
// Again, like the addItem function, this happens after the receiveItem function.
bool JSONCarrienderiaMenuHandler::editItem(const std::string category, const std::string name, const std::string details, int price, size_t index)
{
    receiveItem(category, name, details, price);

    if(counters[category] == 0)
    {
        // please add code here such that the ui is able to detect that there is no items to edit.
        return false;
    }

    if (buffers.find(category) != buffers.end() && index < buffers[category].size())
    {
        buffers[category][index] = itemReceiver;
        itemReceiver.clear(); // The clear serves to ensure that the next addition/edit, it is clean
        return true;
    }
}

// This index comes from an external source, namely from the user through pressing buttons that equate to numbers.
bool JSONCarrienderiaMenuHandler::deleteItem(const std::string& category, size_t index)
{

    if(counters[category] == 0)
    {
        // please add code here such that the ui is able to detect that there is no items to delete and does nothing
        return false;
    }

    if (buffers.find(category) != buffers.end() && index < buffers[category].size())
    {
        buffers[category].erase(buffers[category].begin() + index);
        counters[category]--;
        return true;
    }
}

// This function is called by the load function to search for a carrienderia by name.
// jsonArray represents the entire carrienderia array, with name being the key to compare. Carrienderia represents the specific carrienderia found.
bool JSONCarrienderiaMenuHandler::findCarrienderiaByName(const ordered_json& jsonArray, const std::string& name, ordered_json& carrienderia)
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

// This function is a sub function, to be used in the load functions
// Essentially takes in the carrienderia, representing just one eatery, containing all attributes
// And distributes the contents into
void JSONCarrienderiaMenuHandler::initializeBuffersAndCounters(const ordered_json& carrienderia)
{
    for (const auto& offering : carrienderia["Menu Offerings"])
    {
        std::string category = offering["Category"];
        buffers[category] = offering["Items"];
        counters[category] = buffers[category].size();
    }
}

/*  IMPORTANT!
 *
 *  Filename should be 'CarrienderiaList.json' when the button or so that's responsible for sending the information is clicked.
 *
 */


// this is the load function that is used to load an existing carrienderia for editing by name.
// carrienderia variable represesnts the carrienderia being edited.
// takes one carrienderia from jsonArray and stores it in carrienderia
bool JSONCarrienderiaMenuHandler::load(const std::string& filename, const std::string& name)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Unable to open file " << filename << std::endl;
        return false;
    }

    ordered_json jsonArray; // This is the entire carrienderia list
    file >> jsonArray;
    file.close();

    if (!findCarrienderiaByName(jsonArray, name, carrienderia))
    {
        std::cerr << "Carrienderia with name " << name << " not found." << std::endl;
        return false;
    }

    initializeBuffersAndCounters(carrienderia);
    return true;
}

// Index is the paremeter that is used to specify which carrienderia to load, which is specified by the user.
// buffers contains the items from the respective carrienderia and counters contains the number of items in each category.
// both buffers and counters are kept in sync with the carrienderia, with carrienderia being the main JSON object.
bool JSONCarrienderiaMenuHandler::load(const std::string& filename, size_t index)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Unable to open file " << filename << std::endl;
        return false;
    }

    ordered_json jsonArray;
    file >> jsonArray;
    file.close();

    if (index >= jsonArray.size())
    {
        std::cerr << "Index out of range." << std::endl;
        return false;
    }

    carrienderia = jsonArray[index];

    initializeBuffersAndCounters(carrienderia);
    return true;
}

// Save: This function will first check if the carrienderia exists. If it does, it will update the carrienderia with the new details.
// If it doesn't, it will add the carrienderia to the JSON array.
void JSONCarrienderiaMenuHandler::save(const std::string& filename)
{
    std::ifstream file(filename);
    ordered_json jsonArray;
    if (file.is_open())
    {
        file >> jsonArray;
        file.close();
    }

    for (auto& offering : carrienderia["Menu Offerings"])
    {
        std::string category = offering["Category"];
        if (buffers.find(category) != buffers.end())
        {
            offering["Items"] = buffers[category];
        }
    }

    // This is the important part of this function, which essentially updates that
    // particular carrienderia that has been chosen to have its items to be added/edited/deleted
    bool carrienderiaFound = false;
    for (auto& item : jsonArray)
    {
        if (item["Name"] == carrienderia["Name"])
        {
            item = carrienderia;
            carrienderiaFound = true;
            break;
        }
    }

    // In the improbable event that somehow this function list happens first instead of the setting up of the
    // carrienderia details, then this is what will happen.
    if (!carrienderiaFound)
    {
        jsonArray.push_back(carrienderia);
    }

    std::ofstream outFile(filename);
    if (!outFile.is_open())
    {
        std::cerr << "Unable to open file " << filename << std::endl;
        return;
    }
    outFile << jsonArray.dump(4);
    outFile.close();
}

    // General flow of the code in terms of pseudo code:
    // 1. Load carrienderia, this is where the user chooses which carrienderia they want to edit
        // -  facilitated through an external source providing the value for the index to choose which carienderia
        // -  Side note, there will be another function that would count the total amount of carrienderias and
        // -  send it to a function that would display the names of the carrienderias to choose from
    // 2. Manipulation of items in the carrienderia
        // - The buffers will be filled with the items coming from the carienderia.
        // - key "Items" will have its value pair be equal to the buffers json array for that specific category
        // + Avoids the problem of repeated items in the same category
        // + This streamlines the manipulation of items in the carrienderia as it is all stored in a buffer that is yet to be finalized.
    // 3. Get buffer items to show to user
        // - This is where the user would view the items in the buffer so that they can keep track of what they plan to add or possibly delete.
        // - the counters for each category will be used to keep track of how many items there are in each category, which will be the basis for the limit of what the user can enter for the index before being invalid
    // 4. Save carrienderia
        // -  This is where the user would save the changes by way of having the item keys have their value pairs be equal to the buffers of that category

/* Template on how the potential code would look like:
int main() {

    JSONCarrienderiaMenuHandler handler;

    if (handler.load("CarrienderiaList.json", 1)) {
        std::cout << "Loaded " << carrienderia["Name"] <<  " successfully." << std::endl;
    } else {
        std::cout << "Failed to load Carrienderia 1." << std::endl;
    }

    // Example usage of adding items into categories
    handler.addItem("Meals", "Pork Adobo", "Delicious pork adobo", 100);
    handler.addItem("Meals", "Ten Colored Wings", "Divine and Gracious, Supreme", 999);
    handler.addItem("Drinks", "Halo-Halo", "Refreshing halo-halo", 50);

    // Example usage of edit item and delete item through index
    int index = 1;
    handler.editItem("Drinks", "Ambrosium", "Indulgence made Liquid", 50, --index);
    handler.deleteItem("Drinks", --index);

    // Finalizes all the changes and saves ii all into the JSON file
    handler.save("CarrienderiaList.json");



    return 0;
}



*/
