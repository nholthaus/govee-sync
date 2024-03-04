#include <Windows.h>

#include <QApplication>
#include <QMainWindow>

//======================================================================================================================
//     MAIN FUNCTION
//======================================================================================================================
int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  QMainWindow w;
  w.show();

  return QApplication::exec();
}