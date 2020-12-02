//definição do header
#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H


#include <../Forms/Logon.h>

//inclusão de biblotecas
#include <QWidget>
#include <QTimer>

namespace Ui
{
	class frmSplashScreen;
}

class frmSplashScreen : public QWidget
{
	Q_OBJECT

	public:

		//Construtor
		explicit frmSplashScreen(QWidget *parent = 0);

		//Destrutor
		~frmSplashScreen();

	private:

		//ponteiros
		Ui::frmSplashScreen *ui;
		QTimer *timerIn, *timerOut, *timerProgresso;

		//Variáveis
		double i;

	private slots:

		void InicializandoTimers();

		void FadeIn();

		void FadeOut();

		void BarraProgresso();
};

#endif
