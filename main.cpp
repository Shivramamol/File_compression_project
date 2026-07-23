#include <iostream>
#include <fstream>
#include <map>

using namespace std;

int main() {
    fstream file("C:\\users\\ishaa\\downloads\\DSE26101519 Application Print.pdf");

    if(!file) {
        cout << "File doesn't exist." << endl;
        return 1;
    }

    file.seekg(0, ios::end);
    streamsize size = file.tellg();
    cout << "File size: " << size << " bytes" << endl;
    file.seekg(0, ios::beg);

    cout << endl;

    cout << "Contents of file: " << endl;
    char ch;
    map<char, int> freq;
    while(file.get(ch)) {
        cout << ch;
        freq[ch]++;
    }
    cout << endl << endl;
    
    file.close();

    cout << "Frequency of characters: "<< endl;
    for(auto pair : freq) {
        if (pair.first == '\n')
            cout << "newline: " << pair.second << endl;
        else if (pair.first == ' ')
            cout << "space: " << pair.second << endl;
        else
            cout << pair.first << ": " << pair.second << endl;
    }
    
    return 0;
}