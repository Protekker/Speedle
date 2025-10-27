#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <random>

using namespace std;


int main(){
    string correctword = "PLUMP";
    // vector<string> words = {"APPLE","PLUMP","COULD","SHOWS","PHONE"};
    string guess;
    int lives = 6;
    cout << "Enter a five letter word (CAPS)\n";
    cin >> guess;
    while(guess != correctword && lives > 0){
        if (guess.length() == 5){
            for(int i=0;i<5;i++)
                if (guess[i] == correctword[i])
                    cout << "\033[32m" << guess[i] << "\033[0m";
                else if (correctword.find(guess[i]))
                    cout << "\033[33m" << guess[i] << "\033[0m";
                else
                    cout << guess[i];
                lives--;
                if (lives == 0){
                    cout << "\nYOU LOST";
                }
                cout << "\n";
                cin >> guess;
        }
        else{
            cout << "Not long enough, enter five letters\n";
            cin >> guess;
        }
    }
}

/* TODO
User enter 5 letter word else not ok
if letter correct make green, else yellow.
6 attemps, display word at the end

Have the word be chosen on random from a list of words 
Testing if push worked
*/