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
	return t>0?t:999;
}

float all_cost(int d,vector<info>& c,int pre,int cur,int ar_time[],int** k){
	const vector<city_node*>& t=c[pre].destination();
	vector<city_node*>::const_iterator i=t.begin();
	for(;i!=t.end()&&(*i)->dest_city!=c[cur].name();i++);
	if(i==t.end()) return 999;
	*k=(*i)->ar_time;
	switch (d){
	case 0: return 1;//short
	case 1: return (*i)->cost;//cheap
	case 2:{//fast
		if(ar_time==0) return culculate_time((*i)->de_time,(*i)->ar_time);
		else return culculate_time(ar_time,(*i)->ar_time);
	}
	default: return 999;
	}
}
//kth仍记录第k条路，不然后面拿不出详细的线路
//cost逻辑要改一下，可能有多重边的现象，其余问题大概不大？
void short_path_dijkstra(vector<info>& c,int v,int mode){
	int n=c.size();
	int k;
	int* kth[50];//the kth road between two places
	float min;
	float dist[50],s[50],pre[50];
	for(int i=1;i<=n;i++){
		dist[i]=all_cost(mode,c,v,i,0,kth+i);
		s[i]=0;
		if(dist[i]<999) pre[i]=v;
		else pre[i]=0;
	}
	s[v]=1;pre[v]=0;
	for(int i=1;i<=n;i++){
		min=999;
		k=0;
		for(int j=1;j<=n;j++){
			if(s[j]==0&&dist[j]!=0<min){
				min=dist[j];
				k=j;
			}
		}
		if(k==0) break;
		s[k]=1;
		for(int j=1;j<=n;j++){
			int cost=all_cost(mode,c,k,j,kth[j],kth+j);
			if(s[j]==0&&cost<999){
				if(dist[k]+cost<dist[j]){
					dist[j]=dist[k]+cost;
					pre[j]=k;
				}
			}
		}
	}
}

void fast_way(vector<info>& c,int d,int a,string& v){

}

void short_way(vector<info>& c,int d,int a,string& v){
	
}

void cheap_way(vector<info>& c,int d,int a,string& v){

}

void which_way(vector<info>& c){
	string name,dest,vehi;
	int de,ar;
	while(1){
		cout<<"出发地：";
		cin>>name;
		if(de=find_city(c,name)==-1){
			cout<<"暂时没有火车或飞机从这里出发，换个城市试试！"<<endl;
			continue;
		}
		break;
	}
	while(1){
		cout<<"目的地：";
		cin>>dest;
		if(ar=find_city(c,dest)==-1){
			cout<<"暂时没有火车或飞机到达这里，换个城市试试！"<<endl;
			continue;
		}
		break;
	}
	while(1){
		cout<<"选择交通工具：";
		getline(cin,vehi);
		if(vehi!="train"&&vehi!="aeroplane"){
			cout<<"可供选择的交通方式只有火车和飞机，输入英文，train or aeroplane。"<<endl;
			continue;
		}
		break;
	}
	while(1){
		cout<<endl<<"0、最快； 1、最少中转； 2、最便宜； 3、回到上一步"<<endl
			<<"请输入数字以选择相应功能"<<endl;
		string func;
		getline(cin,func);
		char f=func[0];
		if(!isdigit(f)){
			cout<<"需要输入一个数字！再试试看。"<<endl;
			continue;
		}
		switch(f-'0'){
		case 0: fast_way(c,de,ar,vehi); break;
		case 1: short_way(c,de,ar,vehi); break;
		case 2: cheap_way(c,de,ar,vehi); break;
		case 3: break;
		default:
			cout<<"请输入0、1、2、3这四个功能的其中一个。"<<endl;
		}
	}
}
