#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;
vector<string> readFile(string& filename);
void printVector(vector<string>& vect);

int main() {
    string user_in = "";
    vector<string> lines;
    while (true) {
        cout << "Enter the filename: ";
        if (!(cin >> user_in)) return 1;
        try {
            lines = readFile(user_in);
            break; // success
        } catch (int e) {
            if (e == 1) {
                cout << "Error: File not found." << endl;
            } else {
                cout << "Unknown error." << endl;
            }
            // loop again
        }
    }
    cout << "Your file contains the following lines: " << endl;
    printVector(lines);
    cout << "Program finished." << endl;
    return 0;
}

struct FileError : runtime_error {
    int error_code;
    FileError(int code, const string& message) : runtime_error(message), error_code(code) {
    }
    
};

vector<std::string> readFile(string& filename) {
    vector<string> lines;
    ifstream file(filename);
    if (!file) throw 1; // File not found
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    cout << "File read successfully." << endl;
    return lines;
}

void printVector(vector<string>& vect) {
    int count = 1;
    for(auto itr = vect.begin(); itr != vect.end(); ++itr) {
        cout << count << ": " << *itr << endl;
        count += 1;
    }
}