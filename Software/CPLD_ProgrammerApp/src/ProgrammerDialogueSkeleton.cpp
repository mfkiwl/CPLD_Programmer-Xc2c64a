///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "ProgrammerDialogueSkeleton.h"

///////////////////////////////////////////////////////////////////////////

ProgrammerDialogueSkeleton::ProgrammerDialogueSkeleton( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("JEDEC File") ), wxHORIZONTAL );

	loadFile_button = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Load File"), wxDefaultPosition, wxSize( 120,-1 ), 0 );
	loadFile_button->SetToolTip( wxT("Load file to program to device") );

	sbSizer1->Add( loadFile_button, 0, wxALL|wxEXPAND, 5 );

	loadedFile_static = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("-- No file loaded --"), wxDefaultPosition, wxDefaultSize, 0 );
	loadedFile_static->Wrap( -1 );
	loadedFile_static->SetToolTip( wxT("Name of currently loaded file") );

	sbSizer1->Add( loadedFile_static, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer1->Add( sbSizer1, 1, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer31;
	sbSizer31 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Connect to Device") ), wxHORIZONTAL );

	confirmId_button = new wxButton( sbSizer31->GetStaticBox(), wxID_ANY, wxT("Confirm Device"), wxDefaultPosition, wxSize( 120,-1 ), 0 );
	confirmId_button->SetToolTip( wxT("Read IDCODE from device to confirm connection") );

	sbSizer31->Add( confirmId_button, 0, wxALL|wxEXPAND, 5 );

	idcode_static = new wxStaticText( sbSizer31->GetStaticBox(), wxID_ANY, wxT("No device detected"), wxDefaultPosition, wxDefaultSize, 0 );
	idcode_static->Wrap( -1 );
	idcode_static->SetToolTip( wxT("Last device identified") );

	sbSizer31->Add( idcode_static, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer1->Add( sbSizer31, 1, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Programming") ), wxHORIZONTAL );

	programDevice_button = new wxButton( sbSizer3->GetStaticBox(), wxID_ANY, wxT("Program Device"), wxDefaultPosition, wxSize( 120,-1 ), 0 );
	programDevice_button->Enable( false );
	programDevice_button->SetToolTip( wxT("Program file to device") );

	sbSizer3->Add( programDevice_button, 0, wxALL|wxEXPAND, 5 );

	programAction_static = new wxStaticText( sbSizer3->GetStaticBox(), wxID_ANY, wxT("No Action"), wxDefaultPosition, wxDefaultSize, 0 );
	programAction_static->Wrap( -1 );
	programAction_static->SetToolTip( wxT("Result of last programming attempt") );

	sbSizer3->Add( programAction_static, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer1->Add( sbSizer3, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	loadFile_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ProgrammerDialogueSkeleton::onLoadFile ), NULL, this );
	confirmId_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ProgrammerDialogueSkeleton::onConfirmId ), NULL, this );
	programDevice_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ProgrammerDialogueSkeleton::onProgramDevice ), NULL, this );
}

ProgrammerDialogueSkeleton::~ProgrammerDialogueSkeleton()
{
	// Disconnect Events
	loadFile_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ProgrammerDialogueSkeleton::onLoadFile ), NULL, this );
	confirmId_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ProgrammerDialogueSkeleton::onConfirmId ), NULL, this );
	programDevice_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ProgrammerDialogueSkeleton::onProgramDevice ), NULL, this );

}
