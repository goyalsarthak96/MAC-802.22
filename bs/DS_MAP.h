#include<bitset>
#include"DS_MAP_IE.h"
#include"Extended_DS_MAP_IE.h"
using namespace std;

class DS_MAP
{
	bitset<8> management_msg_type;
	bitset<8> DCD_count;
	bitset<12> no_ie;
//	bitset<24> Extended_DS_MAP_IE1;
	bitset<30> *DS_MAP_IE1;	// array of DS_MAP_IE bitarrays
//	bitset<14> padding;         // padding is equal to size of DS_MAP - 58

	
//constructor of DS_MAP Type 1	
	
	public:DS_MAP(float arr[], unsigned long long int no_ie_in, int sid_in[])
	{
		management_msg_type = 1 ;
		DCD_count = 1;
		no_ie = no_ie_in;
	//	Extended_DS_MAP_IE *obj = new Extended_DS_MAP_IE();
//		Extended_DS_MAP_IE1 = obj->get_all_fields_in_binary();
//		delete obj;
		DS_MAP_IE1 = new bitset<30>[no_ie_in];   
		
		for(int i=0;i<no_ie_in;i++)
		{
			if(i==0)
			{
				DS_MAP_IE * obj23 = new DS_MAP_IE();
				DS_MAP_IE1[i] = obj23->get_all_fields_in_binary();

				delete obj23;
			}
			else
			{
				DS_MAP_IE * obj23 = new DS_MAP_IE(arr[i-1], sid_in[i-1]);
				DS_MAP_IE1[i] = obj23->get_all_fields_in_binary();

				delete obj23;
			}
		}
	
	//	padding.reset();  // set all padding bits to zero
	
	}
	
	
// Constructor of DS_MAP type 2		
	
	/*public:DS_MAP(float arr[],int DCD_count_in,int n_in)
	{
	management_msg_type = 1 ;
	DCD_count = DCD_count_in;
	n = n_in;
	count = n_in;
	DS_MAP_IE1 = new bitset<30>[count];
	for(i=0;i<count;i++)
	{
		
		DS_MAP_IE * obj = new DS_MAP_IE(arr[i]);
		DS_MAP_IE1[i] = obj->get_all_fields_in_binary();
		delete obj;
		
	}
	
	padding.reset();
	
	}*/
	
	
	
		
	
	void get_all_fields_in_binary(string &s)
	{
		s = management_msg_type.to_string();
		string s1 = DCD_count.to_string();
		s = s + s1;
		s1 = no_ie.to_string();
		s = s  + s1 ;
		//s1 = Extended_DS_MAP_IE1.to_string();
		//s = s + s1;

		for(int i = 0;i<no_ie.to_ullong();i++)
		{
			s1 = DS_MAP_IE1[i].to_string();
			s = s  + s1 ;
		} 
		
		
		unsigned long long int dsmap_size = ( no_ie.to_ullong() )* 30 + 28;			//works coz extended diuc also of size 30 bits
		//unsigned long long int subcarriers_no = dsmap_size * 2;
		unsigned long long int no_padding;
		if(dsmap_size % 24 == 0)
			no_padding = 0;
		else
			no_padding = 24 - ( dsmap_size % 24); 
		//s1 = padding.to_string();
		string padding( no_padding, '0');
		s = s  + padding;
		delete DS_MAP_IE1;
	}
	
		
};

