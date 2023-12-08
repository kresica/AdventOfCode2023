#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    string line; 
    string fileName = "../data/Task1Input.txt";
    string digits = "0123456789";
    vector<string> digitsWritten = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    int acc = 0;
    ifstream inStream(fileName, ios_base::in);

    while (getline(inStream, line)) {
        int leftDigit;
        int rightDigit;
        int startIdx = line.find_first_of(digits);
        int endIdx = line.find_last_of(digits);
        int writtenStartIdx = -1;
        int writtenEndIdx = -1;
        int loopIdx = 0;
        vector<int> writtenDigitInt = {-1, -1};

        cout << line << endl;
        for (string digit : digitsWritten) {
            int tempWrittenStartIdx = line.find(digit);
            int tempWrittenEndIdx = line.rfind(digit);
            if ((tempWrittenStartIdx != -1) && ((writtenStartIdx == -1) || (tempWrittenStartIdx < writtenStartIdx))) {
                writtenStartIdx = tempWrittenStartIdx;
                writtenDigitInt[0] = loopIdx;
            }
            if ((tempWrittenEndIdx != -1) && ((writtenEndIdx == -1) || (tempWrittenEndIdx > writtenEndIdx))) {
                writtenEndIdx = tempWrittenEndIdx;
                writtenDigitInt[1] = loopIdx;
            }
            ++loopIdx;
        }
        leftDigit = ((writtenDigitInt[1] == -1) || (startIdx < writtenStartIdx)) ? line[startIdx] - 48 : writtenDigitInt[0];
        rightDigit = ((writtenDigitInt[1] == -1) || (endIdx > writtenEndIdx)) ? line[endIdx] - 48 : writtenDigitInt[1];
        cout << leftDigit << "," << rightDigit << "," << leftDigit * 10 + rightDigit << endl << endl;
        acc += leftDigit * 10 + rightDigit;
    }
    cout << "Result: " << acc << endl;
}