/*
 Puzzle: stores a chess puzzle with its information
 Author: Toma Yuen
*/

#ifndef PUZZLE_H
#define PUZZLE_H

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class Puzzle {
  private:
	string _puzzleId = "";
	string _fen = "";
	vector<string> _moves = {};
	int _rating = 0;
	int _ratingDeviation = 0;
	int _popularity = 0;
	int _nbPlays = 0;
	vector<string> _themes = {};
	string _gameUrl = "";
	vector<string> _openingTags = {};

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
		std::cout << "[DEBUG] Puzzle copy source: "
				  << "puzzleId='" << other._puzzleId << "', "
				  << "fen='" << other._fen << "', moves=[";
		for (size_t i = 0; i < other._moves.size(); ++i) {
			if (i > 0)
				std::cout << ' ';
			std::cout << other._moves[i];
		}
		std::cout << "], rating=" << other._rating
				  << ", ratingDeviation=" << other._ratingDeviation
				  << ", popularity=" << other._popularity
				  << ", nbPlays=" << other._nbPlays << ", themes=[";
		for (size_t i = 0; i < other._themes.size(); ++i) {
			if (i > 0)
				std::cout << ' ';
			std::cout << other._themes[i];
		}
		std::cout << "], gameUrl='" << other._gameUrl << "', openingTags=[";
		for (size_t i = 0; i < other._openingTags.size(); ++i) {
			if (i > 0)
				std::cout << ' ';
			std::cout << other._openingTags[i];
		}
		std::cout << "]" << std::endl;
		if (this != &other) {
			std::cout << "[DEBUG] Original Puzzle ID: " << _puzzleId
					  << std::endl;
			_puzzleId = other._puzzleId;
			std::cout << "[DEBUG] Assigned _puzzleId: " << _puzzleId
					  << std::endl;
			_fen = other._fen;
			std::cout << "[DEBUG] Assigned _fen: " << _fen << std::endl;
			_moves = other._moves;
			std::cout << "[DEBUG] Assigned _moves, size: " << _moves.size()
					  << std::endl;
			_rating = other._rating;
			std::cout << "[DEBUG] Assigned _rating: " << _rating << std::endl;
			_ratingDeviation = other._ratingDeviation;
			std::cout << "[DEBUG] Assigned _ratingDeviation: "
					  << _ratingDeviation << std::endl;
			_popularity = other._popularity;
			std::cout << "[DEBUG] Assigned _popularity: " << _popularity
					  << std::endl;
			_nbPlays = other._nbPlays;
			std::cout << "[DEBUG] Assigned _nbPlays: " << _nbPlays << std::endl;
			_themes = other._themes;
			std::cout << "[DEBUG] Assigned _themes, size: " << _themes.size()
					  << std::endl;
			_gameUrl = other._gameUrl;
			std::cout << "[DEBUG] Assigned _gameUrl: " << _gameUrl << std::endl;
			_openingTags = other._openingTags;
			std::cout << "[DEBUG] Assigned _openingTags, size: "
					  << _openingTags.size() << std::endl;
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
