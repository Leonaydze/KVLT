#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
#include "Player.h"
#include "PlayerInventory.h"

using json = nlohmann::json;

const std::string filename = "dataTest.json";

void Create(std::string color, int amount) {
    json j;
    //Read
    std::ifstream inputFile(filename);
    if (inputFile) {
        inputFile >> j;
    }

    //New Entity
    json newEntry = { {"color", color}, {"amount", amount}};
    j.push_back(newEntry);
    
    //Save File
    std::ofstream outputFile(filename);
    outputFile << j.dump(4);
    outputFile.close();
}

void Read() {
    json j;
    //Read
    std::ifstream inputFile(filename);
    if (inputFile) {
        inputFile >> j;
        //Output On Screen
        std::cout << j.dump(4) << "\n";
    }
    else {
        std::cout << "FileNotFound" << std::endl;
    }
}

void Update(int index, std::string color, int amount) {
    json j;
    //Read
    std::ifstream inputFile(filename);
    if (inputFile) {
        inputFile >> j;
        //Проверка в диапозоне ли индекс
        if (index < 0 or index >= j.size()) {
            std::cout << "Index is out of range" << std::endl;
            return;
        }
        j[index]["color"] = color;
        j[index]["amount"] = amount;
        //Save File
        std::ofstream outputFile(filename);
        outputFile << j.dump(4);
        outputFile.close();
    }
    else {
        std::cout << "FileNotFound" << std::endl;
    }
}

void Remove(int index) {
    json j;
    //Read
    std::ifstream inputFile(filename);
    if (inputFile) {
        inputFile >> j;
        //Проверка в диапозоне ли индекс
        if (index < 0 or index >= j.size()) {
            std::cout << "Index is out of range" << std::endl;
            return;
        }
        j.erase(j.begin() + index);
        //Save File
        std::ofstream outputFile(filename);
        outputFile << j.dump(4);
        outputFile.close();
    }
    else {
        std::cout << "FileNotFound" << std::endl;
    }
}

int main(){
}
