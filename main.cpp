/*
 TODO: add members information and project description
*/

#include "AVL.h"
#include "HashTable.h"
#include "Puzzle.h"
#include "Stack.h"

#include <cctype>
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

HashTable<Puzzle> *globalHash; // Toma: I don't think a global variable should
							   // be used like this

// .............................................................................

// MENU FUNCTION DECLARATIONS

void menu();
char menuInput();

void inputDataFile(HashTable<Puzzle> &hashTable, AVL<Puzzle> &avl, string inputFile = "");
void outputDataFile(const HashTable<Puzzle> &hashTable, string inputFile = "");

void addItem(HashTable<Puzzle> &hashTable, AVL<Puzzle> &avl);
void deleteItem(HashTable<Puzzle> &hashTable, AVL<Puzzle> &avl, Stack<Puzzle>& deleteStack);
void undoDelete(HashTable<Puzzle>& hashTable, AVL<Puzzle>& avl, Stack<Puzzle>& deleteStack);
void findItem();

void listSorted(const AVL<Puzzle> &avl);
void statistics(const HashTable<Puzzle> &hashTable);
char attemptExit();

// HIDDEN MENU OPTIONS

void displayIndentedTree(const AVL<Puzzle> &avl);
void displayTeamMembers();

// HELPER FUNCTION DECLARATIONS
int determineHashSize(string inputFile = "");
static void printIndentedTree(BinaryNode<Puzzle> *node, int level);

// .............................................................................

// MAIN FUNCTION

int main() {
	string inputFile = "puzzles_database.txt";
	string outputFile = "puzzles_database_hashtable.txt";

	int hashSize = determineHashSize(inputFile);

	// Initialize Hash Table， AVL and Stack
	HashTable<Puzzle> hashTable(hashSize);
	AVL<Puzzle> avl;
	Stack<Puzzle> deleteStack;

	// File I/O
	inputDataFile(hashTable, avl, inputFile);
	outputDataFile(hashTable, outputFile);

	globalHash = &hashTable;

	menu();
	char choice;

	do {
		choice = menuInput();
		switch (choice) {
		case 'I':
			inputDataFile(hashTable, avl);
			break;
		case 'O':
			outputDataFile(hashTable);
			break;
		case 'A':
			addItem(hashTable, avl);
			break;
		case 'D':
			deleteItem(hashTable, avl, deleteStack);
			break;
		case 'U': // For undo delete
    		undoDelete(hashTable, avl, deleteStack);
    		break;
		case 'F':
			findItem();
			break;
		case 'L':
			listSorted(avl);
			break;
		case 'S':
			statistics(hashTable);
			break;
		case 'H':
			menu(); // show menu on help request
			break;
		case 'E':
			choice = attemptExit();
			break;
		case 'T': // hidden option: display indented tree
			displayIndentedTree(avl);
			break;
		case 'M': // hidden option: display team members
			displayTeamMembers();
			break;
		default:
			cout << "Invalid choice. Please try again.\n";
			break;
		}
	} while (choice != 'E');
}

// .............................................................................

// MENU FUNCTION DEFINITIONS

void menu() {
	cout << "\nMenu Options:\n";
	cout << "I - Input data from file\n";
	cout << "O - Output data to file\n";
	cout << "A - Add a new puzzle\n";
	cout << "D - Delete a puzzle\n";
	cout << "U - Undo last deletion\n";
	cout << "F - Find a puzzle\n";
	cout << "L - List sorted data\n";
	cout << "S - Show statistics\n";
	cout << "H - Help (show this menu)\n";
	cout << "E - Exit the program\n";
	cout << "T - Display indented tree (hidden option)\n";
	cout << "M - Display team members (hidden option)\n";
}

char menuInput() {
	cout << "\nEnter your choice: ";
	string input;
	getline(cin, input);

	// skip leading whitespace and get first character
	for (char ch : input) {
		if (!isspace(static_cast<unsigned char>(ch))) {
			return toupper(static_cast<unsigned char>(ch));
		}
	}
	return '\0'; // no valid input
}
void inputDataFile(HashTable<Puzzle> &hashTable, AVL<Puzzle> &avl,
				   string inputFile) {
	using namespace std::chrono;
	auto start = high_resolution_clock::now();

	// if inputFile is empty, prompt user for input
	if (inputFile.empty()) {
		cout << "Enter input file name: ";
		getline(cin, inputFile);
	}

	// open the input file
	ifstream file(inputFile);
	if (!file.is_open()) {
		cerr << "Failed to open input file: " << inputFile << endl;
		return;
	}

	// read data and insert into hashTable and avl
	string line;
	int lineNum = 0;
	getline(file, line); // skip header
	while (getline(file, line)) {
		if ((lineNum + 1) % 10000 == 0) {
			cout << "Processing line " << lineNum + 1 << ": " << line << endl;
			cout << "Current hash table size: " << hashTable.getCapacity()
				 << endl;
		}
		lineNum++;
		if (line.empty())
			continue;

		// parse the line into fields
		stringstream ss(line);
		string puzzleId, fen, moves, rating, ratingDeviation, popularity,
			nbPlays, themes, gameUrl, openingTags;
		getline(ss, puzzleId, ',');
		getline(ss, fen, ',');
		getline(ss, moves, ',');
		getline(ss, rating, ',');
		getline(ss, ratingDeviation, ',');
		getline(ss, popularity, ',');
		getline(ss, nbPlays, ',');
		getline(ss, themes, ',');
		getline(ss, gameUrl, ',');

		// openingTags is optional, so check if present
		if (!ss.eof()) {
			getline(ss, openingTags, ',');
		} else {
			openingTags = "";
		}

		// validate required fields (first 9 fields must not be empty)
		if (puzzleId.empty() || fen.empty() || moves.empty() ||
			rating.empty() || ratingDeviation.empty() || popularity.empty() ||
			nbPlays.empty() || themes.empty() || gameUrl.empty()) {
			continue; // skip malformed line
		}

		// parse moves, themes, openingTags as vectors
		vector<string> movesVec, themesVec, openingTagsVec;
		stringstream movesSS(moves), themesSS(themes), tagsSS(openingTags);
		string token;
		while (getline(movesSS, token, ' ')) {
			if (!token.empty())
				movesVec.push_back(token);
		}

		while (getline(themesSS, token, ' ')) {
			if (!token.empty())
				themesVec.push_back(token);
		}

		while (getline(tagsSS, token, ' ')) {
			if (!token.empty())
				openingTagsVec.push_back(token);
		}

		try {
			Puzzle puzzle(puzzleId, fen, movesVec, stoi(rating),
						  stoi(ratingDeviation), stoi(popularity),
						  stoi(nbPlays), themesVec, gameUrl, openingTagsVec);
			hashTable.insert(puzzle);
			avl.insert(puzzle);
		} catch (const exception &e) {
			cerr << "[ERROR] Failed to parse line " << lineNum << ": " << line
				 << " with error: " << e.what() << endl;
			continue; // skip line if conversion fails
		}
	}
	file.close();
	auto end = high_resolution_clock::now();
	double seconds = duration_cast<duration<double>>(end - start).count();
	cout << "[INFO] inputDataFile completed in " << seconds << " seconds.\n";
}

void outputDataFile(const HashTable<Puzzle> &hashTable, string outputFile) {
	// if outputFile is empty, prompt user for input
	if (outputFile.empty()) {
		cout << "Enter output file name: ";
		getline(cin, outputFile);
	}

	// save to file (in hash table sequence)
	ofstream outFile(outputFile);
	if (outFile.is_open()) {
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
		outFile.close();
	} else {
		cerr << "[ERROR] Could not open output file: " << outputFile << endl;
	}
}

void addItem(HashTable<Puzzle> &hashTable, AVL<Puzzle> &avl) {
	cout << "Add a new puzzle:\n";
	cout << "Enter full line (CSV format) or leave blank to input fields "
			"one by one:\n";
	string line;
	getline(cin, line);

	string puzzleId, fen, moves, rating, ratingDeviation, popularity, nbPlays,
		themes, gameUrl, openingTags;

	bool valid = false;
	while (!valid) {
		if (!line.empty()) {
			// Parse CSV line
			stringstream ss(line);
			getline(ss, puzzleId, ',');
			getline(ss, fen, ',');
			getline(ss, moves, ',');
			getline(ss, rating, ',');
			getline(ss, ratingDeviation, ',');
			getline(ss, popularity, ',');
			getline(ss, nbPlays, ',');
			getline(ss, themes, ',');
			getline(ss, gameUrl, ',');
			if (!ss.eof())
				getline(ss, openingTags, ',');
		} else {
			cout << "PuzzleId: ";
			getline(cin, puzzleId);
			cout << "FEN: ";
			getline(cin, fen);
			cout << "Moves (space-separated): ";
			getline(cin, moves);
			cout << "Rating: ";
			getline(cin, rating);
			cout << "RatingDeviation: ";
			getline(cin, ratingDeviation);
			cout << "Popularity: ";
			getline(cin, popularity);
			cout << "NbPlays: ";
			getline(cin, nbPlays);
			cout << "Themes (space-separated): ";
			getline(cin, themes);
			cout << "GameUrl: ";
			getline(cin, gameUrl);
			cout << "OpeningTags (space-separated, optional): ";
			getline(cin, openingTags);
		}

		// Validate required fields
		if (puzzleId.empty() || fen.empty() || moves.empty() ||
			rating.empty() || ratingDeviation.empty() || popularity.empty() ||
			nbPlays.empty() || themes.empty() || gameUrl.empty()) {
			cout << "[ERROR] One or more required fields are empty. "
					"Please re-enter.\n";
			puzzleId.clear();
			fen.clear();
			moves.clear();
			rating.clear();
			ratingDeviation.clear();
			popularity.clear();
			nbPlays.clear();
			themes.clear();
			gameUrl.clear();
			openingTags.clear();
			line.clear();
			cout << "Enter full line (CSV format) or leave blank to input "
					"fields one by one:\n";
			getline(cin, line);
			continue;
		}

		// Parse moves, themes, openingTags as vectors
		auto split = [](const string &s) {
			vector<string> v;
			stringstream ss(s);
			string item;
			while (ss >> item)
				v.push_back(item);
			return v;
		};
		vector<string> movesVec = split(moves);
		vector<string> themesVec = split(themes);
		vector<string> openingTagsVec = split(openingTags);

		// Validate integer fields
		try {
			int ratingInt = stoi(rating);
			int ratingDevInt = stoi(ratingDeviation);
			int popularityInt = stoi(popularity);
			int nbPlaysInt = stoi(nbPlays);

			// Check for duplicate puzzleId
			Puzzle temp;
			if (hashTable.search(temp, puzzleId)) {
				cout << "[ERROR] PuzzleId already exists in the hash "
						"table. Please use a unique PuzzleId.\n";
				puzzleId.clear();
				line.clear();
				continue;
			}

			Puzzle newPuzzle(puzzleId, fen, movesVec, ratingInt, ratingDevInt,
							 popularityInt, nbPlaysInt, themesVec, gameUrl,
							 openingTagsVec);

			hashTable.insert(newPuzzle);
			avl.insert(newPuzzle);
			cout << "Puzzle added successfully!\n";
			valid = true;
		} catch (const invalid_argument &) {
			cout << "[ERROR] One or more numeric fields are not valid "
					"integers. Please re-enter.\n";
			rating.clear();
			ratingDeviation.clear();
			popularity.clear();
			nbPlays.clear();
			line.clear();
			continue;
		} catch (const out_of_range &) {
			cout << "[ERROR] One or more numeric fields are out of range. "
					"Please re-enter.\n";
			rating.clear();
			ratingDeviation.clear();
			popularity.clear();
			nbPlays.clear();
			line.clear();
			continue;
		}
	}
}


void deleteItem(HashTable<Puzzle> &hashTable, AVL<Puzzle> &avl, Stack<Puzzle>& deleteStack) {
	cout << "Delete a puzzle by PuzzleId or FEN.\n";
	string input;
	cout << "Enter PuzzleId (leave blank to use FEN): ";
	getline(cin, input);
	string key = input;

	if (key.empty()) {
		cout << "Enter FEN: ";
		getline(cin, key);
	}

	if (key.empty()) {
		cout << "[ERROR] No PuzzleId or FEN provided.\n";
		return;
	}

	// Try to find by PuzzleId first
	Puzzle found;
	bool foundById = hashTable.search(found, key);
	if (!foundById) {
		// Try to find by FEN (linear search)
		for (int i = 0; i < hashTable.getCapacity(); ++i) {
			if (hashTable.getOccupiedAt(i) == 1) {
				Puzzle p = hashTable.getItemAt(i);
				if (p.fen() == key) {
					found = p;
					foundById = true;
					break;
				}
			}
		}
	}

	if (!foundById) {
		cout << "[ERROR] Puzzle not found by PuzzleId or FEN.\n";
		return;
	}

	// Remove from hash table
	if (hashTable.remove(found, found.getKey())) {
		cout << "[INFO] Puzzle removed from hash table.\n";
	} else {
		cout << "[WARN] Puzzle could not be removed from hash table.\n";
	}

	// Remove from AVL
	if (avl.remove(found.getKey())) {
		cout << "[INFO] Puzzle removed from AVL.\n";
	} else {
		cout << "[WARN] Puzzle could not be removed from AVL.\n";
	}

	// Push to deleteStack
	if (deleteStack.push(found)) {
    	cout << "[INFO] Puzzle pushed to deleteStack for undo.\n";
	} else {
    	cout << "[WARN] deleteStack is full, cannot store deleted puzzle.\n";
	}	
}

void undoDelete(HashTable<Puzzle>& hashTable, AVL<Puzzle>& avl, Stack<Puzzle>& deleteStack) {
    Puzzle lastDeleted;
    if (deleteStack.pop(lastDeleted)) {
        hashTable.insert(lastDeleted);
        avl.insert(lastDeleted);
        std::cout << "Undo successful. Puzzle restored.\n";
    } else {
        std::cout << "No deletion to undo.\n";
    }
}

void findItem() {
	cout << "Find a puzzle by PuzzleId or FEN.\n";
	string input;
	cout << "Enter PuzzleId (leave blank to use FEN): ";
	getline(cin, input);
	string key = input;

	if (key.empty()) {
		cout << "Enter FEN: ";
		getline(cin, key);
	}

	if (key.empty()) {
		cout << "[ERROR] No PuzzleId or FEN provided.\n";
		return;
	}

	// Try to find by PuzzleId first
	Puzzle found;
	bool foundById = globalHash->search(found, key);
	if (!foundById) {
		// Try to find by FEN (linear search)
		for (int i = 0; i < globalHash->getCapacity(); ++i) {
			if (globalHash->getOccupiedAt(i) == 1) {
				Puzzle p = globalHash->getItemAt(i);
				if (p.fen() == key) {
					found = p;
					foundById = true;
					break;
				}
			}
		}
	}

	if (!foundById) {
		cout << "[ERROR] Puzzle not found by PuzzleId or FEN.\n";
		return;
	}

	// Display the found puzzle
	cout << "[INFO] Puzzle found:\n";
	cout << found << endl;
}

void listSorted(const AVL<Puzzle> &avl) {
	cout << "Listing all puzzles sorted by PuzzleId (AVL inorder traversal):\n";
	// Helper function to print each puzzle
	auto printPuzzle = [](string key) {
		Puzzle puzzleOut;
		globalHash->search(puzzleOut, key);
		cout << puzzleOut << endl;
	};
	avl.inorderTraversal(printPuzzle);
}

void statistics(const HashTable<Puzzle> &hashTable) {
	cout << "Hash Table Statistics:\n";
	cout << "Load factor: " << hashTable.getLoadFactor() << "%\n";

	int totalCollisions = 0;
	int longestCollisionPath = 0;
	for (int i = 0; i < hashTable.getCapacity(); ++i) {
		if (hashTable.getOccupiedAt(i) == 1) {
			int col = hashTable.getCollisionsAt(i);
			totalCollisions += col;
			if (col > longestCollisionPath)
				longestCollisionPath = col;
		}
	}
	cout << "Total collisions: " << totalCollisions << "\n";
	cout << "Longest collision path: " << longestCollisionPath << "\n";
}

char attemptExit() {
	cout << "Confirm Exit(Y/N): ";
	string input;
	getline(cin, input);

	for (char ch : input) {
		if (!isspace((unsigned char)ch))
			return (toupper((unsigned char)ch) == 'Y') ? 'E' : '\0';
	}

	return '\0';
}

// HIDDEN MENU OPTIONS

void displayIndentedTree(const AVL<Puzzle> &avl) {
	cout << "Indented AVL (by PuzzleId):\n";
	printIndentedTree(avl.getRoot(), 0);
}

void displayTeamMembers() {}

// .............................................................................

// OTHER FUNCTION DEFINITIONS

int determineHashSize(string inputFile) {
	// if inputFile is empty, prompt user for input
	if (inputFile.empty()) {
		cout << "Enter input file name: ";
		getline(cin, inputFile);
	}

	// open the input file
	ifstream file(inputFile);
	if (!file.is_open()) {
		cerr << "Failed to open input file: " << inputFile << endl;
		return DEFAULT_HASH_SIZE;
	}

	string line;
	int lineCount = 0;
	getline(file, line); // skip header
	while (getline(file, line)) {
		++lineCount;
	}
	file.close(); // CLOSE after counting

	// reopen the file for actual reading
	file.open(inputFile);
	if (!file.is_open()) {
		cerr << "Failed to reopen input file: " << inputFile << endl;
		return DEFAULT_HASH_SIZE;
	}

	// determine hash size using a prime number
	auto isPrime = [](int n) {
		if (n <= 1)
			return false;
		if (n <= 3)
			return true;
		if (n % 2 == 0 || n % 3 == 0)
			return false;
		for (int i = 5; i * i <= n; i += 6) {
			if (n % i == 0 || n % (i + 2) == 0)
				return false;
		}
		return true;
	};
	int hashSize = lineCount * 2;
	while (!isPrime(hashSize))
		++hashSize;

	return hashSize;
}

// Helper for indented AVL display
static void printIndentedTree(BinaryNode<Puzzle> *node, int level) {
	if (!node)
		return;
	for (int i = 0; i < level; ++i)
		cout << ".";
	cout << (level + 1) << ").";
	Puzzle puzzleOut;
	globalHash->search(puzzleOut, node->getKey());
	cout << " " << puzzleOut.puzzleId() << endl;
	printIndentedTree(node->getLeft(), level + 1);
	printIndentedTree(node->getRight(), level + 1);
}
