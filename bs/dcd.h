#include<bitset>
#include<iostream>
#include"dcd_channel_ie_backup_cand.h"
#include"downstream_burst_profile.h"
using namespace std;
class dcd
{
	bitset<8> management_msg_type;
	bitset<8> configuration_change_type;	//not done
	dcd_channel_ie *dcd_channel_ie_obj;       //incomplete
	bitset<6> no_downstream_burst_profiles;
	bitset<2> reserved_bits;
	downstream_burst_profile_format **downstream_burst_profiles;		//not complete
	
	public:
	
	dcd(int no_downstream_burst_profiles_in, int length[], int diuc[], int length_down_profile, int diuc_down_profile, int eirp_in, int ttg_in, 
		int rss_in, int channel_action_in, int action_mode_in, int action_superframe_no_in, int action_frame_no_in, int no_backup_channels_in, 
		int no_channels_in, int backup_candidate_length, int channel_no[]):
		reserved_bits(0), management_msg_type(0)
	{
		
		dcd_channel_ie_obj = new dcd_channel_ie( length_down_profile, diuc_down_profile, eirp_in, ttg_in, rss_in, channel_action_in, action_mode_in, action_superframe_no_in,
					action_frame_no_in, no_backup_channels_in, no_channels_in, backup_candidate_length, channel_no);
	
		
		no_downstream_burst_profiles = no_downstream_burst_profiles_in;
		
		
		for(int i=0;i<no_downstream_burst_profiles_in;i++)
		{
			
			downstream_burst_profiles[i] = new downstream_burst_profile_format( length[i], diuc[i]);
		}
	}
	
	
	
	
	string get_dcd_in_string()
	{
		string dcd_string="";
		
		dcd_string = management_msg_type.to_string() + configuration_change_type.to_string() + dcd_channel_ie_obj->dcd_channel_ie_string() + 
				no_downstream_burst_profiles.to_string() + reserved_bits.to_string() ;
		
		for(int i=0;i<no_downstream_burst_profiles.to_ullong();i++)
		{
			dcd_string = dcd_string + downstream_burst_profiles[i]->down_burst_prof_string();
		}
		
		return dcd_string;
	}
	
	
};
