
#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/richtext/richtextctrl.h>

#include <iostream>
#include <filesystem>

#include "Wordle Solver.h"


namespace fs = std::filesystem;

class Frame : public wxFrame
{

public:

	bool is_restarting = false;

private:

	

	//Class objects

	WordleSolver* m_CwordleSolver = nullptr;

	//Standard Variables

	int currentThread = 0;	

	std::string m_alphabetsDirectoryLocation;
	std::string m_backgroundDirectoryLocation;

	std::string m_userInputLetters;

	std::vector<int> m_StaticBitmapId;

	const int m_row = 6;
	const int m_coloumn = 5;
	const int m_LastIndexOfStaticBitmap = (m_row * m_coloumn) - 1;

	int m_currentRow = 1;

	int m_secondRowIndex = m_coloumn;

	bool m_isEnterPressed = 0;	

	std::string color_Black = "Black", color_Yellow = "Yellow", color_Green = "Green";

	//Filesystem variables
	fs::path m_alphabetDirectoryPath;
	std::vector<fs::path> m_alphabetsChildDirectories;

	fs::path* m_bitmapPathHolder = new fs::path[m_coloumn];

	fs::path m_background_black_path;
	fs::path m_background_yellow_path;
	fs::path m_background_green_path;


	// wxWidgets variables	
	wxWindow* m_parent = nullptr;
	
	//For new Frame while Restarting
	Frame* m_frame = nullptr;
	wxWindow* m_window = nullptr;
	
	
	wxBitmap m_backgroundBlackBitmap, m_backgroundYellowBitmap, m_backgroundGreenBitmap;	

	wxPanel* m_panel1 = nullptr;


	wxString m_inputText;

	wxBoxSizer* m_bSizerFrameMain = nullptr;
	wxBoxSizer* m_bSizerBody = nullptr;

	wxWindowID m_textCtrlID = 1;

	wxStaticBitmap* m_staticBitmap[30]; //column 5, row 6 ; 5 * 6 = 30

	wxMenuBar* menubarMain = nullptr;

	wxStaticText* m_staticText = nullptr;


public:

	Frame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("wxFormBuilder Widgets"), const wxPoint& pos = wxPoint(100, 50), const wxSize& size = wxSize(686, 468), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
	~Frame();


private:
	

	void InitializeSizerFrameMain();

	void InitializePanel();

	void InitializeSizerBody();

	void StaticText(int fontSize = 11);	

	void OnQuit(wxCommandEvent& event);

	void ClearDynamicallyAllocatedMemories();

	void OnHelp(wxCommandEvent& event);

	void OnRestart(wxCommandEvent& event);
	

	void InitializeMemberVariables();

	void InitializeStaticBitmapIds();

	void OnBitmapClicked(wxMouseEvent& event);

	fs::path ChangeBitmapColor(int staticBitmapPos, std::string changeColorTo);

	void HoldPathOfThisBitmap(int index, std::string& bitmapPath);

	void OnClikingAnyBitMapImage();	

	int SetAlphabetsChildDirectories();

	void OnMouseInput();

	void OnKeyBoardInput();

	void OnCharHook(wxKeyEvent& event);	

	void SetAlphabetWithStaticBitmap(int keyCode, int bitmapIndex, int bitmapPathHolderIndex, std::string AlphabetColor);

	std::string GetBlackLetters(fs::path bitmapPathHolder[], std::string& inputLetters);

	std::string GetYellowLetters(fs::path bitmapPathHolder[], std::string& inputLetters);

	std::string GetGreenLetters(fs::path bitmapPathHolder[], std::string& inputLetters);

	

	void ResetBitmapPathHolders();

	void EnableStaticBitmap(int rowIndex);

	void DisableStaticBitmap(int rowIndex);

	void DisableStaticBitmapInRange(int rowIndex_begin, int rowIndex_end);

	fs::path GetTheBackgroundBitmapAsPerColor(fs::path bitmapPathHolder[], int index);

	void EraseTheLastChar(std::string& userInputCharacters);

	fs::path ChangeTheBitmapPathAsPerTheColor(fs::path& currentBitmap, fs::path& destDirectory);

	void OnEnter(wxCommandEvent& event);

	void StoreBitmapPathOfEveryRow();

	void OnPressingKey(wxString& text);

	void OnPressingBackSpace(int& currentPos, int lastPos);

	char GetAlphabet(wxString& text);

	int GetAlphabetPos(wxString& text);

	void OnPressingAlphabeticalKeys(char alphabet, int currentPos);

	void OnPressingNumericalKeys(char number);

	void OnPressingModifierKeys(char modifierKey);


	void FiveBySixSquareBody(wxBoxSizer* bSizerBody);	

};


//Menu object ids
enum ID
{
	windowID = 100,

	new_wordle = 1000,
	quit,
	tutorial,
	helpWindow

};