#include<iostream>
#include<fstream>
using namespace std;
int main(int argc, char* argv[])
{
	ifstream fin1, fin2;
	string gmh, cpe_no;
	//cout<<s<<endl;
	
	int no_rec_data = stoi(argv[2]);
	cout<<no_rec_data;
	int i=1;
	cpe_no = argv[1];
	if(cpe_no.compare("1"))
	{
		fin1.open("serv_rec1.txt",ios::in);
		while(i<no_rec_data)
		{
			getline(fin1,gmh);	
		}
	}
	else
	{
		fin2.open("serv_rec2.txt",ios::in);
		while(i<no_rec_data)
		{
			getline(fin2,gmh);	
		}
	}
	
	cout<<"\n"<<gmh<<endl; 
	if(gmh[11]=='1')
	{
		cout<<"problem";
	}
	else
	{
		cout<<"all well";
	}
	//cout<<argv[0];
	
}
