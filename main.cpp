#include <iostream>
#include <fstream>
#include <filesystem>
#include <map>
#include <queue>
#include <bitset>

using namespace std;

struct Node {
    char ch;
    int freq;
    struct Node* left;
    struct Node* right;

    Node(char c, int f) {
        ch = c;
        freq = f;
        left = right = nullptr;
    }
};

struct Compare {
    bool operator()(Node* a, Node* b)
    {
        if(a->freq == b->freq)
            return a->ch > b->ch;

        return a->freq > b->freq;
    }
};

void generateHuffmanCodes(Node* root, string code, map<char, string>& codes) {
    if (root == nullptr) return;

    if (root->left == nullptr && root->right == nullptr) {
        codes[root->ch] = code;
        return;
    }

    generateHuffmanCodes(root->left, code+"0", codes);
    generateHuffmanCodes(root->right, code+"1", codes);
}

int main() {
    string input_file = "README.md";
    string output_file = input_file + "_compressed.huff";

    fstream file(input_file);

    if(!file) {
        cout << "File doesn't exist." << endl;
        return 1;
    }

    char ch;
    map<char, int> freq_map;
    while(file.get(ch))
        freq_map[ch]++;
    
    priority_queue<Node*, vector<Node*>, Compare> heap;
    for (const auto& pair : freq_map) {
        Node *newNode = new Node(pair.first, pair.second);
        heap.push(newNode);
    }

    while (heap.size() > 1) {
        Node* left = heap.top();
        heap.pop();
        Node* right = heap.top();
        heap.pop();
        int sumFreq = left->freq + right->freq;
        Node* parent = new Node('\0', sumFreq);
        parent->left = left;
        parent->right = right;
        heap.push(parent);
    }

    map<char, string> huffmanCodes;
    generateHuffmanCodes(heap.top(), "", huffmanCodes);
    
    file.clear();
    file.seekg(0, ios::beg);
    string newContent;
    while (file.get(ch)) {
        newContent += huffmanCodes[ch];
    }
    size_t bitlength = newContent.length();
    file.close();

    ofstream compressed_file(output_file, ios::binary);
    if(compressed_file.is_open()) {
        /* Format of compressed file:
        ---------------------------------
        1. Number of unique characters
            Character 1
            Frequency 1
            ...
            Character n
            Frequency n
        ---------------------------------
        2. Bit length (total length)
        ---------------------------------
        3. Compressed bytes (actual data)
        ---------------------------------
        */

        size_t uniqueChars = freq_map.size();
        compressed_file.write(reinterpret_cast<char*>(&uniqueChars), sizeof(uniqueChars));

        for (auto& pair : freq_map) {
            char ch = pair.first;
            int freq = pair.second;
            compressed_file.write(&ch, sizeof(ch));
            compressed_file.write(reinterpret_cast<char*>(&freq), sizeof(freq));
        }

        compressed_file.write(reinterpret_cast<char*>(&bitlength), sizeof(bitlength));

        unsigned char currentByte = 0;
        int bitCount = 0;

        for (char c : newContent) {
            currentByte <<= 1;
            if (c == '1')
                currentByte |= 1;
            bitCount++;

            if (bitCount == 8) {
                compressed_file.write(reinterpret_cast<char*>(&currentByte), 1);
                currentByte = 0;
                bitCount = 0;
            }
        }
        if (bitCount > 0)
        {
            currentByte <<= (8 - bitCount);
            compressed_file.write(
                reinterpret_cast<char*>(&currentByte),
                1
            );
        }

        compressed_file.close();

        cout << "File compressed successfully." << endl << endl;
        cout << "Original file size: " << filesystem::file_size(input_file) << " bytes" << endl;
        cout << "Compressed file size: " << filesystem::file_size(output_file) << " bytes" << endl;
    } else {
        cout << "File opening failed." << endl;
    }
    
    return 0;
}
