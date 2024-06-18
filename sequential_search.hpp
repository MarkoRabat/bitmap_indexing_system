#ifndef SEQUENTIAL_SEARCH_HPP
#define SEQUENTIAL_SEARCH_HPP

#include "search.hpp"
#include "relation.hpp"
#include <vector>
#include <string>
using namespace std;

class SequentialSearch : public Search {
public:
	SequentialSearch(Relation* rrel) : Search(rrel) {}
	vector<vector<string>> search_value(const string &val, vector<int> columns);
};

#endif