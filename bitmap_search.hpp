#ifndef BITMAP_SEARCH_HPP
#define BITMAP_SEARCH_HPP

#include "search.hpp"
#include "relation.hpp"
#include "agregation.hpp"
#include <vector>
#include <string>
using namespace std;

class BitmapSearch : public Search {
public:
	BitmapSearch(Relation* rrel) : Search(rrel) {}
	vector<vector<string>> search_value(
		const string &val, vector<int> columns, vector<Agregate*> agrf);
};

#endif