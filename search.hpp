#ifndef SEARCH_HPP
#define SEARCH_HPP

class Relation;
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Search {
public:
	Search(Relation* rrel) { this->rel = rrel; }
	virtual vector<string> search_value(string val, int column) {
		cout << "search value: " << val << " in column: " << column << endl;
	}
private:
	Relation* rel;
};

#endif