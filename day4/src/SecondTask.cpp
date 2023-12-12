#include <iostream>
#include <fstream>
#include <regex>
#include <set>
#include <cmath>

using namespace std;

struct cardInfo {
    int id;
    int multiplicity;
};

int main () {
    string line;
    string filePath = "../data/Scratchcards.txt";
    regex taskRe("Card\\s+\\d+:\\s+(.*)\\|\\s+(.*)");
    regex numbers("\\s*(\\d+)\\.*");
    int numOfCards = 0;
    int loopIdx = 1;
    ifstream inStream(filePath);
    vector<string> file;
    vector<cardInfo> cards;

    while (getline(inStream, line)) {
        file.push_back(line);
        cards.push_back({.id = loopIdx, .multiplicity = 1});
        ++loopIdx;
    }

    loopIdx = 0;
    for (auto& fLine : file) {
        smatch match;
        string winning;
        string mine;
        set<int> winningSet;
        set<int> mineSet;
        vector<int> winners;
        auto card = cards[loopIdx];
        
        regex_match(fLine, match, taskRe);
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
        for (int multiplicity = 1; multiplicity <= winners.size(); ++multiplicity) {
            if (loopIdx + multiplicity < cards.size()) {
                cards[loopIdx + multiplicity].multiplicity += card.multiplicity;
            }
        }
        
        ++loopIdx;
    }

    for_each(cards.begin(), cards.end(), [&numOfCards](cardInfo card){numOfCards += card.multiplicity;});

    cout << "Result: " << numOfCards << endl;
}