#include "reminder_dialog.h"

FXDEFMAP(ReminderDialog) ReminderDialogMap[] = {
  FXMAPFUNC(SEL_CHANGED, ReminderDialog::ID_DESCRIPTION,
		  ReminderDialog::updateDescription),
  FXMAPFUNC(SEL_CHANGED, ReminderDialog::ID_SLEEPTIME,
		  ReminderDialog::updateTime),
  FXMAPFUNC(SEL_COMMAND, ReminderDialog::ID_SLEEPTIME,
		  ReminderDialog::changeFocus),
  FXMAPFUNC(SEL_COMMAND, ReminderDialog::ID_DESCRIPTION,
		  ReminderDialog::onCmdAccept),
};

FXIMPLEMENT(ReminderDialog, FXDialogBox, ReminderDialogMap,
		ARRAYNUMBER(ReminderDialogMap));

ReminderDialog::ReminderDialog(FXApp *app) :
	FXDialogBox(app, "New Reminder", DECOR_TITLE|DECOR_BORDER,
			0, 0, 300, 125)
{	
	mainFrame = new FXVerticalFrame(this, LAYOUT_FILL_X | LAYOUT_FILL_Y);
	timeFrame = new FXHorizontalFrame(mainFrame, LAYOUT_FILL_X, 0,0,0,50);
	descrFrame = new FXHorizontalFrame(mainFrame, LAYOUT_FILL_X, 0,0,0,50);
	buttonFrame = new FXHorizontalFrame(mainFrame, LAYOUT_FILL_X,0,0,0,50);

	new FXLabel(timeFrame, FXString("Time (in minutes):"));
	timeField = new FXTextField(timeFrame, 4, this, ID_SLEEPTIME,
			TEXTFIELD_NORMAL | TEXTFIELD_INTEGER);

	new FXLabel(descrFrame, FXString("Description:"));
	descrField = new FXTextField(descrFrame, 30, this, ID_DESCRIPTION);

	new FXButton(buttonFrame, "Ok", NULL, this, ID_ACCEPT,
			BUTTON_NORMAL | LAYOUT_FILL_X);
	new FXButton(buttonFrame, "Cancel", NULL, this, ID_CANCEL,
			BUTTON_NORMAL | LAYOUT_FILL_X);
}

ReminderDialog::~ReminderDialog()
{
	delete timeField;
	delete descrField;
	delete timeFrame;
	delete descrFrame;
	delete buttonFrame;
	delete mainFrame;
}

void ReminderDialog::create()
{
	FXDialogBox::create();
	timeField->setFocus();
}

const FXchar *ReminderDialog::getDescription()
{
	return description.text();
}

unsigned long ReminderDialog::getTime()
{
	return sleepTime.toUInt() * 60000000000;
}

long ReminderDialog::updateDescription(FXObject*, FXSelector, void *data)
{
	description.assign((FXchar*)data);
	return 1;
}

long ReminderDialog::updateTime(FXObject*, FXSelector, void *data)
{
	sleepTime.assign((FXchar*)data);
	return 1;
}

long ReminderDialog::changeFocus(FXObject*, FXSelector, void *)
{
	descrField->setFocus();
	return 1;
}
