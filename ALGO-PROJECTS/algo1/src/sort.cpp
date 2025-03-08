#include "tweet.h"

void bubbleSort(std::vector<Tweet>& tweets, const std::string& sortBy, bool ascending) {
    int n = tweets.size();
    bool swapped;

    for (int i = 0; i < n - 1; ++i) {
        swapped = false;

        for (int j = 0; j < n - 1 - i; ++j) {
            if (sortBy == "tweetID") {
                if (ascending) {
                    if (tweets[j].tweetID > tweets[j + 1].tweetID) {
                        std::swap(tweets[j], tweets[j + 1]);
                        swapped = true;
                    }
                } 
                else {
                    if (tweets[j].tweetID < tweets[j + 1].tweetID) {
                        std::swap(tweets[j], tweets[j + 1]);
                        swapped = true;
                    }
                }
            } 
            else if (sortBy == "favoriteCount") {
                if (ascending) {
                    if (tweets[j].favoriteCount > tweets[j + 1].favoriteCount) {
                        std::swap(tweets[j], tweets[j + 1]);
                        swapped = true;
                    }
                } 
                else {
                    if (tweets[j].favoriteCount < tweets[j + 1].favoriteCount) {
                        std::swap(tweets[j], tweets[j + 1]);
                        swapped = true;
                    }
                }
            } else if (sortBy == "retweetCount") {
                if (ascending) {
                    if (tweets[j].retweetCount > tweets[j + 1].retweetCount) {
                        std::swap(tweets[j], tweets[j + 1]);
                        swapped = true;
                    }
                } 
                else {
                    if (tweets[j].retweetCount < tweets[j + 1].retweetCount) {
                        std::swap(tweets[j], tweets[j + 1]);
                        swapped = true;
                    }
                }
            }
        }
        if (!swapped) {
            break;
        }
    }
}

void insertionSort(std::vector<Tweet>& tweets, const std::string& sortBy, bool ascending) 
{
    for (int j = 1; j < tweets.size(); j++) {
        auto key = tweets[j];
        int i = j - 1;
 
        while (i >= 0) {
            bool shouldSwap = false;

            if (sortBy == "tweetID") {
                if(ascending){
                    shouldSwap = (tweets[i].tweetID > key.tweetID);
                }
                else{
                    shouldSwap = (tweets[i].tweetID < key.tweetID);
                }
            } 
            else if (sortBy == "favoriteCount") {
                if(ascending){
                    shouldSwap = (tweets[i].favoriteCount > key.favoriteCount);
                }
                else{
                    shouldSwap = (tweets[i].favoriteCount < key.favoriteCount);
                }
            } 
            else if (sortBy == "retweetCount") {
                if(ascending){
                    shouldSwap = (tweets[i].retweetCount > key.retweetCount);
                }
                else{
                    shouldSwap = (tweets[i].retweetCount < key.retweetCount);
                }
            }

            if (shouldSwap) {
                tweets[i + 1] = tweets[i]; 
                --i; 
            }
            else {
                break; 
            }
        }
        tweets[i + 1] = key; 
    }
}

void merge(std::vector<Tweet>& tweets, int left, int mid, int right, const std::string& sortBy, bool ascending) 
{  
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<Tweet> L(n1);
    std::vector<Tweet> R(n2);

    for (int i = 0; i < n1; i++) {
        L[i] = tweets[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = tweets[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
      if(sortBy == "tweetID"){
        if ((ascending && L[i].tweetID <= R[j].tweetID) || (!ascending && L[i].tweetID >= R[j].tweetID)) {
            tweets[k] = L[i];
            i++;
        } 
        else {
            tweets[k] = R[j];
            j++;
        }
        k++;
     }
     else if(sortBy == "favoriteCount"){
        if ((ascending && L[i].favoriteCount <= R[j].favoriteCount) || (!ascending && L[i].favoriteCount >= R[j].favoriteCount)) {
            tweets[k] = L[i];
            i++;
        } 
        else {
            tweets[k] = R[j];
            j++;
        }
        k++;
     }
     else if(sortBy == "retweetCount"){
        if ((ascending && L[i].tweetID <= R[j].retweetCount) || (!ascending && L[i].retweetCount >= R[j].retweetCount)) {
            tweets[k] = L[i];
            i++;
        } 
        else {
            tweets[k] = R[j];
            j++;
        }
        k++;
    }
    }

    while (i < n1) {
        tweets[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        tweets[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<Tweet>& tweets, int left, int right, const std::string& sortBy, bool ascending) 
{

    if (left >= right) 
        return;
    int mid = left + (right - left) / 2;

    
    mergeSort(tweets, left, mid, sortBy, ascending);
    mergeSort(tweets, mid + 1, right, sortBy, ascending);

    
    merge(tweets, left, mid, right, sortBy, ascending);
}
