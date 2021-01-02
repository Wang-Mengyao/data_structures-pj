#ifndef GUARD_city_info_h
#define GUARD_city_info_h

#include<string>
#include<vector>
using namespace std;

struct city_node{
	string dest_city;
	string vehicle;
	float cost;
	int de_time[2],ar_time[2];
};

class info{
friend void read_from_file(vector<info>& c);
friend int add_city_node(vector<info>& c,string& name);
friend void delete_city(vector<info>& c);
friend void add_f_or_t(vector<info>& c);
friend void delete_f_or_t(vector<info>& c);
public:
	string name()const{ return n;}
	const vector<city_node*>& destination()const{ return dest;}
	void add_node(city_node* t){ dest.push_back(t); }
	void delete_node(int n){
		vector<city_node*>::iterator it=dest.begin();
		for(int i=0;i<n&&it!=dest.end();it++,i++);
		if(it!=dest.end()) dest.erase(it);
	}
	int delete_node(string& d){
		int flag=0;
		for(vector<city_node*>::iterator it=dest.begin();it!=dest.end();){
			if((*it)->dest_city==d){
				it=dest.erase(it);
				flag=1;
			}else it++;
		}
		return flag;
	}
private:
	string n;
	vector<city_node*> dest;
};
void print_time_table(const vector<info>& c);
void print_time(int a[]);
void edit_citys(vector<info>& c);
void add_city(vector<info>& c);
void delete_city(vector<info>& c);
void add_f_or_t(vector<info>& c);
void delete_f_or_t(vector<info>& c);
int add_city_node(vector<info>& c,string& name);

#endif