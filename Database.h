/*
 Database: stores a chess puzzles in ascending puzzleId
 Author:
*/

#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>

using std::string;
using std::vector;

template <class T>
class Database {
 private:
  vector<T> _dataset;

 public:
  // constructors
  Database() : _dataset({}) {};
  Database(const vector<T>& dataset) : _dataset(dataset) {};

  // destructor
  ~Database();

  // setter & getter
  void setDataset(const vector<T>& dataset) { _dataset = dataset; }
  vector<T> dataset() const { return _dataset; }

  // functions
  void addItem(T& item);
  void addFileData(string& fileName);
  void deleteData(string& key);
  void printItem(string& key) const;
  void printDataset() const;
  // TODO: Hidden print option - Team Project-Part 2
  // TODO: Statistics - Team Project-Part 2
};

#endif
