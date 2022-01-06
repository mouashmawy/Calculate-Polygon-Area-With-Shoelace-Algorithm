#include "ActionCalcArea.h"
#include "..\ApplicationManager.h"
#include <string>
#include <iostream>

ActionCalcArea::ActionCalcArea(ApplicationManager *pApp):Action(pApp)
{
}

ActionCalcArea::~ActionCalcArea(void)
{
}

void ActionCalcArea::Execute()
{

	UI* pUI = pManager->GetUI();
	pUI->PrintMsg("Start Drawing your simple polygon");
	int ptsCount = -1; //-1 because user will press a dot more
	struct pt {int x, y;};

	pt* ptsList = new pt[200];
	int maxpts = 200;
	for (int i = 0; i < maxpts; i++) {
		ptsCount++;
		cout << ptsCount;
		pUI->GetPointClicked(ptsList[i].x, ptsList[i].y);
		
		int rounding = 20;
		ptsList[i].x = round(double(ptsList[i].x) / rounding) * rounding;
		ptsList[i].y = round(double(ptsList[i].y) / rounding) * rounding;

		if (i == 0) { continue;
		pUI->DrawLine(ptsList[i].x, ptsList[i].y, ptsList[i].x, ptsList[i].y);}
		pUI->DrawLine(ptsList[i-1].x, ptsList[i-1].y, ptsList[i].x, ptsList[i].y);
		if (i != 0 && ptsList[0].x == ptsList[i].x && ptsList[0].y == ptsList[i].y) break;
	}

	float area = 0;
	for (int i = 0; i < ptsCount ; i++) {
		area += (
			(ptsList[i+1].x + ptsList[i].x)
			*
			(ptsList[i+1].y - ptsList[i].y)
			) / 2;
	}
	area /= pUI->PixelPerCm()* pUI->PixelPerCm()/4;
	
	area = abs( int(area * 10) / 10.f );

	pUI->PrintMsg("The area is "+to_string(area));

}

void ActionCalcArea::Undo()
{}

void ActionCalcArea::Redo()
{}

