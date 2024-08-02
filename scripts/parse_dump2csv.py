#!/usr/bin/python3

"""
__name__ = parse_dump2csv.py
__author__ = Dimitrios Chasapis
__description = Parse the raw output file of ChampSim and creates a csv file with the data
"""

import argparse 
import re
import csv
import traceback

def parse_naive_sim_dump(input_file, output_file):

	data = open(args.input_file, "r").read()
	for line in re.findall( "Branch predictor" + "\s.*\s" + "accuracy:\s.*", data):
		print(line)
		split_line = re.split(":", line)
		print(split_line[1].strip(" ").strip("\n"))
		accuracy = float(split_line[1].strip(" ").strip("\n"))
    
    # Export data to csv format
	output_file = open(output_file, 'w')
	writer = csv.writer(output_file)
	header = [ "accuracy" ]
	data = [ accuracy ]
	writer.writerow(header)
	writer.writerow(data)


### Command Line Arguments ###
parser = argparse.ArgumentParser()
parser.add_argument('--input-file', dest='input_file', required=True, default=None, help="Raw dump file")
parser.add_argument('--output-file', dest='output_file', required=False, default="data.csv", help="Output csv file name")

args = parser.parse_args()

try:
    parse_naive_sim_dump(args.input_file, args.output_file)
except Exception as e:
    print("Parsing Failed: " + args.input_file)
    print(e)
    print(traceback.format_exc())

