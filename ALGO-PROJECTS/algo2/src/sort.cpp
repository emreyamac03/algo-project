#include "methods.h"

std::vector<Item> countingSort(std::vector<Item>& items, const std::string& attribute, bool ascending)
{
    int n = items.size();
    int m = 0;

    if (attribute == "age") {
            for (int i = 0; i < n; i++) {
                m = std::max(m, items[i].age);
            }
        }

        std::vector<int> countArray(m + 1, 0);

        for (int i = 0; i < n; i++) {
            int value = items[i].age;
            countArray[value]++;
        }

        for (int i = 1; i <= m; i++) {
            countArray[i] += countArray[i - 1];
        }

        std::vector<Item> lastArray(n);

        for (int i = n - 1; i >= 0; i--) {
            int value = items[i].age;
            lastArray[countArray[value] - 1] = items[i];
            countArray[value]--;
        }

        if (!ascending) {
            int left = 0;
            int right = n - 1;
            while (left < right) {
                std::swap(lastArray[left], lastArray[right]);
                left++;
                right--;
            }
        }
     return lastArray;   
} 


void heapify(std::vector<Item>& items, int n, int i, bool descending)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int variable = i;

    if (!descending) {
        if (left < n && items[left].rarityScore > items[variable].rarityScore) {
            variable = left;
        }
        if (right < n && items[right].rarityScore > items[variable].rarityScore) {
            variable = right;
        }
    } else {
        if (left < n && items[left].rarityScore < items[variable].rarityScore) {
            variable = left;
        }
        if (right < n && items[right].rarityScore < items[variable].rarityScore) {
            variable = right;
        }
    }

    if (variable != i) {
        std::swap(items[i], items[variable]);
        heapify(items, n, variable, descending);
    }
     
}


std::vector<Item> heapSortByRarity(std::vector<Item>& items, bool descending)
{
    int n = items.size();

    for (int i = (n/2) - 1; i >= 0; i--) {
        heapify(items, n, i, descending);
    }

    for (int i = n - 1; i > 0; i--) {
        std::swap(items[0], items[i]);
        heapify(items, i, 0, descending);  
    }
    return items;
}
