#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <map>
#include <cmath>

using namespace std;

#define RED     (0)
#define GREEN   (1)
#define BLUE    (2)

typedef struct {
    int maxNum;
    regex regexpr;
} colorStruct_t;

int maxRed = 0;
int maxGreen = 0;
int maxBlue = 0;
regex redRegexpr("(.*?)(\\d+)\\s+red.*");
regex greenRegexpr("(.*?)(\\d+)\\s+green.*");
regex blueRegexpr("(.*?)(\\d+)\\s+blue.*");

map<int, colorStruct_t> colorStruct {
    {RED, {maxRed, redRegexpr}},
    {GREEN, {maxGreen, greenRegexpr}},
    {BLUE, {maxBlue, blueRegexpr}}
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
    vector<int> acc = {1, 1, 1};
    int accSet = 1;
    int accTotal = 0;

    while (getline(inStream, line)) {
        smatch sm;
        string gameResult;
        vector<int> maxColor = {0, 0, 0};

        regex_match(line, sm, gameRegexpr);
        gameResult = sm[2].str();

        for (string set : split(gameResult, ';')) {
            smatch smSet;

            // cout << set << endl;
            for (auto& color : colorStruct) {
                int numColor;
                
                regex_match(set, smSet, color.second.regexpr);
                numColor = strtol(smSet[2].str().c_str(), nullptr, 10);
                if (numColor > maxColor[color.first]) {
                    maxColor[color.first] = numColor;
                }
            }
        }
        for (auto& color : colorStruct) {
            // cout << maxColor[color.first] << endl << endl;
            accSet *= maxColor[color.first];
        }
        accTotal += accSet;
        accSet = 1;
    }

    cout << "Result: " << accTotal << endl;
}