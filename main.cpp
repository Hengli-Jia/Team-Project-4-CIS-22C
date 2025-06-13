/*
 TODO: add members information and project description
*/

#include "BST.h"
#include "BST.cpp"

#include "HashNode.h"
#include "HashTable.cpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

bool loadPuzzles(HashTable &hashTable, BinaryTree &bst,
				 const std::string &inputFile);

bool inputDataFile(HashTable &hashTable, BinaryTree &binaryTree,
				   string inputFile);
bool writeDataFile(const HashTable &hashTable, const BinaryTree &BinaryTree,
				   string outputFile);

void menu(HashTable &hashTable, BinaryTree &binaryTree);

void displayMenuOptions();

void displayTeamMembers();
void help();
bool exit();

void horiDisplay(string);
void vertiDisplay(string);
void indentedDisplay(string, int);

void inputDataFromFile(HashTable &hashTable, BinaryTree &binaryTree);
void inputSingleEntry(HashTable &hashTable, BinaryTree &binaryTree);
void deleteEntry(HashTable &hashTable, BinaryTree &binaryTree);
void findEntry(const HashTable &hashTable, const BinaryTree &binaryTree);
void listEntrys(const HashTable &hashTable, const BinaryTree &binaryTree);
void writeToFile(const HashTable &hashTable, const BinaryTree &binaryTree);
void statistics(const HashTable &hashTable, const BinaryTree &binaryTree);

void getPuzzle(string key, Puzzle& puzzleOut);

const HashTable* hash;

int main() {
	string inputFile = "puzzles_database.txt";
	BinaryTree binaryTree;
	HashTable hashTable;

	hash = &(hashTable);

	//loadPuzzles(hashTable, binaryTree, inputFile);

	menu(hashTable, binaryTree);
}

void menu(HashTable &hashTable, BinaryTree &binaryTree) {
	bool exitMenu = false;

	std::cout << "Welcome to ________" << std::endl;

	char input;

	while (!exitMenu) {
		displayMenuOptions();

		std::cout << "Input: ";

		std::cin >> input;

		input = tolower(input);

		switch (input) {
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

	// will loop until the user is done using the data
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

	- Hidden print option (do not show it in the menu: details are given in Team
	Project- Part2). missing

	- Write data to a file.
	missing

	- Statistics (details are given in Team Project-Part2)
	missing

	- Hidden option (do not show it in the menu): when selected, display the
	names of the team members. missing

	- Help – to show the menu. Show the menu once, before the loop, then show
	the menu upon request: “Enter an option (H – for help): ” Done

	- Exit
	Done
	*/
}

void help() { displayMenuOptions(); }

/*
Asks user if they are sure they want to exit
pre:
	User input
post:
	true then exit
	false then continue
out:
*/
bool exit() {
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
bool loadPuzzles(HashTable &hashTable, BinaryTree &bst,
				 const std::string &inputFile) {
	std::cout << "[DEBUG] loadPuzzles() called with inputFile: " << inputFile
			  << std::endl;
	// open the input file
	std::ifstream file(inputFile);
	if (!file.is_open()) {
		std::cerr << "Failed to open input file: " << inputFile << std::endl;
		return false;
	}

	// count lines in the input file
	std::string line;
	int lineCount = 0;
	std::getline(file, line); // skip header
	while (std::getline(file, line)) {
		if (!line.empty())
			lineCount++;
		std::cout << "[DEBUG] Line count: " << lineCount << std::endl;
	}

	// reset file stream to the beginning
	file.clear();
	file.seekg(0);

	// determine hash size using a prime number
	auto isPrime = [](int n) {
		if (n < 2)
			return false;
		for (int i = 2; i * i <= n; ++i)
			if (n % i == 0)
				return false;
		return true;
	};
	int hashSize = lineCount * 2;
	while (!isPrime(hashSize))
		++hashSize;

	std::cout << "[DEBUG] Calculated hash size: " << hashSize << std::endl;

	// recreate hashTable with new size
	hashTable = HashTable(hashSize);

	// read data and insert into hashTable and bst
	int lineNum = 0;
	std::getline(file, line); // skip header
	while (std::getline(file, line)) {
		lineNum++;
		std::cout << "[DEBUG] Processing line " << lineNum << ": " << line
				  << std::endl;
		if (line.empty())
			continue;

		// parse the line into fields
		std::stringstream ss(line);
		std::string puzzleId, fen, moves, rating, ratingDeviation, popularity,
			nbPlays, themes, gameUrl, openingTags;
		std::getline(ss, puzzleId, ',');
		std::getline(ss, fen, ',');
		std::getline(ss, moves, ',');
		std::getline(ss, rating, ',');
		std::getline(ss, ratingDeviation, ',');
		std::getline(ss, popularity, ',');
		std::getline(ss, nbPlays, ',');
		std::getline(ss, themes, ',');
		std::getline(ss, gameUrl, ',');

		// openingTags is optional, so check if present
		if (!ss.eof()) {
			std::getline(ss, openingTags, ',');
		} else {
			openingTags = "";
		}

		// validate required fields (first 9 fields must not be empty)
		if (puzzleId.empty() || fen.empty() || moves.empty() ||
			rating.empty() || ratingDeviation.empty() || popularity.empty() ||
			nbPlays.empty() || themes.empty() || gameUrl.empty()) {
			std::cout << "[DEBUG] Skipping malformed line " << lineNum
					  << std::endl;
			continue; // skip malformed line
		}

		// parse moves, themes, openingTags as vectors
		std::vector<std::string> movesVec, themesVec, openingTagsVec;
		std::stringstream movesSS(moves), themesSS(themes), tagsSS(openingTags);
		std::string token;
		while (std::getline(movesSS, token, ' ')) {
			std::cout << "[DEBUG] Processing move token: " << token
					  << std::endl;
			if (!token.empty())
				movesVec.push_back(token);
		}

		while (std::getline(themesSS, token, ' ')) {
			std::cout << "[DEBUG] Processing theme token: " << token
					  << std::endl;
			if (!token.empty())
				themesVec.push_back(token);
		}

		while (std::getline(tagsSS, token, ' ')) {
			std::cout << "[DEBUG] Processing opening tag token: " << token
					  << std::endl;
			if (!token.empty())
				openingTagsVec.push_back(token);
		}

		try {
			Puzzle puzzle(puzzleId, fen, movesVec, std::stoi(rating),
						  std::stoi(ratingDeviation), std::stoi(popularity),
						  std::stoi(nbPlays), themesVec, gameUrl,
						  openingTagsVec);
			std::cout << "[DEBUG] Successfully created Puzzle object: "
					  << puzzle << std::endl;
			hashTable.insert(puzzle);
			std::cout << "[DEBUG] Successfully inserted into hash table: "
					  << puzzle << std::endl;
			bst.insertBST(puzzle);
			std::cout
				<< "[DEBUG] Successfully inserted into binary search tree: "
				<< puzzle << std::endl;
			std::cout << "[DEBUG] Successfully processed line " << lineNum
					  << std::endl;
		} catch (const std::exception &e) {
			std::cerr << "[ERROR] Failed to parse line " << lineNum << ": "
					  << line << " with error: " << e.what() << std::endl;
			continue; // skip line if conversion fails
		}
	}
	std::cout << "[DEBUG] Finished processing input file." << std::endl;

	file.close();

	// save to file (in hash table sequence)
	std::string outFileName = inputFile;
	size_t dotPos = outFileName.find_last_of('.');
	if (dotPos != std::string::npos) {
		outFileName.insert(dotPos, "_hashtable");
	} else {
		outFileName += "_hashtable";
	}
	std::ofstream outFile(outFileName);
	std::cout << "[DEBUG] Attempting to write output file: " << outFileName
			  << std::endl;
	if (outFile.is_open()) {
		std::cout << "[DEBUG] Output file opened successfully. Writing data..."
				  << std::endl;
		// Write header
		outFile << "PuzzleId,FEN,Moves,Rating,RatingDeviation,Popularity,"
				   "NbPlays,Themes,GameUrl,OpeningTags\n";
		int written = 0;
		for (int i = 0; i < hashTable.getCapacity(); i++) {
			Puzzle item;
			if (hashTable.getOccupiedAt(i) == 1) {
				item = hashTable.getItemAt(i);
				outFile << item << '\n';
				written++;
			}
		}
		std::cout << "[DEBUG] Number of puzzles written: " << written
				  << std::endl;
		outFile.close();
	} else {
		std::cerr << "[ERROR] Could not open output file: " << outFileName
				  << std::endl;
	}

	return true;
}

bool inputDataFile(HashTable &hashTable, BinaryTree &binaryTree,
				   string inputFile) {
	// Todo by file I/O person
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
bool writeDataFile(const HashTable &hashTable, const BinaryTree &BinaryTree,
				   string outputFile) {
	// to do by file I/O person
}

void horiDisplay(string key) 
{
	Puzzle item;
	getPuzzle(key,item);
	std::cout << item << " ";
 }

void vertiDisplay(string key)
{
	Puzzle item;
	getPuzzle(key,item);
	std::cout << item << std::endl; 
}

void indentedDisplay(Puzzle &item, int level) {
	for (int i = 1; i < level; i++)
		std::cout << "..";
	std::cout << level << "). " << item << std::endl;
}

void displayMenuOptions() {
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
void inputDataFromFile(HashTable &hashTable, BinaryTree &binaryTree) {
	std::cout << "Input file name: ";

	std::string fileName;
	std::cin.ignore();

	std::getline(std::cin, fileName);

	if (inputDataFile(hashTable, binaryTree, fileName)) {
		std::cout << "File data added succesfully" << std::endl;
	} else {
		std::cout << "Error in adding data from file" << std::endl;
	}
}
void inputSingleEntry(HashTable &hashTable, BinaryTree &binaryTree) {}
void deleteEntry(HashTable &hashTable, BinaryTree &binaryTree) {}
void findEntry(const HashTable &hashTable, const BinaryTree &binaryTree) {}
void listEntrys(const HashTable &hashTable,const BinaryTree &binaryTree) 
{
	binaryTree.inorderTraversal(horiDisplay);
}

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
void writeToFile(const HashTable &hashTable, const BinaryTree &binaryTree) {
	std::cout << "Output file name: ";

	std::string fileName;
	std::cin.ignore();

	std::getline(std::cin, fileName);

	if (writeDataFile(hashTable, binaryTree, fileName)) {
		std::cout << "Data succesfully written to file" << std::endl;
	} else {
		std::cout << "Error in writing data to file" << std::endl;
	}
}
void statistics(const HashTable &hashTable, const BinaryTree &binaryTree) {}


void getPuzzle(string key, Puzzle& puzzleOut)
{
	hash->search(puzzleOut,key);
}
