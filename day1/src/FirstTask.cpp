#include <iostream>
#include <fstream>

using namespace std;

int main() {
    string line; 
    string fileName = "../data/Task1Input.txt";
    string digits = "0123456789";
    int acc = 0;
    ifstream inStream(fileName, ios_base::in);

    while (getline(inStream, line)) {
        // cout << line << endl;
        std::size_t startIdx = line.find_first_of(digits);
        std::size_t endIdx = line.find_last_of(digits);
        // cout << line[startIdx] << "," << line[endIdx] << "," << (line[startIdx] - 48) * 10 + (line[endIdx] - 48) << endl << endl;
        acc += (line[startIdx] - 48) * 10 + (line[endIdx] - 48);
    }
    cout << "Result: " << acc << endl;
}