#include "tweet.h"
#include <chrono> // Zaman ölçümü için

using namespace :: std;

int main(){
  std::string inputFilePath = "./data/permutations/tweetsNS.csv";
  std::string outputFilePath = "./data/new.csv";

  std::vector<Tweet> tweets;
  tweets = readTweetsFromFile(inputFilePath);

  
  auto start = std::chrono::high_resolution_clock::now();
  bubbleSort(tweets ,"retweetCount", true);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = end - start;
  std::cout << "Süre: " << duration.count() << " ms" << std::endl;
  writeTweetsToFile(outputFilePath ,tweets);
  return EXIT_SUCCESS;
}