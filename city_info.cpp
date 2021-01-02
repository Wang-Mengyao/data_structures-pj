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
		cout<<endl<<"�������������������20���ַ�����";
		cin>>name;
		if(name.size()>=20||name.size()==0){
			cout<<"�����볤�Ⱥ��ʵĳ������������Կ���"<<endl;
			continue;
		}
		if(add_city_node(c,name)) cout<<"�ó����Ѵ��ڡ�"<<endl;
		else cout<<"��ӳɹ���"<<endl;
		getchar();
		break;
	}
	rewrite(c);
}
void delete_city(vector<info>& c){
	string name;
	while(1){
		cout<<endl<<"�������������������20���ַ�����";
		cin>>name;
		if(name.size()>=20||name.size()==0){
			cout<<"�����볤�Ⱥ��ʵĳ������������Կ���"<<endl;
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
			cout<<"�ó��в����ڡ�"<<endl;
			getchar();
			continue;
		}
		c.erase(i);
		rewrite(c);
		getchar();
		cout<<"ɾ���ɹ���"<<endl;
		return;
	}
}
void add_f_or_t(vector<info>& c){
	cout<<endl<<"��������20���ַ�����"<<endl;
	string name,dest;
	while(1){
		cout<<"�����أ�";
		getline(cin,name);
		if(name.size()>=20||name.size()==0){
			cout<<"�����볤�Ⱥ��ʵĳ������������Կ���"<<endl;
			continue;
		}
		break;
	}
	while(1){
		cout<<"Ŀ�ĵأ�";
		getline(cin,dest);
		if(dest.size()>=20||dest.size()==0){
			cout<<"�����볤�Ⱥ��ʵĳ������������Կ���"<<endl;
			continue;
		}
		break;
	}
	string vehicle;
	while(1){
		cout<<"��ͨ��ʽ��";
		getline(cin,vehicle);
		if(vehicle!="train"&&vehicle!="aeroplane"){
			cout<<"�ɹ�ѡ��Ľ�ͨ��ʽֻ�л𳵺ͷɻ�������Ӣ�ģ�train or aeroplane��"<<endl;
			continue;
		}
		break;
	}
	float cost=0;
	while(1){
		cout<<"�۸�";
		cin>>cost;
		if(cost==0){
			cout<<"������������֡�"<<endl;
			continue;
		}
		break;
	}
	getchar();
	cout<<"����05:13�ĸ�ʽ����ʱ��,ע��ð��ʹ��Ӣ�ķ��š�"<<endl;
	string dt,at;
	int d0,d1,a0,a1;
	while(1){
		cout<<"����ʱ�䣺";
		getline(cin,dt);
		if(dt.size()==5){
			d0=(dt[0]-'0')*10+(dt[1]-'0');
			d1=(dt[3]-'0')*10+(dt[4]-'0');
			if(d0<24&&d0>=0&&d1<60&&d1>=0) break;
		}
		cout<<"��ʽ���淶�������ԣ�"<<endl;
	}
	while(1){
		cout<<"����ʱ�䣺";
		getline(cin,at);
		if(at.size()==5){
			a0=(at[0]-'0')*10+(at[1]-'0');
			a1=(at[3]-'0')*10+(at[4]-'0');
			if(a0<24&&a0>=0&&a1<60&&a1>=0) break;
		}
		cout<<"��ʽ���淶�������ԣ�"<<endl;
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
	cout<<"��ӳɹ���"<<endl;
}
void delete_f_or_t(vector<info>& c){
	cout<<"������ʱ����еĶ�Ӧ�����ɾ���ð�Σ��Կո���"<<endl;
	while(1){
		stringstream ss;
		string line;
		getline(cin,line);
		ss<<line;
		int c0,c1;
		ss>>c0>>c1;
		if(c0>=c.size()||c1>=c[c0].dest.size()){
			cout<<"����Ų����ڣ������ԣ�"<<endl;
			continue;
		}
		c[c0].delete_node(c1);
		break;
	}
	rewrite(c);
	cout<<"ɾ���ɹ���"<<endl;
}

void edit_citys(vector<info>& c){
	cout<<endl<<"��ϣ����Щʲô��"<<endl;
	while(1){
		cout<<endl<<"0�����ӳ��У�1��ɾ�����У�2�����Ӱ�Σ�3��ɾ����Σ�4���ص���һ��"
			<<endl<<"������������ѡ����Ӧ����"<<endl;
		string func;
		getline(cin,func);
		char f=func[0];
		if(!isdigit(f)){
			cout<<"��Ҫ����һ�����֣������Կ���"<<endl;
			continue;
		}
		switch(f-'0'){
		case 0: add_city(c);break;
		case 1: delete_city(c);break;
		case 2: add_f_or_t(c);break;
		case 3: delete_f_or_t(c);break;
		case 4: return;
		default:
			cout<<"������0��1��2��3��4��������ܵ�����һ����"<<endl;
		}
	}
}