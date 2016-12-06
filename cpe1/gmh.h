#include<string>
#include<stdint.h>
#include<cmath>
#include<iostream>
#include<bitset>
using namespace std;

typedef bitset<11> uint11;
typedef bitset<1> uint1;
typedef bitset<2> uint2;
typedef bitset<5> uint5;
typedef bitset<3> uint3;
typedef bitset<8> uint8;
typedef bitset<32> uint32;

class generic_mac_header
{
	private:uint11 length;		//11 bit
	uint1 ucs;				//1 bit
	uint1 qpa;				//1 bit
	uint1 ec;					//1 bit
	uint2 eks;				//2 bit
	uint5 type;				//5 bit
	uint3 fid;				//3 bit
	uint8 hcs;				//8 bit
	
	
	
	uint8 generateHCS( bitset<32> n )
	{
		
		int most_sig_bit,i;
		bitset<32> m ;
		bitset<32>devident = n;
		devident<<=8 ;                        //  remove this step in checkHCS;
		bitset<32>devisor (263);
		
		for(i=31;i>=0;i--)
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
			for(i=31;i>=0;i--)
			{
				if(devident[i]==1)
				{
					most_sig_bit = i;
					break;
				}
			}
		
		}
	
		string s = devident.to_string();
		bitset<8> ans (s,24,8);
		return ans;
	}
	
	
	
	
	void convert2binary(string &c, int *target, int size)				//convert target int(decimal) to binary(in string c)
	{
		c = c + " ";
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
	}
	
	
	
	 
	public:generic_mac_header(int length_in)				//default constructor
	{
		length = length_in;		//4 header 4 crc 1 payload
		ucs = 0;
		qpa = 0;
		ec = 0;
		eks = 0;
		type = 0;
		fid = 7;
		 
		unsigned long long int y = fid.to_ullong() + (type.to_ullong()) * pow(2,3) + (eks.to_ullong()) * pow(2,8);
		y = y + (ec.to_ullong()) * pow(2,10) + (qpa.to_ullong()) * pow(2,11) + (ucs.to_ullong()) * pow(2,12) + (length.to_ullong()) * pow(2,13);		//decimal value of header without hcs field
		uint32 gmh_without_hcs(y);
		hcs = generateHCS(gmh_without_hcs);			//calculate hcs
		
		
	}
	
	/*generic_mac_header(uint16_t length_in, uint8_t ucs_in, uint8_t qpa_in, uint8_t ec_in, uint8_t eks_in, uint8_t type_in, uint8_t fid_in, uint8_t hcs_in)		//parametrized costructor
	{
		length = length_in;		//4 header 4 crc 1 payload
		ucs = ucs_in;
		qpa = qpa_in;
		ec = ec_in;
		eks = eks_in;
		type = type_in;
		fid = fid_in;
		
		unsigned long long int y = fid + type*pow(2,3) + eks*pow(2,8) + ec*pow(2,10) + qpa*pow(2,11) + ucs*pow(2,12) + length*pow(2,13);		//decimal value of header without hcs field
		hcs = generateHCS(y);			//calculate hcs
		
	}
	
	
	
	void get_all_fields_in_binary(string &c)
	{
		c="";
		
		convert2binary (c, (int*) &length, 11);			//convert all mac header fields to binary form and stores in string c
		convert2binary (c, (int*) &ucs, 1);
		convert2binary (c, (int*) &qpa, 1);
		convert2binary (c, (int*) &ec, 1);
		convert2binary (c, (int*) &eks, 2);
		convert2binary (c, (int*) &type, 5);
		convert2binary (c, (int*) &fid, 3);
		convert2binary (c, (int*) &hcs, 8);
	
	}
	
	
	unsigned long long int output_mac_value()					//calculate mac header value in decimal
	{
	
		uint32_t mac_header_value = pow (2, 21 )*length + pow(2, 20)*ucs + pow(2, 19)*qpa + pow(2, 18)*ec +		//calculate decimal value of whole mac 
						 pow(2, 16)*eks + pow(2, 11)*type + pow(2, 8)*fid + hcs;							// header by aligning all fields horizontally
																																		//shown below 
	
															/*  |--------------------------------------------------------------------------------------------
															    |31 (11bits) 20 (1 bit) 19 (1 bit) 18 (1 bit) 17 (2 bit) 15 (5 bit) 10 (3 bit) 7 (8 bit) -1 |
															   |    length      ucs 		  qpa 		 ec          eks        type       fid      hcs     |
															   |--------------------------------------------------------------------------------------------|  
	
		return mac_header_value;
		
	}	*/


	/*void print_header_fields()
	{
		
		cout<<" length="<<length<<"\n ucs="<<(int)ucs<<"\n qpa="<<(int)qpa<<"\n ec="<<(int)ec<<"\n eks="<<(int)eks<<"\n type="<<(int)type;
		cout<<"\n fid="<<(int)fid<<"\n hcs="<<(int)hcs;			//print values of fields
	
	}*/
	
	void get_header_in_binary(string &c_without_space)
	{
		//c_without_space = length.to_string() + " " + ucs.to_string() + " " + qpa.to_string() + " " + ec.to_string() + " " + eks.to_string();
		//c_without_space = c_without_space + " " + type.to_string() + " " + fid.to_string() + " " + hcs.to_string();	
	
		c_without_space = length.to_string() + ucs.to_string() + qpa.to_string() + ec.to_string() + eks.to_string();
		c_without_space = c_without_space + type.to_string() + fid.to_string() + hcs.to_string();
	}
	
	
};

