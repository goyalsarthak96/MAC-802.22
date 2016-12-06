#include<bitset>
using namespace std;

class US_MAP_IE
{
	bitset<9> SID;
	bitset<6> UIUC;
	bitset<1> burst_type;
	bitset<12> duration;
	bitset<1> MDP;
	bitset<1> MRT;
	bitset<1> CMRP;
	
	public:
		US_MAP_IE(float dist, int sid_in)
		{
			if(dist <= 15)
				UIUC = 22;
			
			else if(dist <= 22)
				UIUC = 18;
			
			else if(dist <= 30)
				UIUC = 14;
			
			SID = sid_in;
			burst_type = 0;
			duration = 0;
			MDP = 0;
			MRT = 0;
			CMRP = 0;
		}
		
	bitset<31> get_all_fields_in_binary()
	{
		string s = SID.to_string();
		string s1 = UIUC.to_string();
		s = s + s1;
		s1 = burst_type.to_string();
		s = s + s1;
		s1 = duration.to_string();
		s = s + s1;
		s1 = MDP.to_string();
		s = s + s1;
		s1 = MRT.to_string();
		s = s + s1;
		s1 = CMRP.to_string();
		s = s + s1;
		bitset<31> b(s);
		return b;
	}
};
