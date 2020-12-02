//Definição de header
#ifndef CADASTROACESSORIOS_H
#define CADASTROACESSORIOS_H

//Inclusão de bibliotecas
#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QPicture>
#include <QDesktopWidget>

//declaração no namespace
namespace Ui
{
    class frmCadastroAcessorios;
}

//declaração da classe do formulário
class frmCadastroAcessorios : public QWidget
{
    Q_OBJECT

    public:

        //Variáveis
		QString caminhoDestino, caminhoFonte, codigoAcessorio = NULL;

        //Construtor
        explicit frmCadastroAcessorios(QWidget *parent = 0);

        //Destrutor
        ~frmCadastroAcessorios();

    private:

        //Ponteiro para o formulário
        Ui::frmCadastroAcessorios *ui;

	//eventos/métodos privados
    private slots:

        void on_btnCancelar_clicked();
        void on_btnConcluir_clicked();
        void on_btnLimpar_clicked();
        void on_txtPreco_editingFinished();
        void on_txtQuantidade_editingFinished();
        void on_btnCarregar_clicked();
        void on_cmbTipo_currentIndexChanged(const QString &arg1);

		void CopiarArquivo(QString arquivo);
		QStringList PreencherComboBox(int indice);
};

#endif // CADASTROACESSORIOS_H
