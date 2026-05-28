/*
Mason Gross
Software Design Final Project
Extra: Using try/throw/catch exceptions in order to handle errors.
(Also uses file writing/reading too cus why not)
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
using namespace std;
vector<string> readFile(string& filename);
void printVector(vector<string>& vect);
void existingFile(string& file);
void newFile();
void wait(int ms);

int main() {
    string file = "";
    while(true) {
        vector<string> options = {"Read a file", "Write a file", "idk", "Exit"};
        string user_in = "";
        cout << "Welcome to the a program!" << endl;
        cout << "So what do u want?" << endl;
        printVector(options);
        cin >> user_in;
        if (user_in == "1") {
            vector<string> lines;
            while (true) {
                cout << "Enter the filename: ";
                if (!(cin >> user_in)) return 1; // if cin error, exit
                try {
                    lines = readFile(user_in);
                    file = user_in; // store the filename for later use
                    break; // success
                } catch (int e) {
                    if (e == 1) {
                        cout << "Error: File not found." << endl;
                    } else {
                        cout << "Unknown error." << endl;
                    }
                }
            }
            cout << "Your file contains the following lines: " << endl;
            printVector(lines);
        } else if (user_in == "2") {
            if(file != "") { //if the user used a file before
                existingFile(file);
            } else {
                newFile();
            }

        } else if (user_in == "3") {
            cout << "You chose idk." << endl;
        } else if (user_in == "4") {
            cout << "Exiting program." << endl;
            return 0;
        } else {
            cout << "Invalid option." << endl;
        }
    }
    return 0;
}

void existingFile(string& file) {
    string user_in = "";
    cout << "Would you like to modify " << file << "? (y/n)" << endl;
    cin >> user_in;
    if (user_in == "y") {
        try {
            cin.clear();
            auto tmp = readFile(file);
            printVector(tmp);
            cout << "What line would you like to replace? (Enter the line number)" << endl;
            cin >> user_in;
            int line_num = stoi(user_in);
            if(line_num >= 1 && line_num <= tmp.size()) {
                cout << "What would you like to replace " << tmp.at(line_num - 1) << " with?" << endl;
                cin >> user_in;
                cout << "Replacing " << tmp.at(line_num - 1) << " with " << user_in << "." << endl;
                tmp.at(line_num - 1) = user_in;
            } else {
                throw 2; // Line number out of range
            }
            ofstream writeFile(file);
            for(auto itr = tmp.begin(); itr != tmp.end(); ++itr) {
                writeFile << *itr << "\n";
            }
            writeFile.close();
        }
        catch (int e) {
            if (e == 1) {
                cout << "Error: File not found." << endl;
            } else if (e == 2) {
                cout << "Error: Line number out of range." << endl;
            } else {
                cout << "Unknown error." << endl;
            }
        }

    } else if(user_in == "n") {
        cout << "Okay, writing to a new file." << endl;
        newFile();
    } else {
        cout << "Invalid option." << endl;
    }
}

void newFile() {
    string user_in = "";
    string fileName = "";
    cout << "Enter the new filename: ";
    cin.ignore(1000, '\n'); //Why did it take so long to figure out that i needed .ignore and not .clear or smthin
    getline(cin, fileName);
    ofstream writeFile(fileName);
    cout << "Enter the lines you want to write to the file. Type END on a new line to finish." << endl;
    while(getline(cin, user_in)) {
        if (user_in == "END") break;
        writeFile << user_in << "\n";
    }
    writeFile.close();
    auto tmp = readFile(fileName);
    cout << "Your new file, " << fileName << ", contains the following lines: " << endl;
    printVector(tmp);
}

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

void wait_ms(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

int findIndex(vector<string>& v, string val) {
    int count = 0;
    for(auto itr = v.begin(); itr != v.end(); ++itr) {
      
        if (*itr == val) { //If the restaurant is found, the index is returned
            return count;
        }
        count += 1;
    }
  	
  	return -1; //If the restaurant is not found, -1 is returned
}

void printVector(vector<string>& vect) {
    int count = 1;
    for(auto itr = vect.begin(); itr != vect.end(); ++itr) {
        cout << count << ": " << *itr << endl;
        count += 1;
    }
    wait_ms(2000);
}