#ifndef GUARD_rw_txt_h
#define GUARD_rw_txt_h

#include<string>
#include<vector>
using namespace std;

string read_line(city_node* t,string& line);
void read_from_file(vector<info>& c);
void rewrite(vector<info>& c);
void print_time(int a[],fstream& f);

#endif