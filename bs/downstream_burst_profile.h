#ifndef STUDENT_H
#define STUDENT_H

#include<bitset>
using namespace std;
class downstream_burst_profile_format
{
	bitset<8> type;
	bitset<8> length;
	bitset<6> diuc;
	bitset<2> reserved_bits;
	//bitset<>	ie;
	
	public :
	
	downstream_burst_profile_format(int length_in,int diuc_in):
		type(1), reserved_bits(0), length(length_in), diuc(diuc_in)
	{
		
	}
	
	downstream_burst_profile_format()
	{
		
	}
	
	string down_burst_prof_string()
	{
		string c;
		c = type.to_string() + length.to_string() + diuc.to_string() + reserved_bits.to_string();
		return c; 
	}
};

#endif
