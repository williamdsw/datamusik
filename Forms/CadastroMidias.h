//Definição do header
#ifndef CADASTROMIDIAS_H
#define CADASTROMIDIAS_H

//inclusão de bibliotecas
#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QPicture>
#include <QDesktopWidget>

//Declaração da classe no Namespace
namespace Ui
{
    class frmCadastroMidia;
}

//Declaração da classe do formulário
class frmCadastroMidia : public QWidget
{
    Q_OBJECT

    public:

        //variáveis
		QString caminhoFonte, caminhoDestino, codigoMidia = NULL;

		//Construtor
        explicit frmCadastroMidia(QWidget *parent = 0);

		//Destrutor
        ~frmCadastroMidia();

    private:

		//Ponteiro para a ui
        Ui::frmCadastroMidia *ui;

	//eventos-métodos privados
    private slots:

        void on_btnCancelar_clicked();
        void on_btnConcluir_clicked();
        void on_btnLimpar_clicked();
        void on_txtPreco_editingFinished();
        void on_txtQuantidade_editingFinished();
        void on_txtAnoLancamento_editingFinished();
        void on_btnCarregar_clicked();

		void CopiarArquivo(QString arquivo);
};

#endif // CADASTROMIDIA_H
