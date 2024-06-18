#include <iostream>
#include "relation.hpp"
#include "search.hpp"
#include "sequential_search.hpp"
using namespace std;

int main() {
	
	Relation r1("FactTable1.csv");
	r1.add_edependency(nullptr, 7);
	r1.print_column_names();

	Search s1(&r1);
	SequentialSearch s2(&r1);
	vector<vector<string>> rez = s2.search_value(
		"a2 || b2 && abc12 || abc21",
		{1, 2, 5, 6}
	);
	for (vector<string>& row : rez) {
		for (string& column : row)
			cout << column << " "; cout << endl;
	}

	return 0;
}