#include<iostream>
#include<string>
#include<cmath>
#include<bitset>
using namespace std;

typedef bitset<6> uint6;
typedef bitset<10> uint10;
typedef bitset<8> uint8;
typedef bitset<24> uint24;

class fch
{
	uint6 length_frame;			//6 bits
	uint10 length_map_msg;		//10 bits
	uint8 hcs;				//8 bits
	
	
	
	

	bitset<8> generateHCS( bitset<24> n )
	{
		
		int most_sig_bit,i;
		bitset<24> m ;
		bitset<24>devident = n;
		devident<<=8 ;                        //  remove this step in checkHCS;
		bitset<24>devisor (263);
		
		for(i=23;i>=0;i--)
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
			for(i=23;i>=0;i--)
			{
				if(devident[i]==1)
				{
					most_sig_bit = i;
					break;
				}
			}
		
		}
	
		string s = devident.to_string();
		bitset<8> ans (s,16,8);
		return ans;
	}

	
	
	
	
	
	/*bitset<8> checkHCS( bitset<24> n )
	{
		int most_sig_bit,i ;
		bitset<24> m ;
		bitset<24>devident = n;

		bitset<24>devisor = 263;
		
		for(i=23;i>=0;i--)
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
			for(i=23;i>=0;i--)
			{
				if(devident[i]==1)
				{
					most_sig_bit = i;
					break;
				}

			}
			
		
		}
	
		string s = devident.to_string();
		bitset<8> ans (s,16,8);
		cout<< ans;
		//return 0;
	}
	
	
	
		void convert2binary(string &c, string &c_without_spaces, uint10 target, int size)				//convert target int(decimal) to binary(in string c)
	{
		c = c + target.to_string().substr( 10-size, size) + " ";
		c_without_spaces = c_without_spaces + target.to_string().substr( 10-size, size);
		
		/*c = c + " ";
		long long int y = pow(2, size-1);
		for(int i = size-1; i>= 0 ;i--)
		{
			if((*target) & y)							//check ith bit of mac header field 
			{
				c = c + "1";
			}
			else
			{
				c = c + "0";
			}
			y = y/2;
		}
	}*/
	
	
	
	
	
	
	
	public:fch(unsigned long long int cpe_no)
	{
		length_frame = 26;
		double no_sub_carriers = (30 * cpe_no + 28) * 2; 
		length_map_msg = ceil(no_sub_carriers / 48);
		
		//cout<<no_sub_carriers;
		unsigned long long int hcs_dec;
		uint24 fch_without_hcs( (length_frame.to_ullong())*pow(2,10) + length_map_msg.to_ullong() );
		hcs = generateHCS( fch_without_hcs );
		
	//	uint24 fch_with_hcs( length_frame.to_string() + length_map_msg.to_string() + hcs.to_string() );
	//	checkHCS( fch_with_hcs);
	}
	
	
	
	
	
	
	/*fch(uint_8 length_frame_in,uint_16 length_map_msg_in)
	{
		length_frame = length_frame_in;
		length_map_msg = length_map_msg_in;
		
		unsigned long long int hcs_dec;
		
		hcs_dec = length_frame*pow(2,10) + length_map_msg;
		hcs = generateHCS(hcs_dec);	
		
	}
	
	
	
	
	
	void get_all_fields_in_binary(string &s)
	{
		convert2binary( s,(int*) &length_frame,6 );
		convert2binary( s,(int*) &length_map_msg,10 );
		convert2binary( s,(int*) &hcs,8 );
	}*/
	
	
	void get_header_in_binary(string &c, string &c_without_spaces)
	{
		c= length_frame.to_string() + " " + length_map_msg.to_string() + " " + hcs.to_string();
	
		c_without_spaces = length_frame.to_string() + length_map_msg.to_string() + hcs.to_string();
	
	}
	
	/*unsigned long long int output_fch_value()
	{
		unsigned long long int fch_value = hcs + length_map_msg * 256 + length_frame*pow(2,18);
		
		return fch_value;
	}*/
	
	
	
	
	
	
	/*void print_fch_fields()
	{
		cout<<"length frame = "<<(int)length_frame<<"\nlength map msg = "<<(int)length_map_msg<<"\nhcs = "<<(int)hcs;
	}*/
		
};



