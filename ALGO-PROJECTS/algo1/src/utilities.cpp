#include "tweet.h"

std::vector<Tweet> readTweetsFromFile(const std::string& filename) 
{
  std::vector<Tweet> tweets;
    std::ifstream file(filename);

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        if (!line.empty()) {
            std::stringstream ss(line);
            std::string item;

            std::getline(ss, item, ',');
            Tweet tweet;
            tweet.tweetID = std::stoll(item);

            std::getline(ss, item, ',');
            tweet.retweetCount = std::stoi(item);

            std::getline(ss, item, ',');
            tweet.favoriteCount= std::stoi(item);

            tweets.push_back(tweet);
        }
    }
    return tweets;
}

void writeTweetsToFile(const std::string& filename, const std::vector<Tweet>& tweets) 
{
 std::ofstream outFile(filename);

    outFile << "tweetID,retweetCount,favoriteCount\n";

    for (const auto& tweet : tweets) {
        outFile << tweet.tweetID << "," 
                << tweet.retweetCount << "," 
                << tweet.favoriteCount << "\n";
    }

    outFile.close(); 
}