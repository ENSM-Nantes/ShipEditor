# Documentation of the boat.JSON files 📚

This is the documentation to understand better the structure of all boat.json files.

```
"FileName" : string
```
Set the name of the 3D model file to load
```
"ScaleFactor" : number
```
The amount to scale the 3D model by Bridge Command uses *metres* as it's units, so if the model is in feet, then this should be around 0.3. <br /> <br /> 
**Note that all subsequent positions/distances are in the units/coordinate system of the 3D model file, except for the propulsion system**.

```json
"YCorrection" : number
```
The amount to move the model UP. Therefore, if the model's origin is at its keel, this should be a negative value.
```json
"AngleCorrection" : number
```
The number of degrees the model should be rotated about its vertical axis to correctly align it : the Bridge Command axis system is Y up and Z towards the model's stern (when viewed in a 3d model editor with a right handed coordinate system. Bridge Command uses a left handed system internally, so the Z axis is toward the sip's bow)
```json
"Depth" : number
```
The vessel's depth under the water line (in the 3D model's unit)

```json
"HasGPS" : bool
```
If this is set to True, the G¨S position will be displayed
```json
"HasDepthSounder" : bool
```
If this is set to True, a depth sounder reading is displayed
```json
"MaxDepth" : number
```
If there is a depth sounder, the maximum depth that can be measured (m)
```json
"MakeTransparent" : bool
```
If this is set to True, any part of the model that is partially transparent will be made fully transparent. This is useful where models have bridge windows where the material used partially obscures the view.
```json
"Views" : array[array[number, number, number, boolean]]

//For example :
"View": [
    [ 0.0, 10.25, 3.62, false],
    [-1.8, 10.2, 3.2, false],
    [1.8, 10.2, 3.2, false],
    [-4.27, 6.91, -2.58, false],
    [4.27, 6.91, -2.58, false],
    [0.0, 350.0, 0.0, true]
]
```
An array defining the set of viewpoints available on board the vessel. <br />
Each element in the array represents a single viewpoint and must contain **3 or 4 values** as described below:

| Index | Type | Description |
|:------:|:------:|:------------|
| `[0]` | `number` | The viewpoint’s **X coordinate** in the model’s unit system (valid only if `AngleCorrection = 0`). |
| `[1]` | `number` | The viewpoint’s **Y coordinate** in the model’s unit system (valid only if `AngleCorrection = 0`). |
| `[2]` | `number` | The viewpoint’s **Z coordinate** in the model’s unit system (valid only if `AngleCorrection = 0`). |
| `[3]` | `boolean` *(optional)* | Set to `true` if this is an **elevated view**, where the camera should automatically look straight down when activated. |

```json
"RadarScreen" : object {
    "vector": array[number, number, number],
    "size": number,
    "tilt": number
}

//For Example 
"RadarScreen": { 
    "vector": [-0.25, 9.345, 4.485], 
    "size": 0.23, 
    "tilt": 45 
}
```
Optional visualization parameters defining the position and appearance of the radar screen in the vessel model.  
All coordinates and orientations are expressed in **own ship model coordinates**.

| Key | Type | Description |
|:----|:------:|:------------|
| `"vector"` | `array[number, number, number]` | A 3D **position or orientation vector** specifying the radar screen’s location. |
| `"size"` | `number` | The **size** (scale) of the radar screen in model coordinates. |
| `"tilt"` | `number` | The **tilt angle** of the radar screen in degrees *(default: 0)*. |

```json
"PortThrottle": array[number,number,number]
```
Location to display a port engine throttle control.
```json
"StbdThrottle": array[number,number,number]
```
Location to display a stbd engine throttle control.
```json
"Max_propulsion_force": number
```
The maximum propulsion force of one engine (in Newtons)
```json
"Dynamics" : object {
    "speed": array[number, number],
    "turnDrag": array[number, number],
    "lateralDrag": array[number, number],
}

//For example
"Dynamics": {
        "speed": [10402.622, 24082.07],
        "turnDrag": [90000000, 6000000],
        "lateralDrag": [0.0, 0.0]
    },
```
Dynamics variables are not needed if the maxSpeedAhead has been defined

| Key | Type | Description |
|:----|:------:|:------------|
| `"speed"` | `array[number, number]` | First compenent is the amount of drag on the ship proportional to its **speed squared** location and second component i s the amount of drag on the ship proportional to its **speed**. |
| `"turnDrag"` | `array[number, number]` | First component is the amount of angular drag on the ship proportional to **the rate of turn squared**, the second one is the amount of angular drag on the ship proportional to **the rate of turn**. |
| `"lateralDrag"` | `array[number, number]` | First component is the amount of drag on the ship proportional to **its lateral (sideways) speed squared**, the second component is the amount of drag on the ship proportional to **its lateral (sideways) speed**. |

```json
"AsternEfficiency" : number
```
(Optional) - The proportion of thrust available when going astern (range 0-1, default 1)

```json
"BlockCoefficient" : number
```
(Optional) - The ratio of the volume a ships hull displaces of water and the volume of a cuboid of the same length, breadth and draught as the ship. It is used to calculate the ships mass. A typical values are 0.68 for a high speed container ship, 0.75 for an LNG tanker, 0.87 for a bulk carrier. If BlockCoefficient is defined then it overrides Mass and Inertia parameters as the ships mass and inertias are calculated from the dimensions of the ship model and draught. So if Block Coefficient is defined then there is no need to define Mass , Inertia. If however a non displacement craft such as a hovercraft is being modelled then the mass would need to be explicitly declared.
```json
"Mass" : number
```
The vessel's mass (in kg) 
```json
"Inertia" : number
```
The ship's polar moment of inertia about it's vertical axis(kg m^2)
```json
"Prop" : object{
    "space" : number,
    "walkAhead" : number,
    "walkAstern" : number,
    "walkDriftEffect" : number
}


//For example
"Prop" : {
    "space": 6.0,
    "walkAhead": 0.0,
    "walkAstern": 0.0,
    "walkDriftEffect": 0.0
}
```
| Key | Type | Description |
|:----|:------:|:------------|
| `"space"` | `number` | The **spacing between the port and starboard propellors** in metres (world, not model units). Set to zero to model a one-engined vessel. |
| `"walkAhead"` | `number` | (Optional) - **The maximum turning moment** (Nm) **applied by the 'prop walk' effect on the ship**, with the engine engaged forwards. If the vessel has a normal propellor arrangement, with a single right turning propellor, or double outwards turning propellors, this should be positive. |
| `"walkAstern"` | `number` | (Optional) - **The maximum turning moment** (Nm) **applied by the 'prop walk' effect on the ship**, with the engine engaged astern. This should be positive for normal vessels, and should normally be larger than the ahead value. |
| `"walkDriftEffect"` | `number` | (Optional) - **The amount the ship should move sidways due to the 'prop walk' effect** (Metres per Nm of prop walk). |
```json
"AzimuthDrive" : object{
    "azimuthDrive": bool,
    "astern": bool,
    "aziToLengthRatio": number,
    "engineIdleRPM": number,
    "clutchEngageRPM": number,
    "clutchDisengageRPM": number,
    "engineMaxChangePerSecond": number,
    "maxDegPerSecond": number,
    "thrustLeverMaxChangePerSecond": number,
    "sameDirectionAsSchottel": number
}

//For example
"AzimuthDrive" : {
    "azimuthDrive": true,
    "astern": false,
    "aziToLengthRatio": 0.3,
    "engineIdleRPM": 700,
    "clutchEngageRPM": 1000,
    "clutchDisengageRPM": 950,
    "engineMaxChangePerSecond": 0.25,
    "maxDegPerSecond": 30,
    "thrustLeverMaxChangePerSecond": 0.4,
    "sameDirectionAsSchottel": 1.0   
}
```
| Key | Type | Description |
|:----|:------:|:------------|
| `"azimuthDrive"` | `bool` | (Optional) - Set to *true* if the ship has azimuth drives, or *false* for conventional engine and rudder. |
| `"astern"` | `bool` | (Optional) - Set to *true* if the azimuth drives can be engaged astern (for example for an outboard motor). |
| `"azitoLengthRatio"` | `number` | **The distance along the axis of the vessel of the azimuth drives expressed as a proportion of the vessels length**. Valid values lie between (0 and 1). Typical values 0.2 for an azimuth stern drive tug, 0.1 for an azimuth driven coaster, 0.75 for a tractor tug. |
| `"engineIdleRPM"` | `number` | The engine RPM at which an engine idles with the thrust lever all the way back , engine declutched. It must be less than the azimuthDriveClutchDisengageRPM (a typical value for azimuthDriveEngineIdleRPM is 700). |
| `"clutchEngageRPM"` | `number` | The engine RPM which, when exceeded the clutch automaticall engages. It must be greater than the azimuthDriveClutchDisengageRPM (a typical value for azimuthDriveClutchEngageRPM is 1000). |
| `"clutchDisengageRPM"` | `number` | The engine RPM below which the clutch automatically disengages. It must be less than the azimuthDriveClutchEngageRPM but greater than the azimuthDriveEngineIdleRPM. (A typical value for azimuthDriveClutchDisengageRPM is 950). |
| `"engineMaxChangePerSecond"` | `number` | The proportion of the maximum engine rpm that the engine can change rpm in one second. e.g. 0.25 would mean it takes 4 seconds for an engine to go from a standstill to full power (typical value for a coaster 0.25, for an outboard engine on a speedboat 1, for a large bulk carrier 0.05). |
| `"maxDegPerSecond"` | `number` | The maximum number of degrees that the azipod drive can rotate in the lateral plane in one second. (typically 30). |
| `"thrustLeverMaxChangePerSecond"` | `number` | The maximum proportion of the full range that a thrust lever control can be changed in within one second, e.g 0.2 would mean it takes 5 seconds for the lever to go from full back to full forward. It only applies to keyboard control for playability. In reality the thrust lever can be moved as fast as your wrist can move it, however it will take time for the engine to respond to it. This is ignored if you have physical controls (typical value 0.4). |
| `"sameDirectionAsSchottel"` | `number` | On most vessels the azimuth drive turns in the same direction as the shcottel, so the thrust lever is in the same direction as the actual thrust from the propellor. So in the case of an azimuth stern drive configuration, the turning behaviour is similar to a tiller. Turn the schottel clockwise and the ship will turn to port. The opposite is true in a tractor configuration where the azimuth drives are ahead of amidships. However, some vessels equipped with aft mounted azimuth drives (e.g. Lass class ships, Shetland Trader , Neptune) have a different control response, which is when the schottel is turned clockwise then the azimuth drive turns anticlockwise. So when the schottel is turned clockwise the ship steers to starboard. So the thrust lever only points in the direction of the thrust when it is in the dead ahead or dead astern position. The objective is to make it easier to steer. Trust me it doesn't. (value is typically and normally 1). |

```json
"Rudder" : object{
    "A": number,
    "B": number,
    "BAstern": number
}

//For Example
"Rudder" : {
    "A": 0.0,
    "B": 0.0,
    "BAstern": 0.0
}
```
| Key | Type | Description |
|:----|:------:|:------------|
| `"A"` | `number` | The turning effect of the rudder proportional to the ship's speed (Rudder torque(Nm)=RudderA*Speed(m/s)*rudder angle (deg)). |
| `"B"` | `number` | The turning effect of the rudder proportional to the engine speed (Rudder torque(Nm)=Rudder*Engine Thrust (N)*rudder angle (deg)). |
| `"BAstern"` | `number` | The turning effect of the rudder proportional to the engine speed when going astern (Rudder torque(Nm)=Rudder*Engine Thrust (N)*rudder angle (deg)). |

```json
"Buffet" : number
```
The amount the ship is affected by buffeting due to the weather.
```json
"Swell" : number
```
The amount the ship is rolls in the swell, due to the weather.
```json
"Windage" : number
```
(Optional) - The ratio between the speed with which the ship is moved by the wind and the wind speed.
```json
"WindageTurnEffect" : number
```
(Optional) - The rate of turn due to the wind's action on the ship (Degrees/second per metre/second of wind speed when beam on to the wind)
```json
"DeviationMaximum" : number
```
The **maximum compass deviation** (in degrees).  
Represents the largest difference between the magnetic and true heading observed or allowed in the model.

```json
"DeviationMaximumHeading" : number
```
The **heading at which the maximum deviation** occurs.  
Indicates the vessel’s orientation (in degrees) corresponding to `DeviationMaximum`.
```json
"RollPeriod" : number
```
Defines the **roll period** of the vessel — the time (in seconds) required for a full oscillation around its longitudinal axis.
```json
"PitchPeriod" : number
```
Defines the **pitch period** of the vessel — the time (in seconds) required for a full oscillation around its lateral axis.

```json
"MaxRevs" : number
```
Specifies the **maximum engine revolutions** per minute.

```json
"MaxSpeedAhead" : number
```
Specifies the **maximum forward speed** of the vessel.

```json
"centrifugalDriftEffect" : number
```
Defines the **centrifugal drift coefficient**, representing how much lateral drift occurs when the vessel turns sharply.

```json
"Max_propulsion_force" : number
```
Defines the **maximum propulsion force** the vessel can produce in forward direction.

```json
"HasRateOfTurnIndicator" : bool
```
Indicates whether the vessel has a **Rate of Turn indicator** instrument available.

```json
"BowThruster" : object{
    "Force" : number,
    "Distance" : number
}
```
Defines the **bow thruster** parameters, which provide lateral thrust at the front of the vessel.

| Key | Type | Unit | Description |
|:----|:------:|:------:|:------------|
| `"Force"` | `number` | newtons | Lateral thrust force generated by the bow thruster. |
| `"Distance"` | `number` | meters | Distance from the vessel’s center of rotation to the bow thruster position. |

```json
"SternThruster" : object{
    "Force" : number,
    "Distance" : number
}
```
Defines the **stern thruster** parameters — a lateral propulsion device located at the **rear (stern)** of the vessel, used to assist with low-speed maneuvering such as docking or turning on the spot.

| Key | Type | Unit | Description |
|:----|:------:|:------:|:------------|
| `"Force"` | `number` | newtons | Maximum **lateral thrust force** produced by the stern thruster. |
| `"Distance"` | `number` | meters | **Distance** (positive or negative) from the vessel’s **center of rotation** to the **stern thruster** position along the longitudinal axis. A negative value typically indicates a position *aft* (behind the center). |

```json
"Wheel" : object{
    "vector" : array[number, number, number],
    "scale" : number
}
```
Defines the **helm wheel position and scale** — used to determine where and how the steering wheel of the vessel should be displayed in the 3D model or simulation interface.

| Key | Type | Unit | Description |
|:----|:------:|:------:|:------------|
| `"vector"` | `array[number, number, number]` | model units | The **(X, Y, Z)** coordinates of the wheel’s center in the vessel’s model coordinate system. |
| `"scale"` | `number` | — | A **scaling factor** applied to the wheel’s size for visual representation. |

```json
"Sails" : object{
    "list" : array[array[number, number, number]],
    "type" : string,
    "size" : string
}
```
Defines the set of sails present on the vessel and their parameters.  
All coordinates are expressed in the **own ship model coordinate system**.

| Key | Type | Description |
|:----|:------:|:------------|
| `"list"` | `array[array[number, number, number]]` | A list of sails, where each element is a 3D vector `[X, Y, Z]` giving the position of a sail on the vessel. The number of elements corresponds to the sail count. |
| `"type"` | `string` | The **type or category** of sails (e.g. `"main"`, `"jib"`, `"genoa"`). |
| `"size"` | `string` | The **size or class** of the sails (may be a descriptive label or a numeric size). |

```json
"Pano" : object{
    "file" : array[string],
    "yaw" : array[number],
    "pitch" : array[number],
    "roll" : array[number]
}
```
Defines panoramic image files and their orientation parameters, associated with each viewpoint (`View`).  
Each entry corresponds to a single viewpoint, using the same index order as defined in the `View` array.

| Key | Type | Description |
|:----|:------:|:------------|
| `"file"` | `array[string]` | List of **file names or paths** to the panoramic images corresponding to each viewpoint. |
| `"yaw"` | `array[number]` | List of **yaw (horizontal rotation)** angles for each panorama, in degrees. |
| `"pitch"` | `array[number]` | List of **pitch (vertical rotation)** angles for each panorama, in degrees. |
| `"roll"` | `array[number]` | List of **roll (tilt)** angles for each panorama, in degrees. |

