//Inclusão de headers
#include "SessaoAtual.h"
#include "ui_frmSessaoAtual.h"

//--------------------------CONSTRUTOR-DESTRUTOR DA UI----------------------//

//Construtor
frmSessaoAtual::frmSessaoAtual(QFrame *parent) : QFrame(parent), ui(new Ui::frmSessaoAtual)
{
	ui -> setupUi(this);

	this -> setGeometry(QStyle::alignedRect
						(Qt::LeftToRight, Qt::AlignCenter, this -> size(),
						 qApp -> desktop() -> availableGeometry()));

	//Ativando o timer
	ConectarSlots();
}

//Destrutor
frmSessaoAtual::~frmSessaoAtual()
{
    delete ui;

	delete timer;
}

//--------------------------EVENTOS DA UI----------------------------------//

void frmSessaoAtual::on_btnRetornar_clicked()
{
    close();	
}

//--------------------------MÉTODOS DA UI----------------------------------//

void frmSessaoAtual::ConectarSlots()
{
	//Nova instância do timer
	timer = new QTimer();

	//Conectando um evento ao método
	connect(timer, SIGNAL(timeout()), this, SLOT(SetarTexto()));

	//Inicializando o timer
	timer -> start(1000);
}

void frmSessaoAtual::SetarTexto()
{
	//Setando Texto do Label
	ui -> lblTempo -> setText("Tempo atual da sessão : ");

	//QDateTime dataAtual = QDateTime::currentDateTime().fromString(termino, "yyyy-MM-dd hh:mm:ss");
	QDateTime dataAtual = QDateTime::currentDateTime();

	//Definindo a diferença entre elas
	minutos = (entrada.secsTo(dataAtual) / 60);
	segundos = (entrada.secsTo(dataAtual) - (minutos * 60));
	horas = minutos / 60;

	//Setando tempo atual
	QString tempoAtual = ui -> lblTempo -> text() + QString::number(horas) + ':' +
						 QString::number(minutos) + ':' + QString::number(segundos);

	//Setando o label
	ui -> lblTempo -> setText(tempoAtual);
}
