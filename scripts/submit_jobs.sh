#!/bin/bash

HOME=`pwd`
TRACE_DIR="/home/bsc/bsc018186/romol/ChampSim/branch_traces"
RESULTS_DIR=${HOME}/dump

BENCHSUITE=$1 
BPRED=$2

source ${HOME}/scripts/benchmarks_all.sh

#for trace in $TRACES; do
for bench in $BENCHMARKS; do
#  export suffix=.champsimtrace.xz 
#  export bench=${trace%$suffix}
	OLDIFS="$IFS"
	IFS='-' tokens=( ${bench} )
	bench_dir=${tokens[0]}
	IFS="$OLDIFS" # restore IFS

echo "#!/bin/bash
#SBATCH -N 1
##SBATCH -n 1
##SBATCH -c 12
##SBATCH -c 48
#SBATCH -o ${HOME}/dump/${bench}_${BPRED}_run.out 
#SBATCH -J chmpS_${bench}_${BPRED}_run
#SBATCH --time=01:00:00 
##SBATCH --constraint=highmem
#SBATCH -A bsc18
#SBATCH --qos=gp_bsccs
##SBATCH --qos=gp_debug

python3 ./naive_sim.py --input-trace ${TRACE_DIR}/${bench_dir}/${bench}.jsonl --bpred ${BPRED}

" >	simr_${bench}_job.run
		sbatch simr_${bench}_job.run
		#chmod +x simt_${bench}_job.run
		#./simt_${bench}_job.run
		rm simr_${bench}_job.run
done

