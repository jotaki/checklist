#include <fx.h>
#include "checklist.h"

int main(int argc, char *argv[])
{
	FXApp app("Checklist", "Checklist");

	app.init(argc, argv);
	new Checklist(&app);
	app.create();

	return app.run();
}
