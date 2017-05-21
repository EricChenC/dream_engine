#include "dmainview.h"
#include "dopenglwidget.h"
#include "dmainmodel.h"

#include <qmainwindow.h>
#include <qapplication.h>
#include <qdesktopwidget.h>
#include <qmenu.h>
#include <qmenubar.h>
#include <qlist.h>
#include <qaction.h>

DMainView::DMainView()
{
	model_ = new DMainModel();
	model_->InitModel();
}

DMainView::~DMainView()
{
	delete model_;
	delete gl_widget_;
	delete example_menu_;
	delete menu_bar_;
	delete window_;
}

void DMainView::InitUI(QApplication *app)
{
	window_ = new QMainWindow();
	gl_widget_ = new DOpenglWidget();
	window_->setCentralWidget(gl_widget_);
	QRect rect = app->desktop()->screenGeometry();

	// for active mouse and keyboard event
	gl_widget_->setFocusPolicy(Qt::StrongFocus);
	gl_widget_->set_view(model_->get_view()); // default view
	window_->setGeometry(rect.width() / 4, rect.height() / 4, 800, 600);

	menu_bar_ = window_->menuBar();
	example_menu_ = menu_bar_->addMenu("example");
	QList<QString> examples = model_->get_projects();
	for (int i = 0; i < examples.size(); ++i) {
		example_menu_->addAction(examples.at(i));
	}

	mode_menu_ = menu_bar_->addMenu("mode");
	QList<QString> modes = model_->get_modes();
	for (int j = 0; j < modes.size(); ++j) {
		mode_menu_->addAction(modes.at(j));
	}

	connect(example_menu_, SIGNAL(triggered(QAction *)), this, SLOT(ExampleAction(QAction *)));
	connect(mode_menu_, SIGNAL(triggered(QAction *)), this, SLOT(ModeAction(QAction *)));

}

void DMainView::Show()
{
	window_->show();
}

void DMainView::ModeAction(QAction * action)
{
	model_->set_polygon_mode(action->text());
}

void DMainView::ExampleAction(QAction *action) {
	if (last_example_action_ == action) {
		return;
	}

	last_example_action_ = action;
	gl_widget_->set_view(model_->get_view(action->text()));
	gl_widget_->init_view();
	model_->ClearOldView();
}


