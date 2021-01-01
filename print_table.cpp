#include<vector>
#include<string>
#include<iostream>
#include"city_info.h"

using namespace std;

void print_time(int a[]){
	cout<<'\t';
	if(a[0]<10) cout<<'0'<<a[0]<<':';
	else cout<<a[0]<<':';
	if(a[1]<10) cout<<'0'<<a[1];
	else cout<<a[1];
}

void print_time_table(const vector<info>& c){
	for(vector<info>::const_iterator i=c.begin();i!=c.end();i++){
		vector<city_node*> t=i->destination();
		for(vector<city_node*>::iterator it=t.begin();it!=t.end();it++){
			cout<<i->name()<<'\t'<<(*it)->dest_city<<'\t'<<(*it)->vehicle<<'\t'<<(*it)->cost;
			print_time((*it)->de_time);
			print_time((*it)->ar_time);
			cout<<endl;
		}
	}
}
