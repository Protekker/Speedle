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

// struct Timer
// {
//     std::chrono::time_point<std::chrono::steady_clock> start,end;
//     std::chrono::duration<float> duration;
//     Timer() //constructor
//     {
//         start = std::chrono::high_resolution_clock::now();
//     }

//     ~Timer() //destructor
//     {
//         end = std::chrono::high_resolution_clock::now();
//         duration = end-start;
//         float ms = duration.count()*1000.0f;
//         std::cout << "Speedle time " << ms << " ms" << std::endl;
//     }
// };

void GameLoop(string &guess,string &correctword,int &lives,vector<string>& words)
{
        while(guess != correctword && lives > 0){
        getline(cin, guess); //Take input and store in string guess
        transform(guess.begin(), guess.end(), guess.begin(), ::toupper); //Transform begining to end starting at begining make touppercase
        auto it = find(words.begin(),words.end(),guess); //Check if guess in word
        if (it == words.end()){ //if it is the end of the list, "out of range" then it isn't in the dictionary
            cout << "Word not in dictionary, retry\n";
        }
        if (guess == correctword){
            break;
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
        }
        else{
            cout << "Enter valid five letter word\n";
        }
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
    // string correctword = correctWords.at(random_element); 
    string correctword = "APPLE";
    string guess;
    int lives = 6; //Amount of tries, to be changed to the infinite mode
    cout << "Enter a five letter word\n";

    /*This part is the game loop which checks if correct word has been guessed otherwise display the word again but with colorcoding:
    GREEN correct and correct place
    YELLOW correct but incorrect place
    WHITE incorrect and incorrect pace */
    GameLoop(guess,correctword,lives,words); //Implemented the loop in a function for readability

    if (guess == correctword){
        cout << "\033[32m" << correctword << "\033[0m";
        cout << "\nWinner with " << lives << " lives remaining!";
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