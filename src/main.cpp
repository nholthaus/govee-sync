#include <Windows.h>

#include <QApplication>
#include <QMainWindow>
#include <QIcon>
#include <QTimer>

#include "govee.h"

#include <thread>

//----------------------------
//  USING DECLARATIONS
//----------------------------

using namespace std::chrono_literals;

// Run once the event loop starts
#define RUN_ONCE_STARTED(expression) QTimer::singleShot(0, [&] { expression; });

//======================================================================================================================
//     MAIN FUNCTION
//======================================================================================================================
int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	QMainWindow  w;
	w.setWindowIcon(QIcon(":/icons/govee"));
	w.setMinimumSize(QSize(400, 300));
	w.setMaximumSize(QSize(400, 300));
	w.setStyleSheet("background-color: #404040;"); // Dark gray color
	w.show();

	Govee govee;

	return QApplication::exec();
}