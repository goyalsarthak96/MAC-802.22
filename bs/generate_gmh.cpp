#include<iostream>
#include<fstream>
#include"gmh.h"
using namespace std;
int main()
{
	ofstream fout;
	string gmh_without_space;
	fout.open("gmh_binary.txt",ios::out);
	generic_mac_header gmh_obj(5);
	gmh_obj.get_header_in_binary(gmh_without_space);
	cout<<gmh_without_space;
	fout<<gmh_without_space;
}
