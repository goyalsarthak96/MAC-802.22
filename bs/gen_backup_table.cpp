#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	ifstream fin;
	string s;
	int i;
	int no_channels;
	fin.open("channelslist.txt",ios::in);
	getline(fin,s);
	getline(fin,s);
	getline(fin,s);
	no_channels = stoi(s);
	cout<<" _________________________________________________________________"<<endl;
	cout<<"|     Channel Number            |               SNR               |"<<endl;
	cout<<"|_______________________________|_________________________________|"<<endl;          
	for(int j=0;j<no_channels;j++)
	{
		getline(fin,s);
		for(i=0;i<s.length();i++)
		{
			if(s[i]==' ')
				break;
		}
	cout<<"|          "<<stoi(s)<<"                    |              "<<stoi(s.substr(i+1,s.length()-i-1))<<"                 |"<<endl;
	}
	cout<<"|_______________________________|_________________________________|"<<endl;
}
