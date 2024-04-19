// Libraries
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

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

      // Check if a filename is provided
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    // Open the file using the filename provided in the command line
    ifstream file(argv[1]);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << argv[1] << endl;
        return 1;
    }

    // Read the file into a stringstream
    stringstream buffer;
    buffer << file.rdbuf();
    
    // Close the file
    file.close();

    // Convert the stringstream to a string
    string test = buffer.str();

  // Converts string to lowercase (counting grams is not case sensitive)
  for (auto iter = test.begin(); iter != test.end(); iter++)
  {
    *iter = tolower(*iter);
  }

    cout << endl;
    cout << "PRINTING ONE GRAMS!" << endl << endl;

    map<char, int> oneGramMap = oneGram(test);

    // Create a vector and copy elements from the map
    vector<pair<char, int>> oneGramVec(oneGramMap.begin(), oneGramMap.end());

    // Sort the vector by the second element of the pair (value) in descending order
    sort(oneGramVec.begin(), oneGramVec.end(), [](const pair<char, int> &a, const pair<char, int> &b) {
        return a.second > b.second;
    });

    // Print all elements (or modify to print top N elements similar to the two gram example)
    for (auto &[key, value] : oneGramVec) {
        cout << key << ": " << value << endl;
    }

  // used to count the top 10 numbers of the bi-grams and tri-grams
  int count = 0;

  cout << endl;
  cout << "PRINTING TWO GRAMS!" << endl << endl;

  // Establish two gram map
  map<string, int> twoGramMap = twoGram(test);

  // Create a vector and copy the elements from the map
  vector<pair<string, int>> twoGramVec(twoGramMap.begin(), twoGramMap.end());

  // Sort the vector by the second element of the pair (value) in descending order
  sort(twoGramVec.begin(), twoGramVec.end(), [](const pair<string, int> &a, const pair<string, int> &b)
       { return a.second > b.second; });

  // Print the top 10 elements
  for (auto &[key, value] : twoGramVec)
  {
    cout << key << ": " << value << endl;
    if (++count == 10)
      break;
  }
  
   cout << endl;
   cout << "PRINTING THREE GRAMS!" << endl << endl;

  // Establish three gram map
  map<string, int> threeGramMap = threeGram(test);

  // Create a vector and copy the elements from the map
  vector<pair<string, int>> threeGramVec(threeGramMap.begin(), threeGramMap.end());

  // Sort the vector by the second element of the pair (value) in descending order
  sort(threeGramVec.begin(), threeGramVec.end(), [](const pair<string, int> &a, const pair<string, int> &b)
       { return a.second > b.second; });

  // Print the top 10 elements
  // reset count to 0
  count = 0;
  for (auto &[key, value] : threeGramVec)
  {
    cout << key << ": " << value << endl;
    if (++count == 10)
      break;
  }

  return 0;
}
