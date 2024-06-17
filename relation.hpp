#ifndef RELATION_HPP
#define RELATION_HPP

#include "search.hpp"
#include <vector>
#include <string>
#include <tuple>
using namespace std;

class Relation {
public:
	friend class Search;

	Relation(string filename);
	Relation* build_bitmap(int field_index);
	void add_edependency(Relation* ed, int column);

private:
	vector<string> column_names;
	vector<vector<string>> fields;
	vector<tuple<Relation*, int>> foreign_keys;

};

void strip(string& s);

#endif