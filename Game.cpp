#include "Header.h"
#include <cstdlib>  

// Constructor for the Player class
Player::Player(char* newname)
{
    strcpy(name, newname);
}

void Player::playGame(LinuxCommandList<LinuxCommandNode<LinuxCommandData<char>>>* myGame)
{
    int noOfQuestions;
    cout << "Choose between 5-30 questions!:" << endl;
    cin >> noOfQuestions;

    // Makes sure that the user picked between 5-30 questions
    while (noOfQuestions < 5 || noOfQuestions > 30) {
        cout << "Please choose between 5 and 30: ";
        cin >> noOfQuestions;
    }

    // Number generator
    srand((unsigned)time(0));

    for (int i = 1; i <= noOfQuestions; i++)
    {
        // Randomly selects 3 nodes but one of them will be the correct answer
        LinuxCommandNode<LinuxCommandData<char>>* randomnode[3];
        randomnode[0] = myGame->GetNodeAtIndex(rand() % (myGame->countofnodes + 1));
        randomnode[1] = myGame->GetNodeAtIndex(rand() % (myGame->countofnodes + 1));
        randomnode[2] = myGame->GetNodeAtIndex(rand() % (myGame->countofnodes + 1));

        int commandq = rand() % 3;

        cout << "Question Number: " << i << endl;


        for (int j = 0; j < 3; j++) {
            cout << j + 1 << ") " << randomnode[j]->lnxCmd.description << endl;
        }

        // Asks for the description!
        cout << "What is the description for the following command?: " << randomnode[commandq]->lnxCmd.name << endl;

        int answerchoice;

        // Makes sure they picked a valid choice (1, 2, or 3)
        do {
            cin >> answerchoice;
            if (answerchoice < 1 || answerchoice > 3) {
                cout << "Please choose 1, 2, or 3: ";
            }
        } while (answerchoice < 1 || answerchoice > 3);

        // Checks to see if the answer is correct
        if (randomnode[answerchoice - 1]->lnxCmd.name == randomnode[commandq]->lnxCmd.name) {
            points++;
            cout << "That is Correct! Good job. " << randomnode[answerchoice - 1]->lnxCmd.name
                << " - " << randomnode[answerchoice - 1]->lnxCmd.description << endl;
            cout << "You earned a point. Your total points is: " << points << endl;
        }
        else {
            points--;
            cout << "Unfortunately, that was incorrect! " << randomnode[answerchoice - 1]->lnxCmd.name
                << " - " << randomnode[answerchoice - 1]->lnxCmd.description << endl;
            cout << "You lost a point. Your total points is: " << points << endl;
        }
        cout << "Press Enter to continue..." << endl;
        cin.ignore();
        cin.get();
    }
    cout << "The Game is over thanks for playing! Final points: " << points << endl;
}