#include<iostream>
#include<fstream>
#include<iomanip>
#include<map>
#include<queue>
#include <vector>
#include <bitset>

using namespace std;

struct Node{

    char ch;
    size_t frequency;

    Node *left;
    Node *right;

    Node(char c,size_t frequency){
         this->ch=c;
        this->frequency=frequency;
        left=right=nullptr;
    }

};

struct Compare{
    bool operator() (Node* l,Node* r){
        if(l->frequency==r->frequency){
            return l->ch>r->ch;
        }
        return l->frequency>r->frequency;
    }
};
 void deleteTree(Node* root)
    {
    if(root == nullptr)
        return;

    deleteTree(root->left);
    deleteTree(root->right);

    delete root;
    }
    void generateHuffmanCodes(Node* root, string code, map<unsigned char, string>& codes)
{
    if (root == nullptr)
        return;

    if (root->left == nullptr && root->right == nullptr)
    {
        codes[root->ch] = code;
        return;
    }

    generateHuffmanCodes(root->left, code + "0", codes);
    generateHuffmanCodes(root->right, code + "1", codes);
}

int main()
{
    string inputFile="large_input.txt_compressed.huff";
    string outputFile="decompressed.txt";

    ifstream file(inputFile,ios::binary);

    if(!file){
        cout<<"Error opening the compressed file"<<endl;
        return 1;
    }

    size_t uniqueChars;
    file.read(reinterpret_cast<char*>(&uniqueChars), sizeof(uniqueChars));

   map<unsigned char, size_t> freq_map; 
    for(size_t i=0; i<uniqueChars; i++){
        char ch;
        size_t freq;
        file.read(&ch, sizeof(ch));
        file.read(reinterpret_cast<char*>(&freq),sizeof(freq));
        freq_map[ch] = freq;
    }
    cout << "Frequency Table:\n";


    priority_queue<Node*,vector<Node*>,Compare> minHeap;

    for(const auto &pair: freq_map){
        minHeap.push(new Node(pair.first, pair.second));
    }
    while(minHeap.size()>1){
            Node *left=minHeap.top();
            minHeap.pop();

            Node *right=minHeap.top();
            minHeap.pop();

            Node *parent = new Node('\0', left->frequency + right->frequency);
            parent->left=left;
            parent->right=right;
            minHeap.push(parent);

    }
    

    Node *root = minHeap.top();
//cout << "Root frequency = " << root->frequency << endl;
    map<unsigned char, string> huffmanCodes;
generateHuffmanCodes(root, "", huffmanCodes);
cout << "\n========== DECOMPRESSOR HUFFMAN CODES ==========\n";

for (const auto &pair : huffmanCodes)
{
    if (pair.first == ' ')
        cout << "[SPACE]";
    else if (pair.first == '\n')
        cout << "[NEWLINE]";
    else if (pair.first == '\t')
        cout << "[TAB]";
    else
        cout << pair.first;

    cout << " -> " << pair.second << endl;
}

cout << "===============================================\n";

    size_t bitlength;
    file.read(reinterpret_cast<char*>(&bitlength),sizeof(bitlength));

    vector<unsigned char> compressed_data;

    unsigned char byte;
    while(file.read(reinterpret_cast<char*>(&byte),1)){
        compressed_data.push_back(byte);
    }
cout << "\nBits read from file:\n";

int printed = 0;

for(unsigned char b : compressed_data)
{
    for(int i = 7; i >= 0; i--)
    {
        if(printed == 100)
            break;

        cout << ((b >> i) & 1);

        printed++;
    }

    if(printed == 100)
        break;
}

cout << endl;
    ofstream output(outputFile,ios::binary);
    if(!output){
        cout<<"cannot create the decompressed file";
        return 1;
    }

    Node *current = root;
string path = "";

size_t bitsread = 0;

for (unsigned char byte : compressed_data)
{
    for (int i = 7; i >= 0; i--)
    {
        if (bitsread == bitlength)
            break;

        bool bit = (byte >> i) & 1;

        path += (bit ? '1' : '0');

        if (bit)
            current = current->right;
        else
            current = current->left;

        if (current->left == nullptr && current->right == nullptr)
        {
            cout << path << " -> " << current->ch << endl;

            output.put(current->ch);

            current = root;
            path.clear();
        }

        bitsread++;
    }
}
    output.close();
    file.close();

    cout<<"file decompression successfull"<<endl;

 
    deleteTree(root);
    return 0;


}   


