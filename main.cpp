#include<iostream>
#include<fstream>
#include<cstdio>
#include<string>
#include<vector>
#include"city_info.h"
#include"rw_txt.h"
#include"which_way.h"


using namespace std;

int main(){
	string board (18,'*');
	cout<<board<<endl<<"*欢迎进入交通咨询*"<<endl<<board<<endl;
	vector<info> citys;
	read_from_file(citys);
	while(1){
		cout<<endl<<"0、退出； 1、编辑信息； 2、打印时刻表； 3、路线咨询"<<endl
			<<"请输入数字以选择相应功能"<<endl;
		string func;
		getline(cin,func);
		char f=func[0];
		if(!isdigit(f)){
			cout<<"需要输入一个数字！再试试看。"<<endl;
			continue;
		}
		switch(f-'0'){
		case 0: cout<<"感谢使用！"<<endl; return 0;
		case 1: edit_citys(citys); break;
		case 2: print_time_table(citys); break;
		case 3: which_way(citys); break;
		default:
			cout<<"请输入0、1、2、3这四个功能的其中一个。"<<endl;
		}
	}
	return 0;
}