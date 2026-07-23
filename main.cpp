#include <iostream>
#include <map>
#include <fstream>
using namespace std;

int main(){
        fstream file("input.txt");
        
        if(!file){
            cout << "Error opening file." << endl;
            return 1;
        }

        else{
            map<char,int> frequency;
            char ch;
            while(file.get(ch)){
                frequency[ch]++;
            }

            file.close();

            cout<<"Character Frequency in the file:" << endl;
            for(auto pair:frequency){
                if(pair.first == '\n'){
                    cout<<"\\n : "<<pair.second<<endl;
                }
                else if(pair.first == ' '){
                    cout<<"Space : "<<pair.second<<endl;
                }
                else
                cout<<pair.first<<" : "<<pair.second<<endl;
            }
            return 0;
        }


}