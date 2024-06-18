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
	string sse = simplify_search_expr(val); parse_search_ops(sse); parse_search_terms(sse);
	for (int i = 0; i < columns.size(); ++i) if (columns[i] >= this->rel->column_names.size()) {
		cerr << "Error: column index out of range" << endl; return vector<vector<string>>(); }

	for (int i = 0, j = 0; i < this->rel->column_names.size(); ++i) {
		if (j >= agrf.size()) {
			cerr << "Error: agregation function must be specified for every column not indexed" << endl;
			return vector<vector<string>>();
		}
		if (find(columns.begin(), columns.end(), i) == columns.end()) agrf[j++]->set_column(i);
	}

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

	for (int i = 0; i < agrf.size(); ++i) {
		cout << agrf[i]->agr_id() << "(Fact" + to_string(agrf[i]->get_column()) + "): " << agrf[i]->get_result() << endl;
		delete agrf[i];
	}
	return result;
}
