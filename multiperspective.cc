///////////////////////////////////////////////////////////////////////
////  Copyright 2015 Samsung Austin Semiconductor, LLC.                //
/////////////////////////////////////////////////////////////////////////

#include "multiperspective.h"

class MULTIPERSPECTIVE {

	public:
		void initialize()
		{
			cpu = 0;
			std::cout << "CPU " << cpu << " Multiperspective branch predictor" << std::endl;
			predictor = new PREDICTOR();
		}

		uint8_t predict(uint64_t ip)
		{
			uint8_t prediction = predictor->GetPrediction(ip);
			return prediction;
		}

		void update(uint64_t ip, uint32_t branch_type,
                uint32_t taken, uint32_t prediction,
                uint64_t target)
		{
			//FIXME: opType has less types here, maybe need to take better care
			predictor->UpdatePredictor(ip, branch_type, taken, prediction, target);
		}

		void cleanup_branch_predictor() 
		{
			delete predictor;
		}

	private:
		uint32_t cpu;
		PREDICTOR* predictor;
};


extern "C" 
{
	MULTIPERSPECTIVE* create_MULTIPERSPECTIVE() 
	{ 
		return new MULTIPERSPECTIVE; 
	}
	
	void delete_MULTIPERSPECTIVE(MULTIPERSPECTIVE* tage_sc_l) 
	{
		delete tage_sc_l;
	}


	void initialize_MULTIPERSPECTIVE(MULTIPERSPECTIVE* tage_sc_l) 
	{
		tage_sc_l->initialize(); 
	}

	uint8_t predict_MULTIPERSPECTIVE(MULTIPERSPECTIVE* tage_sc_l, uint64_t ip) 
	{ 
		return tage_sc_l->predict(ip); 
	}

	void update_MULTIPERSPECTIVE(MULTIPERSPECTIVE* tage_sc_l, uint64_t ip, uint32_t branch_type, uint32_t taken,
												uint32_t predictor, uint64_t target) 
	{ 
		tage_sc_l->update(ip, branch_type, taken, predictor, target); 
	}
}


