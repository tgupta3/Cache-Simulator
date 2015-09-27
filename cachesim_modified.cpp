#include<iostream>
#include<string>

//! Don't include whole namespace, instead use std::cout where ever neccessary
using namespace std;

int N;




//! Class for a set in a cache
class cache_set {
	public:
	int TAGSIZE;
	char TAG[BLOCK_NUM][TAGSIZE];
	bool valid[BLOCK_NUM];
	bool dirty[BLOCK_NUM];
	int LRU[BLOCK_NUM];
				
	cache_set(int BLOCK_NUM,int TAGSIZE1) {
		TAGSIZE=TAGSIZE1;
		for(int i = 0; i < BLOCK_NUM; i++) {
			valid[i] = false;
			dirty[i] = false;
			LRU[i] = 0;
		}
	} 
		
};

class cache_e {
public:
	int cache_size;
	cache_set cacheset[;	
	
	cache_e(int SET_NO) {
		cacheset = new cache_set[SET_NO];
		cache_size=SET_NO;
	}	
};
  
int main(int argc, char* argv[]) {
	if(argc != 8) {
		cout << "Incorrect arguments, Exiting" << endl;
		return 0;
	} else {
		cout << "No of arguments is "<< argc << endl;
	}

	cache_e cache[10]={0,0,0,0,0,0,0,0,0,0};
		
	for(int i = 0; i < 10; i++) {
		
		cache[i].cacheset[i].LRU[BLOCK_NUM]=i;
	}
for(int i = 0; i < 10; i++) {
		
		cout<<cache[i].cacheset[i].LRU[BLOCK_NUM]<<endl;
	}

	
	return 0;
}
