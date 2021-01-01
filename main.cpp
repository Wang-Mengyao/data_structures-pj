#include<iostream>
#include<fstream>
#include<cstdio>
#include<string>
#include<vector>
#include"city_info.h"

using namespace std;

string read_line(city_node* t,string& line){
	string name;
	int i=-1,j=0;
	char temp[20];
	while(line[++i]!=' ') temp[j++]=line[i];
	temp[j]=0;
	name=temp;
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
		cout<<"����ո�ʽ���롣"<<endl;
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
		string name=read_line(t,line);
		if(name=="wrong") break;
		vector<info>::iterator i=c.begin();
		for(;i!=c.end();i++){
			if(i->name()==name){
				i->dest.push_back(t);
				break;
			}
		}
		if(i==c.end()){
			info* p=new info();
			p->n=name;
			p->dest.push_back(t);
			c.push_back(*p);
		}
	}
	f.close();
}

int main(){
	string board (18,'*');
	cout<<board<<endl<<"*��ӭ���뽻ͨ��ѯ*"<<endl<<board<<endl
		<<"0���˳��� 1���༭������Ϣ�� 2����ӡʱ�̱� 3��·����ѯ"<<endl;
	vector<info> citys;
	read_from_file(citys);
	while(1){
		cout<<endl<<"������������ѡ����Ӧ����"<<endl;
		string func;
		getline(cin,func);
		char f=func[0];
		if(!isdigit(f)){
			cout<<"��Ҫ����һ�����֣������Կ���"<<endl;
			continue;
		}
		switch(f-'0'){
		case 0: cout<<"��лʹ�ã�"<<endl; return 0;
		case 1: //edit_citys(citys); break;
		case 2: print_time_table(citys); break;
		case 3: //which_way(citys); break;
		default:
			cout<<"������0��1��2��3���ĸ����ܵ�����һ����"<<endl;
		}
	}
	return 0;
}