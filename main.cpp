#include <iostream>
#include "compress.h"
#include "decompress.h"

using namespace std;

int main() {
    int choice;

    cout << "===== Huffman Coding Compression =====" << endl << endl;
    cout << "Select an option to proceed: " << endl;
    cout << "1. Compress file" << endl;
    cout << "2. Decompress file" << endl;
    cout << "3. Exit" << endl << endl;
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        string input_file;
        cout << "Enter file path: ";
        getline(cin, input_file);
        compress(input_file);
    }
    else if (choice == 2) {
        string input_file, output_file;
        cout << "Enter compressed file path: ";
        getline(cin, input_file);
        cout << "Enter output file path: ";
        getline(cin, output_file);
        decompress(input_file, output_file);
    }

    return 0;
}