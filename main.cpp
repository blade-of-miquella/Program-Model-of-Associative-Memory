#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream> 
#include <iomanip>

using namespace std;

class AMemory {
public:
    AMemory() {}

    void initMemory(int rows, int cols) {
        for (int row = 0; row < rows; row++) {
            string temp = "";
            for (int col = 0; col < cols; col++) {
                temp += alphabet[rand() % alphabet.size()];
            }
            memory.push_back(temp);
        }
    }

    void TO_SHOW(bool isSearch = false, string data = "", string comparisonType = "") {
        const int memWidth = 15;
        const int patWidth = 15;  
        const int compWidth = 15;  
        const int iterWidth = 8;   
        const int matchWidth = 15; 

        if (isSearch) {
            int totalWidth = 1 + memWidth + 1 + patWidth + 1 + compWidth
                + memory.size() * (iterWidth + 1)
                + matchWidth + 1;
            cout << string(totalWidth, '-') << "\n";
            cout << "|" << setw(memWidth) << left << "Memory"
                << "|" << setw(patWidth) << left << "Pattern"
                << "|" << setw(compWidth) << left << "Comparison";
            for (size_t i = 0; i < memory.size(); i++) {
                string header = "Iter " + to_string(i + 1);
                cout << "|" << setw(iterWidth) << left << header;
            }
            cout << "|" << setw(matchWidth) << left << "Matched" << "|\n";
            cout << string(totalWidth, '-') << "\n";

            for (size_t row = 0; row < memory.size(); row++) {
                cout << "|" << setw(memWidth) << left << memory[row];
                if (row == 0) {
                    cout << "|" << setw(patWidth) << left << data
                        << "|" << setw(compWidth) << left << comparisonType;
                }
                else {
                    cout << "|" << setw(patWidth) << left << ""
                        << "|" << setw(compWidth) << left << "";
                }
                for (size_t col = 0; col < memory.size(); col++) {
                    string result = "";
                    if (col < row)
                        result = "+";
                    else if (col == row && col < found.size())
                        result = found[col];
                    else
                        result = "";
                    cout << "|" << setw(iterWidth) << left << result;
                }
                string matched = "No";
                if (row < found.size() && found[row] == "+")
                    matched = "Yes";
                cout << "|" << setw(matchWidth) << left << matched << "|\n";
            }
            cout << string(totalWidth, '-') << "\n";
        }
        else {
            int totalWidth = 1 + memWidth + 1;
            cout << string(totalWidth, '-') << "\n";
            for (const auto& row : memory) {
                cout << "|" << setw(memWidth) << left << row << "|\n";
            }
            cout << string(totalWidth, '-') << "\n";
        }
    }

    void TO_ADD(string data) {
        cout << "Write your data to the memory...\n";
        memory.push_back(data);
    }

    void TO_SEARCH(string data, const string& comparisonType) {
        found.clear();
        cout << "Searching memory with criteria \"" << comparisonType << "\"...\n";
        int iteration = 1;
        bool isSearch = false;
        for (const auto& row : memory) {
            if ((comparisonType == "=" && row == data) ||
                (comparisonType == ">" && row > data) ||
                (comparisonType == ">=" && row >= data) ||
                (comparisonType == "<" && row < data) ||
                (comparisonType == "<=" && row <= data) ||
                (comparisonType == "<>" && row != data)) {
                found.push_back("+");
            }
            else found.push_back("-");
        }
        TO_SHOW(true, data, comparisonType);
    }

    void TO_LOAD(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cout << "Error: Could not open file " << filename << endl;
            return;
        }
        string line;
        while (getline(file, line)) { 
            stringstream ss(line); 
            string word;
            while (ss >> word) {  
                memory.push_back(word); 
            }
        }
        file.close();
        cout << "Words loaded from file: " << filename << endl;
    }

private:
    vector<string> memory;
    vector<string> found;
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
};

int main() {
    srand(time(0));
    AMemory memory;
    char answer;
    cout << "Wanna fill memory with random data? (y/n): ";
    cin >> answer;
    if (tolower(answer) == 'y') {
        int cols = 0, rows = 0;
        cout << "Enter number of rows and cols: ";
        cin >> rows >> cols;
        memory.initMemory(rows, cols);
    }
    int choice;
    do {
        cout << "\nMenu:" << endl;
        cout << "1. Show memory content;" << endl;
        cout << "2. Add content to memory;" << endl;
        cout << "3. Search content in memory;" << endl;
        cout << "4. Load words from file;" << endl;
        cout << "0. Exit;" << endl;
        cin >> choice;

        switch (choice) {
        case 1: {
            memory.TO_SHOW();
            break;
        }
        case 2: {
            string add;
            cout << "Type new string you want to add: ";
            cin >> add;
            memory.TO_ADD(add);
            break;
        }
        case 3: {
            string searchKey, comparisonType;
            cout << "Enter string to search: ";
            cin >> searchKey;
            cout << "Enter comparison type (=, >, >=, <, <=, <>): ";
            cin >> comparisonType;
            memory.TO_SEARCH(searchKey, comparisonType);
            break;
        }
        case 4: { 
            string filename;
            cout << "Enter filename to load words: ";
            cin >> filename;
            memory.TO_LOAD(filename);
            break;
        }
        case 0: {
            cout << "Exiting...\n";
            break;
        }
        default: {
            cout << "Invalid choice!\n";
        }
        }
    } while (choice != 0);

    return 0;
}
