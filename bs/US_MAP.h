#include<bitset>
#include"US_MAP_IE.h"
using namespace std;

class US_MAP
{
	
	bitset<8> management_msg_type;
	bitset<8> ucd_count;
	bitset<6> allocation_start_time;
	bitset<12> no_ie;
	bitset<31> *US_MAP_IEs;
	
	
	public:US_MAP(float dist_arr[],unsigned long long no_ie_in,int sid_in[])
	{
		
		management_msg_type = 3;
		ucd_count = 1;
		no_ie = no_ie_in;
		US_MAP_IEs = new bitset<31>[no_ie_in];
		
		for(int i=0;i<no_ie_in;i++)
		{
			
			US_MAP_IE * obj = new US_MAP_IE(dist_arr[i],sid_in[i]);
			US_MAP_IEs[i] = obj->get_all_fields_in_binary();
			
			delete obj;
		}
	}
	
	
	string get_all_fields_in_string()
	{
		string s;
		s = management_msg_type.to_string();
		string s1 = ucd_count.to_string();
		s = s + s1;
		s1 = allocation_start_time.to_string();
		s = s + s1;
		s1 = no_ie.to_string();
		s = s + s1;
		
		for(int i = 0;i<no_ie.to_ullong();i++)
		{
			s1 = US_MAP_IEs[i].to_string();
			s = s + s1;
		}
		
		unsigned long long int usmap_size = (no_ie.to_ullong())*31 + 34;
		unsigned long long int no_padding;
		if(usmap_size % 24 == 0)
			no_padding = 0;
		else
			no_padding = 24 - ( usmap_size % 24); 
		
		//s1 = padding.to_string();
		string padding( no_padding, '0');
		s = s  + padding;
		
		return s;
	}
	
};
