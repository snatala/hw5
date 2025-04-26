#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void findHelper(const std::string& in, std::string& floater, const std::set<std::string>& dict, 
int nextDash, int numDash, std::string& word, std::set<std::string>& result)
{
    if(word.size() - nextDash < floater.size()){
        return; //if there are more floating chars than spaces left to fill
    }

    if(nextDash == word.size()){
        if(word.size() == in.size()){ // if word is valid
            if(floater.size() == 0 && dict.find(word) != dict.end()){
                result.insert(word); //insert into results
                return;
            }
        }
        return;
    }
    if(word[nextDash] != '-'){
        findHelper(in, floater, dict, nextDash+1, numDash, word, result);
        return;
    }

    if(numDash == floater.size()){
        for(int i = 0; i < floater.size(); i++){
            word[nextDash] = floater[i];
            string oldFloater = floater;
            floater = floater.substr(0, i) + floater.substr(i + 1);


            findHelper(in, floater, dict, nextDash+1, numDash-1, word, result);
            floater = oldFloater;
        }
    }
    else{
        for(char l = 'a'; l <= 'z'; ++l){
            string oldFloater = floater;
            int index = floater.find(l);

            if(index != std::string::npos){
                word[nextDash] = floater[index];

                floater = floater.substr(0,index) + floater.substr(index+1);
            }
        
            word[nextDash] = l;
            findHelper(in, floater, dict, nextDash+1, numDash-1, word, result);
            floater = oldFloater;
        }
    }

    word[nextDash] = '-';
}

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    std::set<std::string> result;
    std::string word = in;
    
    // Add your code here
    string newFloating = floating;

    int numDash = 0;

    for(int i = 0; i < in.size(); i++){
        if(in[i] == '-'){
            numDash++;
        }
    }

    findHelper(in, newFloating, dict, 0, numDash, word, result);
    return result;
}

// Define any helper functions here
