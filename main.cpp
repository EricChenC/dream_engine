#include <QApplication>

#include "dmainview.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	DMainView view;
	view.InitUI(&app);
	view.Show();

	return app.exec();
}