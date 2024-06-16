#ifndef RELATION_HPP
#define RELATION_HPP

#include <vector>
#include <string>
using namespace std;

class Relation {
public:

	Relation(string filename);
	Relation* build_bitmap(int field_index);


private:
	vector<string> column_names;
	vector<vector<string>> fields;

};

void strip(string& s);

#endif