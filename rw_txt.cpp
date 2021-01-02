#include<iostream>
#include<fstream>
#include<cstdio>
#include<string>
#include<vector>
#include"city_info.h"
#include"rw_txt.h"

using namespace std;

string read_line(city_node* t,string& line,int *flag){
	string name;
	int i=-1,j=0;
	char temp[20];
	while(line[++i]!=' '&&line[i]!='\0') temp[j++]=line[i];
	temp[j]=0;
	name=temp;
	if(line[i]=='\0'){
		*flag=1;
		return name;
	}
	while(line[++i]==' ');
	j=0;--i;
	while(line[++i]!=' ') temp[j++]=line[i];
	temp[j]=0;
	t->dest_city=temp;
	while(line[++i]==' ');
	j=0;--i;
	char vehicle[20];
	while(line[++i]!=' ') vehicle[j++]=line[i];
	vehicle[j]=0;
	t->vehicle=vehicle;
	if(t->vehicle!="train"&&t->vehicle!="aeroplane") {
		cout<<"请参照格式输入。"<<endl;
		return "wrong";
	}
	while(line[++i]==' ');
	--i;
	t->cost=0;
	t->de_time[0]=t->de_time[1]=t->ar_time[0]=t->ar_time[1]=0;
	while(line[++i]!=' ') t->cost=t->cost*10+line[i]-'0';
	while(line[++i]==' ');
	t->de_time[0]=(line[i++]-'0')*10+(line[i++]-'0');
	++i;
	t->de_time[1]=(line[i++]-'0')*10+(line[i++]-'0');
	--i;
	while(line[++i]==' ');
	t->ar_time[0]=(line[i++]-'0')*10+(line[i++]-'0');
	++i;
	t->ar_time[1]=(line[i++]-'0')*10+(line[i++]-'0');
	return name;
}

void read_from_file(vector<info>& c){
	fstream f("data.txt");
	if(!f) cerr<<"Error with reading from data.txt"<<endl;
	string line;
	while(getline(f,line)){
		city_node* t=new city_node();
		int flag=0;
		string name=read_line(t,line,&flag);
		if(name=="wrong") break;
		vector<info>::iterator i=c.begin();
		for(;i!=c.end();i++){
			if(i->name()==name){
				if(flag==1) delete t;
				else i->dest.push_back(t);
				break;
			}
		}
		if(i==c.end()){
			info* p=new info();
			p->n=name;
			if(flag==1) delete t;
			else p->dest.push_back(t);
			c.push_back(*p);
		}
	}
	f.close();
}

void print_time(int a[],fstream& f){
	f<<"   ";
	if(a[0]<10) f<<'0'<<a[0]<<':';
	else f<<a[0]<<':';
	if(a[1]<10) f<<'0'<<a[1];
	else f<<a[1];
}

void rewrite(vector<info>& c){
	fstream f("data.txt",ios::out|ios::trunc);
	if(!f) cerr<<"Error with reading from data.txt"<<endl;
	f.clear();
	for(vector<info>::const_iterator i=c.begin();i!=c.end();i++){
		vector<city_node*> t=i->destination();
		if(t.empty()){
			f<<i->name()<<endl;
			continue;
		}
		for(vector<city_node*>::iterator it=t.begin();it!=t.end();it++){
			f<<i->name()<<"   "<<(*it)->dest_city<<"   "<<(*it)->vehicle<<"   "<<(*it)->cost;
			print_time((*it)->de_time,f);
			print_time((*it)->ar_time,f);
			f<<endl;
		}
	}
	f.close();
}

