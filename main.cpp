#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

string readFile(const string &filename, int &length) {
    ifstream file(filename, ios::in | ios::binary);

    if (!file) {
        cerr << "Error: Could not open file!" << endl;
    }

    // Get file length
    file.seekg(0, ios::end);       // move to end
    length = file.tellg(); // get position (file size)
    file.seekg(0, ios::beg);       // move back to start

    // Read file contents into a string
    string contents;
    contents.resize(length);
    file.read(&contents[0], length);

    file.close();

    cout << "File length: " << length << " bytes\n";
    cout << "File contents:\n" << contents << endl;
    return contents;
}

int main() {
    string filename;
    int cols;

    cin >> filename;
    cin >> cols;

    int contentLength = 0;
    string contents = readFile(filename, contentLength);

    vector< vector<string> > chars;
    chars.reserve(cols);
    int i = 0, j = 0, stringItr = 0;

    vector<int> asciiChars;
    asciiChars.reserve(chars.size() * cols);
    int asciiOfCols = 0;
    {
        string strCols = to_string(cols);
        for (char c : strCols) {
            asciiOfCols += int(c);
        }
    }

    while (stringItr < contentLength) {
        j = 0;
        vector<string> row;
        row.reserve(cols + 1);
        while (j < cols && stringItr < contentLength) {
            row.push_back(contents.substr(stringItr, 1));
            asciiChars.push_back(contents[stringItr]);
            j++;
            stringItr++;
        }

        while (j < cols) {
            row.push_back(to_string(cols));
            asciiChars.push_back(asciiOfCols);
            j++;
        }
        chars.push_back(row);
    }

    string outputHex = "";
    for (int value : asciiChars) {
        stringstream ss;
        ss << std::hex << std::uppercase << value;
        outputHex.append(ss.str());
    }

    int outputLen = cols / 4 * 2;
    cout << "Output HEX: " << outputHex.substr(0, outputLen) << endl;

    return 0;
}