// Libraries
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

string readFileToString(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

/*
 * If a special character is returned, the gram functions will skip testing that string
 */
bool charCheck(char ch)
{
  return ch < 97 || ch > 172;
}

/*
 * Takes in a string and counts the frequency of one-grams present in the string
 * Adds the character and the amount of that character to a map
 */
map<char, int> oneGram(string userString)
{
  map<char, int> oneGramMap;

  for (auto iter = userString.begin(); iter != userString.end(); iter++)
  {

    // Skips counting special characters in the string
    if (charCheck(*iter))
    {
      continue;
    }

    // Looks for the key in the map
    auto mapIter = oneGramMap.find(*iter);

    if (mapIter == oneGramMap.end())
    {
      // Key not found, insert new key with value 1 (starting the count of one-grams)
      oneGramMap.insert({*iter, 1});
    }
    else
    {
      // Key found, increment its value
      mapIter->second++;
    }
  }
  return oneGramMap;
}

/*
 * Takes in a string and counts the frequency of bi-grams present in the string
 * Adds the string and the amount of that character to a map
 */
map<string, int> twoGram(string userString)
{

  map<string, int> twoGramMap;

  for (int i = 0; i != userString.size() - 1; i++)
  {

    // Skips the count if there are special characters
    if (charCheck(userString[i]) || charCheck(userString[i + 1]))
    {
      continue;
    }

    // Two gram string
    string twoGramTest = userString.substr(i, 2);

    if (twoGramMap.find(twoGramTest) == twoGramMap.end())
    {
      twoGramMap.insert({twoGramTest, 1});
    }

    else
    {
      twoGramMap[twoGramTest]++;
    }
  }

  return twoGramMap;
};

/*
 * Takes in a string and counts the frequency of bi-grams present in the string
 * Adds the string and the amount of that character to a map
 */
map<string, int> threeGram(string userString)
{

  map<string, int> threeGramMap;

  for (int i = 0; i != userString.size() - 2; i++)
  {

    // Skips the count if there are special characters
    if (charCheck(userString[i]) || charCheck(userString[i + 1]) || charCheck(userString[i + 2]))
    {
      continue;
    }

    // Two gram string
    string threeGramTest = userString.substr(i, 3);

    if (threeGramMap.find(threeGramTest) == threeGramMap.end())
    {
      threeGramMap.insert({threeGramTest, 1});
    }

    else
    {
      threeGramMap[threeGramTest]++;
    }
  }

  return threeGramMap;
};

int main(int argc, char* argv[])
{
  string targetFilename;
  string target;
  int count = 0;

  // Get target file from standard input or command line argv
  if(argc < 2)
  {
    cout << "Please enter target for frequency analysis: ";
    cin >> targetFilename;
  }
  else
    targetFilename = argv[1];

  // Attempt to read file
  try
  {
    target = readFileToString(targetFilename);
  }
  catch(const exception& e)
  {
    cerr << e.what() << endl;
  }

  // Converts string to lowercase (counting grams is not case sensitive)
  for (auto iter = target.begin(); iter != target.end(); iter++)
  {
    *iter = tolower(*iter);
  }

  // Establish one gram map
  map<char, int> oneGramMap = oneGram(target);
  // Establish two gram map
  map<string, int> twoGramMap = twoGram(target);
  // Establish three gram map
  map<string, int> threeGramMap = threeGram(target);


  // Create a vector and copy the elements from the map
  vector<pair<char, int>> oneGramVec(oneGramMap.begin(), oneGramMap.end());
  sort(oneGramVec.begin(), oneGramVec.end(), [](const pair<char, int> &a, const pair<char, int> &b)
       { return a.second > b.second; });

  // Create a vector and copy the elements from the map
  vector<pair<string, int>> twoGramVec(twoGramMap.begin(), twoGramMap.end());
  // Sort the vector by the second element of the pair (value) in descending order
  sort(twoGramVec.begin(), twoGramVec.end(), [](const pair<string, int> &a, const pair<string, int> &b)
       { return a.second > b.second; });

  // Create a vector and copy the elements from the map
  vector<pair<string, int>> threeGramVec(threeGramMap.begin(), threeGramMap.end());
  // Sort the vector by the second element of the pair (value) in descending order
  sort(threeGramVec.begin(), threeGramVec.end(), [](const pair<string, int> &a, const pair<string, int> &b)
       { return a.second > b.second; });


  // iterators for while loop
  vector<pair<char,int>>::iterator i1 = oneGramVec.begin();
  vector<pair<string,int>>::iterator i2 = twoGramVec.begin();
  vector<pair<string,int>>::iterator i3 = threeGramVec.begin();

  cout << "OneGrams:Count" << "\t" << "TwoGrams:Count" << "\t" << "ThreeGrams:Count" << "\n\n";
  while(i1 != oneGramVec.end())
  {
    cout << i1->first << " : " << i1->second << "\t";

    if(count < 10)
    {
      if(i2 != twoGramVec.end())
        cout << i2->first << " : " << i2->second << "\t";
      if(i3 != threeGramVec.end())
        cout << i3->first << " : " << i3->second;
    }

    cout << endl;

    i1++;
    i2++;
    i3++;
    count++;
  }
  

  return 0;
}