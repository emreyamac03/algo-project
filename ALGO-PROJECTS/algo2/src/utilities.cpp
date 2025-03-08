#include "methods.h"

std::vector<Item> readItemsFromFile(const std::string& filename) {
    std::vector<Item> items;
    std::ifstream file(filename);

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        if (!line.empty()) {
            std::stringstream ss(line);
            std::string itemField;

            Item item;

            std::getline(ss, itemField, ',');
            item.age = std::stoi(itemField);

            std::getline(ss, itemField, ',');
            item.type = std::stoi(itemField);

            std::getline(ss, itemField, ',');
            item.origin = std::stoi(itemField);

            std::getline(ss, itemField, ',');
            item.rarityScore= std::stod(itemField);

            items.push_back(item);
        }
    }

    file.close();
    return items;
}

void writeItemsToFile(const std::string& filename, const std::vector<Item>& items) {
    std::ofstream outFile(filename);

    outFile << "age,type,origin,rarity\n";

    for (const auto& item : items) {
        outFile << item.age << ","
                << item.type << ","
                << item.origin << ","
                << item.rarityScore << "\n";
    }

    outFile.close();
}