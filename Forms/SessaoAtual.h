//declaração do header
#ifndef SESSAOATUAL_H
#define SESSAOATUAL_H

//importação de classes
#include <QFrame>
#include <QTimer>
#include <QDateTime>
#include <QDesktopWidget>

//Declaração da classe no namespace
namespace Ui
{
	class frmSessaoAtual;
}

//Declaração do escopo da classe
class frmSessaoAtual : public QFrame
{
	Q_OBJECT

	public:

		//variáveis
		QDateTime entrada;

		//Construtor
		explicit frmSessaoAtual(QFrame *parent = 0);

		//Destrutor
		~frmSessaoAtual();

	private:

		//ponteiro para a ui
		Ui::frmSessaoAtual *ui;

		//variáveis
		QTimer *timer;
		int minutos, segundos, horas;

	//eventos-métodos privados
	private slots:

		//objetos filhos
		void on_btnRetornar_clicked();

		//métodos
		void ConectarSlots();
		void SetarTexto();
};

#endif // SESSAOATUAL_H
