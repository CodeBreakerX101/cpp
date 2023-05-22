#include "Setup.h"


bool Setup::OnInit()
{
	
	wxWindowID windowID = 1;		

	m_frame = new Frame(m_window, windowID, "Wordle Solver", wxPoint(100, 100), wxSize(600, 600));
		
	MenuBar();

	m_frame->SetIcon(wxICON(IDI_ICON1));	
	m_frame->SetBackgroundColour(wxColor(20, 20, 20));
	
	m_frame->Show(true);
	SetTopWindow(m_frame);

	return true;

}

void Setup::MenuBar()
{
	wxMenuBar* menubarMain = new wxMenuBar(0);
	wxMenu* m_menuFile = new wxMenu();

	wxMenuItem* m_newWordle = new wxMenuItem(m_menuFile, ID::new_wordle, wxString(wxT("New Wordle")), wxEmptyString, wxITEM_NORMAL);

	m_menuFile->Append(m_newWordle);

	m_menuFile->AppendSeparator();

	wxMenuItem* m_quit = new wxMenuItem(m_menuFile, ID::quit, wxString(wxT("Quit")), wxEmptyString, wxITEM_NORMAL);

	m_menuFile->Append(m_quit);

	menubarMain->Append(m_menuFile, wxT("File"));

	wxMenu* m_menuHelp = new wxMenu();

	wxMenuItem* m_tutorial = new wxMenuItem();//submenu
	wxMenuItem* m_tutorial_menuItem = new wxMenuItem(m_menuHelp, ID::tutorial, wxString(wxT("How to use..")), wxEmptyString, wxITEM_NORMAL);

	m_menuHelp->Append(m_tutorial_menuItem);
	menubarMain->Append(m_menuHelp, wxT("Help"));

	//m_menuFile->Append(wxID_PRINT, "&Print\tCtrl+P", NULL);
	m_frame->SetMenuBar(menubarMain);

	m_frame->Bind(wxEVT_MENU, &Setup::OnHelp, this, m_tutorial_menuItem->GetId());
	m_frame->Bind(wxEVT_MENU, &Setup::OnQuit, this, m_quit->GetId());
	m_frame->Bind(wxEVT_MENU, &Setup::OnRestart, this, ID::new_wordle); // A bug is present in the Restart process, will fix later


}

void Setup::OnQuit(wxCommandEvent& event)
{
	m_frame->Close();
}

void Setup::OnHelp(wxCommandEvent& event)
{

	std::string tutorialImg = fs::current_path().string() + "\\Bitmaps\\Menu\\Help\\HelpImg.bmp";
	fs::path imagePath(tutorialImg);

	if (!fs::exists(imagePath))
	{
		wxMessageBox("Failed to load image");
		event.Skip();
		return;
	}

	wxBitmap bitmap = wxBitmap(tutorialImg, wxBITMAP_TYPE_BMP);

	int bitmapWidth = bitmap.GetSize().GetWidth();
	int bitmapHeight = bitmap.GetSize().GetHeight();

	wxSize imageSize(bitmapWidth, bitmapHeight);
	imageSize += wxSize(20, 20);

	//Creating tutorial Window
	wxFrame* m_tutorialFrame = new wxFrame(m_frame, wxID_ANY, "Tutorial", m_frame->GetPosition() + wxPoint(15, 30), imageSize);


	if (m_tutorialFrame == nullptr)
	{
		wxMessageBox("Failed to load tutorial");

		delete m_tutorialFrame;
		event.Skip();
		return;
	}


	wxStaticBitmap* staticBitmap = new wxStaticBitmap(m_tutorialFrame, wxID_ANY, bitmap);

	wxBoxSizer* m_boxSizer = new wxBoxSizer(wxVERTICAL);

	m_boxSizer->Add(staticBitmap, 0, wxALL, 5);

	m_tutorialFrame->SetSizer(m_boxSizer);

	m_tutorialFrame->Show();

}

void Setup::OnRestart(wxCommandEvent& event)
{
	wxString cmd = wxTheApp->argv[0]; // get the path of the current executable
	long pid = wxExecute(cmd, wxEXEC_ASYNC); // launch a new instance of the application
	wxTheApp->ExitMainLoop(); // terminate the current instance
}

Setup::~Setup()
{

	delete m_window;
	

}