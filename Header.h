#ifndef PA1
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#include <fstream>
#include <string.h>
#include <cstdlib>

using namespace std;

template <class T>
class LinuxCommandData
{
public:
    T name[30];
    T description[150];
};

template <class T>
class LinuxCommandNode
{
public:
    T lnxCmd;
    LinuxCommandNode* next;
};

template <class T>
class LinuxCommandList {
public:
    int countofnodes = -1;

protected:
    T* head;

public:

    LinuxCommandList() {
        head = NULL;
    }

    ~LinuxCommandList() {
        // Helps manage the memory and frees the list
        while (head != NULL) {
            LinuxCommandNode<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void PrintGameRules() {
        cout << "================================= Game Rule ===================================" << endl;
        cout << "To play the game, select \"2\" where you will be prompted for your name and number of questions.\n";
        cout << "Each question presents a specific Linux command where you will be able to choose from 3 different options. Each correct answer yields a point.\n";
        cout << "You can also add and delete commands as needed.\n";
        cout << "================================= Game Rule ===================================" << endl << endl;
    }

    void AddCommand(T* newCommand) {
        if (head != NULL) {
            newCommand->next = head;
            head = newCommand;
        }
        else {
            head = newCommand;
            head->next = NULL;
        }
        countofnodes++;
    }

    void RemoveCommand(char* lnxCmdToBeRemoved) {
        LinuxCommandNode<LinuxCommandData<char>>* tempHead = head;
        LinuxCommandNode<LinuxCommandData<char>>* prevNode = NULL;

        while (tempHead != NULL) {
            if (strcmp(tempHead->lnxCmd.name, lnxCmdToBeRemoved) == 0) {
                if (tempHead == head) {
                    // First node match
                    head = tempHead->next;
                }
                else if (tempHead->next == NULL) {
                    // Last node match
                    prevNode->next = NULL;
                }
                else {
                    // Middle node match
                    prevNode->next = tempHead->next;
                }
                delete tempHead;
                countofnodes--;
                return;
            }
            prevNode = tempHead;
            tempHead = tempHead->next;
        }
    }

    void ListCommands() {
        LinuxCommandNode<LinuxCommandData<char>>* p = head;
        while (p != NULL) {
            cout << p->lnxCmd.name << "," << p->lnxCmd.description << endl;
            p = p->next;
        }
    }

    void SaveCommandList() {
        ofstream outfile("commands.csv");
        LinuxCommandNode<LinuxCommandData<char>>* p = head;
        while (p != NULL) {
            outfile << p->lnxCmd.name << "," << p->lnxCmd.description << endl;
            p = p->next;
        }
        outfile.close();
    }

    T* GetNodeAtIndex(int index) {
        if (index < 0 || index > countofnodes)
            return NULL;

        LinuxCommandNode<LinuxCommandData<char>>* current = head;
        for (int i = 0; i <= countofnodes; i++) {
            if (i == index)
                return current;
            current = current->next;
        }
        return NULL;
    }
};

class Player
{
public:
    int points = 0;
    char name[50];

    Player(char* newname);  // Only the declaration
    Player();
    ~Player();

    void playGame(LinuxCommandList<LinuxCommandNode<LinuxCommandData<char>>>* myGame);
};


#endif
