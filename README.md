# White Cane Sensor Attachment
This project was completed in Spring, 2022 for the UCSC Engineering Senior Design Project: [ECE129].

Engineering Team consists of:
Jack Lambert, Kenan Gedik, and Evan Mayhew

* **TODO**:
	* Add design brief / project background

# Required Hardware for Project
* **MCU**:		*Microchip PIC16F18345* - Microcontroller
* **Sensor**:		*Benewake TF-Mini Plus* - LiDAR (ToF) Sensor
* **Motor**: 		*Adafruit* 5VDC "flat coin"-style Vibration Motor
* **Audio Amp**: *Texas Instruments LM4667* - Mono Class D Amplifier IC
* **Speaker**:	Valid for most any 8-32ohm Speaker rated >1W
* **Battery**: 	*Adafruit* Single-Cell (~3.7V) Li+Poly Battery (1200mAh)
* **Charge Controller**: *Microchip MCP73837* - Single Cell Li+Poly Battery Charge Management IC
* **Voltage Regulator**:	*Texas Instruments MC34063A* - Buck-Boost Switching Regulator
* **Power-Button**: Momentary Pushbutton - SPST (Normally Open)
*  **Charging Jack**: Coaxial *"Barrel Jack"* DC Power Connector

Schematic / wiring diagram PDFs may be found in the directory:
* `"/Hardware/WCSA_OrCAD/Schematic PDFs/"`


# Directory Locations
* The ***complete list of source files*** may be found in the directory:
	* `"/Current Software Release/curr_src/"`


* A ***pre-built hex file*** (ready to flash onto MCU) may be found in:
	* `"/Current Software Release/prebuilt_hex/SDP_FinalProject.X.production.hex"`

* ***Previous / abandoned versions of project source files*** (for different MCU and/or distance sensors) may be found in the directories:
	* `"/Old Versions/PIC16F/"` 
	* `"/Old Versions/AVR ProMicro/"`

* ***Testing Scripts*** (e.g. *Python / MATLAB* scripts) may be found in the directory:
	* `"/Testing Scripts/"`

* ***Hardware Directories***:
	* Schematic Capture / PCB Layout / Gerber Files (configured with *Cadence/OrCAD*) may be found in the directory: 
		* `"/Hardware/WCSA_OrCAD/WCSA_SystemSchem/"`
	*  Mechanical Housing project files (configured with *SolidWorks*) may be found in the directory:
		* `"/Hardware/SolidWorks_Assembly/"`
