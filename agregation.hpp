#ifndef AGREGATION_HPP
#define AGREGATION_HPP

#include <vector>
#include <string>
using namespace std;

class Agregate {
public:
	virtual void add_row(const vector<string>& row) = 0;
	virtual string get_result() = 0;
	virtual string agr_id() = 0;
	void set_column(int column) { this->column = column; }
	int get_column() { return this->column; }
protected:
	int column = 0;
};

class NoAgr : public Agregate {
public:
	void add_row(const vector<string>& row) {}
	string get_result() { return ""; }
	string agr_id() { return "NoAgr"; }
private:
};

class Min : public Agregate {
public:
	void add_row(const vector<string>& row) {
		if (min_not_init) { min = stod(row[column]); min_not_init = false; }
		if (stod(row[column]) < min) min = stod(row[column]);
	}
	string get_result() { if (!min_not_init) return to_string(min); return "NoValue"; }
	string agr_id() { return "Min"; }
private:
	double min;
	bool min_not_init = true;
};

class Max : public Agregate {
public:
	void add_row(const vector<string>& row) {
		if (max_not_init) { max = stod(row[column]); max_not_init = false;  }
		if (max < stod(row[column])) max = stod(row[column]);
	}
	string get_result() { if (!max_not_init) return to_string(max); return "NoValue"; }
	string agr_id() { return "Max"; }
private:
	double max;
	bool max_not_init = true;
};

class Sum : public Agregate {
public:
	void add_row(const vector<string>& row) {
		sum += stod(row[column]);
	}
	string get_result() { return to_string(sum); }
	string agr_id() { return "Sum"; }
private:
	double sum = 0;
};

class Count : public Agregate {
public:
	void add_row(const vector<string>& row) { ++cnt; }
	string get_result() { return to_string(cnt); }
	string agr_id() { return "Count"; }
private:
	int cnt = 0;
};

class Avg : public Agregate {
public:
	void add_row(const vector<string>& row) {
		sum += stod(row[column]); ++cnt;
	}
	string get_result() { return to_string(sum / max(cnt, 1)); }
	string agr_id() { return "Avg"; }
private:
	double sum = 0;
	int cnt = 0;
};


#endif