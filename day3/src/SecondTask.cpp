#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <cctype>
#include <map>

using namespace std;

string filePath = "../data/Schematic.txt";
regex numberRegexpr("(\\d+)");

struct coordinates {
    int x;
    int y;
    bool operator==(const coordinates &o) const {
        return x == o.x && y == o.y;
    }
    bool operator<(const coordinates &o) const {
        return x < o.x || (x == o.x && y < o.y);
    }
};

int main () {
    string line;
    vector<string> file;
    int lineNum = 0;
    int acc = 0;
    map<coordinates, vector<int>> coordinateNumbersMap;

    ifstream inStream(filePath);
    while (getline(inStream, line)) {
        file.push_back(line);
    }

    for (const auto& line : file) {
        auto first = line.begin();
        auto last = line.end();
        match_results<decltype(first)> match;
        int numberStart = 0;
        int numberEnd = 0;
        while (regex_search(first, last, match, numberRegexpr)) {
            int symbolLineSearchStart = lineNum <= 0 ? 0 : lineNum - 1;
            int symbolLineSearchEnd = lineNum >= file.size() - 1 ? file.size() - 1 : lineNum + 1;
            int symbolColSearchStart;
            int symbolColSearchEnd;
            bool gearFound = false;
            struct coordinates gearCoordinates;
            
            // cout << match.str();
            
            numberStart += match.position();
            numberEnd += match.position() + match.length() - 1;
            symbolColSearchStart = numberStart <= 0 ? 0 : numberStart - 1;
            symbolColSearchEnd = numberEnd >= line.size() - 1 ? line.size() - 1 : numberEnd + 1;
            numberStart = numberEnd + 2;
            numberEnd += 2;

            // cout << ": " << symbolLineSearchStart << ", " << symbolLineSearchEnd << ";; " << symbolColSearchStart << ", " << symbolColSearchEnd;
            for (auto lineIdx = symbolLineSearchStart; lineIdx <= symbolLineSearchEnd; ++lineIdx) {
                for (auto colIdx = symbolColSearchStart; colIdx <= symbolColSearchEnd; ++colIdx) {
                    if (file[lineIdx][colIdx] == '*') {
                        gearFound = true;
                        gearCoordinates = {colIdx, lineIdx};
                        break;
                    }
                }
            }
            if (gearFound) {
                int gearLineStart = gearCoordinates.y <= 0 ? 0 : gearCoordinates.y - 1;
                int gearLineEnd = gearCoordinates.y >= file.size() - 1 ? file.size() - 1 : gearCoordinates.y + 1;
                int gearColStart = gearCoordinates.x <= 0 ? 0 : gearCoordinates.x - 1;
                int gearColEnd = gearCoordinates.x >= line.size() - 1 ? line.size() - 1 : gearCoordinates.x + 1;

                // cout << gearLineStart << ", " << gearLineEnd << ";; " << gearColStart << ", " << gearColEnd << endl;
                int number = strtol(match.str().c_str(), nullptr, 10);
                auto mapIter = coordinateNumbersMap.find(gearCoordinates);
                if (mapIter != coordinateNumbersMap.end()) {
                    mapIter->second.push_back(number);
                } else {
                    coordinateNumbersMap.insert({gearCoordinates, vector<int>(1, number)});
                }
            }

            if (match.suffix().str().empty()) {
                break;
            }
            first = next(match.suffix().first);
        }
        ++lineNum;
    }
    for (const auto& mapEntry : coordinateNumbersMap) {
        if (mapEntry.second.size() > 1) {
            int multiplication = 1;
            for (const auto& number : mapEntry.second) {
                multiplication *= number;
            }
            acc += multiplication;
        }
    }
    cout << "Result: " << acc << endl;
}