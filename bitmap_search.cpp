#include "bitmap_search.hpp"
#include "agregation.hpp"
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

vector<vector<string>>
BitmapSearch::search_value(
	const string &val, vector<int> columns, vector<Agregate*> agrf) {

	if (!search_initialization(val, columns, agrf, this->rel->column_names.size()))
		return vector<vector<string>>();

	unordered_map<int, unordered_map<string, vector<unsigned>>> bitmaps = this->rel->bitmaps;

	vector<vector<string>> result;
	vector<vector<unsigned>> search_cond;

	for (int i = 0; i < parsed_search_terms.size(); ++i) {
		if (bitmaps[columns[i]].find(parsed_search_terms[i]) == bitmaps[columns[i]].end()) {
			vector<unsigned> search_term_not_found;
			int k = bitmaps[columns[i]].begin()->second.size();
			cout << "here1" << endl;
			for (int j = 0; j < k; ++j) search_term_not_found.push_back(0u);
			search_cond.push_back(search_term_not_found);
		}
		else search_cond.push_back(bitmaps[columns[i]][parsed_search_terms[i]]);
	}


	cout << "initial selection:" << endl;
	for (int i = 0; i < search_cond.size(); ++i) {
		cout << i << ": ";
		for (int j = 0; j < search_cond[i].size(); ++j) {
			cout << search_cond[i][j] << " ";
		}
		cout << endl;
	}

	for (int i = 0; i < parsed_search_ops.size(); ++i)
		if (parsed_search_ops[i] == "and_" && i + 1 < search_cond.size())
			for (int j = 0; j < search_cond[i].size(); ++j) {
				search_cond[i + 1][j] &= search_cond[i][j];
				search_cond[i][j] = 0;
			}

	cout << "selection state after and:" << endl;
	for (int i = 0; i < search_cond.size(); ++i) {
		cout << i << ": ";
		for (int j = 0; j < search_cond[i].size(); ++j) {
			cout << search_cond[i][j] << " ";
		}
		cout << endl;
	}

	vector<unsigned> rows_matched;
	for (int i = 0; i < search_cond[0].size(); ++i)
		rows_matched.push_back(0u);

	for (int i = 0; i < search_cond.size(); ++i) {
		cout << search_cond[i].size() << endl;
		for (int j = 0; j < search_cond[i].size(); ++j) {
			rows_matched[j] |= search_cond[i][j];
			cout << rows_matched[j] << endl;
		}
	}

	cout << "final selection (after or):" << endl;
	for (int i = 0; i < rows_matched.size(); ++i) {
		cout << rows_matched[i] << " ";
	}
	cout << endl;

	//int bsz = 4;
	int fieldsModBsz = this->rel->fields.size() % this->rel->bsz;
	vector<unsigned> selected_rows;
	for (int i = 0; i < rows_matched.size(); ++i) {
		unsigned index_base = this->rel->bsz * i;
		if (i + 1 == rows_matched.size()) {
			if (fieldsModBsz == 0) fieldsModBsz = this->rel->bsz;
			for (unsigned j = 0; j < fieldsModBsz; ++j) {
				if ((rows_matched[i] & (1 << j)) > 0)
					selected_rows.push_back(index_base + (fieldsModBsz - 1 - j));
			}
		}
		else {
			for (unsigned j = 0; j < this->rel->bsz; ++j) {
				if ((rows_matched[i] & (1 << j)) > 0)
					selected_rows.push_back(index_base + (this->rel->bsz - 1 - j));
			}
		}
	}

	cout << "selected rows indeces:" << endl;
	for (int i = 0; i < selected_rows.size(); ++i) {
		cout << selected_rows[i] << " ";
	}
	cout << endl;









	print_search_results(result, agrf);

	for (int i = 0; i < agrf.size(); delete agrf[i++]);
	return result;
}
