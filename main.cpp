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
	cout<<board<<endl<<"*��ӭ���뽻ͨ��ѯ*"<<endl<<board<<endl;
	vector<info> citys;
	read_from_file(citys);
	while(1){
		cout<<endl<<"0���˳��� 1���༭��Ϣ�� 2����ӡʱ�̱� 3��·����ѯ"<<endl
			<<"������������ѡ����Ӧ����"<<endl;
		string func;
		getline(cin,func);
		char f=func[0];
		if(!isdigit(f)){
			cout<<"��Ҫ����һ�����֣������Կ���"<<endl;
			continue;
		}
		switch(f-'0'){
		case 0: cout<<"��лʹ�ã�"<<endl; return 0;
		case 1: edit_citys(citys); break;
		case 2: print_time_table(citys); break;
		case 3: which_way(citys); break;
		default:
			cout<<"������0��1��2��3���ĸ����ܵ�����һ����"<<endl;
		}
	}
	return 0;
}