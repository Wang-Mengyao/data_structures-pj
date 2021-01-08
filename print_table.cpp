#include<vector>
#include<string>
#include<iostream>
#include<iomanip>
#include"city_info.h"

using namespace std;

void print_time(int a[]){
	cout<<setw(10);
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
			cout<<counter0<<' '<<0<<' '<<setw(20)<<i->name()<<setw(40)<<" 暂无航班或火车车次从这里出发"<<endl;
			continue;
		}
		int counter1=0;
		for(vector<city_node*>::iterator it=t.begin();it!=t.end();it++){
			cout<<counter0<<' '<<counter1++<<' '<<setw(20)<<i->name()<<setw(20)<<(*it)->dest_city
				<<setw(20)<<(*it)->vehicle<<setw(15)<<(*it)->cost;
			print_time((*it)->de_time);
			print_time((*it)->ar_time);
			cout<<endl;
		}
	}
}
