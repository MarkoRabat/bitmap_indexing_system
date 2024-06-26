#ifndef RELATION_HPP
#define RELATION_HPP

#include <vector>
#include <string>
#include <tuple>
#include <unordered_map>
using namespace std;

class Relation {
public:
	friend class Search;
	friend class SequentialSearch;
	friend class BitmapSearch;

	Relation(string filename);
	Relation() {}
	unordered_map<string, vector<unsigned>> build_bitmap(int field);
	void add_edependency(Relation* ed, int column);
	void print_column_names();
	void print_bitmaps();

private:
	vector<string> column_names;
	vector<vector<string>> fields;
	vector<tuple<Relation*, int>> foreign_keys;
	unordered_map<int,
		unordered_map<string, vector<unsigned>>
	> bitmaps;
	int bsz = 4;
};

void strip(string& s);
void print_bitmap_index(const unordered_map<string, vector<unsigned>> &bmi);
void print_bitmaps(const unordered_map< int, unordered_map<string, vector<unsigned>>>& bitmaps);

#endif