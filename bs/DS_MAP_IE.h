#include<bitset>
#include"Extended_DS_MAP_IE.h"
using namespace std;

class DS_MAP_IE
{
	bitset<6> DIUC;
	bitset<9> SID;
	bitset<12> Length;
	bitset<3> Boosting;
	
	bitset<24> extended_dsmap_ie_obj;
	
// construstor DS_MAP_IE TYPE 1
	
	public:
	DS_MAP_IE(float dist, int sid_in)
	{
		
		if(dist <= 15 )
		
			DIUC = 22;                 //encoding based on distance
			
		else if(dist <= 22 )
		
			DIUC = 18;                  
		
		else if(dist <= 30)
		
			DIUC = 14;
		
		SID = sid_in;                       //It will convert integer '0' to bitarray as SID is of bitarray type
		Length = 4;
		Boosting = 4;
		
	}
	
	
	DS_MAP_IE()
	{
		DIUC = 62;
		Extended_DS_MAP_IE obj;
		extended_dsmap_ie_obj = obj.get_all_fields_in_binary();
		
	}
	
// Constructor DS_MAP_IE Type 2	

	
	DS_MAP_IE( float dist, int SID_in , int Length_in , int Boosting_in )
	{
		if(dist <= 15 )
		
			DIUC = 22;
			
		else if(dist <= 22 )
		
			DIUC = 18;
		
		else if(dist <= 30)
		
			DIUC = 14;
		
		SID = SID_in;
		Length = Length_in;
		Boosting = Boosting_in;
		
	}
	
	
	
	
	bitset<30> get_all_fields_in_binary()
	{
		string s;
		
		if((DIUC.to_ullong())==62)
		{
			s = DIUC.to_string() + extended_dsmap_ie_obj.to_string();
		}
		else
		s  = DIUC.to_string() +  SID.to_string() + Length.to_string() + Boosting.to_string();
		
		bitset<30> b(s);			//convert string to bitarray
		return b;
	}
		
} ;

