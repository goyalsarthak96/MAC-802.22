#include<bitset>
#include"upstream_burst_profile.h"
using namespace std;
class ucd_channel_ie
{
	pair<bitset<8>, upstream_burst_profile_format> upstream_burst_profile;
	pair<bitset<8>, bitset<8> > content_based_reserve_timeout;
	pair<bitset<8>, bitset<8> > bandwidth_req_opportunity_size;
	pair<bitset<8>, bitset<8> > ucs_notif_req_opportunity_size;
	pair<bitset<8>, bitset<8> > init_ranging_codes;
	pair<bitset<8>, bitset<8> > periodic_ranging_codes;
	pair<bitset<8>, bitset<8> > bandwidth_req_codes;
	pair<bitset<8>, bitset<8> > ucs_notif_codes; 
	pair<bitset<8>, bitset<8> > start_cdms_codes_group;
	
	public:
		
	ucd_channel_ie(int burst_profile_length, int burst_profile_uiuc, int content_based_reserve_timeout_in, int bandwidth_req_opportunity_size_in, 
					int ucs_notif_req_opportunity_size_in, int init_ranging_codes_in, int periodic_ranging_codes_in, int bandwidth_req_codes_in, int ucs_notif_codes_in, 
					int start_cdms_codes_group_in)
	{
		upstream_burst_profile.first = 1;
		upstream_burst_profile_format obj(burst_profile_length, burst_profile_uiuc);
		upstream_burst_profile.second = obj;
		
		content_based_reserve_timeout.first = 2;
		content_based_reserve_timeout.second = content_based_reserve_timeout_in;
		
		bandwidth_req_opportunity_size.first = 3;
		bandwidth_req_opportunity_size.second = bandwidth_req_opportunity_size_in;
		
		ucs_notif_req_opportunity_size.first = 4;
		ucs_notif_req_opportunity_size.second = ucs_notif_req_opportunity_size_in;
		
		init_ranging_codes.first = 150;
		init_ranging_codes.second = init_ranging_codes_in;
		
		periodic_ranging_codes.first = 151;
		periodic_ranging_codes.second = periodic_ranging_codes_in;
		
		bandwidth_req_codes.first = 152;
		bandwidth_req_codes.second = bandwidth_req_codes_in;
		
		ucs_notif_codes.first = 153;
		ucs_notif_codes.second = ucs_notif_codes_in;
		
		start_cdms_codes_group.first = 154;
		start_cdms_codes_group.second = start_cdms_codes_group_in;
		
	}
	
	ucd_channel_ie()
	{
		
	}


	string get_ie_string()
	{
		string c;
		c = upstream_burst_profile.second.up_burst_prof_string() ;
		
		c = c + content_based_reserve_timeout.second.to_string() + bandwidth_req_opportunity_size.second.to_string() +
			ucs_notif_req_opportunity_size.second.to_string() + init_ranging_codes.second.to_string() + periodic_ranging_codes.second.to_string() + 
			bandwidth_req_codes.second.to_string() + ucs_notif_codes.second.to_string() + start_cdms_codes_group.second.to_string();
			
		return c;
	}
};
