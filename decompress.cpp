#include<iostream>
#include<fstream>
#include<iomanip>
#include<map>
#include<queue>

using namespace std;

struct Node{

    char ch;
    size_t frequency;

    Node *left;
    Node *right;

    Node(char c,size_t frequency){
        char ch=c;
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

    priority_queue<Node*,vector<Node*>,Compare> minHeap;

    for(const auto &pair: freq_map){
        minHeap.push(new Node(pair.first, pair.second));
    }
    while(minHeap.size()>1){
            Node *left=minHeap.top();
            minHeap.pop();

            Node *right=minHeap.top();
            minHeap.pop();

            Node *parent = new Node('/0', left->frequency + right->frequency);
            parent->left=left;
            parent->right=right;
            minHeap.push(parent);

    }
}

