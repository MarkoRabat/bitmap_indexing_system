#ifndef SEARCH_HPP
#define SEARCH_HPP

class Relation;
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <regex>
#include <fstream>
#include "agregation.hpp"
using namespace std;
void strip(string&);

class Search {
public:
	Search(Relation* rrel) { this->rel = rrel; }
	virtual vector<vector<string>> search_value(
		const string &val, vector<int> columns, vector<Agregate*> agrf) {
		return vector<vector<string>>();
	}
	void set_filename(string f) { this->filename = f; this->print_to_file = true; }
protected:
	string simplify_search_expr(const string &search_expr) {
		string simplifyed_search_expr = regex_replace(search_expr, regex("\\|\\|"), "|");
		simplifyed_search_expr = regex_replace(simplifyed_search_expr, regex("or"), "|");
		simplifyed_search_expr = regex_replace(simplifyed_search_expr, regex("&&"), "&");
		simplifyed_search_expr = regex_replace(simplifyed_search_expr, regex("and"), "&");
		return simplifyed_search_expr;
	}
	void parse_search_terms(const string &search_expr) {
		stringstream ss(search_expr);
		char delimiter = '&'; string word;
		while (!ss.eof()) {
			getline(ss, word, delimiter);
			stringstream sub_ss(word);
			char delimiter = '|';
			string sub_word;
			while (!sub_ss.eof()) {
				getline(sub_ss, sub_word, delimiter);
				strip(sub_word);
				this->parsed_search_terms.push_back(sub_word);
			}
		}
	}
	void parse_search_ops(const string &search_expr) {
		for (int i = 0; i < search_expr.size(); ++i) {
			if (search_expr[i] == '|') parsed_search_ops.push_back("or_");
			if (search_expr[i] == '&') parsed_search_ops.push_back("and_");
		}
	}
	void print_search_results(const vector<vector<string>>& result, const vector<Agregate*>& agrf) {
		if (!this->print_to_file) {
			cout << "Agregation results: " << endl;
			cout << "=================================" << endl;
			for (int i = 0; i < agrf.size(); ++i)
				cout << agrf[i]->agr_id() << "(Fact" + to_string(agrf[i]->get_column())
				+ (agrf[i]->agr_id() == "NoAgr" ?  "): " : ") ") << agrf[i]->get_result() << endl;
			cout << "=================================" << endl;
			for (const vector<string>& row : result) {
				for (const string& column : row) cout << column << " "; cout << endl; }
		}
		else {
			ofstream rfile(this->filename);
			rfile << "Agregation results: " << endl;
			rfile << "=================================" << endl;
			for (int i = 0; i < agrf.size(); ++i)
				rfile << agrf[i]->agr_id() << "(Fact" + to_string(agrf[i]->get_column())
				+ (agrf[i]->agr_id() == "NoAgr" ?  ") " : "): ") << agrf[i]->get_result() << endl;
			rfile << "=================================" << endl;
			for (const vector<string>& row : result) {
				for (const string& column : row) rfile << column << " "; rfile << endl; }
		}
	}
	bool search_initialization(const string &val, const vector<int>& columns, const vector<Agregate*>& agrf, int cnames_size) {

		string sse = simplify_search_expr(val); parse_search_ops(sse); parse_search_terms(sse);
		for (int i = 0; i < columns.size(); ++i) if (columns[i] >= cnames_size) {
			cerr << "Error: column index out of range" << endl; return false; }

		for (int i = 0, j = 0; i < cnames_size; ++i) {
			if (find(columns.begin(), columns.end(), i) == columns.end()) {
				if (j >= agrf.size()) {
					cerr << "Error: agregation function must be specified for every column not indexed" << endl;
					return false;
				}
				agrf[j++]->set_column(i);
			}
		}
		return true;
	}

	Relation* rel;
	vector<string> parsed_search_terms;
	vector<string> parsed_search_ops;
	string filename;
	bool print_to_file = false;
};

#endif