#include "sequential_search.hpp"
#include "agregation.hpp"
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

vector<vector<string>>
SequentialSearch::search_value(
	const string &val, vector<int> columns, vector<Agregate*> agrf) {

	cout << "agrf.size() " << agrf.size() << endl;

	if (!search_initialization(val, columns, agrf, this->rel->column_names.size()))
		return vector<vector<string>>();

	vector<vector<string>> result;
	for (int i = 0; i < this->rel->fields.size(); ++i) {
		vector<bool> search_cond; bool row_matched = false;
		for (int j = 0; j < columns.size(); ++j)
			search_cond.push_back(this->rel->fields[i][columns[j]] == this->parsed_search_terms[j]);

		for (int j = 0; j < this->parsed_search_ops.size(); ++j)
			if (this->parsed_search_ops[j] == "and_" && j + 1 < search_cond.size()) {
				search_cond[j + 1] = search_cond[j] && search_cond[j + 1]; search_cond[j] = false; }

		for (int j = 0; j < search_cond.size() && !row_matched; ++j)
			row_matched = row_matched || search_cond[j];


		if (row_matched) {
			result.push_back(this->rel->fields[i]);
			for (int j = 0; j < agrf.size(); agrf[j++]->add_row(this->rel->fields[i]));
		}
	}

	print_search_results(result, agrf);

	for (int i = 0; i < agrf.size(); delete agrf[i++]);
	return result;
}
