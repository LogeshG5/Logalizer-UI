///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "ui.h"

///////////////////////////////////////////////////////////////////////////

MyFrame::MyFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );


	this->Centre( wxBOTH );
}

MyFrame::~MyFrame()
{
}

MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bMainSizer;
	bMainSizer = new wxBoxSizer( wxVERTICAL );

	m_notebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, wxT("Generate") );
	m_panelGenerate = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bGenerateMainSizer;
	bGenerateMainSizer = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSelectLogSizer;
	bSelectLogSizer = new wxBoxSizer( wxVERTICAL );

	m_staticTextLogFileTitle = new wxStaticText( m_panelGenerate, wxID_ANY, wxT("Select a log file"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextLogFileTitle->Wrap( -1 );
	bSelectLogSizer->Add( m_staticTextLogFileTitle, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_logFilePicker = new wxFilePickerCtrl( m_panelGenerate, wxID_ANY, wxEmptyString, wxT("Select a log file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	bSelectLogSizer->Add( m_logFilePicker, 0, wxALL|wxEXPAND, 5 );

	m_staticText3 = new wxStaticText( m_panelGenerate, wxID_ANY, wxT("Drag and drop here"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_staticText3->Wrap( -1 );
	bSelectLogSizer->Add( m_staticText3, 0, wxALL|wxEXPAND, 5 );

	m_dropText = new wxTextCtrl( m_panelGenerate, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSelectLogSizer->Add( m_dropText, 1, wxALL|wxEXPAND, 5 );


	bGenerateMainSizer->Add( bSelectLogSizer, 1, wxEXPAND, 5 );

	wxBoxSizer* bGenerateBtnSizer;
	bGenerateBtnSizer = new wxBoxSizer( wxHORIZONTAL );

	m_staticText31 = new wxStaticText( m_panelGenerate, wxID_ANY, wxT("Select profile"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText31->Wrap( -1 );
	bGenerateBtnSizer->Add( m_staticText31, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_profileCombo = new wxComboBox( m_panelGenerate, wxID_ANY, wxT("Select profile"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bGenerateBtnSizer->Add( m_profileCombo, 1, wxALL|wxFIXED_MINSIZE, 5 );

	m_formatCombo = new wxComboBox( m_panelGenerate, wxID_ANY, wxT("PNG"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	m_formatCombo->Append( wxT("PNG") );
	m_formatCombo->Append( wxT("SVG") );
	m_formatCombo->SetSelection( 0 );
	m_formatCombo->Hide();

	bGenerateBtnSizer->Add( m_formatCombo, 0, wxALL|wxFIXED_MINSIZE, 5 );

	m_generateButton = new wxButton( m_panelGenerate, wxID_ANY, wxT("Generate"), wxDefaultPosition, wxDefaultSize, 0 );
	bGenerateBtnSizer->Add( m_generateButton, 2, wxALL, 5 );


	bGenerateMainSizer->Add( bGenerateBtnSizer, 0, wxEXPAND, 5 );


	m_panelGenerate->SetSizer( bGenerateMainSizer );
	m_panelGenerate->Layout();
	bGenerateMainSizer->Fit( m_panelGenerate );
	m_notebook->AddPage( m_panelGenerate, wxT("Generate"), true );

	bMainSizer->Add( m_notebook, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bMainSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_logFilePicker->Connect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( MainFrame::onLogFileChanged ), NULL, this );
	m_profileCombo->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( MainFrame::onProfileSelected ), NULL, this );
	m_generateButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::onGenerate ), NULL, this );
}

MainFrame::~MainFrame()
{
	// Disconnect Events
	m_logFilePicker->Disconnect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( MainFrame::onLogFileChanged ), NULL, this );
	m_profileCombo->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( MainFrame::onProfileSelected ), NULL, this );
	m_generateButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::onGenerate ), NULL, this );

}
