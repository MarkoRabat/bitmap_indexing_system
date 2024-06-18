#ifndef AGREGATION_HPP
#define AGREGATION_HPP

#include <vector>
#include <string>
using namespace std;

class Agregate {
public:
	virtual void add_row(const vector<string>& row) = 0;
	virtual string get_result() = 0;
	void set_column(int column) { this->column = column; }
protected:
	int column = 0;
};

class NoAgr : public Agregate {
public:
	void add_row(const vector<string>& row) {}
	string get_result() { return ""; }
private:
};

class Min : public Agregate {
public:
	void add_row(const vector<string>& row) {
		if (min == "NO_VALUE") min = row[column];
		if (row[column] < min) min = row[column];
	}
	string get_result() { return min; }
private:
	string min = "NO_VALUE";
};

class Max : public Agregate {
public:
	void add_row(const vector<string>& row) {
		if (max == "NO_VALUE") max = row[column];
		if (max < row[column]) max = row[column];
	}
	string get_result() { return max; }
private:
	string max = "NO_VALUE";
};

class Sum : public Agregate {
public:
	void add_row(const vector<string>& row) {
		sum += stod(row[column]);
	}
	string get_result() { return to_string(sum); }
private:
	double sum = 0;
};

class Count : public Agregate {
public:
	void add_row(const vector<string>& row) { ++cnt; }
	string get_result() { return to_string(cnt); }
private:
	int cnt = 0;
};

class Avg : public Agregate {
public:
	void add_row(const vector<string>& row) {
		sum += stod(row[column]); ++cnt;
	}
	string get_result() { return to_string(sum / max(cnt, 1)); }
private:
	double sum = 0;
	int cnt = 0;
};



#endif