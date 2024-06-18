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
	s1.search_value("hello", 3);
	SequentialSearch s2(&r1);
	s2.search_value("hello && hello2 && hello3 || hello4 or hello5 and hello6 and hello7", 3);

	return 0;
}