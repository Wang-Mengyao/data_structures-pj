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

int calculate_time(int a[],int b[]){
	int t=(b[0]-a[0])*60+(b[1]-a[1]);
	return t>0?t:MAX;
}

float all_cost(int d,vector<info>& c,int pre,int cur,int ar_time[],int* k,int** kt,string& vehi){
	const vector<city_node*>& t=c[pre].destination();//mode 0 最少中转；1 最少花费；2 最短用时
	vector<city_node*>::const_iterator i=t.begin();
	float min_cost=MAX;
	int min_time=MAX;
	int counter=0;
	*k=-1;//*k用来记录是第几条弧，以应对多重边
	for(;i!=t.end();i++,counter++){
		if(ar_time==0||(*i)->de_time[0]>ar_time[0]||((*i)->de_time[0]==ar_time[0]&&(*i)->de_time[1]>ar_time[1]));
		else continue;//确认时间合理性
		if((*i)->dest_city==c[cur].name()&&(*i)->vehicle==vehi){
			if(d==0){
				*k=counter;
				*kt=(*i)->ar_time;
				return 1;//最少中转找到一条弧即可，不用继续检索，返回权为1，那么显然中转越少，总权值越低
			}
			if(d==1&&(*i)->cost<min_cost){
				min_cost=(*i)->cost;
				*k=counter;
				*kt=(*i)->ar_time;//记录通过该班次到达该地的时间，以备之后使用
			}//遍历以找到多重边当中最小的那一边
			if(d==2){
				int temp;
				if(ar_time==0) temp=calculate_time((*i)->de_time,(*i)->ar_time);
				else temp=calculate_time(ar_time,(*i)->ar_time);
				//用时分两种情况，第一个班次即用自己的到达时间'减'出发时间
				//之后的班次用自己的到达时间'减'到达出发地的时间
				//'减'被拆解出来，放到calculate_time函数里
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

void short_path_dijkstra(vector<info>& c,int v,int mode,string& vehi,int kth[],int pre[]){
	int n=c.size();
	int k;
	int* kt[50];//到达该城市的时间
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
			j_kt=kt[j];//all_cost函数会对这两个值进行修改，故先保存
			int cost=all_cost(mode,c,k,j,kt[k],kth+j,kt+j,vehi);
			if(cost<MAX&&dist[k]+cost<dist[j]){
				dist[j]=dist[k]+cost;
				pre[j]=k;
			}else{
				kth[j]=j_kth;
				kt[j]=j_kt;//不应修改，遂还原
			}
		}
	}
}

void show_way(vector<info>& c,int d,int a,int kth[],int pre[]){
	stack<print_node> s;
	int i=a;
	print_node* t;
	int counter=-1;
	float cost=0;
	int de[2],ar[2];
	for(;i!=d;){
		if(pre[i]==-1) break;
		t=new print_node();
		t->kth=kth[i];
		i=t->city=pre[i];
		s.push(*t);
		++counter;
	}
	int flag=0;
	if(i!=d) cout<<"暂时无班次可抵达。"<<endl;
	else{
		while(!s.empty()){
			*t=s.top();s.pop();
			const vector<city_node*>& ct=c[t->city].destination();
			city_node* ci=ct[t->kth];
			if(flag==0){
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
		cout<<"总计用时："<<calculate_time(de,ar)<<"分钟   花费："<<cost<<"元   中转站数："<<counter<<"站"<<endl;
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
		cout<<"出发地：";
		cin>>name;
		de=find_city(c,name);
		if(de==-1){
			cout<<"暂时没有火车或飞机从这里出发，换个城市试试！"<<endl;
			continue;
		}
		break;
	}
	while(1){
		cout<<"目的地：";
		cin>>dest;
		ar=find_city(c,dest);
		if(ar==-1){
			cout<<"暂时没有火车或飞机到达这里，换个城市试试！"<<endl;
			continue;
		}
		if(ar==de){
			cout<<"出发地不能与目的地相同，换个城市试试！"<<endl;
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
		case 3: return;
		default:
			cout<<"请输入0、1、2、3这四个功能的其中一个。"<<endl;
		}
	}
}
