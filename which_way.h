#ifndef GUARD_which_way_h
#define GUARD_which_way_h

#include<string>
#include<vector>
#include"city_info.h"
using namespace std;

struct print_node{
	int city;
	int kth;
};

void which_way(vector<info>& c);
void fast_way(vector<info>& c);
void short_way(vector<info>& c);
void cheap_way(vector<info>& c);
int find_city(vector<info>& c,string& n);
int calculate_time(int a[],int b[]);

#endif