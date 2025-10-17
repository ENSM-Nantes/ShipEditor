import requests
import os

dir_tranfo = "transformation/"
url = "https://raw.githubusercontent.com/ENSM-Nantes/bc/refs/heads/main/resources/models/Ownship/%s/boat.ini"

# Boat's list
L = ['3111_Tug', 'Alice Upjohn', 'Alkmini', 'Aquarius_Tug', 'Atlantic85', 'CSL_Wattle', 'ContainerShipRotor',
	'CopenhagenFerry', 'HMAS_Westralia', 'Protis', 'ProtisSingleScrew', 'Puffer', 'ShetlandTrader', 'VIC56',
	'VIC56_360', 'Waverley'
]


# Create the directory where everything will be process
if not os.path.exists(dir_tranfo):
	os.mkdir(dir_tranfo)

for boat in L:
	# Download the file
	response = requests.get(url % boat)
	

	if response.status_code == 200: # code 200: request sucessful
		# Create a path where to save the configuration file
		if not os.path.exists(dir_tranfo+boat):
			os.mkdir(dir_tranfo+boat)

		# Replace commas by points in float number
		lines = response.content.decode().split('\n')
		for i in range(len(lines)):
			if "," in lines[i] and "=" in lines[i]:
				lines[i] = lines[i].replace(",", ".")


		# Save the file
		file_Path = dir_tranfo + boat + "/boat.ini"
		file = open(file_Path, 'w')
		for line in lines:
			file.write(line+'\n')
		file.close()
	else:
		print('Failed to download file', boat)