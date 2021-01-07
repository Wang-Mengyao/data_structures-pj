#define MAX 9999
#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include"which_way.h"

using namespace std;

int find_city(vector<info>& c,string& n){
	int i=0;
	for(;i!=c.size()&&c[i].name()!=n;i++);
	if(i==c.size()) return -1;
	else return i;
}

inline int culculate_time(int a[],int b[]){
	int t=(b[0]-a[0])*60+(b[1]-a[1]);
	return t>0?t:MAX;
}

float all_cost(int d,vector<info>& c,int pre,int cur,int ar_time[],int* k,int** kt,string& vehi){
	const vector<city_node*>& t=c[pre].destination();
	vector<city_node*>::const_iterator i=t.begin();
	float min_cost=MAX;
	int min_time=MAX;
	int counter=0;
	*k=-1;
	for(;i!=t.end();i++,counter++){
		if((*i)->dest_city==c[cur].name()&&(*i)->vehicle==vehi){
			if(d==0) return 1;//short way
			if(d==1&&(*i)->cost<min_cost){
				min_cost=(*i)->cost;
				*k=counter;
			}//cheap way
			if(d==2){
				int temp;
				if(ar_time==0) temp=culculate_time((*i)->de_time,(*i)->ar_time);
				else temp=culculate_time(ar_time,(*i)->ar_time);
				if(temp<min_time){
					*kt=(*i)->ar_time;
					min_time=temp;
					*k=counter;
				}
			}//fast way
		}
	}
	if(d==0) return MAX;
	if(d==1){
		if(*k==-1) return MAX;
		else return min_cost;
	}
	if(d==2){
		if(*k==-1) return MAX;
		else return min_time;
	}
}

void short_path_dijkstra(vector<info>& c,int v,int mode,string& vehi,int kth[50],int pre[50]){
	int n=c.size();
	int k;
	int* kt[50];//����ó��е�ʱ��
	float min;
	float dist[50],s[50];
	for(int i=0;i<n;i++){
		if(i==v) continue;
		dist[i]=all_cost(mode,c,v,i,0,kth+i,kt+i,vehi);
		s[i]=0;
		if(dist[i]<MAX) pre[i]=v;
		else pre[i]=-1;
	}
	s[v]=1;pre[v]=-1;
	for(int i=0;i<n;i++){
		min=MAX;
		k=-1;
		for(int j=0;j<n;j++){
			if(j==v) continue;
			if(s[j]==0&&dist[j]<min){
				min=dist[j];
				k=j;
			}
		}
		if(k==-1) break;
		s[k]=1;
		for(int j=0;j<n;j++){
			if(s[j]==1) continue;
			int j_kth;
			int* j_kt;
			j_kth=kth[j];
			j_kt=kt[j];
			int cost=all_cost(mode,c,k,j,kt[k],kth+j,kt+j,vehi);
			if(cost<MAX){
				if(dist[k]+cost<dist[j]){
					dist[j]=dist[k]+cost;
					pre[j]=k;
				}else{
					kth[j]=j_kth;
					kt[j]=j_kt;
				}
			}
		}
	}
}

void show_way(vector<info>& c,int d,int a,int kth[50],int pre[50]){
	stack<print_node> s;
	int i=a;
	print_node* t;
	int counter=-1;
	float cost=0;
	int de[2],ar[2];
	for(;i!=d;){
		if(pre[i]==-1) break;
		t=new print_node();
		t->city=pre[i];
		t->kth=kth[i];
		s.push(*t);
		++counter;
	}
	int flag=0;
	if(i!=d) cout<<"��ʱ�ް�οɵִ"<<endl;
	else{
		while(!s.empty()){
			*t=s.top();s.pop();
			const vector<city_node*>& ct=c[t->city].destination();
			city_node* ci=ct[t->kth];
			if(flag=0){
				de[0]=ci->de_time[0];
				de[1]=ci->de_time[1];
				flag=1;
			}
			ar[0]=ci->ar_time[0];
			ar[1]=ci->ar_time[1];
			cost+=ci->cost;
			cout<<c[t->city].name()<<'\t'<<ci->dest_city<<'\t'<<ci->vehicle<<'\t'<<ci->cost;
			print_time(ci->de_time);
			print_time(ci->ar_time);
			cout<<endl;
		}
		cout<<"�ܼ���ʱ��"<<culculate_time(de,ar)<<"   ���ѣ�"<<cost<<"   ��תվ����"<<counter<<endl;
	}
}

void fast_way(vector<info>& c,int d,int a,string& v){
	int kth[50],pre[50];//the kth road between two places and the precity
	short_path_dijkstra(c,d,2,v,kth,pre);
	show_way(c,d,a,kth,pre);
}

void short_way(vector<info>& c,int d,int a,string& v){
	int kth[50],pre[50];//the kth road between two places and the precity
	short_path_dijkstra(c,d,0,v,kth,pre);
	show_way(c,d,a,kth,pre);
}

void cheap_way(vector<info>& c,int d,int a,string& v){
	int kth[50],pre[50];//the kth road between two places and the precity
	short_path_dijkstra(c,d,1,v,kth,pre);
	show_way(c,d,a,kth,pre);
}

void which_way(vector<info>& c){
	string name,dest,vehi;
	int de,ar;
	while(1){
		cout<<"�����أ�";
		cin>>name;
		if(de=find_city(c,name)==-1){
			cout<<"��ʱû�л𳵻�ɻ�����������������������ԣ�"<<endl;
			continue;
		}
		break;
	}
	while(1){
		cout<<"Ŀ�ĵأ�";
		cin>>dest;
		if(ar=find_city(c,dest)==-1){
			cout<<"��ʱû�л𳵻�ɻ�������������������ԣ�"<<endl;
			continue;
		}
		break;
	}
	while(1){
		cout<<"ѡ��ͨ���ߣ�";
		getline(cin,vehi);
		if(vehi!="train"&&vehi!="aeroplane"){
			cout<<"�ɹ�ѡ��Ľ�ͨ��ʽֻ�л𳵺ͷɻ�������Ӣ�ģ�train or aeroplane��"<<endl;
			continue;
		}
		break;
	}
	while(1){
		cout<<endl<<"0����죻 1��������ת�� 2������ˣ� 3���ص���һ��"<<endl
			<<"������������ѡ����Ӧ����"<<endl;
		string func;
		getline(cin,func);
		char f=func[0];
		if(!isdigit(f)){
			cout<<"��Ҫ����һ�����֣������Կ���"<<endl;
			continue;
		}
		switch(f-'0'){
		case 0: fast_way(c,de,ar,vehi); break;
		case 1: short_way(c,de,ar,vehi); break;
		case 2: cheap_way(c,de,ar,vehi); break;
		case 3: break;
		default:
			cout<<"������0��1��2��3���ĸ����ܵ�����һ����"<<endl;
		}
	}
}
