/*
 TODO: add members information and project description
*/

#include "BST.cpp"
#include "HashTable.cpp"
#include "Puzzle.h"

#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

const int DEFAULT_HASH_SIZE = 53;

HashTable<Puzzle>
	*hash; // Toma: I don't think a global variable should be used like this

// .............................................................................

// MENU FUNCTION DECLARATIONS

void menu();
char menuInput();
void addItem(HashTable<Puzzle> &hashTable, BST<Puzzle> &bst);
void inputDataFile(HashTable<Puzzle> &hashTable, BST<Puzzle> &bst,
				   string inputFile = "");
void deleteItem(HashTable<Puzzle> &hashTable, BST<Puzzle> &bst);
void findItem();
void listSorted(const BST<Puzzle> &bst);
void outputDataFile(const HashTable<Puzzle> &hashTable, string inputFile = "");
void statistics(const HashTable<Puzzle> &hashTable);
char attemptExit();

// HIDDEN MENU OPTIONS

void displayIndentedTree(const BST<Puzzle> &bst);
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

	// Initialize Hash Table and BST
	HashTable<Puzzle> hashTable(hashSize);
	BST<Puzzle> bst;

	// File I/O
	inputDataFile(hashTable, bst, inputFile);
	outputDataFile(hashTable, outputFile);

	hash = &hashTable;

	menu();
	char choice;

	do {
		choice = menuInput();
		switch (choice) {
		case 'A':
			addItem(hashTable, bst);
			break;
		case 'I':
			inputDataFile(hashTable, bst);
			break;
		case 'D':
			deleteItem(hashTable, bst);
			break;
		case 'F':
			findItem();
			break;
		case 'L':
			listSorted(bst);
			break;
		case 'O':
			outputDataFile(hashTable);
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
			displayIndentedTree(bst);
			break;
		case 'M': // hidden option: display team members
			displayTeamMembers();
			break;
		default:
			std::cout << "Invalid choice. Please try again." << std::endl;
			break;
		}
	} while (choice != 'E');
}

// .............................................................................

// MENU FUNCTION DEFINITIONS

void menu() {
	std::cout << "\nMenu Options:\n";
	std::cout << "A - Add a new puzzle\n";
	std::cout << "I - Input data from file\n";
	std::cout << "D - Delete a puzzle\n";
	std::cout << "F - Find a puzzle\n";
	std::cout << "L - List sorted data\n";
	std::cout << "O - Output data to file\n";
	std::cout << "S - Show statistics\n";
	std::cout << "H - Help (show this menu)\n";
	std::cout << "E - Exit the program\n";
	std::cout << "T - Display indented tree (hidden option)\n";
	std::cout << "M - Display team members (hidden option)\n";
}

char menuInput() {
	std::cout << "\nEnter your choice: ";
	std::string input;
	std::getline(std::cin, input);

	// skip leading whitespace and get first character
	for (char ch : input) {
		if (!std::isspace(static_cast<unsigned char>(ch))) {
			return std::toupper(static_cast<unsigned char>(ch));
		}
	}
	return '\0'; // no valid input
}

void addItem(HashTable<Puzzle> &hashTable, BST<Puzzle> &bst) {
	std::cout << "Add a new puzzle:\n";
	std::cout << "Enter full line (CSV format) or leave blank to input fields "
				 "one by one:\n";
	std::string line;
	std::getline(std::cin, line);

	std::string puzzleId, fen, moves, rating, ratingDeviation, popularity,
		nbPlays, themes, gameUrl, openingTags;

	bool valid = false;
	while (!valid) {
		if (!line.empty()) {
			// Parse CSV line
			std::stringstream ss(line);
			std::getline(ss, puzzleId, ',');
			std::getline(ss, fen, ',');
			std::getline(ss, moves, ',');
			std::getline(ss, rating, ',');
			std::getline(ss, ratingDeviation, ',');
			std::getline(ss, popularity, ',');
			std::getline(ss, nbPlays, ',');
			std::getline(ss, themes, ',');
			std::getline(ss, gameUrl, ',');
			if (!ss.eof())
				std::getline(ss, openingTags, ',');
		} else {
			std::cout << "PuzzleId: ";
			std::getline(std::cin, puzzleId);
			std::cout << "FEN: ";
			std::getline(std::cin, fen);
			std::cout << "Moves (space-separated): ";
			std::getline(std::cin, moves);
			std::cout << "Rating: ";
			std::getline(std::cin, rating);
			std::cout << "RatingDeviation: ";
			std::getline(std::cin, ratingDeviation);
			std::cout << "Popularity: ";
			std::getline(std::cin, popularity);
			std::cout << "NbPlays: ";
			std::getline(std::cin, nbPlays);
			std::cout << "Themes (space-separated): ";
			std::getline(std::cin, themes);
			std::cout << "GameUrl: ";
			std::getline(std::cin, gameUrl);
			std::cout << "OpeningTags (space-separated, optional): ";
			std::getline(std::cin, openingTags);
		}

		// Validate required fields
		if (puzzleId.empty() || fen.empty() || moves.empty() ||
			rating.empty() || ratingDeviation.empty() || popularity.empty() ||
			nbPlays.empty() || themes.empty() || gameUrl.empty()) {
			std::cout << "[ERROR] One or more required fields are empty. "
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
			std::cout << "Enter full line (CSV format) or leave blank to input "
						 "fields one by one:\n";
			std::getline(std::cin, line);
			continue;
		}

		// Parse moves, themes, openingTags as vectors
		auto split = [](const std::string &s) {
			std::vector<std::string> v;
			std::stringstream ss(s);
			std::string item;
			while (ss >> item)
				v.push_back(item);
			return v;
		};
		std::vector<std::string> movesVec = split(moves);
		std::vector<std::string> themesVec = split(themes);
		std::vector<std::string> openingTagsVec = split(openingTags);

		// Validate integer fields
		try {
			int ratingInt = std::stoi(rating);
			int ratingDevInt = std::stoi(ratingDeviation);
			int popularityInt = std::stoi(popularity);
			int nbPlaysInt = std::stoi(nbPlays);

			// Check for duplicate puzzleId
			Puzzle temp;
			if (hashTable.search(temp, puzzleId)) {
				std::cout << "[ERROR] PuzzleId already exists in the hash "
							 "table. Please use a unique PuzzleId.\n";
				puzzleId.clear();
				line.clear();
				continue;
			}

			Puzzle newPuzzle(puzzleId, fen, movesVec, ratingInt, ratingDevInt,
							 popularityInt, nbPlaysInt, themesVec, gameUrl,
							 openingTagsVec);

			hashTable.insert(newPuzzle);
			bst.insert(newPuzzle);
			std::cout << "Puzzle added successfully!\n";
			valid = true;
		} catch (const std::invalid_argument &) {
			std::cout << "[ERROR] One or more numeric fields are not valid "
						 "integers. Please re-enter.\n";
			rating.clear();
			ratingDeviation.clear();
			popularity.clear();
			nbPlays.clear();
			line.clear();
			continue;
		} catch (const std::out_of_range &) {
			std::cout << "[ERROR] One or more numeric fields are out of range. "
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

void inputDataFile(HashTable<Puzzle> &hashTable, BST<Puzzle> &bst,
				   string inputFile) {
	// if inputFile is empty, prompt user for input
	if (inputFile.empty()) {
		std::cout << "Enter input file name: ";
		std::getline(std::cin, inputFile);
	}

	// open the input file
	std::ifstream file(inputFile);
	if (!file.is_open()) {
		std::cerr << "Failed to open input file: " << inputFile << std::endl;
		return;
	}

	// read data and insert into hashTable and bst
	std::string line;
	int lineNum = 0;
	std::getline(file, line); // skip header
	while (std::getline(file, line)) {
		lineNum++;
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
			continue; // skip malformed line
		}

		// parse moves, themes, openingTags as vectors
		std::vector<std::string> movesVec, themesVec, openingTagsVec;
		std::stringstream movesSS(moves), themesSS(themes), tagsSS(openingTags);
		std::string token;
		while (std::getline(movesSS, token, ' ')) {
			if (!token.empty())
				movesVec.push_back(token);
		}

		while (std::getline(themesSS, token, ' ')) {
			if (!token.empty())
				themesVec.push_back(token);
		}

		while (std::getline(tagsSS, token, ' ')) {
			if (!token.empty())
				openingTagsVec.push_back(token);
		}

		try {
			Puzzle puzzle(puzzleId, fen, movesVec, std::stoi(rating),
						  std::stoi(ratingDeviation), std::stoi(popularity),
						  std::stoi(nbPlays), themesVec, gameUrl,
						  openingTagsVec);
			hashTable.insert(puzzle);
			bst.insert(puzzle);
		} catch (const std::exception &e) {
			std::cerr << "[ERROR] Failed to parse line " << lineNum << ": "
					  << line << " with error: " << e.what() << std::endl;
			continue; // skip line if conversion fails
		}
	}
	file.close();
}

void deleteItem(HashTable<Puzzle> &hashTable, BST<Puzzle> &bst) {
	std::cout << "Delete a puzzle by PuzzleId or FEN.\n";
	std::string input;
	std::cout << "Enter PuzzleId (leave blank to use FEN): ";
	std::getline(std::cin, input);
	std::string key = input;

	if (key.empty()) {
		std::cout << "Enter FEN: ";
		std::getline(std::cin, key);
	}

	if (key.empty()) {
		std::cout << "[ERROR] No PuzzleId or FEN provided.\n";
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
		std::cout << "[ERROR] Puzzle not found by PuzzleId or FEN.\n";
		return;
	}

	// Remove from hash table
	if (hashTable.remove(found, found.getKey())) {
		std::cout << "[INFO] Puzzle removed from hash table.\n";
	} else {
		std::cout << "[WARN] Puzzle could not be removed from hash table.\n";
	}

	// Remove from BST
	if (bst.remove(found.getKey())) {
		std::cout << "[INFO] Puzzle removed from BST.\n";
	} else {
		std::cout << "[WARN] Puzzle could not be removed from BST.\n";
	}
}

void findItem() {
	std::cout << "Find a puzzle by PuzzleId or FEN.\n";
	std::string input;
	std::cout << "Enter PuzzleId (leave blank to use FEN): ";
	std::getline(std::cin, input);
	std::string key = input;

	if (key.empty()) {
		std::cout << "Enter FEN: ";
		std::getline(std::cin, key);
	}

	if (key.empty()) {
		std::cout << "[ERROR] No PuzzleId or FEN provided.\n";
		return;
	}

	// Try to find by PuzzleId first
	Puzzle found;
	bool foundById = hash->search(found, key);
	if (!foundById) {
		// Try to find by FEN (linear search)
		for (int i = 0; i < hash->getCapacity(); ++i) {
			if (hash->getOccupiedAt(i) == 1) {
				Puzzle p = hash->getItemAt(i);
				if (p.fen() == key) {
					found = p;
					foundById = true;
					break;
				}
			}
		}
	}

	if (!foundById) {
		std::cout << "[ERROR] Puzzle not found by PuzzleId or FEN.\n";
		return;
	}

	// Display the found puzzle
	std::cout << "[INFO] Puzzle found:\n";
	std::cout << found << std::endl;
}

void listSorted(const BST<Puzzle> &bst) {
	std::cout
		<< "Listing all puzzles sorted by PuzzleId (BST inorder traversal):\n";
	// Helper function to print each puzzle
	auto printPuzzle = [](std::string key) {
		Puzzle puzzleOut;
		hash->search(puzzleOut, key);
		std::cout << puzzleOut << std::endl;
	};
	bst.inorderTraversal(printPuzzle);
}

void outputDataFile(const HashTable<Puzzle> &hashTable, string outputFile) {
	// if outputFile is empty, prompt user for input
	if (outputFile.empty()) {
		std::cout << "Enter output file name: ";
		std::getline(std::cin, outputFile);
	}

	// save to file (in hash table sequence)
	std::ofstream outFile(outputFile);
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
		std::cerr << "[ERROR] Could not open output file: " << outputFile
				  << std::endl;
	}
}
void statistics(const HashTable<Puzzle> &hashTable) {
	std::cout << "Hash Table Statistics:\n";
	std::cout << "Load factor: " << hashTable.getLoadFactor() << "%\n";

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
	std::cout << "Total collisions: " << totalCollisions << "\n";
	std::cout << "Longest collision path: " << longestCollisionPath << "\n";
}

char attemptExit() {
	std::cout << "Confirm Exit(Y/N): ";
	std::string input;
	std::getline(std::cin, input);

	for (char ch : input) {
		if (!std::isspace((unsigned char)ch))
			return (std::toupper((unsigned char)ch) == 'Y') ? 'E' : '\0';
	}

	return '\0';
}

// HIDDEN MENU OPTIONS

void displayIndentedTree(const BST<Puzzle> &bst) {
	std::cout << "Indented BST (by PuzzleId):\n";
	BinaryNode<Puzzle> *root = *(BinaryNode<Puzzle> **)(void *)&bst;
	printIndentedTree(root, 0);
}

void displayTeamMembers() {}

// .............................................................................

// OTHER FUNCTION DEFINITIONS

int determineHashSize(string inputFile) {
	// if inputFile is empty, prompt user for input
	if (inputFile.empty()) {
		std::cout << "Enter input file name: ";
		std::getline(std::cin, inputFile);
	}

	// open the input file
	std::ifstream file(inputFile);
	if (!file.is_open()) {
		std::cerr << "Failed to open input file: " << inputFile << std::endl;
		return DEFAULT_HASH_SIZE;
	}

	std::string line;
	int lineCount = 0;
	std::getline(file, line); // skip header
	while (std::getline(file, line)) {
		++lineCount;
	}
	file.close(); // CLOSE after counting

	// reopen the file for actual reading
	file.open(inputFile);
	if (!file.is_open()) {
		std::cerr << "Failed to reopen input file: " << inputFile << std::endl;
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

// Helper for indented BST display
static void printIndentedTree(BinaryNode<Puzzle> *node, int level) {
	if (!node)
		return;
	printIndentedTree(node->getRight(), level + 1);
	for (int i = 0; i < level; ++i)
		std::cout << "  ";
	Puzzle puzzleOut;
	hash->search(puzzleOut, node->getKey());
	std::cout << puzzleOut.puzzleId() << std::endl;
	printIndentedTree(node->getLeft(), level + 1);
}
