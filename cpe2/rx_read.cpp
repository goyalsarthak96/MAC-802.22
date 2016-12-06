#include<iostream>
#include<fstream>
#include<list>
#include<string>								//put substrings into bitset and convert into decimal rather than performing looop with 'fact' variable
#include<cmath>
#include<bitset>
using namespace std;
int main()
{
	string s, fch_encoding,no_down_ie_str,sid_str,sid_in_str,diuc_in_str, down_burst_length_str;
	string us_map_size_str;
	int no_down_ie=0,sid=0,sid_in=0,diuc_in=0, down_burst_length=0;
	int us_map_size=0;
	list<int> down_burst_no,diuc_list,down_burst_duration;
	
	ifstream fin("cpe_header_recv.txt",ios::in), sid_fin("sid.txt",ios::in);
	getline(sid_fin, sid_str);
	sid = stoi(sid_str);
//	cout<<"sid="<<sid<<endl;
	getline(fin, s);
	if(s[74]=='0')
		fch_encoding = "00";
	else
		fch_encoding = "11";
//	cout<<encoding<<endl;
	if(!fch_encoding.compare("11"))
	{
		cout<<"for frame control header \nmodulation = qpsk\ncoding rate = 1/2\nrepetition = 2\n\n\n";
	}
	else if(!fch_encoding.compare("00"))
	{
		cout<<"for frame control header \nmodulation = qpsk\ncoding rate = 1/2\nrepetition = no repetition\n\n\n";
	}
	
	
	
	
	
	
	
	
	
    no_down_ie_str = s.substr(400,12);
    int fact=1;
    int extended_present=0;
    for(int i=no_down_ie_str.length()-1;i>=0;i--)
    {
    	no_down_ie = no_down_ie + (no_down_ie_str[i]-'0') * fact;
    	fact = fact * 2;
	}
	int ds_ie_size=0;
    int ie_diuc=0;
    string ie_diuc_str;
	for(int i=0;i<no_down_ie;i++)
    {
    	ie_diuc=0;
    	ie_diuc_str = s.substr(412 + ds_ie_size, 6);
    	fact = 1;
    	ie_diuc=0;
    	for(int j=ie_diuc_str.length()-1; j>=0; j--)
    	{
    		ie_diuc = ie_diuc + (ie_diuc_str[j]-'0') * fact;
    		fact = fact * 2;
		}
		if(ie_diuc==62)
		{
			extended_present = 1;
			us_map_size_str = s.substr(432,10);
			fact = 1;
			us_map_size=0;
			for(int j = ie_diuc_str.length()-1 ; j>=0; j--)
			{
				us_map_size = us_map_size + (us_map_size_str[j]-'0') * fact;
			}
			ds_ie_size = 30;
		}
		else
		{
    		sid_in_str = s.substr(412 + ds_ie_size + 6, 9);
    		fact=1;
    		sid_in=0;
    		for(int j=sid_in_str.length()-1;j>=0;j--)
    		{
    			sid_in = sid_in + (sid_in_str[j]-'0') * fact;
    			fact = fact * 2;
			}
			if(sid==sid_in)
    		{
    			down_burst_no.push_back(i-extended_present);
    			diuc_in_str = s.substr( 412+ ds_ie_size, 6);
    			fact=1;
    			diuc_in =0;
    			for(int j=diuc_in_str.length()-1;j>=0;j--)
    			{
    				diuc_in = diuc_in + (diuc_in_str[j]-'0') * fact;
    				fact = fact * 2;
				}
    			diuc_list.push_back(diuc_in);
    			
    			
    			down_burst_length_str = s.substr(412 + ds_ie_size + 15, 12);
    			down_burst_length = 0;
    			fact=1;
    			for(int j=down_burst_length_str.length()-1;j>=0;j--)
    			{
    				down_burst_length = down_burst_length + (down_burst_length_str[j]-'0') * fact;
    				fact = fact * 2;
				}
				down_burst_duration.push_back(down_burst_length);
    		}
    		ds_ie_size = ds_ie_size + 30;
    	}
	}
	
	int ds_map_slots = ceil( (double)(28 + ds_ie_size)/24 );
	int max_bits = ds_map_slots * 24;
	int ds_no_padding = max_bits - (28 + ds_ie_size);


//	412+ie_size+ds_no_padding		//start of usmap
	
	
	
	
	
	
	
	
	
	
	
	
	int upmap_no_ie=0, upmap_uiuc=0, upmap_dur=0;
	string upmap_no_ie_str, upmap_uiuc_str, upmap_dur_str;
	list<int> upmap_duration, up_burst_no, up_burst_uiuc;
	upmap_no_ie_str = s.substr(412 + ds_ie_size + ds_no_padding + 22, 12);
	fact=1;
    for(int j=upmap_no_ie_str.length()-1;j>=0;j--)
   	{
   		upmap_no_ie = upmap_no_ie + (upmap_no_ie_str[j]-'0') * fact;
   		fact = fact * 2;
	}
	string us_sid_str;
	int us_sid = 0, us_ie_size=0;
	for(int i=0;i<upmap_no_ie;i++)
	{
		us_sid_str = s.substr(412 + 34 + ds_ie_size + ds_no_padding + us_ie_size, 9);
		fact=1;
		us_sid=0;
    	for(int j=us_sid_str.length()-1;j>=0;j--)
    	{
    		us_sid = us_sid + (us_sid_str[j]-'0') * fact;
    		fact = fact * 2;
		}
		if(us_sid==sid)
		{
			up_burst_no.push_back(i);
			
			upmap_uiuc_str = s.substr(412 + 34 + ds_ie_size + ds_no_padding + us_ie_size + 9, 6);
			fact = 1;
			upmap_uiuc =0;
			for(int j=upmap_uiuc_str.length()-1;j>=0;j--)
   			{
   				upmap_uiuc = upmap_uiuc + (upmap_uiuc_str[j]-'0') * fact;
   				fact = fact * 2;
			}
			up_burst_uiuc.push_back(upmap_uiuc);
			
			upmap_dur_str = s.substr(446 + ds_ie_size + ds_no_padding + us_ie_size + 16, 12);
			fact = 1;
			upmap_dur=0;
			for(int j=upmap_dur_str.length()-1;j>=0;j--)
   			{
   				upmap_dur = upmap_dur + (upmap_dur_str[j]-'0') * fact;
   				fact = fact * 2;
			}
			upmap_duration.push_back(upmap_dur);
		}
		us_ie_size = us_ie_size + 31;
	}
	//cout<<"up ie "<<upmap_no_ie<<endl;
	int us_map_slots = ceil( (double)(34 + us_ie_size)/24 );
	int max_bits1 = us_map_slots * 24;
	int us_no_padding = max_bits1 - (34 + us_ie_size);
	
	
	
	
	
	
	
	
	
	
	
	
	//446+ ds_ie_size +ds_no_padding + us_ie_size + us_no_padding		start of ucd
	
	int ucd_profiles_no=0;
	bitset<6> ucd_profiles_no_bitset( s.substr(446+ ds_ie_size +ds_no_padding + us_ie_size + us_no_padding + 120, 6) );
	ucd_profiles_no = ucd_profiles_no_bitset.to_ullong();
	
	
	
	
	
	

	
	
	
	
	
	
	//24*ucd_profiles_no+446+ ds_ie_size +ds_no_padding + us_ie_size + us_no_padding + 126   start of dcd
	string backup_no_str, total_channel_no_str;
	int backup_no=0, total_channel_no=0;
	int backup_channel_list[256],candidate_channel_list[256];
	backup_no_str = s.substr(446+ ds_ie_size +ds_no_padding + us_ie_size + us_no_padding + 126 + 24*ucd_profiles_no +  16+40+24, 4);
	fact=1;
    for(int j=backup_no_str.length()-1;j>=0;j--)
    {
    	backup_no = backup_no + (backup_no_str[j]-'0') * fact;
    	fact = fact * 2;
	}
	
	total_channel_no_str = s.substr(446+ ds_ie_size +ds_no_padding + us_ie_size + us_no_padding + 126 + 24*ucd_profiles_no + 16 + 24+ 44 + 16, 8);
	fact=1;
    for(int j=total_channel_no_str.length()-1;j>=0;j--)
    {
    	total_channel_no = total_channel_no + (total_channel_no_str[j]-'0') * fact;
    	fact = fact * 2;
	}
	
	string channel_no_in_str;
	int channel_no_in;
	for(int i=0;i<backup_no;i++)
	{
		channel_no_in=0;
		channel_no_in_str = s.substr(446+ ds_ie_size +ds_no_padding + us_ie_size + us_no_padding + 126 + 24*ucd_profiles_no+ 16 + 24+ 44 + 24 + 8*i, 8);
		fact=1;
    	for(int j=channel_no_in_str.length()-1;j>=0;j--)
    	{
    		channel_no_in = channel_no_in + (channel_no_in_str[j]-'0') * fact;
    		fact = fact * 2;
		}
		backup_channel_list[i] = channel_no_in;
	}
	for(int i=0;i<total_channel_no-backup_no;i++)
	{
		channel_no_in=0;
		channel_no_in_str = s.substr(446+ ds_ie_size +ds_no_padding + us_ie_size + us_no_padding + 126 + 24*ucd_profiles_no + 16 + 24+ 44 + 24 + 8*backup_no + 8*i, 8);
		fact=1;
    	for(int j=channel_no_in_str.length()-1;j>=0;j--)
    	{
    		channel_no_in = channel_no_in + (channel_no_in_str[j]-'0') * fact;
    		fact = fact * 2;
		}
		candidate_channel_list[i] = channel_no_in;
	}
	
	
	
	
	
	
	
	
	int diuc_val;
	for(int i=0;i<no_down_ie-extended_present;i++)
	{
		//getline(fin, s);
		if(down_burst_no.front()==i)
		{
			diuc_val = diuc_list.front();
			down_burst_no.pop_front();
			diuc_list.pop_front();
			if(diuc_val==14)
			{
				cout<<"for downstream burst \nmodulation = qpsk\ncoding = convolutional code\n";
			}
			else if(diuc_val==18)
			{
				cout<<"for downstream burst \nmodulation = qam-16\ncoding = convolutional code\n";
			}
			else if(diuc_val==22)
			{
				cout<<"for downstream burst \nmodulation = qam-64\ncoding = convolutional code\n";
			}
			//cout<<"payload   "<<s.substr(32, s.length()-64)<<endl;
		}
	}
	
	
	cout<<endl;
	
	int uiuc_val;
	for(int i=0;i<upmap_no_ie;i++)
	{
		//getline(fin, s);
		if(up_burst_no.front()==i)
		{
			uiuc_val = up_burst_uiuc.front();
			up_burst_no.pop_front();
			up_burst_uiuc.pop_front();
			if(uiuc_val==14)
			{
				cout<<"for upstream burst  \nmodulation = qpsk\ncoding = convolutional code\n";
			}
			else if(uiuc_val==18)
			{
				cout<<"for upstream burst  \nmodulation = qam-16\ncoding = convolutional code\n";
			}
			else if(uiuc_val==22)
			{
				cout<<"for upstream burst  \nmodulation = qam-64\ncoding = convolutional code\n";
			}
			//cout<<"payload   "<<s.substr(32, s.length()-64)<<endl;
		}
	}
	
	cout<<endl;
	
	
	
	for(int i=0;i<backup_no;i++)
	{
		cout<<backup_channel_list[i]<<"  ";
	}
	cout<<endl;
	for(int i=0;i<total_channel_no-backup_no;i++)
	{
		cout<<candidate_channel_list[i]<<"  ";
	}
	
	
	
}
