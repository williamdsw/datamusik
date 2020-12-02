//definição do header
#ifndef CONSULTA_H
#define CONSULTA_H

//Headers externos
#include "../Classes/ClasseGenerica.h"
#include "../Classes/Usuario.h"
#include "CadastroAcessorios.h"
#include "CadastroInstrumentos.h"
#include "CadastroMidias.h"
#include "CadastroUsuario.h"
#include "TelaSessao.h"
#include "TelaPrincipal.h"

//inclusão de biblioteca
#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include <QDebug>
#include <QPlainTextEdit>
#include <QRadioButton>
#include <QDesktopWidget>

//declaração no namespace
namespace Ui
{
    class frmConsulta;
}

//declaração da classe do formulário
class frmConsulta : public QDialog
{
    Q_OBJECT

	class frmTelaPrincipal;

    public:

		QString tabela, perfil;
        int consulta;

        //Construtor
		explicit frmConsulta(QDialog *parent = 0);

        //Destrutor
        ~frmConsulta();

    private:

        //Ponteiro para o formulário
        Ui::frmConsulta *ui;
		QString forms;

	signals:

		void AdicionarForms(QString forms);

    //Métodos públicos
    public slots:

		void PreencheTable(QSqlQuery query, QString pesquisa);
		void Controle();

		void closeEvent(QCloseEvent *event);

	//Métodos-eventos privados
    private slots:

		//Objetos filhos
        void on_btnCancelar_clicked();
        void on_btnNovo_clicked();
        void on_btnEditar_clicked();
        void on_btnExcluir_clicked();
        void on_txtPalavraChave_textChanged(const QString &arg1);
		void on_tblTabelaDados_doubleClicked(const QModelIndex &index);

		//Objeto pai

		//Métodos secundários
        void PreencheCampos(QString botao);
        void ExcluirRegistro();
};

#endif // CONSULTA_H
