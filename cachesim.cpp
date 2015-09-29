#include<iostream>
#include<string>
#include<vector>
#include<cstring>
#include<stdlib.h>
#include<fstream>
#include<sstream>
#include<bitset>
#include<math.h>
#include<algorithm>
#include <cstddef> 
#include<iterator>


using namespace std;


//#define BLOCK_NUM 32
//#define TAGSIZE 16
//#define C_NUM 2
int C_NUM=2;
int memory_traffic=0;

struct cache_params{
int SIZE,BLOCKSIZE,ASSOC,SET_NO,TAG_SIZE,INDEX_SIZE,BLOCK_OFFSET_BITS;
				int READS,READS_MISSES,WRITE,WRITES_MISSES,SWAP_REQUEST;
				int SWAP_RATE,SWAP_NO;
				
};

vector<cache_params> cachep;
cache_params victimp[2];

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

class victim_cache{
			public:
					cache_set vitcimset;
};

  
vector<cache_e> cache;
victim_cache victim[2];


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
int bin2dec(string);
int read_request(string,int);
void write_request(string,int);

void write_request(string write_addr,int cache_no)
{
	string TAG;
	string INDEX;
	int INDEX1;
	int LRU_replace;
	bool dirty_replace;
	string rep_addr;
	int hit;
	
	cachep[cache_no].WRITE++;
	
	write_addr=hex2bin(write_addr);
	TAG=write_addr.substr(0,(write_addr.length()-cachep[cache_no].INDEX_SIZE-cachep[cache_no].BLOCK_OFFSET_BITS));
	INDEX=write_addr.substr(TAG.length(),cachep[cache_no].INDEX_SIZE);
	
	TAG=bin2hex(TAG);
	INDEX1=bin2dec(INDEX);
	
	//assoc will give the block number of the valid bit, which is false
	int assoc=find(cache[cache_no].cacheset[INDEX1].valid.begin(),cache[cache_no].cacheset[INDEX1].valid.end(),false)-cache[cache_no].cacheset[INDEX1].valid.begin();
	if(assoc>=cache[cache_no].cacheset[INDEX1].valid.size())   //set is full
			{
				//find if address block already exist in cache
				int TAG_match=find(cache[cache_no].cacheset[INDEX1].TAG.begin(),cache[cache_no].cacheset[INDEX1].TAG.end(),TAG)-cache[cache_no].cacheset[INDEX1].TAG.begin();
				if(TAG_match>=cache[cache_no].cacheset[INDEX1].TAG.size())  //Not in set& set is full																												 }
				{
						cachep[cache_no].WRITES_MISSES++;
						LRU_replace=distance(cache[cache_no].cacheset[INDEX1].LRU.begin(),max_element(cache[cache_no].cacheset[INDEX1].LRU.begin(),cache[cache_no].cacheset[INDEX1].LRU.end()));
						dirty_replace=cache[cache_no].cacheset[INDEX1].dirty[LRU_replace];
						cout<<"Write request,Set full,but dont have tag "<<bin2hex(write_addr)<<" Cache No : "<<cache_no<<endl;
						if(dirty_replace==true)    //perform a write request to next level
 						   {
							/*if(cache[cache_no].cacheset[INDEX1].TAG[LRU_replace].length()==8)
								rep_addr.append(hex2bin(cache[cache_no].cacheset[INDEX1].TAG[LRU_replace].substr(2)));
							else*/
							rep_addr.append(hex2bin(cache[cache_no].cacheset[INDEX1].TAG[LRU_replace]));
							
							cout<<rep_addr<<endl;
							rep_addr.append(INDEX);
							cout<<' ' <<INDEX<<endl;
							
							rep_addr.append(cachep[cache_no].BLOCK_OFFSET_BITS,'0');//add random block bits
							
							
							rep_addr=rep_addr.substr(rep_addr.length()-32);
							rep_addr=bin2hex(rep_addr);
							cout<<rep_addr<<endl;
				
							cache[cache_no].cacheset[INDEX1].dirty[LRU_replace]=false;
							cout<<"performing write to next level coz dirty bit"<<endl;
							if(cache_no!=C_NUM-1)//check if it's not  the last cache
							{	
							write_request(rep_addr,(cache_no+1));    
							}
							else
							{	
								memory_traffic++;
							}	
							}
						
							if(cache_no!=C_NUM-1)//check if it's not the last cache
							{
							hit=read_request(bin2hex(write_addr),(cache_no+1));
							}
							
							else
							{
								memory_traffic++;
							}
					
							cache[cache_no].cacheset[INDEX1].dirty[LRU_replace]=true;
							cache[cache_no].cacheset[INDEX1].valid[LRU_replace]=true;
							cache[cache_no].cacheset[INDEX1].TAG[LRU_replace]=TAG;
							cache[cache_no].cacheset[INDEX1].LRU[LRU_replace]=0;
							for(int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
							{
								if(cache[cache_no].cacheset[INDEX1].valid[i]==true&&(i!=LRU_replace))
								{
									cache[cache_no].cacheset[INDEX1].LRU[i]++;
								}	
							}	
					
				}
				
				else   //In set, set is full
				{
					cout<<"Write request,Set full,but have tag "<<bin2hex(write_addr)<<" Cache No : "<<cache_no<<endl;
					cache[cache_no].cacheset[INDEX1].dirty[TAG_match]=true;
					cache[cache_no].cacheset[INDEX1].valid[TAG_match]=true;
					cache[cache_no].cacheset[INDEX1].TAG[TAG_match]=TAG;
					for(int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
					{
						if(cache[cache_no].cacheset[INDEX1].LRU[i]<cache[cache_no].cacheset[INDEX1].LRU[TAG_match])
							cache[cache_no].cacheset[INDEX1].LRU[i]++;
					}	
					
				cache[cache_no].cacheset[INDEX1].LRU[TAG_match]=0;	
					
				}
				
				
				
				
				}	
	else  //set is not full
	{
		int TAG_match=find(cache[cache_no].cacheset[INDEX1].TAG.begin(),cache[cache_no].cacheset[INDEX1].TAG.end(),TAG)-cache[cache_no].cacheset[INDEX1].TAG.begin();
		if(TAG_match>=cache[cache_no].cacheset[INDEX1].TAG.size()) //set is not full,and doesn't have the particular element
		{
			cachep[cache_no].WRITES_MISSES++;
			cout<<"Write request,Set not full,but doesn't have tag "<<bin2hex(write_addr)<<" Cache No : "<<cache_no<<endl;
			if(cache_no!=C_NUM-1)//check if it's the last cache
			{	
			cout<<"reading from catch "<<cache_no+1<<endl;
			hit=read_request(bin2hex(write_addr),(cache_no+1));
			}
			
			else
			{
				memory_traffic++;
			}	
			cache[cache_no].cacheset[INDEX1].dirty[assoc]=true;
			cache[cache_no].cacheset[INDEX1].valid[assoc]=true;
			cache[cache_no].cacheset[INDEX1].TAG[assoc]=TAG;
			cache[cache_no].cacheset[INDEX1].LRU[assoc]=0;
			for(int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
			{
				if(cache[cache_no].cacheset[INDEX1].valid[i]==true&&(i!=assoc))
					cache[cache_no].cacheset[INDEX1].LRU[i]++;
			}	
		
				
		}		
		
		else //set is not full and have a particular element
		
		{
					cout<<"Write request,Set not full,but have tag "<<bin2hex(write_addr)<<" Cache No : "<<cache_no<<endl;
					cache[cache_no].cacheset[INDEX1].dirty[TAG_match]=true;
					cache[cache_no].cacheset[INDEX1].valid[TAG_match]=true;
					cache[cache_no].cacheset[INDEX1].TAG[TAG_match]=TAG;	
					
			for(int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
					{
						if((cache[cache_no].cacheset[INDEX1].LRU[i]<cache[cache_no].cacheset[INDEX1].LRU[TAG_match])&&(cache[cache_no].cacheset[INDEX1].valid[i]==true))
							cache[cache_no].cacheset[INDEX1].LRU[i]++;
					}	
					cache[cache_no].cacheset[INDEX1].LRU[TAG_match]=0;	
					
		}								 					 
	}						
}





int read_request(string read_addr,int cache_no)
{
	
	cachep[cache_no].READS++;	
	
	string TAG;
	string INDEX;
	int INDEX1;
	int LRU_replace;
	bool dirty_replace;
	string rep_addr;
	int TAG_match=-1;
	int hit;
	
	
	read_addr=hex2bin(read_addr);
	TAG=read_addr.substr(0,(read_addr.length()-cachep[cache_no].INDEX_SIZE-cachep[cache_no].BLOCK_OFFSET_BITS));
	INDEX=read_addr.substr(TAG.length(),cachep[cache_no].INDEX_SIZE);
	TAG=bin2hex(TAG);
	
	INDEX1=bin2dec(INDEX);
	
	//assoc will give the block number of the valid bit, which is false
	int assoc=find(cache[cache_no].cacheset[INDEX1].valid.begin(),cache[cache_no].cacheset[INDEX1].valid.end(),false)-cache[cache_no].cacheset[INDEX1].valid.begin();
	
	for(int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
	{
		if((cache[cache_no].cacheset[INDEX1].valid[i]==true)&&(TAG==cache[cache_no].cacheset[INDEX1].TAG[i]))
		   {
			TAG_match=i;
			 break;
		   } 
	}
	
	if(TAG_match!=-1)  //Tag match
	{
		cout<<"Read request,Tag Match, Set may or may not be empty  "<<bin2hex(read_addr)<<" Cache No : "<<cache_no<<endl;
		cache[cache_no].cacheset[INDEX1].valid[TAG_match]=true;
		cache[cache_no].cacheset[INDEX1].TAG[TAG_match]=TAG;
		for(int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
					{
						if((cache[cache_no].cacheset[INDEX1].LRU[i]<cache[cache_no].cacheset[INDEX1].LRU[TAG_match])&&(cache[cache_no].cacheset[INDEX1].valid[i]==true))
							cache[cache_no].cacheset[INDEX1].LRU[i]++;
					}	
		cache[cache_no].cacheset[INDEX1].LRU[TAG_match]=0;
		
		return 1; //it's a hit
	}
	
	else//tag doesn't match
	{
		
		cachep[cache_no].READS_MISSES++;
		if(assoc>=cache[cache_no].cacheset[INDEX1].valid.size())//set is full & tag doesn'match->perform eviction
				{
						cout<<"Read request,Tag No Match, Set full "<<bin2hex(read_addr)<<" Cache No : "<<cache_no<<endl;
						LRU_replace=distance(cache[cache_no].cacheset[INDEX1].LRU.begin(),max_element(cache[cache_no].cacheset[INDEX1].LRU.begin(),cache[cache_no].cacheset[INDEX1].LRU.end()));
						dirty_replace=cache[cache_no].cacheset[INDEX1].dirty[LRU_replace];
						
						if(dirty_replace==true)    //perform a write request to next level
 						   {
							//if(cache[cache_no].cacheset[INDEX1].TAG[LRU_replace].length()==8)
							//rep_addr.append((cache[cache_no].cacheset[INDEX1].TAG[LRU_replace].substr(2)));
						         //}						
							//else
							rep_addr.append(hex2bin(cache[cache_no].cacheset[INDEX1].TAG[LRU_replace]));				
							cout<<hex2bin(rep_addr)<<endl;
							
					        rep_addr.append(INDEX);
							
							cout<<"   "<<INDEX<<endl;
							rep_addr.append(cachep[cache_no].BLOCK_OFFSET_BITS,'0');//add random block bits
							rep_addr=rep_addr.substr(rep_addr.length()-32);
							cout<<rep_addr<<endl;
							rep_addr=bin2hex(rep_addr);
							cout<<rep_addr<<endl;
							
							cache[cache_no].cacheset[INDEX1].dirty[LRU_replace]=false;
							if(cache_no!=C_NUM-1)//check if it's the last cache
							{
								
								write_request(rep_addr,(cache_no+1));
							}
							else
							{
								memory_traffic++;
							}
						    }
							
							if(cache_no!=C_NUM-1)
							{//check if it's not the last cache
							
							hit=read_request(bin2hex(read_addr), (cache_no+1));
							}
							else
							{
								memory_traffic++;
							}	
							cache[cache_no].cacheset[INDEX1].dirty[LRU_replace]=false;
							cache[cache_no].cacheset[INDEX1].valid[LRU_replace]=true;
							cache[cache_no].cacheset[INDEX1].TAG[LRU_replace]=TAG;
							cache[cache_no].cacheset[INDEX1].LRU[LRU_replace]=0;
							for(int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
							{
								if(cache[cache_no].cacheset[INDEX1].valid[i]==true&&(i!=LRU_replace))
								{
									cache[cache_no].cacheset[INDEX1].LRU[i]++;
								}	
							}
			  	 
				return 1;		
		    }
		else //tag doesn't match and there is space
			{
					cout<<"Read request,Tag No Match, Set Space "<<bin2hex(read_addr)<<" Cache No : "<<cache_no<<endl;	
				if(cache_no!=C_NUM-1)//check if it's the last cache
					{	
						cout<<"Sending read request "<<endl;
						hit=read_request(bin2hex(read_addr),(cache_no+1));
					}
				else
				{
					memory_traffic++;
				}
			
					cache[cache_no].cacheset[INDEX1].dirty[assoc]=false;
					cache[cache_no].cacheset[INDEX1].valid[assoc]=true;
					cache[cache_no].cacheset[INDEX1].TAG[assoc]=TAG;
					cache[cache_no].cacheset[INDEX1].LRU[assoc]=0;
			for(int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
			{
				if(cache[cache_no].cacheset[INDEX1].valid[i]==true&&(i!=assoc))
					cache[cache_no].cacheset[INDEX1].LRU[i]++;
			}	
				
		
		
	
		return 1;
		
		}
		
	
}
}
	
	
				
			

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
		
		victimp[0].BLOCKSIZE=atoi(argv[1]);
		victimp[1].BLOCKSIZE=0;
		victimp[0].ASSOC=atoi(argv[4]);
		victimp[1].ASSOC=0;
		
		cachep.resize(C_NUM);
		
		for(int i=0;i<C_NUM;i++)
		{
				
				cachep[i].BLOCKSIZE=atoi(argv[1]);
				cachep[i].SIZE=atoi(argv[(3*i)+2]);
				cachep[i].ASSOC=atoi(argv[(3*i)+3]);
				cachep[i].SET_NO=cachep[i].SIZE/(cachep[i].BLOCKSIZE*cachep[i].ASSOC);
				cachep[i].INDEX_SIZE=log2(cachep[i].SET_NO);
				cachep[i].BLOCK_OFFSET_BITS=log2 (cachep[i].BLOCKSIZE);
				cachep[i].READS=0;
				cachep[i].READS_MISSES=0;
				cachep[i].WRITE=0;
				cachep[i].WRITES_MISSES=0;
				
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
			//cout<<cachep[i].SET_NO<<endl;
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
					//cout<<cache[i].cacheset[j].LRU.size()<<endl;
			    }
			}
	
	caches_init();
	
	int hit;
	ifstream trace_file(argv[7]);
	string linebuffer;
	string rw;
	

	while(trace_file && getline(trace_file, linebuffer)){
		
		if(linebuffer.length()==0) continue;
  		rw=linebuffer.substr(0,1);
		linebuffer=trace_address(linebuffer.substr(2));
		if(rw[0]=='w')
		{
			cout<<"Sending write request to cache0 for Address "<<linebuffer<<endl;
			
			write_request(linebuffer,0);
		}
		if(rw[0]=='r')
		{	
			cout<<"Sending read request to cache0 for Address "<<linebuffer<<endl;
			
			hit=read_request(linebuffer,0);
		}
		//write_request(linebuffer,1);
		
		
		//cout<<linebuffer<<endl;
	}
	
		
	for(int i=0;i<C_NUM;i++)
	{
		for(int j=0;j<cachep[i].SET_NO;j++)
		{
			cout<<"SET "<<j<<"     ";
			for(int k=0;k<cachep[i].ASSOC;k++)
			{
				cout<<"   "<<cache[i].cacheset[j].TAG[k];
				if(cache[i].cacheset[j].dirty[k]==true)
					cout<<"  D";
			} 
			cout<<endl;
		} }
	
	
	for(int i=0;i<C_NUM;i++)
	{
		cout<<"Read request: "<<cachep[i].READS<<endl;
		cout<<"Write request: "<<cachep[i].WRITE<<endl;
		cout<<"Read misses: "<<cachep[i].READS_MISSES<<endl;
		cout<<"Write misses: "<<cachep[i].WRITES_MISSES<<endl;
	}	
	
	cout<<"Memory traffic "<<memory_traffic<<endl;
	
	
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
	//address_hex1=trace_address(address_hex.str());
	return address_hex.str();
}


int bin2dec(string addre_binary)
{
	unsigned int value;
	//value=stoull(addre_binary,0,2);
	bitset<64> set(addre_binary);
	value=set.to_ulong();
	return value;
}
		
	
	


				
				
				
