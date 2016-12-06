#ifndef up
#define up
#include<bitset>
using namespace std;
class upstream_burst_profile_format
{
	bitset<8> type;
	bitset<8> length;
	bitset<6> uiuc;
	bitset<2> reserved_bits;
	//bitset<> ie;
	
	public:
		
	upstream_burst_profile_format( int length_in, int uiuc_in):
		type(1), length(length_in), uiuc(uiuc_in), reserved_bits(0)
	{
		
	}
	
	upstream_burst_profile_format()
	{
		
	}
	
	string up_burst_prof_string()
	{
		string c;
		c = type.to_string() + length.to_string() + uiuc.to_string() + reserved_bits.to_string();
		return c;
	}
};

#endif
