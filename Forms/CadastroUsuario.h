//Definição do header
#ifndef CADASTROUSUARIO_H
#define CADASTROUSUARIO_H

//inclusão de biblioteca
#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QPicture>
#include <QDebug>
#include <QDesktopWidget>

//declaração no namespace
namespace Ui
{
    class frmCadastroUsuario;
}

//declaração da classe do formulário
class frmCadastroUsuario : public QWidget
{
    Q_OBJECT


    public:

        //Variáveis
		QString caminhoFonte, caminhoDestino, codigoUsuario = NULL;
		bool senhaConfirmada = false, nomeConfirmado = true;

        //Construtor
        explicit frmCadastroUsuario(QWidget *parent = 0);

        //Destrutor
        ~frmCadastroUsuario();

    private:

        //Ponteiro para o formulário
        Ui::frmCadastroUsuario *ui;

	//eventos-métodos privados
    private slots:

        void on_btnCancelar_clicked();
        void on_btnConcluir_clicked();
        void on_btnLimpar_clicked();
        void on_btnCarregar_clicked();
        void on_txtSenha_textChanged(const QString &arg1);
        void on_txtConfirmeSenha_textChanged(const QString &arg1);
		void on_txtNome_editingFinished();

		void CopiarArquivo(QString arquivo);
		bool VerificaSenha(QString senha);
};

#endif // CADASTROUSUARIO_H
