#ifndef SEARCH_HPP
#define SEARCH_HPP

class Relation;
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <regex>
using namespace std;
void strip(string&);

class Search {
public:
	Search(Relation* rrel) { this->rel = rrel; }
	virtual vector<vector<string>> search_value(const string &val, int column) {
		cout << "search value: " << val << " in column: " << column << endl;
		return vector<vector<string>>();
	}
protected:
	string simplify_search_expr(const string &search_expr) {
		string simplifyed_search_expr = regex_replace(search_expr, regex("\\|\\|"), "|");
		simplifyed_search_expr = regex_replace(simplifyed_search_expr, regex("or"), "|");
		simplifyed_search_expr = regex_replace(search_expr, regex("&&"), "&");
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
	Relation* rel;
	vector<string> parsed_search_terms;
	vector<string> parsed_search_ops;
};

#endif