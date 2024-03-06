#include <Windows.h>

#include <QApplication>
#include <QMainWindow>
#include <QIcon>

//======================================================================================================================
//     MAIN FUNCTION
//======================================================================================================================
int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  QMainWindow w;
  w.setWindowIcon(QIcon(":/icons/govee"));
// w.setWindowFlag(Qt::FramelessWindowHint);
  w.setMinimumSize(QSize(400,300));
  w.setMaximumSize(QSize(400,300));
  w.setStyleSheet("background-color: #404040;"); // Dark gray color
  w.show();

  return QApplication::exec();
}