/*
 * ConfigPanel.cpp
 *
 *  Created on: Apr 30, 2009
 *      Author: brent
 */
#include "configuration/configPanel.h"

enum{
	ID_BUTTON_READ_CONFIG= wxID_HIGHEST + 10000,
	ID_BUTTON_WRITE_CONFIG,
	ID_CONFIG_NAVIGATION,
	ID_FLASH_CONFIG,
	ID_READWRITE_PROGRESS
};


ConfigPanel::ConfigPanel() : wxPanel()
{
	InitComponents();
}

ConfigPanel::ConfigPanel(wxWindow *parent,
			wxWindowID id,
			const wxPoint &pos,
			const wxSize &size,
			long style,
			const wxString &name
			)
			: wxPanel(	parent,
						id,
						pos,
						size,
						style,
						name)
{
	InitComponents();
}

ConfigPanel::~ConfigPanel(){

}

void ConfigPanel::InitComponents(){

	wxFlexGridSizer *sizer = new wxFlexGridSizer(2,1,3,3);
	sizer->AddGrowableCol(0);
	sizer->AddGrowableRow(0);

	m_configNavigation = new wxTreebook(this,-1, wxDefaultPosition, wxSize(600,400),wxNB_LEFT);

	m_analogInputPanel = new AnalogInputPanel(m_configNavigation,-1,&m_raceCaptureConfig);
	m_analogInputPanel->InitComponents();

	m_timerInputPanel = new PulseInputPanel(m_configNavigation,-1,&m_raceCaptureConfig);
	m_timerInputPanel->InitComponents();

	m_accelInputPanel = new AccelInputPanel(m_configNavigation,-1,&m_raceCaptureConfig);
	m_accelInputPanel->InitComponents();

	m_analogPulseOutPanel = new AnalogPulseOutputPanel(m_configNavigation,-1,&m_raceCaptureConfig);
	m_analogPulseOutPanel->InitComponents();

	m_gpioPanel = new GpioPanel(m_configNavigation,-1,&m_raceCaptureConfig);
	m_gpioPanel->InitComponents();

	m_gpsPanel = new GpsConfigPanel(m_configNavigation,-1,&m_raceCaptureConfig);
	m_gpsPanel->InitComponents();

	m_loggerOutputPanel = new LoggerOutputConfigPanel(m_configNavigation, -1, &m_raceCaptureConfig);
	m_loggerOutputPanel->InitComponents();

	m_configNavigation->AddPage(m_gpsPanel,"GPS");
	m_configNavigation->AddPage(m_analogInputPanel,"Analog Inputs");
	m_configNavigation->AddPage(m_timerInputPanel,"Pulse Inputs");
	m_configNavigation->AddPage(m_accelInputPanel,"Accelerometer Inputs");
	m_configNavigation->AddPage(m_analogPulseOutPanel,"Analog/Pulse Outputs");
	m_configNavigation->AddPage(m_gpioPanel,"Digital I/O");
	m_configNavigation->AddPage(m_loggerOutputPanel,"Logging/Telemetry");

	m_configSettings = new wxPanel(this);

	sizer->Add(m_configNavigation,1,wxEXPAND);

	wxButton *readButton = new wxButton(this,ID_BUTTON_READ_CONFIG,"Read");
	wxButton *writeButton = new wxButton(this, ID_BUTTON_WRITE_CONFIG,"Write");
	wxCheckBox *flashConfig = new wxCheckBox(this,ID_FLASH_CONFIG,"Also Flash Configuration");
	flashConfig->SetValue(true);

	wxGridSizer *buttonBarSizer = new wxGridSizer(1,2,3,3);

	wxBoxSizer *leftButtonSizer = new wxBoxSizer(wxHORIZONTAL);

	leftButtonSizer->Add(readButton,0,wxALIGN_LEFT | wxALL);
	leftButtonSizer->Add(writeButton,0,wxALIGN_RIGHT | wxALL);
	leftButtonSizer->AddSpacer(10);
	leftButtonSizer->Add(flashConfig,0,wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL);

	buttonBarSizer->Add(leftButtonSizer,1,wxEXPAND | wxALL);

	sizer->Add(buttonBarSizer,1,wxEXPAND);
	this->SetSizer(sizer);
}


void ConfigPanel::InitOptions(){

}

void ConfigPanel::SetComm(RaceAnalyzerComm *comm){
	m_comm = comm;
}

void ConfigPanel::OnReadConfig(wxCommandEvent &event){
	try{
		m_comm->readConfig(m_raceCaptureConfig);
		m_analogInputPanel->OnConfigUpdated();
		m_timerInputPanel->OnConfigUpdated();
		m_accelInputPanel->OnConfigUpdated();
		m_analogPulseOutPanel->OnConfigUpdated();
		m_gpioPanel->OnConfigUpdated();
		m_gpsPanel->OnConfigUpdated();
		m_loggerOutputPanel->OnConfigUpdated();
	}
	catch(CommException &e){
		wxLogMessage("Error reading script: %s", e.GetErrorMessage().ToAscii());
	}
}

BEGIN_EVENT_TABLE ( ConfigPanel, wxPanel )
	EVT_BUTTON(ID_BUTTON_READ_CONFIG,ConfigPanel::OnReadConfig)
END_EVENT_TABLE()
