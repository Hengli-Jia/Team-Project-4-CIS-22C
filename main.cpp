/*
 TODO: add members information and project description
*/

//#include "Database.h"
#include "Puzzle.h"

#include "hashtable.h"
#include "hashtable.cpp"

#include "BST.h"
//#include "BST.cpp"

#include <iostream>


bool inputData(HashTable &hashTable, BinaryTree &bst,string inputFile);

void menu();


const void displayTeamMembers();
void help();
bool exit();

void horiDisplay(string &);
void vertiDisplay(string &);
void indentedDisplay(string &, int);

int main() 
{
    /*
    HashTable hashTable;
    BinaryTree bst;

    string inputFile = "puzzles_database.txt";

    inputData(hashTable, bst, inputFile);*/


    BinaryTree binaryTree;

    HashTable hashTable;

    menu(hashTable, binaryTree);

    std::cout << binaryTree.isEmpty();


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
    std::cout << "input data function";
    //Input data using puzzles_database.txt and output resulting hashtables and bst in the aprameters

    return true;
}


void menu(HashTable &HashTable, BinaryTree &bst)
{
    //will loop until the user is done using the data
    /*
    - Add data froma file
    Missing
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
    std::cout << item << " ";
}

void vertiDisplay (Puzzle &item) 
{
    std::cout << item << std::endl;
}

void indentedDisplay(Puzzle &item, int level)
{
    for (int i = 1; i < level; i++)
        std::cout << "..";
    std::cout << level << "). " << item << std::endl;
    
}
