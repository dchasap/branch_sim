
source ./scripts/spec_cpu_workloads.sh
#source ./scripts/gap_workloads.sh
#source ./scripts/qualcom_srv_workloads.sh
#source ./scripts/qualcomm_srv_workloads.sh
#source ./scripts/cloudsuite_workloads.sh
#source ./scripts/datacenter_workloads.sh

if [ "${BENCHSUITE}" == "qualcom_srv" ];then
			TRACES="${QUALCOM_SRV1} ${QUALCOM_SRV2} ${QUALCOM_SRV3}"
elif [ "${BENCHSUITE}" == "qualcom_srv1" ];then
	    TRACES="${QUALCOM_SRV1}"
elif [ "${BENCHSUITE}" == "qualcom_srv2" ];then
			TRACES="${QUALCOM_SRV2}"
elif [ "${BENCHSUITE}" == "qualcom_srv3" ];then
			TRACES="${QUALCOM_SRV3}"
elif [ "${BENCHSUITE}" == "selected_qualcom_srv"  ]; then
			TRACES="${SELECTED_QUALCOM_SRV}"
elif [ "${BENCHSUITE}" == "top10_qualcom_srv"  ]; then
			TRACES="${TOP_QUALCOM_SRV}"
elif [ "${BENCHSUITE}" == "smt_qualcom_srv"  ]; then
			TRACES="${SMT_QUALCOM_SRV}"
elif [ "${BENCHSUITE}" == "qualcomm_srv_ap"  ]; then
			TRACES="${QUALCOMM_SRV_AP}"
elif [ "${BENCHSUITE}" == "selected_qualcomm_srv_ap"  ]; then
			TRACES="${SELECTED_QUALCOMM_SRV_AP}"
elif [ "${BENCHSUITE}" == "smt_qualcomm_srv_ap"  ]; then
			TRACES="${SMT_QUALCOMM_SRV_AP}"
elif [ "${BENCHSUITE}" == "cloudsuite"  ]; then
			TRACES="${CLOUDSUITE}"
elif [ "${BENCHSUITE}" == "gap" ]; then
			TRACES="${GAP}"
elif [ "${BENCHSUITE}" == "datacenter" ]; then
			TRACES="${DATACENTER}"
elif [ "${BENCHSUITE}" == "spec" ]; then
			TRACES="${SPEC_CPU_2006} ${SPEC_CPU_2017}"
			#TRACES="${SPEC_MCF}"
elif [ "${BENCHSUITE}" == "test" ]; then 
			#TRACES="srv_408.champsimtrace.xz"
			#TRACES="smt_srv_12_srv_99_1024i.champsimtrace.xz"
			TRACES="401.bzip2-226B.champsimtrace.xz"
			#TRACES="smt_srv_s60_srv_s61_1024i.champsimtrace.xz"
fi

SIMPOINTS=''
for trace in $TRACES; do
	export suffix=.champsimtrace.xz 
	export bench=${trace%$suffix}
	SIMPOINTS="$SIMPOINTS $bench"
done

BENCHMARKS=''
for simpoint in $SIMPOINTS; do
	export suffix=-*
	export bench=${simpoint%$suffix}
	BENCHMARKS="${BENCHMARKS} ${bench}"
done
BENCHMARKS=$(echo "${BENCHMARKS}" | xargs -n1 | sort -u | xargs)
#BENCHMARKS=${TRACES}
BENCHMARKS=${SIMPOINTS}
