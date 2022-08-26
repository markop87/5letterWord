/*
Game based on a popular The New York Times game - Wordle.
Guessing a 5-letter word in 5 tries.
*/

#include <iostream>
#include <random>
#include <time.h>
#include <windows.h>
#include <fstream>
#include <algorithm>

using namespace std;

int main()
{
    system("title 5-LETTER WORD");
    char again;

    do {
        system("CLS");

        //draw a random number
        static mt19937 gen(time(nullptr));; // seed the generator
        uniform_int_distribution<> distr(1, 2499); //range

        int number = distr(gen);

        //loading random word from file
        ifstream words("words.txt");
        string word;

        for (int i = 1; i <= number; i++)
        {
            getline(words, word);
        }

        //printing word for testing
        // cout << word << endl;

        string guess;

        int tries = 1;

        //rules
        cout << "Guess a 5-letter word in 5 tries!\n";
        cout << "Green - the letter is on correct spot\n";
        cout << "Yellow - letter occurs in word, but is on wrong spot\n";
        cout << "Red - letter don't occurs in this word\n\n";

        while(tries < 6)
        {
            //clues if letter is on a right spot [A], wrong spot [B] or don't occurs [C]
            char check[5] = {0, 0, 0, 0, 0};

            //checking if a letter in a word was already used
            bool hits[5] = {false, false, false, false, false};

            do {
                cout << "Try nr " << tries << ": ";
                cin >> guess;
            } while (guess.length() < 5);

            for (auto & c: guess) c = toupper(c);

            guess = guess.substr(0,5);

            //first check if letter is on a right spot
            for(int g = 0; g < 5; g++)
            {
                if(guess[g] == word[g])
                {
                    check[g] = 'A';
                    hits[g] = true;
                }

            }

            //second check if letter occurs in a word
            for (int g=0; g<5; g++)
            {
                if (check[g] == 0) //checking if letter is not on a right spot
                {
                    for (int w=0; w<5; w++)
                    {
                        if (guess[g] == word[w] && !hits[w])
                        {
                          check[g] = 'B';
                          hits[w] = true;
                          break; //breaking loop to not check same letter on other spots
                        }
                    }
                }
            }

            //checking other letters as wrong ones
            for (int g=0; g<5; g++)
            {
                if (check[g] == 0)
                {
                    check[g] = 'C';
                }
            }



            for(int c = 0; c < 5; c++)
                {
                    //if letter is in correct spot, print it in green
                    if(check[c] == 'A')
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
                        cout << guess[c];
                    }

                    //if letter occurs in word and is not in correct spot, print in in yellow
                    if(check[c] == 'B')
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                        cout << guess[c];
                    }

                    //if letter doesn't occurs in word, print it in red
                    if(check[c] == 'C')
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                        cout << guess[c];
                    }
                }
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //return to basic color

                cout << "\n\n";

            //if the player did guess the word
            if(guess == word)
            {
                cout << "\n\nCongratulations! You won!" << endl;
                break;
            }

            tries++;
        }

        //if the player did not guess the word
        if(tries > 5)
        {
            cout << "You've lost!\nThe word was " << word << endl;
        }

        cout << "\nWanna play again? (Y to play) ";
        cin >> again;

    } while(again == 'Y' || again == 'y');

    return 0;
}
