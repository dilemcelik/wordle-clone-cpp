#include <iostream>
#include <string>
using namespace std;

void toLowerCase(string & word) {
    string lowerword = "";
    for(int i = 0; i < (int)word.length(); i++) {
        char currentchar = word.at(i);
        if(currentchar >= 'A' && currentchar <= 'Z') {
            currentchar = currentchar + 'a' - 'A';
        }
        lowerword = lowerword + currentchar;
    }
    word = lowerword;
}

bool isValidLength(const string& word, int minLen, int maxLen) {
    if((int)word.length() >= minLen && (int)word.length() <= maxLen) {
        return true;
    }
    return false;
}

string buildFeedback(const string& word, const string& guess) {
    string currentfeedback = "";
    string wordCopy = word;
    string tempStatus = "";

    for(int i = 0; i < (int)guess.length(); i++) {
        tempStatus += "-";
    }

    for(int i = 0; i < (int)guess.length(); i++) {
        if(guess[i] == wordCopy[i]) {
            tempStatus[i] = 'G';
            wordCopy[i] = '*';
        }
    }

    for(int i = 0; i < (int)guess.length(); i++) {
        if(tempStatus[i] != 'G') {
            for(int j = 0; j < (int)wordCopy.length(); j++) {
                if(guess[i] == wordCopy[j]) {
                    tempStatus[i] = 'Y';
                    wordCopy[j] = '*';
                    break;
                }
            }
        }
    }

    for(int i = 0; i < (int)tempStatus.length(); i++) {
        if(tempStatus[i] == 'G') {
            currentfeedback += "[G]";
        } else if(tempStatus[i] == 'Y') {
            currentfeedback += "[Y]";
        } else {
            currentfeedback += "[-]";
        }
    }
    return currentfeedback;
}

void updateGameState(const string& word, const string& guess,
                     const string& feedback, string& allGuesses,
                     string& allFeedbacks, int& attemptsLeft,
                     bool& gameWon) {
    
    allGuesses = allGuesses + guess + "\n";
    allFeedbacks = allFeedbacks + feedback + "\n";
    attemptsLeft--;

    string winCondition = "";
    for(int i = 0; i < (int)word.length(); i++) {
        winCondition += "[G]";
    }
    if(feedback == winCondition) {
        gameWon = true;
    }
}

void printGameBoard(const string& allGuesses, const string& allFeedbacks,
                    int wordLen, int attemptsLeft, int maxAttempts) {
                    
    int currentAttempt = 1;
    int guessStart = 0;
    int feedStart = 0;
    int totalGuesses = maxAttempts - attemptsLeft;

    for(int i = 0; i < totalGuesses; i++) {
        cout << "Attempt " << currentAttempt << "/" << maxAttempts << ":\n";
        
        string g = allGuesses.substr(guessStart, wordLen);
        string f = allFeedbacks.substr(feedStart, wordLen * 3);
        
        cout << g << "  " << f << "\n";

        guessStart += wordLen + 1;
        feedStart += (wordLen * 3) + 1;
        currentAttempt++;
    }
}

int main() {
    bool status = true;
    while(status == true) {
        int choice;
        cout << "=== Wordle Game ===\n";
        cout << "1. New Game\n";
        cout << "2. How to Play\n";
        cout << "3. Exit\n\n";
        cout << "Enter your choice:\n";
        cin >> choice;

        if(!(choice == 1 || choice == 2 || choice == 3)) {
            cout << "\nInvalid input.\n\n";
        }
        else if(choice == 3) {
            cout << "\nGoodbye!\n";
            status = false;
        }
        else if(choice == 2) {
            cout << "\n=== How to Play ===\n";
            cout << "Player 1 enters a secret word (3-10 characters).\n";
            cout << "Player 2 gets one more attempt than the number of letters in the word.\n";
            cout << "After each guess, feedback is given for each letter:\n";
            cout << "[G] Green : correct letter, correct position.\n";
            cout << "[Y] Yellow : correct letter, wrong position.\n";
            cout << "[-] Grey : letter not in the word.\n\n";
        }
        else if(choice == 1) {
            string secret;
            bool ls = true;
            
            while(ls == true) {
                cout << "\nPlayer 1, enter the secret word:\n";
                cin >> secret;
                
                if(isValidLength(secret, 3, 10) == false) {
                    cout << "\nInvalid word length. Please enter a word between 3 and 10 characters.\n";
                } else {
                    ls = false;
                }
            }

            toLowerCase(secret);
            int lensecret = int(secret.length());
            int maxAttempts = lensecret + 1;
            int attemptsLeft = maxAttempts;

            cout << "\nThe word has " << lensecret << " characters. Player 2 has " << maxAttempts << " attempts.\n";

            string allguesses = "";
            string allfeedbacks = "";
            bool gamewon = false;

            while(attemptsLeft > 0 && gamewon == false) {
                string guess;
                cout << "\nPlayer 2, enter your guess:\n";
                cin >> guess;
                cout << "\n";

                if((int)guess.length() != lensecret) {
                    cout << "Invalid guess length. Please enter a " << lensecret << "-character word.\n";
                } else {
                    toLowerCase(guess);
                    
                    string feedback = buildFeedback(secret, guess);
                    updateGameState(secret, guess, feedback, allguesses, allfeedbacks, attemptsLeft, gamewon);
                    printGameBoard(allguesses, allfeedbacks, lensecret, attemptsLeft, maxAttempts);
                }
            }

            if(gamewon == true) {
                cout << "\nYou won! The word was: " << secret << "\n\n";
            } else {
                cout << "\nYou lost! The word was: " << secret << "\n\n";
            }
        }
    }
    return 0;
}
