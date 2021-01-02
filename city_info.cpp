#include<vector>
#include<string>
#include<iostream>
#include<sstream>
#include"city_info.h"
#include"rw_txt.h"

using namespace std;

int add_city_node(vector<info>& c,string& name){
	for(vector<info>::iterator i=c.begin();i!=c.end();i++){
		if(i->name()==name) return 1;
	}
	info* t=new info();
	t->n=name;
	c.push_back(*t);
	return 0;
}

void add_city(vector<info>& c){
	string name;
	while(1){
		cout<<endl<<"请输入城市名（不超过20个字符）：";
		cin>>name;
		if(name.size()>=20||name.size()==0){
			cout<<"请输入长度合适的城市名，再试试看！"<<endl;
			continue;
		}
		if(add_city_node(c,name)) cout<<"该城市已存在。"<<endl;
		else cout<<"添加成功！"<<endl;
		getchar();
		break;
	}
	rewrite(c);
}
void delete_city(vector<info>& c){
	string name;
	while(1){
		cout<<endl<<"请输入城市名（不超过20个字符）：";
		cin>>name;
		if(name.size()>=20||name.size()==0){
			cout<<"请输入长度合适的城市名，再试试看！"<<endl;
			continue;
		}
		vector<info>::iterator i=c.begin();
		for(;i!=c.end()&&i->name()!=name;i++);
		int flag=0,f=0;
		for(vector<info>::iterator j=c.begin();j!=c.end();j++){
			if(i==j) continue;
			flag=j->delete_node(name);
			if(flag==1) f=1;
		}
		if(f==1&&i==c.end()){
			cout<<"该城市不存在。"<<endl;
			getchar();
			continue;
		}
		c.erase(i);
		rewrite(c);
		getchar();
		cout<<"删除成功！"<<endl;
		return;
	}
}
void add_f_or_t(vector<info>& c){
	cout<<endl<<"城市名在20个字符以内"<<endl;
	string name,dest;
	while(1){
		cout<<"出发地：";
		getline(cin,name);
		if(name.size()>=20||name.size()==0){
			cout<<"请输入长度合适的城市名，再试试看！"<<endl;
			continue;
		}
		break;
	}
	while(1){
		cout<<"目的地：";
		getline(cin,dest);
		if(dest.size()>=20||dest.size()==0){
			cout<<"请输入长度合适的城市名，再试试看！"<<endl;
			continue;
		}
		break;
	}
	string vehicle;
	while(1){
		cout<<"交通方式：";
		getline(cin,vehicle);
		if(vehicle!="train"&&vehicle!="aeroplane"){
			cout<<"可供选择的交通方式只有火车和飞机，输入英文，train or aeroplane。"<<endl;
			continue;
		}
		break;
	}
	float cost=0;
	while(1){
		cout<<"价格：";
		cin>>cost;
		if(cost==0){
			cout<<"请输入合理数字。"<<endl;
			continue;
		}
		break;
	}
	getchar();
	cout<<"按照05:13的格式输入时间,注意冒号使用英文符号。"<<endl;
	string dt,at;
	int d0,d1,a0,a1;
	while(1){
		cout<<"出发时间：";
		getline(cin,dt);
		if(dt.size()==5){
			d0=(dt[0]-'0')*10+(dt[1]-'0');
			d1=(dt[3]-'0')*10+(dt[4]-'0');
			if(d0<24&&d0>=0&&d1<60&&d1>=0) break;
		}
		cout<<"格式不规范，再试试！"<<endl;
	}
	while(1){
		cout<<"到达时间：";
		getline(cin,at);
		if(at.size()==5){
			a0=(at[0]-'0')*10+(at[1]-'0');
			a1=(at[3]-'0')*10+(at[4]-'0');
			if(a0<24&&a0>=0&&a1<60&&a1>=0) break;
		}
		cout<<"格式不规范，再试试！"<<endl;
	}
	city_node *p=new city_node();
	p->dest_city=dest;
	p->cost=cost;
	p->vehicle=vehicle;
	p->de_time[0]=d0;
	p->de_time[1]=d1;
	p->ar_time[0]=a0;
	p->ar_time[1]=a1;
	vector<info>::iterator i=c.begin();
	for(;i!=c.end()&&i->name()!=name;i++);
	if(i!=c.end()) i->add_node(p);
	else{
		info *t=new info();
		t->add_node(p);
		t->n=name;
		c.push_back(*t);
	}
	add_city_node(c,dest);
	rewrite(c);
	cout<<"添加成功！"<<endl;
}
void delete_f_or_t(vector<info>& c){
	cout<<"请输入时间表中的对应序号以删除该班次，以空格间隔"<<endl;
	while(1){
		stringstream ss;
		string line;
		getline(cin,line);
		ss<<line;
		int c0,c1;
		ss>>c0>>c1;
		if(c0>=c.size()||c1>=c[c0].dest.size()){
			cout<<"该序号不存在，再试试！"<<endl;
			continue;
		}
		c[c0].delete_node(c1);
		break;
	}
	rewrite(c);
	cout<<"删除成功！"<<endl;
}

void edit_citys(vector<info>& c){
	cout<<endl<<"您希望做些什么？"<<endl;
	while(1){
		cout<<endl<<"0、增加城市；1、删除城市；2、增加班次；3、删除班次；4、回到上一步"
			<<endl<<"请输入数字以选择相应功能"<<endl;
		string func;
		getline(cin,func);
		char f=func[0];
		if(!isdigit(f)){
			cout<<"需要输入一个数字！再试试看。"<<endl;
			continue;
		}
		switch(f-'0'){
		case 0: add_city(c);break;
		case 1: delete_city(c);break;
		case 2: add_f_or_t(c);break;
		case 3: delete_f_or_t(c);break;
		case 4: return;
		default:
			cout<<"请输入0、1、2、3、4这五个功能的其中一个。"<<endl;
		}
	}
}