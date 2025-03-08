#include "methods.h"

int getMax(std::vector<Item>& items, const std::string& attribute)
{
    int maxAge = 0;
    if(attribute == "age"){
        for(auto& item : items){
            maxAge = std::max(maxAge , item.age);
        }
    }   
     return maxAge;
}
// min = age - ageWindow
// max = age + ageWindow
// rarityScore = (1 - probability) * (1 + item.age/ageMax)
void calculateRarityScores(std::vector<Item>& items, int ageWindow) {
    int ageMax = getMax(items, "age");

    for (auto& item : items) { 
        int minAge = std::max(0, item.age - ageWindow); 
        int maxAge = item.age + ageWindow;

        int countSimilar = 0;
        int countTotal = 0;

        for (const auto& findsimilar : items) {
            if (findsimilar.age >= minAge && findsimilar.age <= maxAge) {
                countTotal++; 
                if (findsimilar.type == item.type && findsimilar.origin == item.origin) {
                    countSimilar++;
                }
            }
        }

        if (countTotal > 0) {
            double probability = static_cast<double>(countSimilar) / countTotal;
            double rarityScore = (1.0 - probability) * (1.0 + static_cast<double>(item.age) / ageMax);
            item.rarityScore = rarityScore;  
        } else {
            double otherwiseRarity = 1.0 + static_cast<double>(item.age/ageMax);
            item.rarityScore = otherwiseRarity;
        }
    }
}