

#include "Frame.h"

const int Error_occured = -1;

Frame::Frame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size,
	long style) : wxFrame(parent, id, title, pos, size, style)
{
	m_parent = parent;

	//Initializing WordleSolver class object
	std::string fiveLetterWordsLocation = "Five Letter Words.txt";
	m_CwordleSolver = new WordleSolver(fiveLetterWordsLocation);

	if (m_CwordleSolver->m_ErrorOccured)
	{
		wxMessageBox(m_CwordleSolver->m_errorMsg);
		return;
	}

	// Creating Frame 

	InitializeMemberVariables();

	InitializeStaticBitmapIds();

	StoreBitmapPathOfEveryRow();


	//Graphic Area
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	m_bSizerFrameMain = new wxBoxSizer(wxVERTICAL);
	m_bSizerFrameMain->Add(0, 30, 0, wxEXPAND, m_coloumn);

	m_panel1 = new wxPanel(this, wxID_ANY, wxPoint(200, 50), wxSize(-1, -1), wxTAB_TRAVERSAL);

	m_bSizerBody = new wxBoxSizer(wxVERTICAL);
	m_bSizerBody->SetMinSize(wxSize(0, 0));

	InitializeSizerFrameMain();

	InitializePanel();

	InitializeSizerBody();

	FiveBySixSquareBody(m_bSizerBody);

	StaticText();	

	//
	DisableStaticBitmapInRange(m_secondRowIndex, std::size(m_staticBitmap) - 1);

	SetAlphabetsChildDirectories();


	//On User Input	
	OnMouseInput();
	OnKeyBoardInput();
	

	this->SetSizer(m_bSizerFrameMain);
	this->Layout();

	this->Centre(wxBOTH);

}

void Frame::InitializeSizerFrameMain()
{



}

void Frame::InitializePanel()
{

}

void Frame::InitializeSizerBody()
{

}

void Frame::StaticText(int fontSize)
{
	m_staticText = new wxStaticText(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	m_staticText->Wrap(-1);
	
	wxFont font = m_staticText->GetFont();
	font.SetPointSize(fontSize);

	m_staticText->SetFont(font);	
	m_staticText->SetForegroundColour(wxColour(255, 255, 255));

	m_bSizerFrameMain->Add(m_staticText, 1, wxALIGN_LEFT | wxALL, 30);

	
}

void Frame::InitializeMemberVariables()
{	

	std::string icon_path_str = "wordleIcon.ico";
	fs::path icon_path(icon_path_str);

	m_alphabetsDirectoryLocation = "Bitmaps\\Alphabets";
	m_backgroundDirectoryLocation = "Bitmaps\\Background";

	m_background_black_path = m_backgroundDirectoryLocation + "\\Black.bmp";
	m_background_yellow_path = m_backgroundDirectoryLocation + "\\Yellow.bmp";
	m_background_green_path = m_backgroundDirectoryLocation + "\\Green.bmp";

	m_alphabetDirectoryPath = m_alphabetsDirectoryLocation;

	m_backgroundBlackBitmap = wxBitmap(m_background_black_path.string(), wxBITMAP_TYPE_BMP);
	m_backgroundYellowBitmap = wxBitmap(m_background_yellow_path.string(), wxBITMAP_TYPE_BMP);
	m_backgroundGreenBitmap = wxBitmap(m_background_yellow_path.string(), wxBITMAP_TYPE_BMP);

	for (int i = 0; i < std::size(m_staticBitmap); i++)
	{
		m_staticBitmap[i] = nullptr;
	}
}

void Frame::InitializeStaticBitmapIds()
{
	for (int i = 0; i < 30; i++)
	{
		m_StaticBitmapId.push_back(i);
	}
}

int Frame::SetAlphabetsChildDirectories()
{

	if (!fs::exists(m_alphabetDirectoryPath))
	{
		wxMessageBox("Alphabets directory is missing");
		return -1;
	}
	//Get child directories
	std::vector<std::string> childDirectories;
	for (fs::path x : fs::directory_iterator(m_alphabetDirectoryPath))
	{
		int index = 0;
		if (fs::is_directory(x))
		{
			childDirectories.push_back(x.string());
		}
	}
	//Sort the folder names as per alphabets
	std::sort(childDirectories.begin(), childDirectories.end());

	for (std::string directory : childDirectories)
	{
		m_alphabetsChildDirectories.push_back(directory);
	}

}
void Frame::OnMouseInput()
{
	OnClikingAnyBitMapImage();
}

void Frame::OnKeyBoardInput()
{
	m_panel1->Bind(wxEVT_CHAR_HOOK, &Frame::OnCharHook, this);
}

void Frame::OnCharHook(wxKeyEvent& event)
{

	int keyCode = event.GetKeyCode();
	//int keyCode = event.GetRawKeyCode();
	char coloumn_chr = '0' + m_coloumn;

	int bitmapIndexByInputNumber = ((m_currentRow - 1) * m_coloumn) + ((keyCode - '0') - 1);

	int bitmapPathHolderIndex = m_userInputLetters.size();
	int lastIndexForBitmapPathHolder = bitmapPathHolderIndex - 1;

	int currentBitmapIndex = bitmapPathHolderIndex + ((m_currentRow - 1) * m_coloumn);
	int lastBitmapIndex = currentBitmapIndex - 1;

	int firstIndexOfRow = ((m_currentRow - 1) * m_coloumn);
	int lastIndexOfRow = (m_coloumn * m_currentRow) - 1;

	if ((keyCode == WXK_BACK || keyCode == WXK_RETURN) && (currentBitmapIndex > firstIndexOfRow && currentBitmapIndex <= lastIndexOfRow + 1)
		&& (lastIndexOfRow <= m_LastIndexOfStaticBitmap))
	{
		//Change the image to background image with same color
		if (keyCode == WXK_RETURN && currentBitmapIndex == m_coloumn * m_currentRow) //On Enter key
		{
			std::string words;
			std::string blackLetters, yellowLetters, greenLetters;

			blackLetters = GetBlackLetters(m_bitmapPathHolder, m_userInputLetters);
			yellowLetters = GetYellowLetters(m_bitmapPathHolder, m_userInputLetters);
			greenLetters = GetGreenLetters(m_bitmapPathHolder, m_userInputLetters);

			//Getting wordle result
			m_CwordleSolver->Run(blackLetters, yellowLetters, greenLetters) == Error_occured;
			
			//Upto 20 words will shown
			words = m_CwordleSolver->GetWordsFromIndex(m_CwordleSolver->m_nonRepeatingLetterWordsIndex,
				m_CwordleSolver->m_repeatingLetterWordsIndex);

			m_staticText->SetLabel(words);


			ResetBitmapPathHolders();

			DisableStaticBitmap(m_currentRow);

			m_currentRow += 1; //Go to  next Row

			if (m_currentRow <= m_row && !(m_CwordleSolver->m_nonRepeatingLetterWordsIndex.empty() &&
				m_CwordleSolver->m_repeatingLetterWordsIndex.empty()))
			{
				EnableStaticBitmap(m_currentRow);
			}

			//Clear data
			m_userInputLetters.clear();

			blackLetters.clear();
			yellowLetters.clear();
			greenLetters.clear();

		}
		else if (keyCode == WXK_BACK)
		{

			EraseTheLastChar(m_userInputLetters);

			fs::path toBackGroundImg = GetTheBackgroundBitmapAsPerColor(m_bitmapPathHolder, lastIndexForBitmapPathHolder);

			m_bitmapPathHolder[lastIndexForBitmapPathHolder] = toBackGroundImg;

			wxBitmap bitmap(m_bitmapPathHolder[lastIndexForBitmapPathHolder].string(), wxBITMAP_TYPE_BMP);
			m_staticBitmap[lastBitmapIndex]->SetBitmap(bitmap);


		}
	}
	else if (event.ControlDown() || event.ShiftDown() || (keyCode >= '1' && keyCode <= coloumn_chr))
	{

		if (event.ControlDown() && event.ShiftDown() )
		{			
			int index = keyCode - '1';

			if (index >= 0 && index < m_coloumn)
			{

				std::string bitmapAddress = ChangeBitmapColor(index, color_Green).string();

				wxBitmap bitmap(bitmapAddress, wxBITMAP_TYPE_BMP);
				m_staticBitmap[bitmapIndexByInputNumber]->SetBitmap(bitmap);

				HoldPathOfThisBitmap(index, bitmapAddress);
			}

		}
		else if (event.ControlDown())
		{
			int index = (keyCode - '1');


			if (index >= 0 && index < m_coloumn)
			{
				std::string bitmapAddress = ChangeBitmapColor(index, color_Yellow).string();

				wxBitmap bitmap(bitmapAddress, wxBITMAP_TYPE_BMP);
				m_staticBitmap[bitmapIndexByInputNumber]->SetBitmap(bitmap);

				HoldPathOfThisBitmap(index, bitmapAddress);
			}
		}
		else
		{
			int index = (keyCode - '1'); // On number input from 1 to 5

			if (index >= 0 && index < m_coloumn)
			{
				std::string bitmapAddress = ChangeBitmapColor(index, color_Black).string();

				wxBitmap bitmap(bitmapAddress, wxBITMAP_TYPE_BMP);
				m_staticBitmap[bitmapIndexByInputNumber]->SetBitmap(bitmap);

				HoldPathOfThisBitmap(index, bitmapAddress);//
			}

		}
	}
	else if (((keyCode >= 'A' && keyCode <= 'Z') || (keyCode >= 'a' && keyCode <= 'z')) &&
		(currentBitmapIndex <= lastIndexOfRow))
	{

		m_userInputLetters += char(keyCode);

		int alphabetsIndex = keyCode - 'A';


		fs::path alphabetsChildDirectory = m_alphabetsChildDirectories[alphabetsIndex].string() + "\\";

		fs::path alphabetsPath = ChangeTheBitmapPathAsPerTheColor(m_bitmapPathHolder[bitmapPathHolderIndex], alphabetsChildDirectory);

		wxBitmap bitmap(wxString(alphabetsPath.string()), wxBITMAP_TYPE_BMP);

		m_staticBitmap[currentBitmapIndex]->SetBitmap(bitmap);

		m_bitmapPathHolder[bitmapPathHolderIndex] = alphabetsPath;

	}


	event.Skip();
}

void Frame::SetAlphabetWithStaticBitmap(int keyCode, int bitmapIndex, int bitmapPathHolderIndex, std::string AlphabetColor)
{
	int alphabetsIndex = keyCode - 'A';

	fs::path alphabetsPath = m_alphabetsChildDirectories[alphabetsIndex].string() + "\\" + AlphabetColor + ".bmp";;

	wxBitmap bitmap(wxString(alphabetsPath.string()), wxBITMAP_TYPE_BMP);

	m_staticBitmap[bitmapIndex]->SetBitmap(bitmap);

	m_bitmapPathHolder[bitmapPathHolderIndex] = alphabetsPath;
}

std::string Frame::GetBlackLetters(fs::path bitmapPathHolder[], std::string& inputLetters)
{
	std::string letters = "";
	std::string black = "Black";

	for (int x = 0; x < m_coloumn; x++)
	{
		if (bitmapPathHolder[x].stem().string() == black)
			letters += inputLetters[x];
	}
	return letters;
}

std::string Frame::GetYellowLetters(fs::path bitmapPathHolder[], std::string& inputLetters)
{
	std::string yellow = "Yellow";
	std::string letters;

	for (int x = 0; x < m_coloumn; x++)
	{
		if (bitmapPathHolder[x].stem().string() == yellow)
			letters += inputLetters[x];
		else
			letters += '*';
	}
	return letters;
}

std::string Frame::GetGreenLetters(fs::path bitmapPathHolder[], std::string& inputLetters)
{
	std::string green = "Green";
	std::string letters;

	for (int x = 0; x < m_coloumn; x++)
	{
		if (bitmapPathHolder[x].stem().string() == green)
			letters += inputLetters[x];
		else
			letters += '*';
	}
	return letters;
}


void Frame::ResetBitmapPathHolders()
{
	for (int i = 0; i < m_coloumn; i++)
	{
		m_bitmapPathHolder[i] = m_background_black_path;
	}
}

void Frame::EnableStaticBitmap(int rowIndex)
{
	int firstStaticBitmapIndexOftheRow = (rowIndex - 1) * m_coloumn;
	int lastStaticBitmapIndexOftheRow = firstStaticBitmapIndexOftheRow + m_coloumn;

	for (int index = firstStaticBitmapIndexOftheRow; index < lastStaticBitmapIndexOftheRow; index++)
	{
		m_staticBitmap[index]->Enable(true);
		//m_staticBitmap[index]->SetBitmap(m_backgroundBlackBitmap);
	}
}

void Frame::DisableStaticBitmap(int rowIndex)
{
	int firstStaticBitmapIndexOftheRow = (rowIndex - 1) * m_coloumn;
	int lastStaticBitmapIndexOftheRow = firstStaticBitmapIndexOftheRow + m_coloumn;

	for (int index = firstStaticBitmapIndexOftheRow; index < lastStaticBitmapIndexOftheRow; index++)
	{
		m_staticBitmap[index]->Enable(false);
		//m_staticBitmap[index]->SetBitmap(m_staticBitmap[index]->GetBitmap().ConvertToDisabled());
	}
}

void Frame::DisableStaticBitmapInRange(int rowIndex_begin, int rowIndex_end)
{
	for (int index = rowIndex_begin; index <= rowIndex_end; index++)
	{
		m_staticBitmap[index]->Enable(false);

		//Turning the image to grey		
		//m_staticBitmap[index]->SetBitmap(m_staticBitmap[index]->GetBitmap().ConvertToDisabled());
	}
}

fs::path Frame::GetTheBackgroundBitmapAsPerColor(fs::path bitmapPathHolder[], int index)
{
	fs::path bitmapFileName = bitmapPathHolder[index].filename();
	for (fs::path x : fs::directory_iterator(m_backgroundDirectoryLocation))
	{
		if (bitmapFileName == x.filename())
		{
			return x;
		}
	}
}
void Frame::EraseTheLastChar(std::string& userInputCharacters)
{
	int lastCharIndex = m_userInputLetters.size() - 1;
	m_userInputLetters.erase(lastCharIndex, 1);
}

fs::path Frame::ChangeTheBitmapPathAsPerTheColor(fs::path& currentBitmap, fs::path& destDirectory)
{
	//Get the Child files
	std::vector<fs::path> childFiles;
	for (fs::path x : fs::directory_iterator(destDirectory))
	{
		childFiles.push_back(x);
	}

	//Get the file path that matched with the current bitmap color
	for (fs::path x : childFiles)
	{
		if (currentBitmap.filename() == x.filename())
			return x;
	}
}
void Frame::OnEnter(wxCommandEvent& event)
{

	wxMessageBox("ladsfdsf");

}

void Frame::StoreBitmapPathOfEveryRow()
{
	for (int i = 0; i < m_coloumn; i++)
		m_bitmapPathHolder[i] = m_background_black_path;
}

void Frame::OnBitmapClicked(wxMouseEvent& event)
{

	wxStaticBitmap* clickedBitmap = dynamic_cast<wxStaticBitmap*>(event.GetEventObject());

	int staticBitmapID = event.GetId(); //ID in wxStaticBitmap has a starting from 0 to 29 & this is to use these ID as index
	int index = staticBitmapID % m_coloumn; //m_bitmapPath[] stores last image path of a row of wxStaticBitmap	


	if (event.ControlDown() && event.ShiftDown())
	{
		std::string bitmapAddress = ChangeBitmapColor(index, "Green").string();

		wxBitmap bitmap(bitmapAddress, wxBITMAP_TYPE_BMP);
		clickedBitmap->SetBitmap(bitmap);

		HoldPathOfThisBitmap(index, bitmapAddress);
	}
	else if (wxGetKeyState(WXK_CONTROL))
	{
		std::string bitmapAddress = ChangeBitmapColor(index, "Yellow").string();

		wxBitmap bitmap(bitmapAddress, wxBITMAP_TYPE_BMP);
		clickedBitmap->SetBitmap(bitmap);

		HoldPathOfThisBitmap(index, bitmapAddress);
	}
	else
	{
		std::string bitmapAddress = ChangeBitmapColor(index, "Black").string();

		wxBitmap bitmap(bitmapAddress, wxBITMAP_TYPE_BMP);
		clickedBitmap->SetBitmap(bitmap);

		HoldPathOfThisBitmap(index, bitmapAddress);//Can't get image path staticBitmap so storing the path manually in a var per single row
	}

}

fs::path Frame::ChangeBitmapColor(int bitmapIndex, std::string changeColorTo)
{

	fs::path parentPath = m_bitmapPathHolder[bitmapIndex].parent_path().string() + "\\";

	std::vector<fs::path> childDirectories;

	for (fs::path x : fs::directory_iterator(parentPath))
	{
		std::string currentPath = x.filename().stem().string();
		if (currentPath == changeColorTo)
			return x;
	}

}
void Frame::HoldPathOfThisBitmap(int index, std::string& bitmapPath)
{
	m_bitmapPathHolder[index] = bitmapPath;
}

char Frame::GetAlphabet(wxString& text)
{
	char alphabet = text[text.length()];

	return alphabet;
}

int Frame::GetAlphabetPos(wxString& text)
{
	int textLength = text.length();
	return textLength;
}

void Frame::OnPressingKey(wxString& text)
{
	char character = GetAlphabet(text);
	int currentPos = GetAlphabetPos(text);

	bool isAlphabet = (character >= 65 && character <= 90) || (character >= 97 && character <= 122);
	bool isNumber = character >= 49 && character <= 53;// 1..m_coloumn

	if (isAlphabet)
		OnPressingAlphabeticalKeys(character, currentPos);
	else if (isNumber)
		OnPressingNumericalKeys(character); // To change alphabets Colors by numbers
	else
		OnPressingModifierKeys(character);


}

void Frame::OnPressingAlphabeticalKeys(char alphabet, int currentPos)
{

}

void Frame::OnPressingNumericalKeys(char number)
{

}
void Frame::OnPressingModifierKeys(char modifierKey)
{

}

void Frame::OnPressingBackSpace(int& currentPos, int lastPos)
{
	if (lastPos > currentPos)
		currentPos = lastPos;
}


void Frame::FiveBySixSquareBody(wxBoxSizer* m_bSizerBody)
{

	wxString backgroundPath_str = m_background_black_path.string();

	wxBoxSizer* bSizerRow1;
	bSizerRow1 = new wxBoxSizer(wxHORIZONTAL);

	m_staticBitmap[0] = new wxStaticBitmap(m_panel1, m_StaticBitmapId[0], wxBitmap(backgroundPath_str, wxBITMAP_TYPE_ANY), wxPoint(50, 0), wxSize(45, 45), 0);
	bSizerRow1->Add(m_staticBitmap[0], 0, wxALL, 5);

	m_staticBitmap[1] = new wxStaticBitmap(m_panel1, m_StaticBitmapId[1], wxBitmap(backgroundPath_str, wxBITMAP_TYPE_ANY), wxPoint(50, 0), wxSize(45, 45), 0);
	bSizerRow1->Add(m_staticBitmap[1], 0, wxALL, 5);

	m_staticBitmap[2] = new wxStaticBitmap(m_panel1, m_StaticBitmapId[2], wxBitmap(backgroundPath_str, wxBITMAP_TYPE_ANY), wxPoint(50, 0), wxSize(45, 45), 0);
	bSizerRow1->Add(m_staticBitmap[2], 0, wxALL, 5);

	m_staticBitmap[3] = new wxStaticBitmap(m_panel1, m_StaticBitmapId[3], wxBitmap(backgroundPath_str, wxBITMAP_TYPE_ANY), wxPoint(50, 0), wxSize(45, 45), 0);
	bSizerRow1->Add(m_staticBitmap[3], 0, wxALL, 5);

	m_staticBitmap[4] = new wxStaticBitmap(m_panel1, m_StaticBitmapId[4], wxBitmap(backgroundPath_str, wxBITMAP_TYPE_ANY), wxPoint(50, 0), wxSize(45, 45), 0);
	bSizerRow1->Add(m_staticBitmap[4], 0, wxALL, 5);


	m_bSizerBody->Add(bSizerRow1, 0, 0, 0);

	wxBoxSizer* bSizerRow2;
	bSizerRow2 = new wxBoxSizer(wxHORIZONTAL);

	m_staticBitmap[5] = new wxStaticBitmap(m_panel1, m_StaticBitmapId[5], wxBitmap(backgroundPath_str, wxBITMAP_TYPE_ANY), wxPoint(50, 0), wxSize(45, 45), 0);
	bSizerRow2->Add(m_staticBitmap[5], 0, wxALL, 5);

	m_staticBitmap[6] = new wxStaticBitmap(m_panel1, m_StaticBitmapId[6], wxBitmap(backgroundPath_str, wxBITMAP_TYPE_ANY), wxPoint(50, 0), wxSize(45, 45), 0);
	bSizerRow2->Add(m_staticBitmap[6], 0, wxALL, 5);

	m_staticBitmap[7] = new wxStaticBitmap(m_panel1, m_StaticBitmapId[7], wxBitmap(backgroundPath_str, wxBITMAP_TYPE_ANY), wxPoint(50, 0), wxSize(45, 45), 0);
	bSizerRow2->Add(m_staticBitmap[7], 0, wxALL, 5);

	m_staticBitmap[8] = new wxStaticBitmap(m_panel1, m_StaticBitmapId[8], wxBitmap(backgroundPath_str, wxBITMAP_TYPE_ANY), wxPoint(50, 0), wxSize(45, 45), 0);
	bSizerRow2->Add(m_staticBitmap[8], 0, wxALL, 5);

	m_staticBitmap[9] = new wxStaticBitmap(m_panel1, m_StaticBitmapId[9], wxBitmap(backgroundPath_str, wxBITMAP_TYPE_ANY), wxPoint(50, 0), wxSize(45, 45), 0);
	bSizerRow2->Add(m_staticBitmap[9], 0, wxALL, 5);


	m_bSizerBody->Add(bSizerRow2, 1, 0, 5);

	wxBoxSizer* bSizerRow3;
	bSizerRow3 = new wxBoxSizer(wxHORIZONTAL);

	m_staticBitmap[10] = new wxStaticBitmap(m_panel1, m_StaticBitmapId[10], wxBitmap(backgroundPath_str, wxBITMAP_TYPE_ANY), wxPoint(50, 0), wxSize(45, 45), 0);
	bSizerRow3->Add(m_staticBitmap[10], 0, wxALL, 5);

	m_staticBitmap[11] = new wxStaticBitmap(m_panel1, m_StaticBitmapId[11], wxBitmap(backgroundPath_str, wxBITMAP_TYPE_ANY), wxPoint(50, 0), wxSize(45, 45), 0);
	bSizerRow3->Add(m_staticBitmap[11], 0, wxALL, 5);

	m_staticBitmap[12] = new wxStaticBitmap(m_panel1, m_StaticBitmapId[12], wxBitmap(backgroundPath_str, wxBITMAP_TYPE_ANY), wxPoint(50, 0), wxSize(45, 45), 0);
	bSizerRow3->Add(m_staticBitmap[12], 0, wxALL, 5);

	m_staticBitmap[13] = new wxStaticBitmap(m_panel1, m_StaticBitmapId[13], wxBitmap(backgroundPath_str, wxBITMAP_TYPE_ANY), wxPoint(50, 0), wxSize(45, 45), 0);
	bSizerRow3->Add(m_staticBitmap[13], 0, wxALL, 5);

	m_staticBitmap[14] = new wxStaticBitmap(m_panel1, m_StaticBitmapId[14], wxBitmap(backgroundPath_str, wxBITMAP_TYPE_ANY), wxPoint(50, 0), wxSize(45, 45), 0);
	bSizerRow3->Add(m_staticBitmap[14], 0, wxALL, 5);


	m_bSizerBody->Add(bSizerRow3, 1, 0, 5);

	wxBoxSizer* bSizerRow4;
	bSizerRow4 = new wxBoxSizer(wxHORIZONTAL);

	m_staticBitmap[15] = new wxStaticBitmap(m_panel1, m_StaticBitmapId[15], wxBitmap(backgroundPath_str, wxBITMAP_TYPE_ANY), wxPoint(50, 0), wxSize(45, 45), 0);
	bSizerRow4->Add(m_staticBitmap[15], 0, wxALL, 5);

	m_staticBitmap[16] = new wxStaticBitmap(m_panel1, m_StaticBitmapId[16], wxBitmap(backgroundPath_str, wxBITMAP_TYPE_ANY), wxPoint(50, 0), wxSize(45, 45), 0);
	bSizerRow4->Add(m_staticBitmap[16], 0, wxALL, 5);

	m_staticBitmap[17] = new wxStaticBitmap(m_panel1, m_StaticBitmapId[17], wxBitmap(backgroundPath_str, wxBITMAP_TYPE_ANY), wxPoint(50, 0), wxSize(45, 45), 0);
	bSizerRow4->Add(m_staticBitmap[17], 0, wxALL, 5);

	m_staticBitmap[18] = new wxStaticBitmap(m_panel1, m_StaticBitmapId[18], wxBitmap(backgroundPath_str, wxBITMAP_TYPE_ANY), wxPoint(50, 0), wxSize(45, 45), 0);
	bSizerRow4->Add(m_staticBitmap[18], 0, wxALL, 5);

	m_staticBitmap[19] = new wxStaticBitmap(m_panel1, m_StaticBitmapId[19], wxBitmap(backgroundPath_str, wxBITMAP_TYPE_ANY), wxPoint(50, 0), wxSize(45, 45), 0);
	bSizerRow4->Add(m_staticBitmap[19], 0, wxALL, 5);


	m_bSizerBody->Add(bSizerRow4, 1, 0, 5);

	wxBoxSizer* bSizerRow5;
	bSizerRow5 = new wxBoxSizer(wxHORIZONTAL);

	m_staticBitmap[20] = new wxStaticBitmap(m_panel1, m_StaticBitmapId[20], wxBitmap(backgroundPath_str, wxBITMAP_TYPE_ANY), wxPoint(50, 0), wxSize(45, 45), 0);
	bSizerRow5->Add(m_staticBitmap[20], 0, wxALL, 5);

	m_staticBitmap[21] = new wxStaticBitmap(m_panel1, m_StaticBitmapId[21], wxBitmap(backgroundPath_str, wxBITMAP_TYPE_ANY), wxPoint(50, 0), wxSize(45, 45), 0);
	bSizerRow5->Add(m_staticBitmap[21], 0, wxALL, 5);

	m_staticBitmap[22] = new wxStaticBitmap(m_panel1, m_StaticBitmapId[22], wxBitmap(backgroundPath_str, wxBITMAP_TYPE_ANY), wxPoint(50, 0), wxSize(45, 45), 0);
	bSizerRow5->Add(m_staticBitmap[22], 0, wxALL, 5);

	m_staticBitmap[23] = new wxStaticBitmap(m_panel1, m_StaticBitmapId[23], wxBitmap(backgroundPath_str, wxBITMAP_TYPE_ANY), wxPoint(50, 0), wxSize(45, 45), 0);
	bSizerRow5->Add(m_staticBitmap[23], 0, wxALL, 5);

	m_staticBitmap[24] = new wxStaticBitmap(m_panel1, m_StaticBitmapId[24], wxBitmap(backgroundPath_str, wxBITMAP_TYPE_ANY), wxPoint(50, 0), wxSize(45, 45), 0);
	bSizerRow5->Add(m_staticBitmap[24], 0, wxALL, 5);


	m_bSizerBody->Add(bSizerRow5, 1, 0, 5);

	wxBoxSizer* bSizerRow6;
	bSizerRow6 = new wxBoxSizer(wxHORIZONTAL);

	m_staticBitmap[25] = new wxStaticBitmap(m_panel1, m_StaticBitmapId[25], wxBitmap(backgroundPath_str, wxBITMAP_TYPE_ANY), wxPoint(50, 0), wxSize(45, 45), 0);
	bSizerRow6->Add(m_staticBitmap[25], 0, wxALL, 5);

	m_staticBitmap[26] = new wxStaticBitmap(m_panel1, m_StaticBitmapId[26], wxBitmap(backgroundPath_str, wxBITMAP_TYPE_ANY), wxPoint(50, 0), wxSize(45, 45), 0);
	bSizerRow6->Add(m_staticBitmap[26], 0, wxALL, 5);

	m_staticBitmap[27] = new wxStaticBitmap(m_panel1, m_StaticBitmapId[27], wxBitmap(backgroundPath_str, wxBITMAP_TYPE_ANY), wxPoint(50, 0), wxSize(45, 45), 0);
	bSizerRow6->Add(m_staticBitmap[27], 0, wxALL, 5);

	m_staticBitmap[28] = new wxStaticBitmap(m_panel1, m_StaticBitmapId[28], wxBitmap(backgroundPath_str, wxBITMAP_TYPE_ANY), wxPoint(50, 0), wxSize(45, 45), 0);
	bSizerRow6->Add(m_staticBitmap[28], 0, wxALL, 5);

	m_staticBitmap[29] = new wxStaticBitmap(m_panel1, m_StaticBitmapId[29], wxBitmap(backgroundPath_str, wxBITMAP_TYPE_ANY), wxPoint(50, 0), wxSize(45, 45), 0);
	bSizerRow6->Add(m_staticBitmap[29], 0, wxALL, 5);


	m_bSizerBody->Add(bSizerRow6, 1, 0, 5);

	m_panel1->SetSizer(m_bSizerBody);
	m_panel1->Layout();
	m_bSizerBody->Fit(m_panel1);
	m_bSizerFrameMain->Add(m_panel1, 0, wxALIGN_CENTER | wxALL, 5);
}

void Frame::OnClikingAnyBitMapImage()
{
	for (int i = 0; i <= m_LastIndexOfStaticBitmap; i++)
		m_staticBitmap[i]->Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(Frame::OnBitmapClicked), NULL, this);

}


Frame::~Frame()
{

	m_panel1->Disconnect(wxEVT_CHAR_HOOK, wxKeyEventHandler(Frame::OnCharHook));

	delete m_CwordleSolver;

	delete[] m_bitmapPathHolder;

	
}


