
#include <iostream>
#include <cstdlib>
#include "tage_sc_l.h"

//BranchTracer *tracer;

class TAGE_SC_L {

	public:
		void initialize()
		{
			cpu = 0;
			std::cout << "CPU " << cpu << " TAGE-SC-L branch predictor" << std::endl;
			tage_sc_l = new PREDICTOR();
			//tracer = new BranchTracer();
		}

		uint8_t predict(uint64_t ip)
		{
			uint8_t prediction = tage_sc_l->GetPrediction(ip);
			return prediction;
		}

		void update(uint64_t ip, uint32_t branch_type,
                uint32_t taken, uint32_t prediction,
                uint64_t target)
		{
			//FIXME: opType has less types here, maybe need to take better care
			tage_sc_l->UpdatePredictor(ip, branch_type, taken, prediction, target);
		}

		void cleanup_branch_predictor() 
		{
			delete tage_sc_l;
		}

	private:
		uint32_t cpu;
		PREDICTOR* tage_sc_l;
};


extern "C" 
{
	TAGE_SC_L* create_TAGE_SC_L() 
	{ 
		return new TAGE_SC_L; 
	}
	
	void delete_TAGE_SC_L(TAGE_SC_L* tage_sc_l) 
	{
		delete tage_sc_l;
	}


	void initialize_TAGE_SC_L(TAGE_SC_L* tage_sc_l) 
	{
		tage_sc_l->initialize(); 
	}

	uint8_t predict_TAGE_SC_L(TAGE_SC_L* tage_sc_l, uint64_t ip) 
	{ 
		return tage_sc_l->predict(ip); 
	}

	void update_TAGE_SC_L(TAGE_SC_L* tage_sc_l, uint64_t ip, uint32_t branch_type, uint32_t taken,
												uint32_t predictor, uint64_t target) 
	{ 
		tage_sc_l->update(ip, branch_type, taken, predictor, target); 
	}
}


