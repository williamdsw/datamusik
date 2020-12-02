//Definição do header
#ifndef LOGON_H
#define LOGON_H

//inclusão de biblioteca
#include <QWidget>
#include <QMessageBox>
#include <QDesktopWidget>

//declaração no namespace
namespace Ui
{
    class frmLogon;
}

//declaração da classe do formulário
class frmLogon : public QWidget
{
    Q_OBJECT

    public:

        //Construtor
        explicit frmLogon(QWidget *parent = 0);

        //Destrutor
        ~frmLogon();

    private:

        //Ponteiro para o formulário
        Ui::frmLogon *ui;

	//eventos-métodos privados
	private slots:

        void on_btnNovo_clicked();
        void on_btnLogar_clicked();
        void on_txtSenha_textChanged(const QString &arg1);
        void on_txtNome_editingFinished();
        void on_txtSenha_editingFinished();

		void closeEvent(QCloseEvent *event);
};

#endif // LOGON_H
