#include "relation.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
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
		vector<string> row;
		stringstream line_stream(line); string cell;
		while (getline(line_stream, cell, ',')) {
			strip(cell); row.push_back(cell); }
		this->fields.push_back(row);
	}
}

void Relation::add_edependency(Relation* ed, int column) {
	foreign_keys.push_back(make_tuple(ed, column));
	bitmaps[column] = build_bitmap(column);
}

void Relation::print_column_names() {
	for (int i = 0; i < this->column_names.size() - 1; ++i)
		cout << this->column_names[i] << " ";
	cout << this->column_names[this->column_names.size() - 1] << endl;
}

unordered_map<string, vector<unsigned>> Relation::build_bitmap(int column) {

	unordered_map<string, vector<unsigned>> bitmap;
	for (int i = 0; i < this->fields.size(); ++i) {
		int barr_size = (i != 0 && i % bsz == 0) ? 1 : 0;
		if (bitmap.begin() != bitmap.end())
			barr_size += bitmap[bitmap.begin()->first].size() - 1;
		for (auto it = bitmap.begin(); it != bitmap.end(); ++it) {
			if (i % bsz == 0) bitmap[it->first].push_back(0u);
			bitmap[it->first][barr_size] <<= 1u;
		}

		if (bitmap.find(this->fields[i][column]) == bitmap.end()) {
			bitmap[this->fields[i][column]] = vector<unsigned>();
			for (int k = 0; k < 1 + i / bsz; ++k)
				bitmap[this->fields[i][column]].push_back(0u);
		}
		bitmap[this->fields[i][column]][barr_size]++;
	}
	return bitmap;

}

void Relation::print_bitmaps() {
	for (auto it = bitmaps.begin(); it != bitmaps.end(); ++it) {
		cout << "bitmap for column " << it->first << ":" << endl;
		print_bitmap_index(it->second);
	}
}

void print_bitmap_index(const unordered_map<string, vector<unsigned>>& bmi) {
	for (auto it = bmi.begin(); it != bmi.end(); ++it) {
		cout << it->first << ": #";
		cout.setf(ios::hex, ios::basefield);
		for (auto s : it->second) cout << s << " ";
		cout.unsetf(ios::hex);
		cout << endl;
	}
}

void print_bitmaps(const unordered_map<
	int, unordered_map<string, vector<unsigned>>> &bitmaps) {
	for (auto it = bitmaps.begin(); it != bitmaps.end(); ++it) {
		cout << "bitmap for column " << it->first << ":" << endl;
		print_bitmap_index(it->second);
	}
}
