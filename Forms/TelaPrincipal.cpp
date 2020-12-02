//headers necessários
#include "TelaPrincipal.h"
#include "ui_frmTelaPrincipal.h"

frmConsulta *con;
QTimer *tmr;

//--------------------------CONSTRUTOR-DESTRUTOR DA UI----------------------//

//Construtor
frmTelaPrincipal::frmTelaPrincipal(QWidget *parent) : QMainWindow(parent),
	ui(new Ui::frmTelaPrincipal)
{
	ui -> setupUi(this);

	this -> setGeometry(QStyle::alignedRect
						(Qt::LeftToRight, Qt::AlignCenter, this -> size(),
						 qApp -> desktop() -> availableGeometry()));

	con = NULL;

	//Ativando o timer
	ConectarSlots();

	entrada = QDateTime::currentDateTime();

	CriarDiretorio();
}

//Destrutor
frmTelaPrincipal::~frmTelaPrincipal()
{
	//Parando o timer
	tmr -> stop();

	delete tmr;
	delete ui;
	delete con;
}

//--------------------------EVENTOS DA UI----------------------------------//

void frmTelaPrincipal::on_actCadastroAcessorio_triggered()
{
	forms += "Cadastro Acessórios\n";

	frmCadastroAcessorios *frm = new frmCadastroAcessorios();

	frm -> show();
}

void frmTelaPrincipal::on_actCadastroInstrumento_triggered()
{
	forms += "Cadastro Instrumentos\n";

	frmCadastroInstrumentos *frm = new frmCadastroInstrumentos();

	frm -> show();
}

void frmTelaPrincipal::on_actCadastroMidia_triggered()
{
	forms += "Cadastro Mídias\n";

	frmCadastroMidia *frm = new frmCadastroMidia();

	frm -> show();
}

void frmTelaPrincipal::on_actCadastroUsuario_triggered()
{
	forms += "Cadastro Usuário\n";

	frmCadastroUsuario *frm = new frmCadastroUsuario();

	frm -> show();
}

//Consulta
void frmTelaPrincipal::on_actConsultaAcessorio_triggered()
{
	//Se o form for nulo, criará uma nova instância
	if(con == NULL)
	{
		con = new frmConsulta();
	}

	//Se ele não estiver visível, irá setar parâmetros e mostrá-lo
	if(!con -> isVisible())
	{
		//Adicionando conteúdo à string
		forms += "Consulta de Acessórios\n";

		//Trocando variáveis entre forms
		con -> perfil = perfil;

		con -> consulta = 0;
		con -> tabela = "acessorio";

		//Chamada do método
		con -> Controle();

		//Criação de query
		QSqlQuery query;

		//Chama de método
		con -> PreencheTable(query, "Não");

		//Setando propriedades dos objetos filhos do form
		con -> setWindowTitle("Consulta de Acessórios");
		con -> findChild<QLabel*>("lblConsulta") ->
			   setText("CONSULTA DE ACESSÓRIOS");

		//Setando Signal-slot para pegar os forms adicionais
		connect(con, SIGNAL(AdicionarForms(QString)), this, SLOT(ReceberForms(QString)));

		//Exibindo
		con -> show();
	}
}

void frmTelaPrincipal::on_actConsultaInstrumento_triggered()
{
	if(con == NULL)
	{
		con = new frmConsulta();
	}

	if(!con -> isVisible())
	{
		forms += "Consulta de Instrumentos\n";

		con -> perfil = perfil;

		con -> consulta = 1;
		con -> tabela = "instrumento";

		con -> Controle();

		QSqlQuery query;

		con -> PreencheTable(query, "Não");

		con -> setWindowTitle("Consulta de Instrumentos");
		con -> findChild<QLabel*>("lblConsulta") ->
			   setText("CONSULTA DE INSTRUMENTOS");

		connect(con, SIGNAL(AdicionarForms(QString)), this, SLOT(ReceberForms(QString)));

		con -> show();
	}
}

void frmTelaPrincipal::on_actConsultaMidia_triggered()
{
	if(con == NULL)
	{
		con = new frmConsulta();
	}

	if(!con -> isVisible())
	{
		forms += "Consulta de Mídias\n";

		con -> perfil = perfil;

		con -> consulta = 2;
		con -> tabela = "midia";

		con -> Controle();

		QSqlQuery query;

		con -> PreencheTable(query, "Não");

		con -> setWindowTitle("Consulta de Mídias");
		con -> findChild<QLabel*>("lblConsulta") ->
			   setText("CONSULTA DE MÍDIAS");

		connect(con, SIGNAL(AdicionarForms(QString)), this, SLOT(ReceberForms(QString)));

		con -> show();
	}
}

void frmTelaPrincipal::on_actConsultaUsuario_triggered()
{
	if(con == NULL)
	{
		con = new frmConsulta();
	}

	if(!con -> isVisible())
	{
		forms += "Consulta de Usuários\n";

		con -> perfil = perfil;

		con -> consulta = 3;
		con -> tabela = "usuario";

		con -> Controle();

		//con -> frm = this;

		QSqlQuery query;

		con -> PreencheTable(query, "Não");

		con -> setWindowTitle("Consulta de Usuários");
		con -> findChild<QLabel*>("lblConsulta") ->
			   setText("CONSULTA DE USUÁRIOS");

		connect(con, SIGNAL(AdicionarForms(QString)), this, SLOT(ReceberForms(QString)));

		con -> show();
	}
}

void frmTelaPrincipal::on_actConsultaSessao_triggered()
{
	if(con == NULL)
	{
		con = new frmConsulta();
	}

	if(!con -> isVisible())
	{
		forms += "Consulta de Sessões\n";

		con -> perfil = perfil;

		con -> consulta = 4;
		con -> tabela = "sessao";

		con -> Controle();

		QSqlQuery query;

		con -> PreencheTable(query, "Não");

		con -> setWindowTitle("Consulta de Sessões");
		con -> findChild<QLabel*>("lblConsulta") ->
			   setText("CONSULTA DE SESSÕES");

		connect(con, SIGNAL(AdicionarForms(QString)), this, SLOT(ReceberForms(QString)));

		con -> show();
	}
}

//Outros
void frmTelaPrincipal::on_actManual_triggered()
{
	QMessageBox::information(this, "", "Em breve...");

}

void frmTelaPrincipal::on_actSessaoAtual_triggered()
{
	//Adicionando string à "forms"
	forms += "Sessão Atual\n";

	//Nova instância para o form
	frmSessaoAtual *frm = new frmSessaoAtual();

	//Pegando datas
	QString inicio = frm -> findChild<QLabel*>("lblInicio") -> text();
	inicio += entrada.toString("yyyy/MM/dd hh:mm:ss");

	//Pegando as telas visitadas
	QStringList telas = forms.split('\n', QString::KeepEmptyParts);

	//Pegando o texto do Label
	QString numeroTelas = frm -> findChild<QLabel*>("lblNumeroTelas") -> text();

	//Remove último item (em branco)
	telas.removeLast();

	//Pegando e passando o numero de telas
	numeroTelas += QString::number(telas.count());

	//Trocando variáveis
	frm -> entrada = this -> entrada;

	//Modificando "text" dos objetos filhos do form
	frm -> findChild<QLabel*>("lblInicio") -> setText(inicio);
	frm -> findChild<QLabel*>("lblNumeroTelas") -> setText(numeroTelas);
	frm -> findChild<QComboBox*>("cmbTelas") -> addItems(telas);

	//Setando o modality
	frm -> setWindowModality(Qt::ApplicationModal);

	//Exibindo o form
	frm -> show();
}

void frmTelaPrincipal::on_actSobre_triggered()
{
	QString msg = "Um simples CRUD para artefatos músicais...\n\n"
				  "Desenvolvido por Dragula\n"
				  "william@gmail.com";

	QMessageBox::information(this, "DataMusik v.01", msg);
}

//Fechando o form
void frmTelaPrincipal::on_actSair_triggered()
{
	this -> close();
}

//Quando o formulário for fechado...
void frmTelaPrincipal::closeEvent(QCloseEvent *event)
{
	(void)event;

	//Se a string estiver vazia
	if(forms == NULL)
	{
		forms = "Nenhuma tela visitada";
	}

	//Definindo o DateTime
	saida = QDateTime::currentDateTime();

	//Instância da classe
	Sessao *sessao = new Sessao(forms, idUser, entrada, saida);

	//Inserindo dados da sessão no banco
	sessao -> Insere();

	//Abrindo form de Login
	if(log -> isHidden())
	{
		log -> findChild<QLineEdit*>("txtSenha") -> setText("Senha*");
		log -> findChild<QLineEdit*>("txtSenha") -> setEchoMode(QLineEdit::Normal);

		log -> show();
	}

	delete sessao;
}

//--------------------------MÉTODOS DA UI----------------------------------//

//Setando Signal e slot para timer
void frmTelaPrincipal::ConectarSlots()
{
	//Nova instância do timer
	tmr = new QTimer();

	//Conectando um evento ao método
	connect(tmr, SIGNAL(timeout()), this, SLOT(SetarTexto()));

	//Inicializando o timer
	tmr -> start(1000);
}

void frmTelaPrincipal::SetarTexto()
{
	//Setando a data para uma variável
	QString data = QDateTime::currentDateTime().toLocalTime().toString();

	//Setando o label
	ui -> lblData -> setText(data);
}

void frmTelaPrincipal::Controle()
{
	//Restrigindo acessos
	if(perfil == "Parcial")
	{
		ui -> actConsultaUsuario -> setDisabled(true);
		ui -> actConsultaSessao -> setDisabled(true);
	}
}

void frmTelaPrincipal::ReceberForms(const QString &forms)
{
	this -> forms = forms;
}

void frmTelaPrincipal::CriarDiretorio()
{
	//Definido o diretório padrão
	//QString caminhoDiretorio = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);

	QString caminhoDiretorio = QDir::currentPath();

	caminhoDiretorio.append("/Fotos");

	//Criando uma "instância" desse diretório
	QDir diretorio(caminhoDiretorio);

	//Se ele existir
	if(!diretorio.exists())
	{
		caminhoDiretorio.append("/Usuarios");
		diretorio.mkpath(caminhoDiretorio);

		caminhoDiretorio.replace("/Usuarios", "/Midias");
		diretorio.mkpath(caminhoDiretorio);

		caminhoDiretorio.replace("/Midias", "/Acessorios");
		diretorio.mkpath(caminhoDiretorio);

		caminhoDiretorio.replace("/Acessorios", "/Instrumentos");
		diretorio.mkpath(caminhoDiretorio);
	}
}

