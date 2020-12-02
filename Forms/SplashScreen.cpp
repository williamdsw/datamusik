//inclusão de headers
#include "SplashScreen.h"
#include "ui_frmSplashScreen.h"

//--------------------------CONSTRUTOR-DESTRUTOR DA UI----------------------//

//Construtor
frmSplashScreen::frmSplashScreen(QWidget *parent) : QWidget(parent), ui(new Ui::frmSplashScreen)
{
	//Setando a ui do form
	ui -> setupUi(this);

	//Setando posição do form na tela
	this -> setGeometry(QStyle::alignedRect
						(Qt::LeftToRight, Qt::AlignCenter, this -> size(),
						 qApp -> desktop() -> availableGeometry()));

	//Esconde os itens de fechar e minimizar do form
	this -> setWindowFlag(Qt::FramelessWindowHint);

	//Chamada do método
	InicializandoTimers();
}

//Destrutor
frmSplashScreen::~frmSplashScreen()
{
	delete ui;
}

//--------------------------EVENTOS DA UI----------------------------------//

//--------------------------MÉTODOS DA UI----------------------------------//

void frmSplashScreen::InicializandoTimers()
{
	//Deixando o form "invisível"
	this -> setWindowOpacity(0);

	//Novas instâncias de timers
	timerIn = new QTimer();
	timerProgresso = new QTimer();

	//Conectando os métodos nos "eventos" - timeout() equivalente à Tick(?)
	connect(timerIn, SIGNAL(timeout()), this, SLOT(FadeIn()));
	connect(timerProgresso, SIGNAL(timeout()), this, SLOT(BarraProgresso()));

	//Iniciando os timers
	timerIn -> start(100);
	timerProgresso -> start(100);
}

//método para aparecer o form na tela
void frmSplashScreen::FadeIn()
{
	//Incrementa a opacidade
	i+= 0.05;

	//Se...
	if(i >= 1)
	{
		//Totalmente visível
		this -> setWindowOpacity(1);

		//Para o timer
		timerIn -> stop();

		delete timerIn;

		return;
	}

	//Setando a opacidade...
	this -> setWindowOpacity(i);
}

//Método para desaparecer o form na tela
void frmSplashScreen::FadeOut()
{
	//decrementa a opacidade
	i -= 0.05;

	//Se...
	if(i <= 0.01)
	{
		//"desaparece" a form
		this -> setWindowOpacity(0);

		//Para o timer
		timerOut -> stop();

		//Esconde o form
		this -> hide();

		//Nova instância de form de Logon
		frmLogon *frm = new frmLogon();

		//Mostra o form na tela
		frm -> show();

		delete timerOut;
	}

	//Seta a opacidade
	this -> setWindowOpacity(i);
}

//Método para mudar valor da Progress Bar
void frmSplashScreen::BarraProgresso()
{
	//Pega o valor da ProgressBar
	int valor = ui -> pgbProgresso -> value();

	//Se...
	if(valor < 100)
	{
		//Incrementa esse valor
		valor += 1;

		//Seta o valor
		ui -> pgbProgresso -> setValue(valor);
	}
	else
	{
		//Para o timer
		timerProgresso -> stop();

		//Nova instância de timer de FadeOut
		timerOut = new QTimer();

		//Conecta o método de fade out à um evento timeout (tick)
		connect(timerOut, SIGNAL(timeout()), this, SLOT(FadeOut()));

		//Inicializa o timer
		timerOut -> start(100);

		delete timerProgresso;
	}
}
