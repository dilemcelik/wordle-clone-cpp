# Wordle Clone in C++ 🎮

A terminal-based word guessing game written in C++, inspired by the popular game Wordle. 
This is my first portfolio project to practice and demonstrate fundamental C++ programming concepts.

## 📝 About the Project

In this two-player game:
* **Player 1** enters a secret word (between 3 and 10 characters).
* **Player 2** tries to guess the secret word. They get one more attempt than the number of letters in the secret word.
* After each guess, the game provides format-based feedback for every letter to help Player 2 deduce the word.

## 🚀 Features & Concepts Used

* **String Manipulation:** Custom ASCII math to convert inputs to lowercase without using standard library functions like `tolower()`.
* **Two-Pass Algorithm:** Accurately evaluates guesses to assign Green, Yellow, or Grey statuses, handling duplicate letters correctly.
* **Pass-by-Reference:** Efficiently updates the game state, guess history, and feedback boards across multiple functions.
* **Control Flow & Loops:** Implements a continuous game loop, input validation, and interactive menus.

## 🕹️ How to Play

1. Run the game and select `1. New Game` from the menu.
2. Player 1 enters the secret word blindly.
3. Player 2 inputs their guess. The feedback format is as follows:
   * `[G]` **Green:** Correct letter in the correct position.
   * `[Y]` **Yellow:** Correct letter but in the wrong position.
   * `[-]` **Grey:** Letter is not in the secret word.
4. Win by getting all `[G]`s before you run out of attempts!

## 💻 How to Run

If you want to run this code on your local machine, open your terminal and run the following commands:

```bash
g++ main.cpp -o wordle
./wordle
