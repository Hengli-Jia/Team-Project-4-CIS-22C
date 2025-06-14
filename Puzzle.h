/*
 Puzzle: stores a chess puzzle with its information
 Author: Toma Yuen
*/

#ifndef PUZZLE_H
#define PUZZLE_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Puzzle {
  private:
	string _puzzleId;
	string _fen;
	vector<string> _moves;
	int _rating;
	int _ratingDeviation;
	int _popularity;
	int _nbPlays;
	vector<string> _themes;
	string _gameUrl;
	vector<string> _openingTags;

  public:
	// constructors
	Puzzle()
		: _puzzleId(""), _fen(""), _moves({}), _rating(0), _ratingDeviation(0),
		  _popularity(0), _nbPlays(0), _themes({}), _gameUrl(""),
		  _openingTags({}) {}
	Puzzle(string puzzleId, string fen, vector<string> moves, int rating,
		   int ratingDeviation, int popularity, int nbPlays,
		   vector<string> themes, string gameUrl, vector<string> openingTags)
		: _puzzleId(puzzleId), _fen(fen), _moves(moves), _rating(rating),
		  _ratingDeviation(ratingDeviation), _popularity(popularity),
		  _nbPlays(nbPlays), _themes(themes), _gameUrl(gameUrl),
		  _openingTags(openingTags) {}

	// copy constructor
	Puzzle(const Puzzle &other)
		: _puzzleId(other._puzzleId), _fen(other._fen), _moves(other._moves),
		  _rating(other._rating), _ratingDeviation(other._ratingDeviation),
		  _popularity(other._popularity), _nbPlays(other._nbPlays),
		  _themes(other._themes), _gameUrl(other._gameUrl),
		  _openingTags(other._openingTags) {}

	// setters
	void setPuzzleId(const string &puzzleId) { _puzzleId = puzzleId; }
	void setFen(const string &fen) { _fen = fen; }
	void setMoves(const vector<string> &moves) { _moves = moves; }
	void setRating(int rating) { _rating = rating; }
	void setRatingDeviation(int deviation) { _ratingDeviation = deviation; }
	void setPopularity(int popularity) { _popularity = popularity; }
	void setNbPlays(int nbPlays) { _nbPlays = nbPlays; }
	void setThemes(const vector<string> &themes) { _themes = themes; }
	void setGameUrl(const string &url) { _gameUrl = url; }
	void setOpeningTags(const vector<string> &tags) { _openingTags = tags; }

	// getters
	string puzzleId() const { return _puzzleId; }
	string fen() const { return _fen; }
	vector<string> moves() const { return _moves; }
	int rating() const { return _rating; }
	int ratingDeviation() const { return _ratingDeviation; }
	int popularity() const { return _popularity; }
	int nbPlays() const { return _nbPlays; }
	vector<string> themes() const { return _themes; }
	string gameUrl() const { return _gameUrl; }
	vector<string> openingTags() const { return _openingTags; }

	// get key will return whatever we decide will be the key
	// for now that will be the puzzle id
	string getKey() const { return _puzzleId; }

	// copy assignment operator
	Puzzle &operator=(const Puzzle &other) {
		if (this != &other) {
			_puzzleId = other._puzzleId;
			_fen = other._fen;
			_moves = other._moves;
			_rating = other._rating;
			_ratingDeviation = other._ratingDeviation;
			_popularity = other._popularity;
			_nbPlays = other._nbPlays;
			_themes = other._themes;
			_gameUrl = other._gameUrl;
			_openingTags = other._openingTags;
		}
		return *this;
	}

	friend std::ostream &operator<<(std::ostream &stream, const Puzzle &p) {
		stream << p.puzzleId() << ',';
		stream << p.fen() << ',';
		for (size_t j = 0; j < p.moves().size(); ++j) {
			if (j > 0)
				stream << ' ';
			stream << p.moves()[j];
		}
		stream << ',' << p.rating() << ',' << p.ratingDeviation() << ','
			   << p.popularity() << ',' << p.nbPlays() << ',';
		for (size_t j = 0; j < p.themes().size(); ++j) {
			if (j > 0)
				stream << ' ';
			stream << p.themes()[j];
		}
		stream << ',' << p.gameUrl() << ',';
		for (size_t j = 0; j < p.openingTags().size(); ++j) {
			if (j > 0)
				stream << ' ';
			stream << p.openingTags()[j];
		}
		return stream;
	}
};

#endif
