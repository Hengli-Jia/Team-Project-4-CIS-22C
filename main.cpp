/*
 TODO: add members information and project description
*/

#include "BST.cpp"
#include "HashTable.cpp"

#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

HashTable
	*hash; // Toma: I don't think a global variable should be used like this

// .............................................................................

// MENU FUNCTION DECLARATIONS

void menu();
char menuInput();
void addItem(HashTable &hashTable, BinaryTree &bst);
void inputDataFile(HashTable &hashTable, BinaryTree &bst,
				   string inputFile = "");
void deleteItem(HashTable &hashTable, BinaryTree &bst);
void findItem(const BinaryTree &bst);
void printData(const BinaryTree &bst);
void outputDataFile(const BinaryTree &bst, string inputFile = "");
void statistics(const HashTable &hashTable);
char attemptExit();

// HIDDEN MENU OPTIONS

void displayIndentedTree(const BinaryTree &bst);
void displayTeamMembers();

// .............................................................................

// OTHER FUNCTION DECLARATIONS

void hDisplay(const string &key, Puzzle &puzzleOut);
void vDisplay(const string &key, Puzzle &puzzleOut);

void getPuzzle(const string &key, Puzzle &puzzleOut);

// .............................................................................

// MAIN FUNCTION

int main() {
	// Initialize Hash Table and BST
	HashTable hashTable;
	BinaryTree bst;

	hash = &hashTable;

	// File I/O
	string inputFile = "puzzles_database.txt";
	// inputDataFile(hashTable, bst, inputFile);
	// outputDataFile(bst, inputFile);

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
			findItem(bst);
			break;
		case 'P':
			printData(bst);
			break;
		case 'O':
			outputDataFile(bst);
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
	std::cout << "P - Print all puzzles\n";
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

void addItem(HashTable &hashTable, BinaryTree &bst) {}

void inputDataFile(HashTable &hashTable, BinaryTree &bst, string inputFile) {
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

	// count lines in the input file
	std::string line;
	int lineCount = 0;
	std::getline(file, line); // skip header
	while (std::getline(file, line)) {
		if (!line.empty())
			lineCount++;
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

	// recreate hashTable with new size
	hashTable = HashTable(hashSize);

	// read data and insert into hashTable and bst
	int lineNum = 0;
	std::getline(file, line); // skip header
	while (std::getline(file, line)) {
		lineNum++;
		if (line.empty())
			continue;

		std::cout << "[DEBUG] Processing line " << lineNum << ": " << line
				  << std::endl;

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
			std::cout << "[DEBUG] Inserting Puzzle to hashTable: " << std::endl;
			hashTable.insert(puzzle);
			std::cout << "[DEBUG] Inserting Puzzle to bst: " << std::endl;
			bst.insertBST(puzzle);
		} catch (const std::exception &e) {
			std::cerr << "[ERROR] Failed to parse line " << lineNum << ": "
					  << line << " with error: " << e.what() << std::endl;
			continue; // skip line if conversion fails
		}
	}
	file.close();
}
void deleteItem(HashTable &hashTable, BinaryTree &bst) {}
void findItem(const BinaryTree &bst) {}
void printData(const BinaryTree &bst) { /*bst.inorderTraversal(hDisplay);*/ }

void outputDataFile(const BinaryTree &bst, string outputFile) {
	/*
	// if outputFile is empty, prompt user for input
	if (outputFile.empty()) {
		std::cout << "Enter output file name: ";
		std::getline(std::cin, outputFile);
	}

	// save to file (in hash table sequence)
	std::string outFileName = outputFile;
	size_t dotPos = outFileName.find_last_of('.');
	if (dotPos != std::string::npos) {
		outFileName.insert(dotPos, "_hashtable");
	} else {
		outFileName += "_hashtable";
	}
	std::ofstream outFile(outFileName);
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
		std::cerr << "[ERROR] Could not open output file: " << outFileName
				  << std::endl;
	}
	*/
}
void statistics(const HashTable &hashTable) {}

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

void displayIndentedTree(const BinaryTree &bst) {}
void displayTeamMembers() {}

// .............................................................................

// OTHER FUNCTION DEFINITIONS

void hDisplay(const string &key, Puzzle &puzzleOut) {
	getPuzzle(key, puzzleOut);
	std::cout << puzzleOut << " ";
}
void vDisplay(const string &key, Puzzle &puzzleOut) {
	getPuzzle(key, puzzleOut);
	std::cout << puzzleOut << std::endl;
}

void getPuzzle(const string &key, Puzzle &puzzleOut) {
	hash->search(puzzleOut, key);
}
