//#include<stdint.h>
#include<bitset>
#include<cmath>
using namespace std;

typedef bitset<48> uint48;
typedef bitset<16> uint16;
typedef bitset<8> uint8;
typedef bitset<2> uint2;
typedef bitset<4> uint4;
typedef bitset<12> uint12;
typedef bitset<6> uint6;
typedef bitset<312> uint312;
typedef bitset<32> uint32;

class sch	//padding in end
{
	uint48 bs_id;															//48 bits
	uint16 frame_allocation_map;											//16 bits
	static uint8 superframe_number;										//8 bits
	uint2 cyclic_prefix;													//2 bits
	uint2 fch_encoding_flag;												//2 bits
	uint4 sc_capablity_ind;												//4 bits
	uint8 mac_version;													//8 bits
		
	uint8 current_intra_frame_qp_cycle_length;							//8 bits
	uint8 current_intra_frame_qp_cycle_offset;							//8 bits
	uint16 current_intra_frame_qp_cycle_frame_bitmap;						//16 bits
	uint8 current_intra_frame_qp_duration;								//8 bits
		
	uint8 claimed_intra_frame_qp_cycle_length;							//8 bits
	uint8 claimed_intra_frame_qp_cycle_offset;							//8 bits
	uint16 claimed_intra_frame_qp_cycle_frame_bitmap;						//16 bits
	uint8 claimed_intra_frame_qp_duration;								//8 bits
		
	uint8 sync_counter_for_intra_frame_qp_rate;							//8 bits
	uint8 sync_counter_for_intra_frame_qp_duration;						//8 bits
		
	uint4 inter_frame_qp_duration;										//4 bits
	uint12 inter_frame_qp_offset;											//12 bits
		
	uint8 scw_cycle_length;												//8 bits
	uint8 scw_cycle_offset;												//8 bits
	uint32 scw_cycle_frame_bitmap;										//32 bits
		
	uint6 current_ds_us_split;											//6 bits
	uint6 claimed_ds_us_split;											//6 bits
	uint12 ds_us_change_offset;											//12 bits
		
	uint32 incumbent_detection_timer;										//32 bits
	uint8 hcs;															//8 bits
		
		
		
		

	
	uint8 generateHCS( bitset<312> n )
	{
		
		int most_sig_bit,i;
		bitset<312> m ;
		bitset<312>devident = n;
		devident<<=8 ;                        //  remove this step in checkHCS;
		bitset<312>devisor (263);
		
		for(i=311;i>=0;i--)
		{
			if(devident[i]==1)
			{
				most_sig_bit = i;
				break;
			}
		}
		
		while(most_sig_bit > 7)
		{

			m = devisor << (most_sig_bit - 8);
		
			devident = devident ^ m;
			most_sig_bit = 0;
			for(i=311;i>=0;i--)
			{
				if(devident[i]==1)
				{
					most_sig_bit = i;
					break;
				}
			}
		
		}
	
		string s = devident.to_string();
		bitset<8> ans (s,304,8);
		return ans;
	}
		
		
		
		
	/*bitset<8> checkHCS( bitset<312> n )
	{
		int most_sig_bit,i ;
		bitset<312> m ;
		bitset<312>devident = n;

		bitset<312>devisor = 263;
		
		for(i=311;i>=0;i--)
		{
			if(devident[i]==1)
			{
				most_sig_bit = i;
				break;
			}
		}

		while(most_sig_bit > 7)
		{

			m = devisor << (most_sig_bit - 8);
		
			devident = devident ^ m;

			most_sig_bit = 0;
			for(i=311;i>=0;i--)
			{
				if(devident[i]==1)
				{
					most_sig_bit = i;
					break;
				}

			}
			
		
		}
	
		string s = devident.to_string();
		bitset<8> ans (s,304,8);
		cout<<"ans="<<ans<<endl;
	}*/
		

		
	
	void convert2binary(string &c, string &c_without_spaces, uint48 target,unsigned int size)				//convert target int(decimal) to binary(in string c)
	{
		c = c + target.to_string().substr( 48-size, size) + " ";
		c_without_spaces = c_without_spaces + target.to_string().substr( 48-size, size);
		
		//c = c + target.to_string().substr(48-size,size) + " ";					//to print fields with space in b/w
		/*unsigned long long int y = pow(2, size-1);
		for(unsigned int i = size-1; i>= 0 ;i--)
		{
			if((target.to_ullong()) & y)							//check ith bit of mac header field 
			{
				c = c + "1";
			}
			else
			{
				c = c + "0";
			}
			y = y/2;
			cout<<y<<endl;
		}*/
	}	
		
		
		
		
		
		
	public:sch(uint48 bs_id_in, string &c, string &c_without_spaces)
	{
			
		bs_id = bs_id_in;
		frame_allocation_map = 65535;
		superframe_number = (superframe_number.to_ullong() + 1) % 256;
		cyclic_prefix = 0;
		fch_encoding_flag = 3;
		sc_capablity_ind = 0;
		mac_version = 1;
			
		current_intra_frame_qp_cycle_length = 0;
		current_intra_frame_qp_cycle_offset = 0;
		current_intra_frame_qp_cycle_frame_bitmap = 0;
		current_intra_frame_qp_duration = 0;
		
		claimed_intra_frame_qp_cycle_length = 0;
		claimed_intra_frame_qp_cycle_offset = 0;
		claimed_intra_frame_qp_cycle_frame_bitmap = 0;
		claimed_intra_frame_qp_duration = 0;
		
		sync_counter_for_intra_frame_qp_rate = 0;
		sync_counter_for_intra_frame_qp_duration = 0;
	
		inter_frame_qp_duration = 0;
		inter_frame_qp_offset = 0;
		
		scw_cycle_length = 0;
		scw_cycle_offset = 0;
		scw_cycle_frame_bitmap = 0;
		
		current_ds_us_split = 0;
		claimed_ds_us_split = 0;
		ds_us_change_offset = 0;
		
		incumbent_detection_timer = 0;
		
		get_all_fields_in_binary(c, c_without_spaces);
		uint312 sch_val_without_hcs ( c_without_spaces );
		
		//hcs=0;
		hcs = generateHCS (sch_val_without_hcs);			//calculate hcs
		//uint312 sch_with_hcs(c_without_spaces+hcs.to_string());
		//checkHCS(sch_with_hcs);
		
		
			
	}
	
	
	
	
	
	void get_all_fields_in_binary(string &c, string &c_without_spaces)
	{
		c = "";	
		c_without_spaces = "";
		convert2binary (c, c_without_spaces, bs_id.to_ullong(), 48);
		convert2binary (c, c_without_spaces, frame_allocation_map.to_ullong(), 16);
		convert2binary (c, c_without_spaces, superframe_number.to_ullong(), 8);
		convert2binary (c, c_without_spaces, cyclic_prefix.to_ullong(), 2);
		convert2binary (c, c_without_spaces, fch_encoding_flag.to_ullong(), 2);
		convert2binary (c, c_without_spaces, sc_capablity_ind.to_ullong(), 4);
		convert2binary (c, c_without_spaces, mac_version.to_ullong(), 8);
		convert2binary (c, c_without_spaces, current_intra_frame_qp_cycle_length.to_ullong(), 8);
		convert2binary (c, c_without_spaces, current_intra_frame_qp_cycle_offset.to_ullong(), 8);
		convert2binary (c, c_without_spaces, current_intra_frame_qp_cycle_frame_bitmap.to_ullong(), 16);
		convert2binary (c, c_without_spaces, claimed_intra_frame_qp_duration.to_ullong(), 8);
		convert2binary (c, c_without_spaces, claimed_intra_frame_qp_cycle_length.to_ullong(), 8);
		convert2binary (c, c_without_spaces, claimed_intra_frame_qp_cycle_offset.to_ullong(), 8);
		convert2binary (c, c_without_spaces, claimed_intra_frame_qp_cycle_frame_bitmap.to_ullong(), 16);
		convert2binary (c, c_without_spaces, claimed_intra_frame_qp_duration.to_ullong(), 8);
		convert2binary (c, c_without_spaces, sync_counter_for_intra_frame_qp_rate.to_ullong(), 8);
		convert2binary (c, c_without_spaces, sync_counter_for_intra_frame_qp_duration.to_ullong(), 8);
		convert2binary (c, c_without_spaces, inter_frame_qp_duration.to_ullong(), 4);
		convert2binary (c, c_without_spaces, inter_frame_qp_offset.to_ullong(), 12);
		convert2binary (c, c_without_spaces, scw_cycle_length.to_ullong(), 8);
		convert2binary (c, c_without_spaces, scw_cycle_offset.to_ullong(), 8);
		convert2binary (c, c_without_spaces, scw_cycle_frame_bitmap.to_ullong(), 32);
		convert2binary (c, c_without_spaces, current_ds_us_split.to_ullong(), 6);
		convert2binary (c, c_without_spaces, claimed_ds_us_split.to_ullong(), 6);
		convert2binary (c, c_without_spaces, ds_us_change_offset.to_ullong(), 12);
		convert2binary (c, c_without_spaces, incumbent_detection_timer.to_ullong(), 32);		
		
		
		
	
	}
	
	void get_header_in_binary(string &c, string &c_without_spaces)
	{
		//all fields except hcs have already been added to c (when constructor called get_all_fields_in_binary())
		convert2binary (c, c_without_spaces, hcs.to_ullong(), 8);
		c = c + " ";
		
		string padding( 48, '0');
		c = c + padding;  					//add padding to header	
		c_without_spaces = c_without_spaces + padding;			
	}
	
	
	
	
	
};
uint8 sch::superframe_number=0;
