#!/usr/bin/python3

"""
__name__ = naive_sim.py
__author__ = Dimitrios Chasapis 
__description = Very simple simulator that reads traces file by file and invokes the branch predictor
"""

import argparse	
import branch_predictor as bp

## function declarations
def open_trace(filename):
    return open(filename, 'r')
#end of open_trace  

def run_simulation(trace_file, bpred):
    lines_read = 0
    total_predictions = 0
    correct_predictions = 0
    for line in trace_file:
        line = line.strip('\n').strip('{').strip('}')
        line = line.split(',')
        ip = int(line[0].split(':')[1].strip('""')) #FIXME: need to change to int64
        branch_type = int(line[1].split(':')[1].strip('""'))
        branch_outcome = int(line[2].split(':')[1].strip('""'))
        print("branch_type:" + str(branch_type))
        #TODO: need to keep track of histories as well        
        prediction = bpred.predict(ip)
        bpred.update(ip, branch_type, branch_outcome, prediction, 0) 
        exit()
        #FIXME: check if any predictor acutally needs target
        if (int(prediction) == int(branch_outcome)):
            correct_predictions += 1
        total_predictions += 1

        #lines_read += 1
        #if (lines_read >= 10): break

    accuracy = ((100 * correct_predictions) / total_predictions)
    return accuracy
#end of run_simulation

            
### argument parser setup
parser = argparse.ArgumentParser()
parser.add_argument('--input-trace', dest='input_trace', required=True, help="Trace file to read.") 
parser.add_argument('--bpred', dest='bpred', required=False, default='GShare', help="Name of the branch predictor to use.") 

### MAIN ###
args = parser.parse_args()

trace_file = open_trace(args.input_trace)
bpred = bp.create_branch_predictor(args.bpred)
accuracy = run_simulation(trace_file, bpred)

print("Trace finished.")
print("Branch predictor " + args.bpred + " accuracy: " + str(accuracy))
