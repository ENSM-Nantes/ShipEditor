import keyword_file as keyfile

def convert2dict(filename):
	file_ini = open(filename, 'r')
	lines = file_ini.readlines()
	file_ini.close()
	
	var = {}

	for line in lines:
		# Pass comments
		if line[0] == '#':
			continue

		# Not a key-value line
		if '=' not in line:
			continue

		# Read key and value
		temp = line.split('=')
		key = temp[0].strip()
		value = temp[1].strip()

		# Simple transformation
		if key in keyfile.key_str:
			index = keyfile.key_str.index(key)
			new_key = keyfile.key_str_rename[index]
			var[new_key] = value.replace("\"", "").strip()

		elif key in keyfile.key_int:
			index = keyfile.key_int.index(key)
			new_key = keyfile.key_int_rename[index]
			var[new_key] = int(value)

		elif key in keyfile.key_float:
			index = keyfile.key_float.index(key)
			new_key = keyfile.key_float_rename[index]
			var[new_key] = float(value)

		elif key in keyfile.key_bool:
			index = keyfile.key_bool.index(key)
			new_key = keyfile.key_bool_rename[index]
			var[new_key] = ('1' in value)

		else: # Keys that need format
			if 'View' in key:
				# Search for the renamed key
				index = keyfile.key_wrap.index('View')
				new_key = keyfile.key_wrap_rename[index]

				if key == 'Views' and new_key not in var:
					# Create the tree if needed
					var[new_key] = []
					for i in range(int(value)):
						var[new_key].append([0.0, 0.0, 0.0, False])
				else:
					temp = key.split('(')
					vector_index = int(temp[1].replace(')', '')) - 1

					axis = temp[0][-1]
					axis_no = ['X', 'Y', 'Z', 'h'].index(axis)

					if axis_no == 3: # ViewHigh
						var[new_key][vector_index][3] = True
					else:
						var[new_key][vector_index][axis_no] = float(value)

			elif 'zimuthDrive' in key:
				index = keyfile.key_wrap.index('zimuthDrive')
				new_key = keyfile.key_wrap_rename[index]
				if new_key not in var:
					var[new_key] = {}

				sub_key = key[12:]
				if sub_key == '':
					var[new_key]['azimuthDrive'] = ('1' in value)
				elif sub_key == 'Astern':
					var[new_key]['astern'] = ('1' in value)
				elif sub_key == 'EngineIdleRPM':
					var[new_key]['engineIdleRPM'] = int(value)
				elif sub_key == 'ClutchDisengageRPM':
					var[new_key]['clutchDisengageRPM'] = int(value)
				elif sub_key == 'ClutchEngageRPM':
					var[new_key]['clutchEngageRPM'] = int(value)
				elif sub_key == 'MaxDegPerSecond':
					var[new_key]['maxDegPerSecond'] = int(value)
				elif sub_key == 'SameDirectionAsSchottel':
					var[new_key]['sameDirectionAsSchottel'] = float(value)
				

			elif key in ['aziToLengthRatio', 'engineMaxChangePerSecond', 'schottelMaxDegPerSec', 'schottelMaxDegPerSecond','thrustLeverMaxChangePerSecond']:
				index = keyfile.key_wrap.index('zimuthDrive')
				new_key = keyfile.key_wrap_rename[index]
				if new_key not in var:
					var[new_key] = {}

				if key == 'aziToLengthRatio':
					var[new_key]['aziToLengthRatio'] = float(value)
				elif key == 'engineMaxChangePerSecond':
					var[new_key]['engineMaxChangePerSecond'] = float(value)
				elif key in ['schottelMaxDegPerSec', 'schottelMaxDegPerSecond']:
					var[new_key]['schottelMaxDegPerSec'] = int(value)
				elif key == 'thrustLeverMaxChangePerSecond':
					var[new_key]['thrustLeverMaxChangePerSecond'] = float(value)


			elif 'dynamics' in key.lower():
				index = keyfile.key_wrap.index('Dynamics')
				new_key = keyfile.key_wrap_rename[index]
				if new_key not in var:
					var[new_key] = {"speed":[0.0, 0.0], "turnDrag":[0, 0], "lateralDrag":[0.0, 0.0]}

				sub_key = key.replace("Dynamics", "")
				if 'dynamics' in key:
					sub_key = key.replace("dynamics", "")
				axis = sub_key[-1]
				axis_no = ['A', 'B'].index(axis)

				if 'Speed' in sub_key:
					var[new_key]['speed'][axis_no] = float(value)
				elif 'TurnDrag' in sub_key:
					var[new_key]['turnDrag'][axis_no] = int(value)
				elif 'LateralDrag' in sub_key:
					var[new_key]['lateralDrag'][axis_no] = float(value)


			elif 'Rudder' in key:
				index = keyfile.key_wrap.index('Rudder')
				new_key = keyfile.key_wrap_rename[index]
				if new_key not in var:
					var[new_key] = {}

				sub_key = key.replace("Rudder", "")

				if sub_key == 'A':
					var[new_key]['A'] = float(value)
				elif sub_key == 'B':
					var[new_key]['B'] = float(value)
				elif sub_key == 'BAstern':
					var[new_key]['BAstern'] = float(value)


			elif 'BowThruster' in key:
				index = keyfile.key_wrap.index('BowThruster')
				new_key = keyfile.key_wrap_rename[index]
				if new_key not in var:
					var[new_key] = {}

				sub_key = key.replace("BowThruster", "")
				if sub_key == 'Force':
					var[new_key]['force'] = int(value)
				elif sub_key == 'Distance':
					var[new_key]['distance'] = int(value)

			elif 'SternThruster' in key:
				index = keyfile.key_wrap.index('SternThruster')
				new_key = keyfile.key_wrap_rename[index]
				if new_key not in var:
					var[new_key] = {}

				sub_key = key.replace("SternThruster", "")
				if sub_key == 'Force':
					var[new_key]['force'] = int(value)
				elif sub_key == 'Distance':
					var[new_key]['distance'] = int(value)


			elif 'Prop' in key:
				index = keyfile.key_wrap.index('Prop')
				new_key = keyfile.key_wrap_rename[index]
				if new_key not in var:
					var[new_key] = {}

				sub_key = key.replace("Prop", "")
				if sub_key == 'Space':
					var[new_key]['space'] = float(value)
				elif sub_key == 'WalkAhead':
					var[new_key]['walkAhead'] = float(value)
				elif sub_key == 'WalkAstern':
					var[new_key]['walkAstern'] = float(value)
				elif sub_key == 'WalkDriftEffect':
					var[new_key]['walkDriftEffect'] = float(value)
				

			elif 'RadarScreen' in key:
				index = keyfile.key_wrap.index('RadarScreen')
				new_key = keyfile.key_wrap_rename[index]
				if new_key not in var:
					var[new_key] = {'vector':[0.0, 0.0, 0.0]}

				axis = temp[0][-1]
				axis_no = ['X', 'Y', 'Z', 'e', 't'].index(axis)

				if axis_no == 3: # Size
					var[new_key]['size'] = float(value)
				elif axis_no == 4: # Tilt
					var[new_key]['tilt'] = int(value)
				else:
					var[new_key]['vector'][axis_no] = float(value)


			elif 'PortThrottle' in key:
				index = keyfile.key_wrap.index('PortThrottle')
				new_key = keyfile.key_wrap_rename[index]
				if new_key not in var:
					var[new_key] = [0.0, 0.0, 0.0]

				axis = temp[0][-1]
				axis_no = ['X', 'Y', 'Z'].index(axis)
				var[new_key][axis_no] = float(value)


			elif 'StbdThrottle' in key:
				index = keyfile.key_wrap.index('StbdThrottle')
				new_key = keyfile.key_wrap_rename[index]
				if new_key not in var:
					var[new_key] = [0.0, 0.0, 0.0]

				axis = temp[0][-1]
				axis_no = ['X', 'Y', 'Z'].index(axis)
				var[new_key][axis_no] = float(value)


			elif 'Wheel' in key:
				index = keyfile.key_wrap.index('Wheel')
				new_key = keyfile.key_wrap_rename[index]
				if new_key not in var:
					var[new_key] = {'vector':[0.0, 0.0, 0.0]}

				axis = temp[0][-1]
				axis_no = ['X', 'Y', 'Z', 'e'].index(axis)

				if axis_no == 3: # Scale
					var[new_key]['scale'] = float(value)
				else:
					var[new_key]['vector'][axis_no] = float(value)

			elif 'Sails' in key:
				index = keyfile.key_wrap.index('Sails')
				new_key = keyfile.key_wrap_rename[index]

				if key == 'SailsCount' and new_key not in var:
					var[new_key] = {'list':[]}
					for i in range(int(value)):
						var[new_key]['list'].append([0.0, 0.0, 0.0])
				elif '(' in key:
					temp = key.split('(')
					vector_index = int(temp[1].replace(')', '')) - 1
					
					axis = temp[0][-1]
					axis_no = ['X', 'Y', 'Z'].index(axis)

					var[new_key]['list'][vector_index][axis_no] = float(value)
				else:
					sub_key = key.replace("Sails", "")
					if sub_key == 'Type':
						var[new_key]['type'] = value.replace("\"", "").strip()
					elif sub_key == "Size":
						var[new_key]['size'] = value.replace("\"", "").strip()

			elif 'Pano' in key:
				index = keyfile.key_wrap.index('Pano')
				new_key = keyfile.key_wrap_rename[index]

				if new_key not in var:
					index_view = keyfile.key_wrap.index('View')
					key_view = keyfile.key_wrap_rename[index_view]
					n = len(var[key_view])
					var[new_key] = {'file':[""]*n, 'yaw':[0]*n, 'pitch':[0]*n, 'roll':[0]*n}
				else:
					temp = key.split('(')
					sub_key = temp[0].replace('Pano', '')
					vector_index = int(temp[1].replace(')', '')) - 1

					if sub_key == '':
						var[new_key]['file'][vector_index] = value.replace("\"", "").strip()
					elif sub_key == 'RotationYaw':
						var[new_key]['yaw'][vector_index] = int(value)
					elif sub_key == 'RotationPitch':
						var[new_key]['pitch'][vector_index] = int(value)
					elif sub_key == 'RotationRoll':
						var[new_key]['roll'][vector_index] = int(value)


			else:
				print("Unknow key:", key, "in file", folder)
	return var