#ifndef extended
#define extended

#include<bitset>
using namespace std;

class Extended_DS_MAP_IE
{
	bitset<6> Extended_DIUC;
	bitset<8> Length;
	bitset<10> US_MAP_Length;
	
	public:
		Extended_DS_MAP_IE()
		{
			Extended_DIUC = 62;
			Length = 24;
			US_MAP_Length = 3;
		}
		
	bitset<24> get_all_fields_in_binary()
	{
		string s = Extended_DIUC.to_string();
		string s1 = Length.to_string();
		s = s + s1;
		s1 = US_MAP_Length.to_string();
		s = s +  s1;
		bitset<24> b(s);
		return b;
	}
	
};

#endif
