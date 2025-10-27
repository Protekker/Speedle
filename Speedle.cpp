#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>

using namespace std;


int main(){
    // string correctword = "PLUMP";
    // int wordlen;
    // cin >> wordlen;
    ifstream MyReadFile("speedlewords.txt");
    if (!MyReadFile.is_open()){
        cout << "Unable to open file." << endl;
        return 1;
    }
    vector<string> words;
    string line;
    int lineCount = 0;
    while(getline(MyReadFile, line)){ 
        lineCount++; 
        transform(line.begin(),line.end(),line.begin(), ::toupper);
        words.push_back(line);
    }
    MyReadFile.close();
    random_device random_device;
    mt19937 engine{random_device()};
    uniform_int_distribution<int> dist(0, words.size() - 1); 
    int random_element = dist(engine);
    string correctword = words.at(random_element); //words.at(random_element)
    // vector<string> words = {"APPLE","PLUMP","COULD","SHOWS","PHONE"};
    // vector<int> v = {0, 1, 2, 3, 4};
    // string correctword = words.at(randomIndex);
    string guess;
    int lives = 6;
    // cin >> guess;
    cout << "Enter a five letter word (CAPS)\n";

    while(guess != correctword && lives > 0){
        getline(cin, guess);
        transform(guess.begin(), guess.end(), guess.begin(), ::toupper);
        // transform(guess.begin(), guess.end(), guess.begin(), ::tolower);
        auto it = find(words.begin(),words.end(),guess);
        if (it == words.end()){
            cout << "Word not in dictionary, retry\n";
        }
        if (guess.length() == 5 && it != words.end()){
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
                // getline(cin, guess);
                // transform(guess.begin(), guess.end(), guess.begin(), ::toupper);
                // // transform(guess.begin(), guess.end(), guess.begin(), ::tolower);
                // auto it = find(words.begin(),words.end(),guess);
                // if (it == words.end()){
                //     cout << "Word not in dictionary, retry\n";
                // }
                // cin >> guess;
        }
        else{
            cout << "Enter valid five letter word\n";
                // getline(cin, guess);
                // transform(guess.begin(), guess.end(), guess.begin(), ::toupper);
                // // transform(guess.begin(), guess.end(), guess.begin(), ::tolower);
                // auto it = find(words.begin(),words.end(),guess);
                // if (it == words.end()){
                //     cout << "Word not in dictionary, retry\n";
                // }
            // cin >> guess; //make more readable by checking this first and the next by itself not nested if loop
        }
    }
    if (guess == correctword){
        cout << "\033[32m" << correctword << "\033[0m";
        cout << "\nWinner!";
    }
    else{
        cout << "\nBetter luck next time, the correct word was: " << correctword;
    }
}

/* TODO
User enter 5 letter word else not ok
if letter correct make green, else yellow.
6 attemps, display word at the end

Have the word be chosen on random from a list of words 
Testing if push worked
*/