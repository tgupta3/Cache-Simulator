#include<iostream>
#include<string>
#include<vector>
#include<cstring>
#include<stdlib.h>
#include <fstream>
#include<sstream>
#include<bitset>
#include<math.h>


using namespace std;

int N=5;
//#define BLOCK_NUM 32
//#define TAGSIZE 16
//#define C_NUM 2
int C_NUM=2;

struct cache_params{
int SIZE,BLOCKSIZE,ASSOC,SET_NO,TAG_SIZE,INDEX_SIZE,BLOCK_OFFSET_BITS;
				int READS,READS_MISSES,WRITE,WRITES_MISSES,SWAP_REQUEST;
				int SWAP_RATE,SWAP_NO;
				
};

vector<cache_params> cachep;
//class for a set in a cache
class cache_set{
			public:
				
	
				vector<string> TAG;
				vector<bool> valid;
				vector<bool> dirty;
				vector<int> LRU;
				
		
};

class cache_e{
		public:
				vector<cache_set> cacheset;
					
			};
  
vector<cache_e> cache;


void caches_init()
{
	for(int i=0;i<C_NUM;i++)
	{
		for(int j=0;j<cachep[i].SET_NO;j++)
		{
			for(int k=0;k<cachep[i].ASSOC;k++)
			{
				cache[i].cacheset[j].TAG[k]='x';
				cache[i].cacheset[j].LRU[k]=0;
				cache[i].cacheset[j].valid[k]=false;
				cache[i].cacheset[j].dirty[k]=false;
			}
		}
	}
	/*for(int i=0;i<C_NUM;i++)
	{
		for(int j=0;j<cachep[i].SET_NO;j++)
		{
			for(int k=0;k<cachep[i].ASSOC;k++)
			{
				cout<<cache[i].cacheset[j].TAG[k]<<cache[i].cacheset[j].LRU[k]<<cache[i].cacheset[j].valid[k]<<cache[i].cacheset[j].dirty[k]<<endl;
			} } }*/
	
	}

string trace_address(string);
string hex2bin(string);
string bin2hex(string);


				



int main(int argc, char* argv[])
{
	if(argc!=8)
	{
		cout<<"Incorrect arguments, Exiting"<<endl;
		return 0;
	}
	else
		cout<<"No of arguments is "<<argc<<endl;
	
		if(atoi(argv[5])==0)
		   C_NUM=1;
	
		cachep.resize(C_NUM);
		for(int i=0;i<C_NUM;i++)
		{
				cachep[i].BLOCKSIZE=atoi(argv[1]);
				cachep[i].SIZE=atoi(argv[(3*i)+2]);
				cachep[i].ASSOC=atoi(argv[(3*i)+3]);
				cachep[i].SET_NO=cachep[i].SIZE/(cachep[i].BLOCKSIZE*cachep[i].ASSOC);
				cachep[i].INDEX_SIZE=log2(cachep[i].SET_NO);
				cachep[i].BLOCK_OFFSET_BITS=log2 (cachep[i].BLOCKSIZE);
				
		}
	
		
		for(int i=0;i<C_NUM;i++)
		{
				cout<<cachep[i].BLOCKSIZE<<endl;
				cout<<cachep[i].SIZE<<endl;
				cout<<cachep[i].ASSOC<<endl;
				cout<<cachep[i].SET_NO<<endl;
				cout<<cachep[i].INDEX_SIZE<<endl;
				cout<<cachep[i].BLOCK_OFFSET_BITS<<endl;
				
		}
		
	
		cache.resize(C_NUM);
	
		for(int i=0;i<C_NUM;i++)
		{
			cout<<cachep[i].SET_NO<<endl;
			cache[i].cacheset.resize(cachep[i].SET_NO);
			
		}
	
	
	for(int i=0;i<C_NUM;i++)
	{
			for(int j=0;j<cachep[i].SET_NO;j++)
				{
					cache[i].cacheset[j].TAG.resize(cachep[i].ASSOC);  
					cache[i].cacheset[j].LRU.resize(cachep[i].ASSOC);
					cache[i].cacheset[j].valid.resize(cachep[i].ASSOC);
					cache[i].cacheset[j].dirty.resize(cachep[i].ASSOC);
					cout<<cache[i].cacheset[j].LRU.size()<<endl;}
			}
	
	caches_init();
	
	
	ifstream trace_file(argv[7]);
	string linebuffer;
	while(trace_file && getline(trace_file, linebuffer)){
		
		if(linebuffer.length()==0) continue;
  		linebuffer=trace_address(linebuffer.substr(2));
		linebuffer=hex2bin(linebuffer);
		
		linebuffer=bin2hex(linebuffer);
		cout<<linebuffer<<endl;
	}
	
		
				
		
		
	
	
	return 0;
}

string trace_address(string line_elem)
{
	int len;
	len=line_elem.length();
	string addre=line_elem;
	string addre_new;
	if(addre.length()<8)
	{
		addre_new.append(8-(addre.length()),'0');
		addre_new.append(addre);
		return addre_new;
	}
	else
		return addre;
}

string hex2bin(string addre_hex)
{
	
	int addre_bin;
	istringstream st(addre_hex);
	st>>hex>>addre_bin;;
	
	bitset<32> bits(addre_bin);
	
	string address_binary(bits.to_string());
	return address_binary;
	
}	

string bin2hex(string addre_binary)
{
	bitset<32> set(addre_binary);
	stringstream address_hex;
	string address_hex1;
	address_hex << hex<< set.to_ulong();
	address_hex1=trace_address(address_hex.str());
	return address_hex1;
}


		
		
	
	


				
				
				
