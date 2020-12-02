//Definição de header
#ifndef CADASTROINSTRUMENTOS_H
#define CADASTROINSTRUMENTOS_H

//inclusão de bibliotecas
#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QPicture>
#include <QDesktopWidget>

//declaração no namespace
namespace Ui
{
    class frmCadastroInstrumentos;
}

//declaração da classe do formulário
class frmCadastroInstrumentos : public QWidget
{
    Q_OBJECT

    public:

        //variáveis
		QString caminhoDestino, caminhoFonte,
                codigoInstrumento = NULL, estadoInstrumento = NULL;

        //Construtor
        explicit frmCadastroInstrumentos(QWidget *parent = 0);

        //Destrutor
        ~frmCadastroInstrumentos();

    private:

        //Ponteiro para o arquivo .ui
        Ui::frmCadastroInstrumentos *ui;

	//Eventos - métodos privados
    private slots:

        void on_btnCancelar_clicked();
        void on_btnConcluir_clicked();
        void on_btnLimpar_clicked();
        void on_txtPreco_editingFinished();
        void on_txtQuantidade_editingFinished();
        void on_btnCarregar_clicked();
        void on_cmbTipo_currentIndexChanged(const QString &arg1);
        void on_rbtUsado_clicked();
        void on_rbtNovo_clicked();

		void CopiarArquivo(QString arquivo);
		QStringList PreencherComboBox(int indice);
};

#endif // CADASTROINSTRUMENTOS_H
