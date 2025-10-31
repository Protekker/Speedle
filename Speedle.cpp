//Speedle by Jakob 2025
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <thread>
using namespace std;


struct Timer
{
    std::chrono::time_point<std::chrono::high_resolution_clock> start,end;
    std::chrono::duration<float> duration;
    Timer() //constructor
    {
        start = std::chrono::high_resolution_clock::now();
    }

    ~Timer() //destructor
    {
        end = std::chrono::high_resolution_clock::now();
        duration = end-start;
        float s = duration.count()*1.00f;
        std::cout << "Speedle time " << s << " s" << std::endl;
    }
};

void GameLoop(string &guess,string &correctword,int &lives,vector<string>& words)
{
    Timer timer;
    vector<char> alphabet = {'A','B','C','D','E','F','G','H','I','J','K','L','M',
                            'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    while(guess != correctword && lives > 0){
        getline(cin, guess); //Take input and store in string guess
        transform(guess.begin(), guess.end(), guess.begin(), ::toupper); //Transform begining to end starting at begining make touppercase

        auto it = find(words.begin(),words.end(),guess); //Check if guess in word
        if (it == words.end()){ //if it is the end of the list, "out of range" then it isn't in the dictionary
            cout << "Word not in dictionary, retry\n";
        }
        else{
            vector<char> usedletters; 
        for(int i=0;i<guess.size();i++){
            usedletters.push_back(guess[i]);
        };
        // string usedletterString(usedletters.begin(),usedletters.end());
        // cout << usedletterString << endl;

        alphabet.erase(
            remove_if(alphabet.begin(), alphabet.end(),
                    [&](char c){ return guess.find(c) != string::npos; }),
            alphabet.end()
        );
        string alphabetString(alphabet.begin(),alphabet.end());
        cout << "Letters not used: " << alphabetString << endl;
        }
        
        if (guess == correctword){
            cout << "\033[32m" << correctword << "\033[0m";
            cout << "\nWinner with " << (lives-1) << " lives remaining!" << endl;
            break;
        }
        if (guess.length() == 5 && it != words.end()){
            //Create arrays to track states
            char colors[3]; //'G' = green, 'Y' = yellow, 'W' = white
            bool used[5] = {false}; //Track which letters in correctword are used
            
            //First pass: Mark all greens
            for(int i = 0; i < 5; i++) {
                if (guess[i] == correctword[i]) {
                    colors[i] = 'G';
                    used[i] = true;
                } else {
                    colors[i] = 'W'; // Default to white
                }
            }
            
            // Second pass: Mark yellows
            for(int i = 0; i < 5; i++) {
                if (colors[i] == 'W') { // Only check non-green letters
                    for(int j = 0; j < 5; j++) {
                        if (!used[j] && guess[i] == correctword[j]) {
                            colors[i] = 'Y';
                            used[j] = true;
                            break;
                        }
                    }
                }
            }
            
            //Display with colors
            for(int i = 0; i < 5; i++) {
                if (colors[i] == 'G')
                    cout << "\033[32m" << guess[i] << "\033[0m"; //green
                else if (colors[i] == 'Y')
                    cout << "\033[33m" << guess[i] << "\033[0m"; //yellow
                else
                    cout << "\033[37m" << guess[i] << "\033[0m"; //white
            }
            
            lives--;
            if (lives == 0){
                cout << "\nYOU LOST";
                break;
            }
            cout << "\n";
        }
        else{
            cout << "Enter valid five letter word\n";
        }

    }
    if(guess != correctword){
        cout << "\nBetter luck next time, the correct word was: " << correctword << "\n";
    }
}

int main(){
    //First part is reading file and putting the words that are guessable in a vector in all uppercase
    ifstream MyReadFile("speedlewords.txt"); //Read file
    if (!MyReadFile.is_open()){ //Check if openable
        cout << "Unable to open file." << endl;
        return 1;
    }
    vector<string> words; //Define a vector (dynamic array)
    string line;
    int lineCount = 0;
    while(getline(MyReadFile, line)){ //Go through each line
        lineCount++; //Count lines not used rn.
        transform(line.begin(),line.end(),line.begin(), ::toupper); //Read all lines and transform to uppercase since all were lower
        words.push_back(line); //Put them in the vector
    }
    MyReadFile.close(); 

    //Now the words that can be chosen
    ifstream MyReadFile2("realisticguesses.txt"); //Read file
    if (!MyReadFile2.is_open()){ //Check if openable
        cout << "Unable to open file." << endl;
        return 1;
    }
    vector<string> correctWords; //Define a vector (dynamic array) correct words
    string correctLine;
    int lineCount2 = 0;
    while(getline(MyReadFile2, correctLine)){ //Go through each line
        lineCount2++; //Count lines not used rn.
        transform(correctLine.begin(),correctLine.end(),correctLine.begin(), ::toupper); //Read all lines and transform to uppercase since all were lower
        correctWords.push_back(correctLine); //Put them in the vector
    }
    MyReadFile2.close(); 


    //This part randomizes and picks element at random position from words.
    random_device random_device; //
    mt19937 engine{random_device()};
    uniform_int_distribution<int> dist(0, correctWords.size() - 1); 
    int random_element = dist(engine);
    string correctword = correctWords.at(random_element); 
    // string correctword = "APPLE";
    
    // usedletters.push_back(guess);
    // string guess2;
    // getline(cin,guess2);
    // usedletters.push_back(guess2);
    // for (const char& c : usedletters){
    //     cout << c;
    // };
    // sort(usedletters.begin(),usedletters.end());
    // cout << usedletters;
    string guess;

    int lives = 6; //Amount of tries, to be changed to the infinite mode
    // string name;
    // cout << "Enter Username: ";
    // cin << name;
    cout << "Enter a five letter word\n";

    /*This part is the game loop which checks if correct word has been guessed otherwise display the word again but with colorcoding:
    GREEN correct and correct place
    YELLOW correct but incorrect place
    WHITE incorrect and incorrect pace */
    GameLoop(guess,correctword,lives,words); //Implemented the loop in a function for readability
}

/* TODO
Make a leaderboard for attempts and time.
show letters used and unused different colors.
Move function to other file

implementation of letters used:
1. Show all letters in alphabet
2. if used, display but not the ones in used list
*/