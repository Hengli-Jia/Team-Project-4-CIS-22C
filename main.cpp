/*
 TODO: add members information and project description
*/

//#include "Database.h"
#include "Puzzle.h"

#include "hashtable.h"
//#include "hashtable.cpp"

#include "BST.h"
//#include "BST.cpp"

#include <iostream>


bool inputDataFile(HashTable& hashTable, BinaryTree& binaryTree,string inputFile);
bool writeDataFile(const HashTable& hashTable, const BinaryTree& BinaryTree, string outputFile);

void menu(HashTable &hashTable, BinaryTree &binaryTree);

void displayMenuOptions();


const void displayTeamMembers();
void help();
bool exit();

void horiDisplay(string &);
void vertiDisplay(string &);
void indentedDisplay(string &, int);

void inputDataFromFile(HashTable& hashTable, BinaryTree& binaryTree);
void inputSingleEntry(HashTable& hashTable, BinaryTree& binaryTree);
void deleteEntry(HashTable& hashTable, BinaryTree& binaryTree);
void findEntry(const HashTable& hashTable, const BinaryTree& binaryTree);
void listEntrys(const HashTable& hashTable, const BinaryTree& binaryTree);
void writeToFile(const HashTable& hashTable, const BinaryTree& binaryTree);
void statistics(const HashTable& hashTable, const BinaryTree& binaryTree);



int main() 
{
    BinaryTree binaryTree;

    HashTable hashTable;

    menu(hashTable, binaryTree);
}


void menu(HashTable &hashTable, BinaryTree &binaryTree)
{
    bool exitMenu = false;

    std::cout << "Welcome to ________" << std::endl;

    char input;
    
    while (!exitMenu)
    {
        displayMenuOptions();

        std::cout << "Input: ";

        std::cin >> input;

        input = tolower(input);

        switch (input)
        {
            case 'e':
                exitMenu = exit();
                break;
            
            case 'a':
                inputSingleEntry(hashTable, binaryTree);
                break;
            
            case 'i':
                inputDataFromFile(hashTable, binaryTree);
                break;
            
            case 'd':
                deleteEntry(hashTable, binaryTree);
                break;

            case 'f':
                findEntry(hashTable, binaryTree);
                break;

            case 'l':
                listEntrys(hashTable, binaryTree);
                break;

            case 'w':
                writeToFile(hashTable, binaryTree);
                break;

            case 's':
                exitMenu = exit();
                break;

            case 'h':
                help();
                break;
            
            default:
                std::cout << "Invalid Input. Try again" << std::endl;
                break;
        }


        std::cout << std::endl << std::endl;
    }
    
    //will loop until the user is done using the data
    /*
    - Add data froma file
    Missing

    - Add a new data item. 
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
    Done

    - Exit
    Done
    */
}

const void displayTeamMembers() {}

void help() 
{
    displayMenuOptions();
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
bool inputDataFile(HashTable &hashTable, BinaryTree &binaryTree,string inputFile)
{
    //Todo by file I/O person
}


/*
Creates or overwrites file with data from binary tree or hashtable
pre:
    hashTable: hash table containing data
    or
    binaryTree: binary tree contiang data
post:
    bool: If the file output of data was succssful
out:
*/
bool writeDataFile(const HashTable& hashTable, const BinaryTree& BinaryTree, string outputFile)
{
    //to do by file I/O person
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

void displayMenuOptions()
{
    std::cout << "The menu controls are: " << std::endl;
        std::cout << "   E to Exit" << std::endl;
        std::cout << "   A to Add 1 entry" << std::endl;
        std::cout << "   I to Input data from file" << std::endl;
        std::cout << "   D to Delete an entry" << std::endl;
        std::cout << "   F to Find an entry" << std::endl;
        std::cout << "   L to List" << std::endl;
        std::cout << "   W to Write data to file" << std::endl;
        std::cout << "   S for Statistics" << std::endl;
        std::cout << "   H for help" << std::endl;
}


/*
Menu Function
Gets file input from user and writes file
pre:
    hashTable: hash table containing data
    binaryTree: binary tree contiang data
post:
out:
*/
void inputDataFromFile(HashTable& hashTable, BinaryTree& binaryTree)
{
    std::cout << "Input file name: ";

    std::string fileName;
    std::cin.ignore();

    std::getline(std::cin,fileName);

    if(inputDataFile(hashTable, binaryTree, fileName))
    {
        std::cout << "File data added succesfully" << std::endl;
    }
    else
    {
        std::cout << "Error in adding data from file" << std::endl;
    }


}
void inputSingleEntry(HashTable& hashTable, BinaryTree& binaryTree){}
void deleteEntry(HashTable& hashTable, BinaryTree& binaryTree){}
void findEntry(const HashTable& hashTable, const BinaryTree& binaryTree){}
void listEntrys(const HashTable& hashTable, const BinaryTree& binaryTree){}


/*
Menu Function
Gets file to output from user
pre:
    hashTable: hash table containing data
    or
    binaryTree: binary tree contiang data
post:
    
out:
    file containg data
*/
void writeToFile(const HashTable& hashTable, const BinaryTree& binaryTree)
{
    std::cout << "Output file name: ";

    std::string fileName;
    std::cin.ignore();

    std::getline(std::cin,fileName);

    if(writeDataFile(hashTable, binaryTree, fileName))
    {
        std::cout << "Data succesfully written to file" << std::endl;
    }
    else
    {
        std::cout << "Error in writing data to file" << std::endl;
    }
}
void statistics(const HashTable& hashTable, const BinaryTree& binaryTree){}
