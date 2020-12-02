//Definição do header
#ifndef TELAPRINCIPAL_H
#define TELAPRINCIPAL_H

//headers secundários
#include "Logon.h"
#include "CadastroAcessorios.h"
#include "CadastroInstrumentos.h"
#include "CadastroMidias.h"
#include "CadastroUsuario.h"
#include "Consulta.h"
#include "SessaoAtual.h"
#include "../Classes/Sessao.h"

//Bibliotecas
#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>
#include <QCloseEvent>
#include <QLineEdit>
#include <QDesktopWidget>

//declaração da classe no namespace
namespace Ui
{
	class frmTelaPrincipal;
}

//declaração do escopo da classe
class frmTelaPrincipal : public QMainWindow
{
	Q_OBJECT

	public:

		//Variáveis
		QString perfil, forms;
		int idUser;

		//ponteiros
		frmLogon *log;

		//Construtor
		explicit frmTelaPrincipal(QWidget *parent = 0);

		//Destrutor
		~frmTelaPrincipal();

	private:

		//ponteiros
		Ui::frmTelaPrincipal *ui;

		//Variáveis
		QDateTime entrada, saida;

	//métodos públicos
	public slots:

		void Controle();

	//métodos privados
	private slots:

		//Cadastro
		void on_actCadastroAcessorio_triggered();
		void on_actCadastroInstrumento_triggered();
		void on_actCadastroMidia_triggered();
		void on_actCadastroUsuario_triggered();

		//Consulta
		void on_actConsultaAcessorio_triggered();
		void on_actConsultaInstrumento_triggered();
		void on_actConsultaMidia_triggered();
		void on_actConsultaUsuario_triggered();
		void on_actConsultaSessao_triggered();

		//Outros
		void on_actManual_triggered();
		void on_actSessaoAtual_triggered();
		void on_actSobre_triggered();
		void on_actSair_triggered();

		//form
		void closeEvent(QCloseEvent *event);

		//métodos secundários
		void ConectarSlots();
		void SetarTexto();

		void ReceberForms(const QString &forms);

		void CriarDiretorio();
};

#endif
