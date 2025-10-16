import requests
import os

path = os.getcwd() + '/transformation/'
url = "https://raw.githubusercontent.com/ENSM-Nantes/bc/refs/heads/main/resources/models/Ownship/%s/boat.ini"

# Boat's list
L = ['3111_Tug', 'Alice Upjohn', 'Alkmini', 'Aquarius_Tug', 'Atlantic85', 'CSL_Wattle', 'ContainerShipRotor',
	'CopenhagenFerry', 'HMAS_Westralia', 'Protis', 'ProtisSingleScrew', 'Puffer', 'ShetlandTrader', 'VIC56',
	'VIC56_360', 'Waverley'
]


for boat in L:
	response = requests.get(url % boat)
	file_Path = "./transformation/"+ boat + "/boat.ini"

	if response.status_code == 200: # code 200: request sucessful
		# Create a path where to save the configuration file
		os.mkdir(path+boat)
		# Download then save the file
		with open(file_Path, 'wb') as file:
			file.write(response.content)
	else:
		print('Failed to download file', boat)