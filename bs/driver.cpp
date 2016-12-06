#include<iostream>
#include<fstream>
#include"sch.h"
#include"fch.h"
#include<bitset>
#include<cstdlib>
#include<string>
#include"gmh.h"
#include"DS_MAP.h"
#include"dcd.h"
#include"ucd.h"
#include"US_MAP.h"
using namespace std;

typedef bitset<48> uint48;

uint48 cal_mac_Addr_in_dec(string &s)
{
	uint48 val=0;
	unsigned int y=1;
	for(unsigned int i = 0; i < 6; i++)
	{	
	
		if( s[i*3] >= 'A')
			y = 16 * (s[3*i] - 55);
		else
			y = 16 * (s[3*i] - 48);

		if(s[3*i + 1] >= 'A')
			y = y + (s[3*i+1] - 55);
		else
			y = y + (s[3*i+1] - 48) ;
			
		val = val.to_ullong() + y * pow(2, 8 * (5 -i));
		
	}
	return val;
}

int main()
{
	string s, sch_with_space, sch_without_spaces, fch_with_space, fch_without_spaces, ds_map_without_space, gmh_without_space, dcd_without_space;
	ifstream sch_fin,fch_fin, payload_fin, backup_fin;
	sch_fin.open ("sch_in.txt", ios::in);
	fch_fin.open ("cpe_info.txt", ios::in);
	payload_fin.open("payload.txt",ios::in);
	backup_fin.open("channelslist.txt",ios::in);
	
	ofstream fout;
	fout.open("sch_out.txt",ios::out);

	int cur_frame_no=0;
	
	//while(1)
	//{
		if(cur_frame_no==0)
		{
			getline( sch_fin, s);
			getline( sch_fin, s);
		
			uint48 mac_addr_decimal = cal_mac_Addr_in_dec (s);
	
			sch superframe_obj(mac_addr_decimal, sch_with_space, sch_without_spaces);
	
			superframe_obj.get_header_in_binary(sch_with_space, sch_without_spaces);
			fout<<sch_without_spaces;
		}
		
		
		
		
		
		getline( fch_fin, s);
		getline( fch_fin, s);
		unsigned long long int no_cpe = stoi(s);
		
		fch fch_obj( no_cpe+1);
		fch_obj.get_header_in_binary( fch_with_space, fch_without_spaces);
		fout<<fch_without_spaces;
		//make frame 
		
		
		
		
	
		
		float cpe_dist_arr[ no_cpe ];
		unsigned long long int arr_index = 0, str_prev_index = 0, i=0;
		getline( fch_fin, s);
		string s1;
		while( arr_index < no_cpe)
		{
			if( (s[i] < 48) || (s[i] > 57) )
			{
				s1 = s.substr( str_prev_index , i - str_prev_index );
				cpe_dist_arr[arr_index] = stoi(s1);
				str_prev_index = i + 1;
				arr_index++;	
			}
			i++;
		}
		
		int cpe_id[no_cpe];
		arr_index=0;
		str_prev_index = 0;
		i=0;
		getline( fch_fin, s);
		while( arr_index < no_cpe)
		{
			if( (s[i] < 48) || (s[i] > 57) )
			{
				s1 = s.substr( str_prev_index , i - str_prev_index );
				cpe_id[arr_index] = stoi(s1);
				str_prev_index = i+1;
				arr_index++;	
			}
			i++;
		}
		
		DS_MAP dsmap_obj (cpe_dist_arr , no_cpe+1, cpe_id);				//nocpe+ 1 = no_ie_in_dsmap     1-> for extended diuc
		dsmap_obj.get_all_fields_in_binary( ds_map_without_space);
		fout<<ds_map_without_space;
		
		
		
		
		
		US_MAP us_map_obj = US_MAP(cpe_dist_arr, no_cpe, cpe_id);
		string us_map_str = us_map_obj.get_all_fields_in_string();
		fout<<us_map_str;
		
		
		
		
		
		ucd ucd_obj(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		string ucd_str = ucd_obj.ucd_string();
		fout<<ucd_str;
		
		
		
		
		
		
		int no_down_burst_profile = 0;
		int down_burst_profile_length[no_down_burst_profile], down_burst_profile_diuc[no_down_burst_profile]; 
		string b;
		getline( backup_fin, b);
		getline( backup_fin, b);
		int no_back_channel = stoi(b);
		getline( backup_fin, b);
		int no_total_channel = stoi(b);
		int back_cand_list_length = no_total_channel * 8 + 24;
		int channels[no_total_channel];
		for(int i=0; i<no_total_channel; i++)
		{
			getline(backup_fin,b);
			channels[i]  = stoi(b);
		}
		dcd dcd_obj(no_down_burst_profile, down_burst_profile_length, down_burst_profile_diuc, 0, 0, 0, 0, 0, 0, 0, 0, 0, no_back_channel, no_total_channel, 
		back_cand_list_length, channels);
		dcd_without_space = dcd_obj.get_dcd_in_string();
		fout<<dcd_without_space;
		
		
		
		
		
		
		
		
		/*int no_of_bursts = 2;
		string payload_data;
		string crc(32, '0');
		for(int i = 0; i < no_of_bursts; i++)
		{
			getline(payload_fin, payload_data);
			generic_mac_header gmh_obj(5);
			gmh_obj.get_header_in_binary(gmh_without_space); 
			fout<<gmh_without_space + payload_data + crc;		
		}
		
		
		
		/*fout<<sch_without_spaces<<endl;
		fout<<fch_without_spaces<<endl;
		fout<<ds_map_without_space;*/
		
		
		
	/*	generic_mac_header gmh_obj;
		gmh_obj.get_header_in_binary(gmh_without_space);
		fout<<gmh_without_space;*/
		
		
		
		
		
		
		
		cur_frame_no=(cur_frame_no+1)%16;
		
	//}
	
		cout<<"Headers Generated"<<endl;
	
}
