/*
Spell Checker using custom dictionary
*/

#include <iostream>
#include <vector>
using namespace std;

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h> // for displaying colors
#endif // Windows
#define color_dark_red   4






struct TrieNode {
    bool terminating = false;
    TrieNode* children[26] = {NULL};
};

class Trie {
    TrieNode* root;
public:
    Trie();

    void insertWord(string word);
    bool searchWord(string word);
    bool deleteWord(string word);
    bool updateWord(string oldWord, string newWord);

    //vector<string, int> getDictionary();
};



#define underlineOn "\033[4m"
#define underlineOff "\033[0m"





Trie::Trie(){
    root = new TrieNode();
}


void Trie::insertWord(string word){
    TrieNode* currNode = root;
    for(char c: word){
        if (currNode->children[c - 'a']==NULL) {
            currNode->children[c - 'a'] = new TrieNode();        
        }
        currNode = currNode->children[c - 'a'];
    }    
    currNode->terminating = true;
}

bool Trie::searchWord(string word){
    TrieNode* currNode = root;
    for(char c: word){
        if( currNode->children[c - 'a'] != NULL) {        
            currNode = currNode->children[c - 'a'];
        }else{
            return false;
        }
    }
    return currNode->terminating;
}


bool Trie::deleteWord(string word){
    TrieNode* currNode = root;
    for(char c: word){
        if( currNode->children[c - 'a'] != NULL) {        
            currNode = currNode->children[c - 'a'];
        }else{
            return false;
        }
    }
    currNode->terminating = false;
    return true;
}


bool Trie::updateWord(string oldWord, string newWord){
    
    bool ret = deleteWord(oldWord);
    if(ret)
        this->insertWord(newWord);
    
    return ret;
}








int main(){

    Trie oTrie;

    vector<string> words = { "cat", "car", "cart", "ball", "bat", "bats"};
    for(string word: words)
        oTrie.insertWord(word);


    string s = "";
    while(true){
        char c = getchar(); 
        if(c == '\n'){ // break on enter
            oTrie.searchWord(s) ? cout << s : cout << 4 << s << underlineOff;
            cout << c;
            break;
        }
        if(c == ' '){ 
            oTrie.searchWord(s) ? cout << s : cout << 4 << s << underlineOff;
            s = "";
            cout << c;
        }
        else{
            s = s + char(c);
        }
    }    

    cout << endl << endl;
    return 0;
}