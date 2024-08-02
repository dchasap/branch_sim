
#include <iostream>

#define NUM_CPUS 1
#define GLOBAL_HISTORY_LENGTH 14
#define GLOBAL_HISTORY_MASK (1 << GLOBAL_HISTORY_LENGTH) - 1
#define GS_HISTORY_TABLE_SIZE 16384

class GShare {
	
	public:

		void initialize() 
		{
				cpu = 0;
				//std::cout << "CPU " << cpu << " GSHARE branch predictor" << std::endl;

   	 		branch_history_vector[cpu] = 0;
    		my_last_prediction[cpu] = 0;

    		for(int i=0; i<GS_HISTORY_TABLE_SIZE; i++)
        gs_history_table[cpu][i] = 2; // 2 is slightly taken
		}

		uint8_t predict(uint64_t ip) 
		{
			int prediction = 1;
			int gs_hash = gs_table_hash(ip, branch_history_vector[cpu]);

    	if(gs_history_table[cpu][gs_hash] >= 2)
      	prediction = 1;
    	else
      	prediction = 0;

    	my_last_prediction[cpu] = prediction;

    	return prediction;
		}

		void update(uint64_t ip, uint8_t branch_type,
                uint8_t taken, uint8_t prediction,
                uint64_t target) 
		{
    	int gs_hash = gs_table_hash(ip, branch_history_vector[cpu]);

    	if(taken == 1) {
      	if(gs_history_table[cpu][gs_hash] < 3)
            gs_history_table[cpu][gs_hash]++;
    	} else {
        if(gs_history_table[cpu][gs_hash] > 0)
            gs_history_table[cpu][gs_hash]--;
    	}

    	// update branch history vector
    	branch_history_vector[cpu] <<= 1;
    	branch_history_vector[cpu] &= GLOBAL_HISTORY_MASK;
    	branch_history_vector[cpu] |= taken;
		}
	

	private:

		int branch_history_vector[NUM_CPUS];
		int gs_history_table[NUM_CPUS][GS_HISTORY_TABLE_SIZE];
		int my_last_prediction[NUM_CPUS];
	  int cpu;

		unsigned int gs_table_hash(uint64_t ip, int bh_vector) 
		{
			unsigned int hash = ip^(ip>>GLOBAL_HISTORY_LENGTH)^(ip>>(GLOBAL_HISTORY_LENGTH*2))^bh_vector;
    	hash = hash%GS_HISTORY_TABLE_SIZE;
			//printf("%d\n", hash);
			return hash;
		}

};


extern "C" 
{
	GShare* create_GShare() 
	{ 
		return new GShare; 
	}
	
	void delete_GShare(GShare* gshare) 
	{
		delete gshare;
	}


	void initialize_GShare(GShare* gshare) 
	{
		gshare->initialize(); 
	}

	uint8_t predict_GShare(GShare* gshare, uint64_t ip) 
	{ 
		return gshare->predict(ip); 
	}

	void update_GShare(	GShare* gshare, uint64_t ip, uint8_t branch_type, uint8_t taken,
											uint8_t predictor, uint64_t target) 
	{ 
		gshare->update(ip, branch_type, taken, predictor, target); 
	}
}


