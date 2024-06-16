#include "relation.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <string>
using namespace std;

void strip(string& s) {
	if (s.length() == 0) return;
	string::iterator start_it = s.begin();
	for (; start_it != s.end() && isspace(*start_it); ++start_it);
	string::reverse_iterator end_it = s.rbegin();
	for (; end_it != s.rend() && isspace(*end_it); ++end_it);

	int start_pos = start_it - s.begin(), end_pos = end_it.base() - s.begin();
	s = start_pos <= end_pos ? string(start_it, end_it.base()) : "";
}

Relation::Relation(string filename) {
	ifstream rel_data(filename); string line;
	if (getline(rel_data, line)) {
		stringstream line_stream(line); string cell;
		while (getline(line_stream, cell, ',')) {
			strip(cell); this->column_names.push_back(cell); }

	}

	while (getline(rel_data, line)) {
		stringstream line_stream(line); string cell;
		while (getline(line_stream, cell, ',')) {

		}
	}
}

Relation* Relation::build_bitmap(int field_index) {
	return nullptr;
}
