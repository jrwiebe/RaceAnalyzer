
#include "appOptions.h"
#include "wx/config.h"

#define DEFAULT_COM_PORT 						1
#define DEFAULT_AUTO_LOAD_CONFIG 				true
#define DEFAULT_DATALOG_CHANNEL_COUNT 			-1
#define DEFAULT_DATALOG_CHANNEL_TYPES_COUNT 	-1

#define CONFIG_KEY_COM_PORT 					"COM_Port"
#define CONFIG_KEY_AUTO_LOAD					"AutoLoadConfig"
#define CONFIG_KEY_DATALOG_CHANNEL				"DatalogChannel_"
#define CONFIG_KEY_DATALOG_CHANNEL_TYPE			"DatalogChannelType_"
#define CONFIG_KEY_DATALOG_CHANNEL_COUNT		"DatalogChannelCount"
#define CONFIG_KEY_DATALOG_CHANNEL_TYPE_COUNT	"DatalogChannelTypeCount"

AppOptions::AppOptions()
	: 	m_serialPort(DEFAULT_COM_PORT) ,
		m_autoLoadConfig(DEFAULT_AUTO_LOAD_CONFIG)
{}

int AppOptions::GetSerialPort(){
	return m_serialPort;
}

void AppOptions::SetSerialPort(int comPort){
	m_serialPort = comPort;
}

bool & AppOptions::GetAutoLoadConfig(){
	return m_autoLoadConfig;
}

void AppOptions::SetAutoLoadConfig(bool autoConnect){
	m_autoLoadConfig = autoConnect;
}

void AppOptions::SaveAppOptions(){
	wxConfig config(RACE_ANALYZER_APP_NAME);

	config.Write(CONFIG_KEY_COM_PORT,m_serialPort);
	config.Write(CONFIG_KEY_AUTO_LOAD, m_autoLoadConfig);
}

void AppOptions::LoadAppOptions(){
	wxConfig config(RACE_ANALYZER_APP_NAME);

	config.Read(CONFIG_KEY_COM_PORT,&m_serialPort, DEFAULT_COM_PORT);
	config.Read(CONFIG_KEY_AUTO_LOAD, &m_autoLoadConfig, DEFAULT_AUTO_LOAD_CONFIG);

	int standardChannelCount = 0;
	config.Read(CONFIG_KEY_DATALOG_CHANNEL_COUNT, &standardChannelCount, DEFAULT_DATALOG_CHANNEL_COUNT );

	if (DEFAULT_DATALOG_CHANNEL_COUNT == standardChannelCount){
		LoadDefaultStandardChannels(m_standardChannels);
	}

	int standardChannelTypesCount = 0;
	config.Read(CONFIG_KEY_DATALOG_CHANNEL_TYPE_COUNT, &standardChannelTypesCount, DEFAULT_DATALOG_CHANNEL_TYPES_COUNT );

	if (DEFAULT_DATALOG_CHANNEL_TYPES_COUNT == standardChannelTypesCount){
		LoadDefaultStandardChannelTypes(m_standardChannelTypes);
	}
}

DatalogChannels & AppOptions::GetStandardChannels(){
	return m_standardChannels;
}

DatalogChannelTypes & AppOptions::GetStandardChannelTypes(){
	return m_standardChannelTypes;
}

void AppOptions::LoadDefaultStandardChannelTypes(DatalogChannelTypes &types){

	types.Add( DatalogChannelType("Raw","Number", 0,0,1024) );
	types.Add( DatalogChannelType("GForce", "G", 5,-2.0,2.0) );
	types.Add( DatalogChannelType("Rotation", "Degrees/Sec", 5, -300.0, 300.0) );
	types.Add( DatalogChannelType("TimeDate", "UTC", 0, 0, 0) );
	types.Add( DatalogChannelType("Count", "Count", 0,0, 10.0) );
	types.Add( DatalogChannelType("Latitude", "Degrees", 0, 0, 360.0) );
	types.Add( DatalogChannelType("Longitude", "Degrees", 0, 0, 360.0) );
	types.Add( DatalogChannelType("Speed", "KPH", 0, 0, 300.0) );
	types.Add( DatalogChannelType("Volts", "Volts", 0, 0, 25.0) );
	types.Add( DatalogChannelType("Pressure", "PSI", 0, 0, 300.0) );
	types.Add( DatalogChannelType("Temperature", "F", 0, 0, 300.0) );
	types.Add( DatalogChannelType("Frequency", "Hz", 0, 0, 2000.0) );
	types.Add( DatalogChannelType("RPM", "RPM", 0, 0, 10000.0) );
	types.Add( DatalogChannelType("Duration", "Ms.", 0, 0, 100.0) );
	types.Add( DatalogChannelType("Percent", "%", 0, 0, 100.0) );
	types.Add( DatalogChannelType("Digital", "Off/On", 0, 0, 1) );
}

void AppOptions::LoadDefaultStandardChannels(DatalogChannels &channels){

	//Accelerometer inputs
	channels.Add( DatalogChannel("AccelX", 0, "Accelerometer X Axis") );
	channels.Add( DatalogChannel("AccelY", 0, "Accelerometer Y Axis") );
	channels.Add( DatalogChannel("AccelZ", 0, "Accelerometer Z Axis") );
	channels.Add( DatalogChannel("Yaw", 1, "Accelerometer Z Axis Rotation") );

	//GPS inputs
	channels.Add( DatalogChannel("GPSTime", 2, "GPS Time in UTC") );
	channels.Add( DatalogChannel("GPSQual", 3, "GPS signal quality indicator") );
	channels.Add( DatalogChannel("GPSSats", 3, "Number of Active Satellites") );
	channels.Add( DatalogChannel("GPSLatitude", 4, "GPS Latitude in Degrees") );
	channels.Add( DatalogChannel("GPSLongitude", 5,"GPS Longitude in Degrees") );
	channels.Add( DatalogChannel("GPSVelocity", 6, "GPS Velocity") );

	//Analog inputs
	channels.Add( DatalogChannel("Battery", 7, "Battery Voltage") );
	channels.Add( DatalogChannel("AnalogIn1", 7, "Analog Input 1") );
	channels.Add( DatalogChannel("AnalogIn2", 7, "Analog Input 2") );
	channels.Add( DatalogChannel("AnalogIn3", 7, "Analog Input 3") );
	channels.Add( DatalogChannel("AnalogIn4", 7, "Analog Input 4") );
	channels.Add( DatalogChannel("AnalogIn5", 7, "Analog Input 5") );
	channels.Add( DatalogChannel("AnalogIn6", 7, "Analog Input 6") );
	channels.Add( DatalogChannel("AnalogIn7", 7, "Analog Input 7") );
	channels.Add( DatalogChannel("OilPressure", 8, "Oil Pressure") );
	channels.Add( DatalogChannel("OilTemp", 9, "Engine Oil Temperature") );
	channels.Add( DatalogChannel("CoolantTemp", 9, "Engine Coolant Temperature") );

	//Frequency Inputs
	channels.Add( DatalogChannel("FrequencyIn1", 10, "Frequency Input 1") );
	channels.Add( DatalogChannel("FrequencyIn2", 10, "Frequency Input 2") );
	channels.Add( DatalogChannel("FrequencyIn3", 10, "Frequency Input 3") );
	channels.Add( DatalogChannel("EngineRPM", 11, "Engine Speed in RPM") );
	channels.Add( DatalogChannel("WheelSpeed", 11, "Wheel Speed in RPM") );
	channels.Add( DatalogChannel("PulseWidth", 12, "Signal Pulse width in Ms.") );
	channels.Add( DatalogChannel("DutyCycle", 13, "Signal Duty Cycle in %") );

	//Analog Outputs
	channels.Add( DatalogChannel("AnalogOut1", 7, "Analog Output 1") );
	channels.Add( DatalogChannel("AnalogOut2", 7, "Analog Output 2") );
	channels.Add( DatalogChannel("AnalogOut3", 7, "Analog Output 3") );
	channels.Add( DatalogChannel("AnalogOut4", 7, "Analog Output 4") );

	//Frequency Outputs
	channels.Add( DatalogChannel("FrequencyOut1", 10, "Frequency Output 1") );
	channels.Add( DatalogChannel("FrequencyOut2", 10, "Frequency Output 2") );
	channels.Add( DatalogChannel("FrequencyOut3", 10, "Frequency Output 3") );
	channels.Add( DatalogChannel("FrequencyOut4", 10, "Frequency Output 4") );

	//Digital Inputs
	channels.Add(DatalogChannel("DigitalIn1", 14, "Digital Input 1") );
	channels.Add(DatalogChannel("DigitalIn2", 14, "Digital Input 2") );
	channels.Add(DatalogChannel("DigitalIn3", 14, "Digital Input 3") );

	//Digital Outputs
	channels.Add(DatalogChannel("DigitalOut1", 14, "Digital Output 1") );
	channels.Add(DatalogChannel("DigitalOut2", 14, "Digital Output 2") );
	channels.Add(DatalogChannel("DigitalOut3", 14, "Digital Output 3") );
}