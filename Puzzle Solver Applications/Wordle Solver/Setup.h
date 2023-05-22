#pragma once

#include "Frame.h"

class Setup : public wxApp
{

private:

	wxWindow* m_window = nullptr;
	Frame* m_frame;

public:

	virtual bool OnInit();

	

	~Setup();

private:

	void MenuBar();

	void OnQuit(wxCommandEvent& event);

	void OnHelp(wxCommandEvent& event);

	void OnRestart(wxCommandEvent& event);
};

