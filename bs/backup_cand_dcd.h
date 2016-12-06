#include<bitset>
using namespace std;
class backup_and_candidate_channel_list
{
	bitset<8> elm_id;
	bitset<8> length;
	bitset<8> no_channels;
	bitset<8> channel_no[256];			
	
	public:
	
	backup_and_candidate_channel_list(int length_in, int no_channels_in, int channel_no_in[]): 
		length(length_in), elm_id(10), no_channels(no_channels_in)
	{
		
		for(int i=0;i<no_channels_in;i++)
		{
		
			channel_no[i] = channel_no_in[i];
		}
	}
	
	backup_and_candidate_channel_list()
	{
		
	}
	
	string back_list_string()
	{
		string c;
		c = elm_id.to_string() + length.to_string() + no_channels.to_string();
		for(int i=0;i<no_channels.to_ullong();i++)
		{
			c = c + channel_no[i].to_string();
		}
		return c;
	}
};
