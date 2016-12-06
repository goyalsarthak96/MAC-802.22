#include<iostream>
#include<fstream>
#include<cstring>
#include<algorithm>
using namespace std;

struct list
{
	int channelID;
	int StoN;
};

bool compare(list l1 , list l2)
{
	return (l1.StoN < l2.StoN);
}

int main()
{
	ifstream str;
	string s,s1,s2;
	str.open("channelslist.txt",ios::in);
	getline(str,s);
	int oper_freq = stoi(s);
	getline(str,s);
	int tot = stoi(s);
	getline(str,s);
	int back = stoi(s);
	list* arr = new list[tot+1];
	
	for(int i=0;i<tot+1;i++)
	{
		arr[i].channelID = -1;
		arr[i].StoN = -1;
	 }

	int j,ind;
	
		getline(str,s);
		for(j=0;j<s.length();j++)
		{
			if(s[j]==' ')
			ind = j;
		}
		
		s1 = s.substr(0,ind);
		//cout<<s1<<" ";
		oper_freq = stoi(s1);
	//	s2 = s.substr(ind+1,s.length()-ind-1);
	//	cout<<s2<<endl;
		
		for(int i=0;i<tot-1;i++)
		{
			getline(str,s);
			for(j=0;j<s.length();j++)
			{
				if(s[j] == ' ')
				ind = j;
			}
			s1 = s.substr(0,ind);
			arr[i].channelID = stoi(s1);
			s2 = s.substr(ind+1,s.length()-ind-1);
			arr[i].StoN = stoi(s2);
		}

//	cout<<"a";
	/*for(int i=0;i<tot-1;i++)
	{
		cout<< arr[i].channelID<<" "<<arr[i].StoN<<endl;
	}*/
	
//	cout<< endl;
	
	list *brr = new list[tot-1];
	
	
	
	int k =0;
	for(int i=0;i<tot-1;i++)
	{
		if(arr[i].channelID==oper_freq+1 || arr[i].channelID==oper_freq-1)
		{
			arr[tot+k-1].channelID = arr[i].channelID;
			arr[tot+k-1].StoN = arr[i].StoN;
			arr[i].channelID = -1;
			arr[i].StoN = -1;
			k++; 
		}
	}
	k = 0;
	for(int i=0;i<tot+1;i++)
	{
		if(arr[i].channelID!=-1)
		{
			brr[k].channelID = arr[i].channelID;
			//cout<<brr[k].channelID<<" ";
			brr[k].StoN = arr[i].StoN;
			//cout<<brr[k].StoN<<endl;
			k++;
		}
	}
	
	
	tot--;
	back--;
	
	cout<<oper_freq;
	
	ofstream fout("channelslist.txt",ios::out);
	fout<<oper_freq<<endl;
	fout<<tot<<endl;
	fout<<back<<endl;
	for(int i=0;i<tot;i++)
	{
		fout<<brr[i].channelID<<" "<<brr[i].StoN<<endl;
	}
	fout<<"4";
}

