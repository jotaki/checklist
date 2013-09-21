#ifndef REMINDER_DIALOG_H_
# define REMINDER_DIALOG_H_

# include <fx.h>

class ReminderDialog : public FXDialogBox
{
	FXDECLARE(ReminderDialog);

public:
	ReminderDialog(FXApp *app);
	virtual ~ReminderDialog();
	
	enum {
		ID_DESCRIPTION = FXDialogBox::ID_LAST,

		ID_LAST
	};
protected:
	ReminderDialog() {}

private:
	FXVerticalFrame *mainFrame;
	FXHorizontalFrame *timeFrame, *descrFrame, *buttonFrame;
	FXTextField *timeField, *descrField;
	FXString description;

public:
	const FXchar *getDescription();

	long updateDescription(FXObject *, FXSelector, void*);
};

#endif	/* !REMINDER_DIALOG_H_ */
