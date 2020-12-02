//Headers necessários
#include "Logon.h"
#include "ui_frmLogon.h"

//Headers secundários
#include "../Forms/TelaPrincipal.h"
#include "../Forms/CadastroUsuario.h"
#include "../Classes/Usuario.h"

#include <QDebug>

//--------------------------CONSTRUTOR-DESTRUTOR DA UI----------------------//

//Construtor com parâmetro inicializado
frmLogon::frmLogon(QWidget *parent) : QWidget(parent), ui(new Ui::frmLogon)
{
    ui -> setupUi(this);

	this -> setGeometry(QStyle::alignedRect
						(Qt::LeftToRight, Qt::AlignCenter, this -> size(),
						 qApp -> desktop() -> availableGeometry()));
}

//Destrutor
frmLogon::~frmLogon()
{
    //Deletando o ponteiro
    delete ui;
}

//--------------------------EVENTOS DA UI----------------------------------//

//Abrindo o form de cadastro
void frmLogon::on_btnNovo_clicked()
{
	//Irá criar uma nova instância
	frmCadastroUsuario *frm = new frmCadastroUsuario();

	//Setando o modality
	frm -> setWindowModality(Qt::ApplicationModal);

	//Mostrando na tela
	frm -> show();
}

//Logando no sistema
void frmLogon::on_btnLogar_clicked()
{
	//Instância da classe
    Usuario user;

	//Verificando a autenticação
    if(user.Autentica(ui -> txtNome -> text(), ui -> txtSenha -> text()))
    {
		//Criando uma query
		QSqlQuery query = user.RetornaDados(ui -> txtNome -> text());

		//Definindo Strings...
		QString texto = "Bem vindo, " + ui -> txtNome -> text() + "!";
		QString perfil;
		int idUsuario;

		//Pegando o perfil do usuário
		while(query.next())
		{
			idUsuario = query.value(0).toInt();
			perfil = query.value(3).toString();
		}

		//Messagem de boas vindas
		QMessageBox::information(this, "DataMusik v0.1", texto);

		//Ponteiro do form
		frmTelaPrincipal *main = new frmTelaPrincipal();

		//Mudando o valor text do Label
		main -> findChild<QLabel*>("lblUsuario") -> setText(texto);

		//Passando variáveis
		main -> idUser = idUsuario;

		main -> perfil = perfil;

		main -> Controle();

		main -> log = this;

		this -> hide();

		//Mostrando o formulário
		main -> show();
    }
    else
    {
		QMessageBox::critical(this, "Erro de autenticação",
							 "Usuário ou senha errada!");
    }
}

//Mudando Echo Mode
void frmLogon::on_txtSenha_textChanged(const QString &arg1)
{
	//Setando o EchoMode para Password
    ui -> txtSenha -> setEchoMode(QLineEdit::Password);

	(void)arg1;
}

//Resetando valor do LineEdit
void frmLogon::on_txtNome_editingFinished()
{
    if(ui -> txtNome -> text() == NULL)
    {
        ui -> txtNome -> setText("Nome de Logon*");
    }

	if(ui -> txtNome -> text() != NULL || ui -> txtNome -> text() != "Nome de Logon*")
	{
		Usuario *user = new Usuario();

		//Criando uma query
		QSqlQuery query = user -> RetornaDados(ui -> txtNome -> text());

		QString caminhoImagem;

		//Pegando o perfil do usuário
		while(query.next())
		{
			caminhoImagem = query.value(5).toString();
		}

		//Pegando imagem caso tenha no banco
		if(caminhoImagem != NULL)
		{
			QPixmap imagem(caminhoImagem);

			if(!imagem.isNull())
			{
				ui -> ptbImagem -> setStyleSheet("");
				ui -> ptbImagem -> setPixmap(imagem);
				ui -> ptbImagem -> setScaledContents(true);
			}
		}
		else
		{
			QString css = "border-image: url(:/Imagens/Others/Funcionario.png) 0 0 0 0 stretch stretch;";

			QPixmap imagem;

			ui -> ptbImagem -> setPixmap(imagem);
			ui -> ptbImagem -> setStyleSheet(css);
		}

		delete user;
	}
}

//Resetando valor do LineEdit
void frmLogon::on_txtSenha_editingFinished()
{
    if(ui -> txtSenha -> text() == NULL)
    {
        ui -> txtSenha -> setText("Senha*");
    }
}

//Quando o form for fechado, fechar o aplicativo
void frmLogon::closeEvent(QCloseEvent *event)
{
	(void)event;

	qApp -> exit(1);
}

//--------------------------MÉTODOS DA UI----------------------------------//
