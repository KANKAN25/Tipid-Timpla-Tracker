#include "mainwindow.h"

#include <QApplication>
#include "json.hpp"
#include <fstream>
#include <iostream>


using json = nlohmann::json;
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    ifstream file("people.json");
    json j;
    file >> j;
    file.close();

    // Create a new person object
    json newPerson;
    newPerson["name"] = "Alice Brown";
    newPerson["age"] = 28;
    newPerson["occupation"] = "Teacher";
    json address;
    address["street"] = "901 Maple St";
    address["city"] = "Newtown";
    address["state"] = "FL";
    address["zip"] = "12345";
    newPerson["address"] = address;

    // Append the new person object to the existing JSON array
    j.push_back(newPerson);

    // Write the updated JSON data to the file
    ofstream fileOut("people.json");
    fileOut << j.dump(4); // 4 is the indentation level
    fileOut.close();

    return a.exec();
}
