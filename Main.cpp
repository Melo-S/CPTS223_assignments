// ADVANTAGES & DISADVANTAGES LINKED LIST:
// Advantage: Easier to insert and delete commands in the list.
// Disadvantage: Takes up more memory and can't traverse backwards or access elements by index.
// ADVANTAGES & DISADVANTAGES ARRAY:
// Advantage: Arrays can access elements by index directly.
// Disadvantage: Its fixed size, making dynamic resizing and efficient insertions or deletions difficult.


#include "Header.h"
#include <cstdlib> 

int main(void)
{
    LinuxCommandList<LinuxCommandNode<LinuxCommandData<char>>>* myGame = new LinuxCommandList<LinuxCommandNode<LinuxCommandData<char>>>();

    Player* players[20];
    int currentplayerindex = -1;

    char username[30];
    int input;

    do
    {
        cout << "Please select an option listed below:\n";
        cout << "1. Game Rules\n2. Play Game\n3. Load Previous Game\n4. Add Command\n5. Remove Command\n6. Exit\n";
        cout << "Your selection: ";
        cin >> input;

        while (input < 1 || input > 6)
        {
            cout << "Please Choose between 1-6!: ";
            cin >> input;
        }

        switch (input)
        {
        case 1:
            myGame->PrintGameRules();
            cout << "Press enter to continue..." << endl;
            cin.ignore();
            cin.get();
            break;

        case 2: {
            // Loads commands from file! Had to manually input the file path
            FILE* infile = fopen("D:/Downloads/PA1/commands.csv", "r");
            if (infile == NULL) {
                cerr << "Error: Could not open commands.csv" << endl;
                break;
            }

            cout << "Hold on! Loading file..." << endl;
            while (!feof(infile)) {
                LinuxCommandNode<LinuxCommandData<char>>* newCommand = new LinuxCommandNode<LinuxCommandData<char>>();
                fscanf(infile, "%[^,],%[^\n]\n", newCommand->lnxCmd.name, newCommand->lnxCmd.description);
                myGame->AddCommand(newCommand);
            }
            fclose(infile);

            cout << "Please enter your name: ";
            cin >> username;
            players[++currentplayerindex] = new Player(username);

            players[currentplayerindex]->playGame(myGame);

            cout << "Press enter to continue..." << endl;
            cin.ignore();
            cin.get();
            break;
        }

        case 3: {
            char savedprofilename[30];
            cout << "Enter the name of the profile to resume playing: ";
            cin >> savedprofilename;

            for (int i = 0; i <= currentplayerindex; i++) {
                if (strcmp(savedprofilename, players[i]->name) == 0) {
                    cout << "We Found You! " << players[i]->name << " Heres how many points you had: " << players[i]->points << endl;
                    players[i]->playGame(myGame);
                    break;
                }
            }
            break;
        }

        case 4: {
            LinuxCommandNode<LinuxCommandData<char>>* newCommand = new LinuxCommandNode<LinuxCommandData<char>>();
            cout << "Name of command: ";
            cin >> newCommand->lnxCmd.name;
            cout << "Description of command: ";
            cin.ignore();
            cin.getline(newCommand->lnxCmd.description, 150);
            myGame->AddCommand(newCommand);
            myGame->ListCommands();
            cout << "Press enter to continue..." << endl;
            cin.ignore();
            cin.get();
            break;
        }

        case 5: {
            char removecommand[30];
            cout << "Enter command name to remove: ";
            cin >> removecommand;
            myGame->RemoveCommand(removecommand);
            myGame->ListCommands();
            cout << "Press enter to continue..." << endl;
            cin.ignore();
            cin.get();
            break;
        }

        case 6: {
            myGame->SaveCommandList();
            ofstream outfile("profiles.csv");
            for (int i = 0; i <= currentplayerindex; i++) {
                outfile << players[i]->name << "," << players[i]->points << endl;
            }
            outfile.close();
            break;
        }

        }
    } while (input != 6);
}
