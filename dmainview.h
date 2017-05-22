
#ifndef DMAINVIEW_H
#define DMAINVIEW_H

#include <qobject.h>

class DOpenglWidget;
class QMainWindow;
class QApplication;
class DMainModel;
class QMenu;
class QMenuBar;
class QAction;

class DMainView : public QObject
{
	Q_OBJECT

public:
	explicit DMainView();
	virtual ~DMainView();

	void InitUI(QApplication *app);
	void Show();

public slots:
	void ExampleAction(QAction *action);
	void ModeAction(QAction *action);

private:
	QMainWindow *window_;
	DOpenglWidget *gl_widget_;
	DMainModel *model_;

	QMenuBar *menu_bar_;
	QMenu *example_menu_;
	QMenu *mode_menu_;
	QAction *last_example_action_;

};

#endif // !DMAINVIEW_H




