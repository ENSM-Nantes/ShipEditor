import json
import os

from convert2dict import *

tree_directory = 'transformation/'
path = os.getcwd() + '/' + tree_directory

# List the boats
directory = os.listdir(path)


for folder in directory:
	# Convert the file into a dict
	var = convert2dict(tree_directory + folder + '/boat.ini')

	
	#print(json.dumps(var, indent=4))
	#break

	# Save data
	file_json = open(tree_directory + folder + '/boat.json', 'w')
	json.dump(var, file_json, indent=2)
	file_json.close()
		
	

	

