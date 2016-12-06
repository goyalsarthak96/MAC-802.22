#include<bitset>
#include"upstream_burst_profile.h"
#include"ucd_channel_ie.h"

using namespace std;
class ucd
{
	bitset<8> management_msg_type;
	bitset<8> config_change_count;	//not done
	bitset<4> bw_request_backoff_start;
	bitset<4> bw_request_backoff_end;
	bitset<4> ucs_notif_backoff_start;
	bitset<4> ucs_notif_backoff_end;
	ucd_channel_ie *ie_for_overall_channel;
	bitset<6> no_upstream_burst_profile;
	upstream_burst_profile_format **upstream_burst_profiles;
	public:
		
	ucd(int bw_request_backoff_start_in, int bw_request_backoff_end_in, int ucs_notif_backoff_start_in, int ucs_notif_backoff_end_in, int no_upstream_burst_profile_in,
		int upstream_burst_profile_length, int upstream_burst_profile_uiuc,
		int ucd_channel_ie_length, int ucd_channel_ie_uiuc, int content_based_reserve_timeout, int bandwidth_req_opportunity_size, int ucs_notif_req_opportunity_size, 
		int init_ranging_codes, int periodic_ranging_codes, int bandwidth_req_codes, int ucs_notif_codes, int start_cdms_codes_group):
		management_msg_type(2), bw_request_backoff_start(bw_request_backoff_start_in), bw_request_backoff_end(bw_request_backoff_end_in), 
		ucs_notif_backoff_start(ucs_notif_backoff_start_in), ucs_notif_backoff_end(ucs_notif_backoff_end_in), no_upstream_burst_profile(no_upstream_burst_profile_in)
	{
		
		ie_for_overall_channel = new ucd_channel_ie(ucd_channel_ie_length, ucd_channel_ie_uiuc, content_based_reserve_timeout, bandwidth_req_opportunity_size, 
								ucs_notif_req_opportunity_size, init_ranging_codes, periodic_ranging_codes, bandwidth_req_codes, ucs_notif_codes, start_cdms_codes_group);
		
		for(int i=0;i<no_upstream_burst_profile_in;i++)
		{
			upstream_burst_profiles[i] = new upstream_burst_profile_format(upstream_burst_profile_length, upstream_burst_profile_uiuc );	
		}
			
	}
	
	
	string ucd_string()
	{
		string c;
		c = management_msg_type.to_string() + config_change_count.to_string() + bw_request_backoff_start.to_string() + bw_request_backoff_end.to_string() + 
			ucs_notif_backoff_start.to_string() + ucs_notif_backoff_end.to_string() + ie_for_overall_channel->get_ie_string() + no_upstream_burst_profile.to_string();
			
		for(int i=0; i<no_upstream_burst_profile.to_ullong(); i++)
		{
			c = c + upstream_burst_profiles[i]->up_burst_prof_string();
		}
		
		
		return c;
	}
};
