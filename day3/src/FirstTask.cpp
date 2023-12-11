#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <cctype>

using namespace std;

string filePath = "../data/Schematic.txt";
regex numberRegexpr("(\\d+)");

int main () {
    string line;
    vector<string> file;
    int lineNum = 0;
    int acc = 0;

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
            bool symbolFound = false;
            
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
                    if ((file[lineIdx][colIdx] != '.') && !isdigit(file[lineIdx][colIdx])) {
                        symbolFound = true;
                        acc += strtol(match.str().c_str(), nullptr, 10);
                        break;
                    }
                }
                if (symbolFound) {
                    // cout << " HAS!" << endl;
                    break;
                }
            }
            if (!symbolFound) {
                // cout << endl;
            }

            if (match.suffix().str().empty()) {
                break;
            }
            first = next(match.suffix().first);
        }
        ++lineNum;
    }
    cout << "Result: " << acc << endl;
}