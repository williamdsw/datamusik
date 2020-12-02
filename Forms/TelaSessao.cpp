//Inclusão de headers
#include "TelaSessao.h"
#include "ui_frmTelaSessao.h"

//--------------------------CONSTRUTOR-DESTRUTOR DA UI----------------------//

//Construtor
frmTelaSessao::frmTelaSessao(QWidget *parent) : QWidget(parent), ui(new Ui::frmTelaSessao)
{
	//Setando a ui para o form
	ui -> setupUi(this);

	//Setando para o form ficar no centro da tela
	this -> setGeometry(QStyle::alignedRect
						(Qt::LeftToRight, Qt::AlignCenter, this -> size(),
						 qApp -> desktop() -> availableGeometry()));
}

//Destrutor
frmTelaSessao::~frmTelaSessao()
{
	delete ui;
}

//--------------------------EVENTOS DA UI----------------------------------//

void frmTelaSessao::on_btnRetornar_clicked()
{
	close();
}

//--------------------------MÉTODOS DA UI----------------------------------//
