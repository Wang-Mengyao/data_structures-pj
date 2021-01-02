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
	cout<<endl<<"Time Table"<<endl;
	int counter0=0;
	for(vector<info>::const_iterator i=c.begin();i!=c.end();i++,counter0++){
		vector<city_node*> t=i->destination();
		if(t.empty()){
			cout<<counter0<<' '<<0<<' '<<i->name()<<" 暂无航班或火车车次从这里出发"<<endl;
			continue;
		}
		int counter1=0;
		for(vector<city_node*>::iterator it=t.begin();it!=t.end();it++){
			cout<<counter0<<' '<<counter1++<<' '<<i->name()<<'\t'<<(*it)->dest_city<<'\t'<<(*it)->vehicle<<'\t'<<(*it)->cost;
			print_time((*it)->de_time);
			print_time((*it)->ar_time);
			cout<<endl;
		}
	}
}
