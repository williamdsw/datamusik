#include "../Forms/SplashScreen.h";
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	frmSplashScreen *frm = new frmSplashScreen();

	frm -> show();

    return a.exec();
}
