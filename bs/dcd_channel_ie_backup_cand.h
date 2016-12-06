#include<bitset>
#include"downstream_burst_profile.h"
#include"backup_cand_dcd.h"
using namespace std;

class dcd_channel_ie
{
	pair<bitset<8>, downstream_burst_profile_format> downstream_burst_profile; 	//incomplete
	pair<bitset<8>, bitset<8> > eirp;
	pair<bitset<8>, bitset<8> > ttg;
	pair<bitset<8>, bitset<8> > rss;
	pair<bitset<8>, bitset<3> > channel_action;
	pair<bitset<8>, bitset<1> > action_mode;
	pair<bitset<8>, bitset<8> > action_superframe_no;
	pair<bitset<8>, bitset<4> > action_frame_no;
	pair<bitset<8>, bitset<4> > no_backup_channels;
	pair<bitset<8>, backup_and_candidate_channel_list> backup_and_candidate_channel_list_obj;
	pair<bitset<8>, bitset<8> > mac_version;
	public:
		
	dcd_channel_ie()
	{
		
	}
		
	dcd_channel_ie( int length_down_profile, int diuc, int eirp_in, int ttg_in, int rss_in, int channel_action_in, int action_mode_in, 
		int action_superframe_no_in, int action_frame_no_in, int no_backup_channels_in, int no_channels_in, int backup_candidate_length, int channel_no[])
	{
			
			downstream_burst_profile.first = 1;
			downstream_burst_profile_format obj( length_down_profile, diuc);
			downstream_burst_profile.second = obj; 
			
			eirp.first = 2;
			eirp.second = eirp_in;
			
			ttg.first = 3;
			ttg.second = ttg_in;
			
			rss.first = 4;
			rss.second = rss_in;
			
			channel_action.first = 5;
			channel_action.second = channel_action_in;
			
			action_mode.first = 6;
			action_mode.second = action_mode_in;
			
			action_superframe_no.first = 7;
			action_superframe_no.second = action_superframe_no_in;
			
			action_frame_no.first = 8;
			action_frame_no.second = action_frame_no_in;
			
			no_backup_channels.first = 9;
			no_backup_channels.second = no_backup_channels_in;
			
			
			backup_and_candidate_channel_list_obj.first = 10;
			backup_and_candidate_channel_list obj1(backup_candidate_length, no_channels_in, channel_no);
			backup_and_candidate_channel_list_obj.second = obj1;

			
			mac_version.first = 11;
			mac_version.second = 1;
	}
	
	
	string dcd_channel_ie_string()
	{
		string c;
		c= downstream_burst_profile.second.down_burst_prof_string() + eirp.second.to_string() + ttg.second.to_string() + rss.second.to_string() + 
			channel_action.second.to_string() + action_mode.second.to_string() + action_superframe_no.second.to_string() +  action_frame_no.second.to_string() + 
			no_backup_channels.second.to_string() + backup_and_candidate_channel_list_obj.second.back_list_string() + mac_version.second.to_string();
		
		return c;
		
	}
	
};
