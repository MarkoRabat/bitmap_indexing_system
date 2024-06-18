#include "sequential_search.hpp"
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
using namespace std;


vector<vector<string>>
SequentialSearch::search_value(const string &val, int column) {

	string sse = simplify_search_expr(val);


	parse_search_ops(sse);
	for (string& st : parsed_search_ops) {
		cout << st << " _ ";
	} cout << endl;

	parse_search_terms(sse);
	for (string &st : parsed_search_terms) {
		cout << st << " _ ";
	} cout << endl;

	if (column >= this->rel->column_names.size()) {
		cerr << "Error: column index out of range" << endl; return vector<vector<string>>(); }
	cout << this->rel->column_names[column] << endl;
	vector<vector<string>> result;
	for (int i = 0; i < this->rel->fields.size(); ++i)
		if (sse == this->rel->fields[i][column])
			result.push_back(this->rel->fields[i]);
	return result;
}
