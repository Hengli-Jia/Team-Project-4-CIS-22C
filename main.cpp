/*
 TODO: add members information and project description
*/

//#include "Database.h"
#include "Puzzle.h"
#include "hashtable.h"
//#include "BST.h"

#include <iostream>


bool inputData(HashTable &hashTable, BinaryTree &bst,string inputFile);

void menu();


const void displayTeamMembers();
void help();
bool exit();

void horiDisplay(Puzzle &);
void vertiDisplay(Puzzle &);
void indentedDisplay(Puzzle &, int);

int main() 
{
    
    HashTable hashTable;
    BinaryTree bst;

    string inputFile = 'puzzles_database.txt';

    inputData(hashTable, bst, inputFile);



}

const void displayTeamMembers() {}

void help() 
{

}

/*
Asks user if they are sure they want to exit
pre:
    User input
post:
    true then exit
    false then continue
out:
*/
bool exit() 
{
    std::cout << "Are you sure you want to exit(Y): ";
    char input;

    std::cin >> input;

    input = tolower(input);

    return (input == 'y');
}

/*
Using input file, create hastable and binary search tree contianing the data 
pre:
    inputFile: string is the name of the input file to be used to get that data
post:
    bool: If the input of data was succssful
out:
    hashtable: hash table that stores the data
    bst: binary search tree that containes the keys to be used in the hashtable
*/
bool inputData(HashTable &hashTable, BinaryTree &bst,string inputFile)
{
    //Input data using puzzles_database.txt and output resulting hashtables and bst in the aprameters
}


void menu(HashTable &HashTable, BinaryTree &bst)
{
    //will loop until the user is done using the data
    /*
    - Add a new data item. 
    missing
    - Add data from an input file (get the name of the input file from the user).
    missing
    - Delete data (one item).
    missing
    - Find and display one element using the primary key.
    missing
    - List data sorted by the primary key.
    missing
    - Hidden print option (do not show it in the menu: details are given in Team Project-
    Part2).
    missing
    - Write data to a file.
    missing
    - Statistics (details are given in Team Project-Part2)
    missing
    - Hidden option (do not show it in the menu): when selected, display the names of the
    team members.
    missing
    - Help – to show the menu. Show the menu once, before the loop, then show the menu
    upon request: “Enter an option (H – for help): ”
    missing
    - Exit
    untested
    */
}

void horitDisplay (Puzzle & item) 
{
    cout << item << " ";
}

void vertiDisplay (Puzzle &item) 
{
    cout << item << endl;
}

void indentedDisplay(Puzzle &item, int level)
{
    for (int i = 1; i < level; i++)
        cout << "..";
    cout << level << "). " << item << endl;
    
}
