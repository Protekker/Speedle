#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;


int main(){
    // string correctword = "PLUMP";
    vector<string> words = {"APPLE","PLUMP","COULD","SHOWS","PHONE"};
    // vector<int> v = {0, 1, 2, 3, 4};
    random_device random_device;
    mt19937 engine{random_device()};
    uniform_int_distribution<int> dist(0, words.size() - 1);
    int random_element = dist(engine);
    string correctword = words.at(random_element);
    // string correctword = words.at(randomIndex);
    string guess;
    int lives = 6;
    cout << "Enter a five letter word (CAPS)\n";
    getline(cin, guess);
    transform(guess.begin(), guess.end(), guess.begin(), ::toupper);
    // cin >> guess;
    while(guess != correctword && lives > 0){
        if (guess.length() == 5){
            for(int i=0;i<5;i++)
                if (guess[i] == correctword[i])
                    cout << "\033[32m" << guess[i] << "\033[0m"; // green
                else if (correctword.find(guess[i]) != string::npos)
                    cout << "\033[33m" << guess[i] << "\033[0m"; // yellow
                else
                    cout << "\033[37m" << guess[i] << "\033[0m"; // white
                lives--;
                if (lives == 0){
                    cout << "\nYOU LOST";
                    break;
                }
                cout << "\n";
                getline(std::cin, guess);
                transform(guess.begin(), guess.end(), guess.begin(), ::toupper);

                // cin >> guess;
        }
        else{
            cout << "Not long enough, enter five letters\n";
            getline(cin, guess);
            transform(guess.begin(), guess.end(), guess.begin(), ::toupper);

            // cin >> guess; //make more readable by checking this first and the next by itself not nested if loop
        }
    }
    if (guess == correctword){
        cout << "\033[32m" << correctword << "\033[0m";
        cout << "\nWinner!";
    }
    else{
        cout << "\nBetter luck next time";
    }
}

/* TODO
User enter 5 letter word else not ok
if letter correct make green, else yellow.
6 attemps, display word at the end

Have the word be chosen on random from a list of words 
Testing if push worked
*/