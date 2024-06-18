#include <iostream>
#include <unordered_map>
#include "relation.hpp"
#include "search.hpp"
#include "sequential_search.hpp"
#include "agregation.hpp"
using namespace std;

int main() {
	
	Relation r1("FactTable1.csv");
	r1.add_edependency(nullptr, 1);
	r1.add_edependency(nullptr, 2);
	r1.add_edependency(nullptr, 5);
	r1.print_column_names();

	Search s1(&r1);
	SequentialSearch s2(&r1);
	s2.set_filename("search1_rez.txt");
	vector<vector<string>> rez = s2.search_value(
		"a2 || b2 && abc12",
		{1, 2, 5},
		{new Avg(), new Avg(), new Min(), new NoAgr(), new Max(), new Sum()}
	);
	for (vector<string>& row : rez) {
		for (string& column : row)
			std::cout << column << " "; std::cout << endl;
	}

	unordered_map<string, vector<unsigned>> c0_bmap = r1.build_bitmap(0);
	print_bitmap_index(c0_bmap);
	std::cout << endl;
	r1.print_bitmaps();

	return 0;
}