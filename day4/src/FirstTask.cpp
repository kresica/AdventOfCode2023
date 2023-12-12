#include <iostream>
#include <fstream>
#include <regex>
#include <set>
#include <cmath>

using namespace std;

int main () {
    string line;
    string filePath = "../data/Scratchcards.txt";
    regex taskRe("Card\\s+\\d+:\\s+(.*)\\|\\s+(.*)");
    regex numbers("\\s*(\\d+)\\.*");
    int acc = 0;
    ifstream inStream(filePath);

    while (getline(inStream, line)) {
        smatch match;
        string winning;
        string mine;
        set<int> winningSet;
        set<int> mineSet;
        vector<int> winners;
        
        regex_match(line, match, taskRe);
        winning = match[1].str();
        mine = match[2].str();

        while (regex_search(winning, match, numbers)) {
            winningSet.insert(strtol(match[1].str().c_str(), nullptr, 10));
            winning = match.suffix().str();
        }
        while (regex_search(mine, match, numbers)) {
            mineSet.insert(strtol(match[1].str().c_str(), nullptr, 10));
            mine = match.suffix().str();
        }

        set_intersection(winningSet.begin(), winningSet.end(), mineSet.begin(), mineSet.end(), back_inserter(winners));
        if (winners.size() > 0) {
            acc += pow(2, winners.size() - 1);
        }
    }

    cout << "Result: " << acc << endl;
}