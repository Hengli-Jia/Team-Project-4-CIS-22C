Project Title: Lichess Puzzles Database
Application Data: Puzzle with the following member variables:

    PuzzleId (key, string) - 5 characters including numbers, lowercase, and uppercase alphabets
    FEN (string) - Contains the position of a chess puzzle
    Moves (string) - The following moves to solve the puzzle in regular chess notation
    Rating (int) - Targeted audience chess ratings to solve the puzzle (Difficulty)
    # Rating Derivation (int) - Targeted audience in a range (Rating +- Rating Derivation)
    # Popularity (int) - Popularity of the puzzle based on Lichess player reviews
    # NbPlays (int) - Number of attempts on Lichess
    Themes (vector<string> or string) - Themes of the puzzle. Such as {"Checkmate in 2", "Sacrifice"}
    # GameUrl (string) - Lichess URL to game analysis
    # OpeningTags (vector<string> or string) - Chess opening of the game. Such as {"Queen's Gambit", "Queen’s Gambit Declined"}

The database is based on https://database.lichess.org/#puzzles.
It is a downloadable file called lichess_db_puzzle.csv.zst, which is basically a zipped, comma-separated text file that can easily be converted into a .txt file if necessary.
We can also take a small section of the database if necessary, since the whole database is over 800 MB.
I am simply explaining the "member variables" in the database, and we can ignore the variables marked with "#" if necessary.
