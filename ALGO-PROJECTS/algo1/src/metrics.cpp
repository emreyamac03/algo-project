#include "tweet.h"

int binarySearch(const std::vector<Tweet>& tweets, long long key, const std::string& sortBy)
{
    int low = 0;
    int high = tweets.size() - 1;
    if(sortBy == "tweetID"){
       while(low <= high){
         int mid = low + (high - low) / 2;
          if(tweets[mid].tweetID == key){
            return mid;
          }
          else if(tweets[mid].tweetID < key){
            low = mid + 1;  
          }
          else{
            high = mid - 1;
          } 
        }
    }
    else if(sortBy == "favoriteCount"){
        while(low <= high){
          int mid = low + (high - low) / 2;
          if(tweets[mid].favoriteCount == key){
             return mid;
          }
          else if(tweets[mid].favoriteCount < key){
             low = mid + 1;  
          }
          else{
            high = mid - 1;
          } 
        }    
    }
    else if(sortBy == "retweetCount"){
        while(low <= high){
          int mid = low + (high - low) / 2;
          if(tweets[mid].retweetCount == key){
             return mid;
          }
          else if(tweets[mid].retweetCount < key){
             low = mid + 1;  
          }
          else{
            high = mid - 1;
          } 
        }    
    }
   return -1; 
}

int countAboveThreshold(const std::vector<Tweet>& tweets, const std::string& metric, int threshold) 
{ 
    int tweetcounter = 0;
    if(metric == "favoriteCount"){
        for(auto tweet : tweets){
            if(tweet.favoriteCount > threshold){
                tweetcounter++;
            }
        }
    }
    else if(metric == "retweetCount"){
         for(auto tweet : tweets){
            if(tweet.retweetCount > threshold){
                tweetcounter++;
            }
        }
    }
    return tweetcounter;
}
