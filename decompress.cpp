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
        left=nullptr;
        right=nullptr;
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
    
int main()
{
    string inputFile="input.txt_compressed.huff";
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
    size_t bitlength;
    file.read(reinterpret_cast<char*>(&bitlength),sizeof(bitlength));

    vector<unsigned char> compressed_data;

    unsigned char byte;
    while(file.read(reinterpret_cast<char*>(&byte),1)){
        compressed_data.push_back(byte);
    }

cout << endl;
    ofstream output(outputFile,ios::binary);
    if(!output){
        cout<<"cannot create the decompressed file";
        return 1;
    }

    Node *current=root;

    size_t bitsread = 0;
    for(unsigned char byte : compressed_data){
        for(int i = 7;i>=0;i--){
            if(bitsread==bitlength)
                break;
            
            bool bit = (byte >> i) & 1;
            if(bit)
                current = current->right;
            
            else
                current = current->left;
            
            if(current->left==nullptr && current->right==nullptr){
                output.put(current->ch);
                current = root;
            }
            bitsread++;
        }
        if(bitsread==bitlength)
        break;
    }
    output.close();
    file.close();

    cout<<"file decompression successfull"<<endl;

 
    deleteTree(root);
    return 0;


}   


