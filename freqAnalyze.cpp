// Libraries
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
 * If a special character is returned, the gram functions will skip testing that string
 */
bool charCheck(char ch)
{
  return ch == ' ' || ch == ',' || ch == '\'' || ch == '.' || ch == ';';
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

int main()
{

  // the given string from supporting PA3 docs
  string test = "bt jpx rmlx pcuv amlx icvjp ibtwxvr ci m lmt'r pmtn, mtn yvcjx cdxv mwmbtrj jpx amtngxrjbah uqct jpx qgmrjxv ci jpx ymgg ci jpx hbtw'r qmgmax; mtn jpx hbtw rmy jpx qmvj ci jpx pmtn jpmj yvcjx. jpxt jpx hbtw'r acutjxtmtax ymr apmtwxn, mtn pbr jpcuwpjr jvcufgxn pbl, rc jpmj jpx scbtjr ci pbr gcbtr yxvx gccrxn, mtn pbr htxxr rlcjx ctx mwmbtrj mtcjpxv. jpx hbtw avbxn mgcun jc fvbtw bt jpx mrjvcgcwxvr, jpx apmgnxmtr, mtn jpx rccjprmexvr. mtn jpx hbtw rqmhx, mtn rmbn jc jpx ybrx lxt ci fmfegct, ypcrcxdxv rpmgg vxmn jpbr yvbjbtw, mtn rpcy lx jpx btjxvqvxjmjbct jpxvxci, rpmgg fx agcjpxn ybjp ramvgxj, mtn pmdx m apmbt ci wcgn mfcuj pbr txah, mtn rpmgg fx jpx jpbvn vugxv bt jpx hbtwncl. jpxt amlx bt mgg jpx hbtw'r ybrx lxt; fuj jpxe acugn tcj vxmn jpx yvbjbtw, tcv lmhx htcyt jc jpx hbtw jpx btjxvqvxjmjbct jpxvxci. jpxt ymr hbtw fxgrpmoomv wvxmjge jvcufgxn, mtn pbr acutjxtmtax ymr apmtwxn bt pbl, mtn pbr gcvnr yxvx mrjctbrpxn. tcy jpx kuxxt, fe vxmrct ci jpx ycvnr ci jpx hbtw mtn pbr gcvnr, amlx btjc jpx fmtkuxj pcurx; mtn jpx kuxxt rqmhx mtn rmbn, c hbtw, gbdx icvxdxv; gxj tcj jpe jpcuwpjr jvcufgx jpxx, tcv gxj jpe acutjxtmtax fx apmtwxn; jpxvx br m lmt bt jpe hbtwncl, bt ypcl br jpx rqbvbj ci jpx pcge wcnr; mtn bt jpx nmer ci jpe ybrncl ci jpx wcnr, ymr icutn bt pbl; ypcl jpx hbtw txfuapmntxoomv jpe imjpxv, jpx hbtw, b rme, jpe imjpxv, lmnx lmrjxv ci jpx lmwbabmtr, mrjvcgcwxvr, apmgnxmtr, mtn rccjprmexvr; icvmrluap mr mt xzaxggxtj rqbvbj, mtn htcygxnwx, mtn utnxvrjmtnbtw, btjxvqvxjbtw ci nvxmlr, mtn rpcybtw ci pmvn rxtjxtaxr, mtn nbrrcgdbtw ci ncufjr, yxvx icutn bt jpx rmlx nmtbxg, ypcl jpx hbtw tmlxn fxgjxrpmoomv; tcy gxj nmtbxg fx amggxn, mtn px ybgg rpcy jpx btjxvqvxjmjbct.";

  // Converts string to lowercase (counting grams is not case sensitive)
  for (auto iter = test.begin(); iter != test.end(); iter++)
  {
    *iter = tolower(*iter);
  }

  cout << "PRINTING ONE GRAMS!" << endl << endl;

  // Establish one gram map
  map<char, int> oneGramMap = oneGram(test);

  // Prints out Key/Value pairs for one gram
  for (auto iter = oneGramMap.begin(); iter != oneGramMap.end(); iter++)
  {
    cout << iter->first << ":" << iter->second << endl;
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
