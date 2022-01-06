#include "UI.h"

UI::UI()
{
	AppMode = DESIGN;	//Design Mode is the startup mode

	//Initilaize interface colors
	DrawColor = BLACK;
	SelectColor = BLUE;
	ConnColor = BLUE;
	MsgColor = BLUE;
	BkGrndColor = WHITE;
	
	//Create the drawing window
	pWind = new window(width, height, wx, wy);	


	ChangeTitle("Vector Calculus project Ashmawy & Morgan");
	PrintMsgX("Calculate your Area with Shoelace Algorithm", 250, 10,25);
	PrintMsgX("This is by Green's therom and like Planometer", 240, 40,25);

	PrintMsgX("program by Ashmawy & Morgan", 800, 10, 25);
	PrintMsgX("Supervision: Dr. Ashraf", 840, 40, 25);


	CreateDesignToolBar();	//Create the desgin toolbar
	CreateStatusBar();		//Create Status bar
	//DrawRuler();
	CreateGrid();
}


void UI::CreateGrid()
{
	for (int i = 0; i <= width; i += 20) {
		pWind->SetPen(REDX1, 1);
		pWind->DrawLine(i, ToolBarHeight, i, height - StatusBarHeight);
	}
	for (int i = 0; i <= height; i += 20) {
		pWind->SetPen(REDX1, 1);
		pWind->DrawLine(0, ToolBarHeight + i, width, ToolBarHeight + i);
	}

	for (int i = 0; i <= width; i += 40) {
		pWind->SetPen(REDX2, 1);
		pWind->DrawLine(i, ToolBarHeight, i, height - StatusBarHeight);
	}
	for (int i = 0; i <= height; i += 40) {
		pWind->SetPen(REDX2, 1);
		pWind->DrawLine(0, ToolBarHeight + i, width, ToolBarHeight + i);
	}

}



//======================================================================================//
//								Input Functions 										//
//======================================================================================//

void UI::GetPointClicked(int &x, int &y)
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string UI::GetSrting()
{
	//Reads a complete string from the user until the user presses "ENTER".
	//If the user presses "ESCAPE". This function should return an empty string.
	//"BACKSPACE" is also supported
	//User should see what he is typing at the status bar


	string userInput;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);

		switch(Key)
		{
		case 27: //ESCAPE key is pressed
			PrintMsg("");
			return ""; //returns nothing as user has cancelled the input
		
		case 13:		//ENTER key is pressed
			return userInput;
		
		case 8:		//BackSpace is pressed
			if(userInput.size() > 0)
				userInput.resize(userInput.size() -1 );
			break;
		
		default:
			userInput+= Key;
		};
		
		PrintMsg(userInput);
	}

}

//This function reads the position where the user clicks to determine the desired action
ActionType UI::GetUserAction() const
{	
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if (AppMode == DESIGN)	//application is in design mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / 2 / ToolItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_RES:	return ADD;

			default: return DSN;	//A click on empty place in desgin toolbar

			}
		}


	}
}

void UI::DrawLine(int x1, int y1, int x2, int y2)
{
	pWind->SetPen(BLUE, 3);
	pWind->DrawLine(x1, y1, x2, y2);
}



//======================================================================================//
//								Output Functions										//
//======================================================================================//

//////////////////////////////////////////////////////////////////////////////////
void UI::ChangeTitle(string Title) const
{
	pWind->ChangeTitle(Title);
}
//////////////////////////////////////////////////////////////////////////////////
void UI::CreateStatusBar() const
{
	pWind->SetPen(RED,3);
	pWind->DrawLine(0, height-StatusBarHeight, width, height-StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////
void UI::PrintMsg(string msg) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = StatusBarHeight - 10;

	// Print the Message
    pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial"); 
	pWind->SetPen(MsgColor); 
	pWind->DrawString(MsgX, height - MsgY, msg);
}


void UI::PrintMsgX(string msg,int x,int y, int f) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = StatusBarHeight - 10;

	// Print the Message
	pWind->SetFont(f, BOLD | ITALICIZED, BY_NAME, "Arial");
	pWind->SetPen(BLUE);
	pWind->DrawString(x, y, msg);
}

//////////////////////////////////////////////////////////////////////////////////
void UI::ClearStatusBar()const
{
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = StatusBarHeight - 10;

	//Overwrite using bachground color to erase the message
	pWind->SetPen(BkGrndColor);
	pWind->SetBrush(BkGrndColor);
	pWind->DrawRectangle(MsgX, height - MsgY, width, height);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Clears the drawing (degin) area
void UI::ClearDrawingArea() const
{
	pWind->SetPen(RED, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, ToolBarHeight, width, height - StatusBarHeight);
	
}
int UI::PixelPerCm()
{
	return Pixel_Per_Cm;
}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the Design mode
void UI::CreateDesignToolBar() 
{
	AppMode = DESIGN;	//Design Mode

	//You can draw the tool bar icons in any way you want.

	//First prepare List of images for each menu item
	string MenuItemImages[ITM_DSN_CNT];
	MenuItemImages[ITM_RES] = "images\\Menu\\Add.jpg";

	//TODO: Prepare image for each menu item and add it to the list

	//Draw menu item one image at a time
	for(int i=0; i<ITM_DSN_CNT; i++)
		pWind->DrawImage(MenuItemImages[i],i*ToolItemWidth,0,ToolItemWidth*2, ToolBarHeight);


	//Draw a line under the toolbar
	pWind->SetPen(RED,3);
	pWind->DrawLine(0, ToolBarHeight, width, ToolBarHeight);	

}


void UI::DrawRuler() {
	pWind->SetPen(RED, 2);

	for (int i = 1; i < width; i += Pixel_Per_Cm) {
		pWind->DrawLine(i, height - StatusBarHeight - 10, i, height-StatusBarHeight);

	}

	for (int i = ToolBarHeight+1; i < height- StatusBarHeight; i += Pixel_Per_Cm) {
		pWind->DrawLine(width-25,i,width,i);

	}
	



}




UI::~UI()
{
	delete pWind;
}