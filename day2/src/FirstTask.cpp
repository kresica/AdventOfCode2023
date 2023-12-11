#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <map>

using namespace std;

int maxRed = 12;
int maxGreen = 13;
int maxBlue = 14;
regex redRegexpr("(.*?)(\\d+)\\s+red.*");
regex greenRegexpr("(.*?)(\\d+)\\s+green.*");
regex blueRegexpr("(.*?)(\\d+)\\s+blue.*");

map<int, regex> regMaxMap {
    {maxRed, redRegexpr},
    {maxGreen, greenRegexpr},
    {maxBlue, blueRegexpr}
};

vector<string> split (const string &s, char delim) {
    vector<string> result;
    stringstream ss(s);
    string item;

    while (getline(ss, item, delim)) {
        const string whitespace = " ";
        const auto itemBegin = item.find_first_not_of(whitespace);
        const auto itemEnd = item.find_last_not_of(whitespace);
        item = item.substr(itemBegin, itemEnd - itemBegin + 1);
        result.push_back(item);
    }
    return result;
}

int main () {
    string line;
    string fileName = "../data/Games.txt";
    ifstream inStream(fileName, ios_base::in);
    regex gameRegexpr("Game (\\d+):\\s+(.*)");
    int acc = 0;

    while (getline(inStream, line)) {
        smatch sm;
        int gameNum;
        string gameResult;
        bool impossibleGame = false;

        regex_match(line, sm, gameRegexpr);
        gameNum = strtol(sm[1].str().c_str(), nullptr, 10);
        gameResult = sm[2].str();

        // cout << gameNum << endl;
        for (string set : split(gameResult, ';')) {
            smatch smSet;

            // cout << set << endl;
            for (const auto& regMax : regMaxMap) {
                int numColor;
                
                regex_match(set, smSet, regMax.second);
                numColor = strtol(smSet[2].str().c_str(), nullptr, 10);
                if (numColor > regMax.first) {
                    impossibleGame = true;
                    break;
                }
            }
            if (impossibleGame) {
                break;
            }
        }
        // cout << endl;
        if (!impossibleGame) {
            acc += gameNum;
        }
        impossibleGame = false;
    }

    cout << "Result: " << acc << endl;
}