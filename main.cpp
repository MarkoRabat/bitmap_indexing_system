#include <iostream>
#include "relation.hpp"
using namespace std;

int main() {
	
	Relation r1("FactTable1.csv");
	r1.add_edependency(nullptr, 7);



	return 0;
}