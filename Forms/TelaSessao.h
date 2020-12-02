//definição do header
#ifndef TELASESSAO_H
#define TELASESSAO_H

//inclusão de bibliotecas
#include <QWidget>
#include <QDesktopWidget>

//declaração da classe na namespace
namespace Ui
{
	class frmTelaSessao;
}

//Definição da classe
class frmTelaSessao : public QWidget
{
	Q_OBJECT

	public:

		//construtor
		explicit frmTelaSessao(QWidget *parent = 0);

		//destrutor
		~frmTelaSessao();

	private:

		//ponteiro para a ui
		Ui::frmTelaSessao *ui;

	//eventos-métodos privados
	private slots:

		void on_btnRetornar_clicked();
};

#endif // TELASESSAO_H
