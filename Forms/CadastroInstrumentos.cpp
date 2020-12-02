//inclusão de headers
#include "CadastroInstrumentos.h"
#include "ui_frmCadastroInstrumentos.h"
#include "../Classes/Instrumento.h"

//--------------------------CONSTRUTOR-DESTRUTOR DA UI----------------------------------//

//Construtor
frmCadastroInstrumentos::frmCadastroInstrumentos(QWidget *parent) :
                         QWidget(parent), ui(new Ui::frmCadastroInstrumentos)
{
    ui -> setupUi(this);

	this -> setGeometry(QStyle::alignedRect
						(Qt::LeftToRight, Qt::AlignCenter, this -> size(),
						 qApp -> desktop() -> availableGeometry()));
}

//Destrutor
frmCadastroInstrumentos::~frmCadastroInstrumentos()
{
    delete ui;
}

//--------------------------EVENTOS DA UI----------------------------------//

//Fechar formúlario
void frmCadastroInstrumentos::on_btnCancelar_clicked()
{
    //Fechando formulário
    this -> close();
}

//Cadastrar acessório
void frmCadastroInstrumentos::on_btnConcluir_clicked()
{

    //Se os campos forem válidos, irá cadastrar
    if(ui -> txtNome -> text() != NULL && ui -> cmbTipo -> currentText() != "Tipo*" &&
       ui -> cmbInstrumento -> currentText() != "Instrumento*" &&
       estadoInstrumento != NULL)
    {
        //Se estiver uma foto escolhida, será criada a pasta e a cópia dela
		if(!caminhoFonte.isNull())
        {
			CopiarArquivo(caminhoFonte);
        }

        //Instanciando a classe
        Instrumento *ins = new Instrumento(ui -> txtNome -> text(),
                                           ui -> cmbTipo -> currentText(),
                                           ui -> cmbInstrumento -> currentText(),
                                           estadoInstrumento, ui -> txtMarca -> text(),
										   caminhoDestino,
                                           ui -> rtxInformacoes -> toPlainText(),
                                           QDateTime::currentDateTime(),
                                           ui -> txtQuantidade -> text().toInt(),
                                           ui -> txtPreco -> text().toFloat());

        //Verificando se é cadastro ou edição
        if(codigoInstrumento == NULL)
        {
            //Retornando a mensagem de cadastro
            QMessageBox::information(this, "", ins -> Insere());
        }
        else
        {
            QMessageBox::information(this, "", ins -> Altera(codigoInstrumento.toInt()));
        }

        delete ins;
    }
    else
    {
        QMessageBox::warning(this, "Atenção", "Você não preencheu os campos principais!");
    }
}

//Limpando campos
void frmCadastroInstrumentos::on_btnLimpar_clicked()
{
    //TextBox - LineEdit
    ui -> txtNome -> setText("Nome*");
    ui -> txtMarca -> setText("Marca");
    ui -> txtPreco -> setText("Preço");
    ui -> txtQuantidade -> setText("Quantidade");
    ui -> txtPreco -> setStyleSheet("background-color : rgba(0,0,0,100)");
    ui -> txtQuantidade -> setStyleSheet("background-color : rgba(0,0,0,100)");

    //ComboBox
    ui -> cmbInstrumento -> setCurrentIndex(0);
    ui -> cmbTipo -> setCurrentIndex(0);

    //RichTextBox - QPlainText
    ui -> rtxInformacoes -> setPlainText("Informações Adicionais");

    //QLabel aka "Picture Box"
    QPixmap img;
    ui -> ptbImagem -> setPixmap(img);
    ui -> ptbImagem -> setStyleSheet("border-image: url(:/Imagens/Others/Microfone.png) "
                                     "0 0 0 0 stretch stretch;");

    ui -> rbtUsado -> setChecked(false);
    ui -> rbtNovo -> setChecked(false);
}

//Verificando valor da String
void frmCadastroInstrumentos::on_txtPreco_editingFinished()
{
    bool ok;

    float valor = ui -> txtPreco -> text().toFloat(&ok);

    //Modificando as cores da LineEdit
    if(ui -> txtPreco -> text() != "Preço")
    {
        if(!ok)
        {
			ui -> txtPreco -> setStyleSheet("background-color: rgb(153,0,0)");
        }
        else
        {
			ui -> txtPreco -> setStyleSheet("background-color: rgb(0, 102, 0)");
        }
    }

	(void)valor;
}

//Verificando valor da String
void frmCadastroInstrumentos::on_txtQuantidade_editingFinished()
{
    bool ok;

    int valor = ui -> txtQuantidade -> text().toInt(&ok);

    //Modificando as cores da LineEdit
    if(ui -> txtQuantidade -> text() != "Quantidade")
    {
        if(!ok)
        {
			ui -> txtQuantidade -> setStyleSheet("background-color: rgb(153,0,0)");
        }
        else
        {
			ui -> txtQuantidade -> setStyleSheet("background-color: rgba(0, 102, 0)");
        }
    }

	(void)valor;
}

//Carregando arquivo no label
void frmCadastroInstrumentos::on_btnCarregar_clicked()
{
    //Criando um FileDialog (instância)
    QFileDialog dialog(this);

    //Setando o tipo de arquivo para "arquivo existente"
    dialog.setFileMode(QFileDialog::ExistingFile);

    //Setando o nome e tipo dos filtros de arquivos (png, jpg, etc)
    dialog.setNameFilter(tr("Imagens (*.png *.jpg *.gif)"));

    //Setando o modo de visualização para "detalhes"
    dialog.setViewMode(QFileDialog::Detail);

    //Se a FileDialog executar...
    if(dialog.exec())
    {
        //o caminho do arquivo será o primeiro do "selectedFiles"
		caminhoFonte = dialog.selectedFiles().first();
    }

    //Criando uma imagem apartir desse caminho
	QPixmap imagem(caminhoFonte);

    //Limpando o css do Label
    ui -> ptbImagem -> setStyleSheet("");

    //Setando a imagem no label
    ui -> ptbImagem -> setPixmap(imagem);

    //Setando a escala "certa" da imagem no label
    ui -> ptbImagem -> setScaledContents(true);
}

//Modifica ComboBox
void frmCadastroInstrumentos::on_cmbTipo_currentIndexChanged(const QString &arg1)
{
	(void)arg1;

    int indice = ui -> cmbTipo -> currentIndex();

    switch(indice)
    {
        case 1: case 2: case 3: case 4:

            ui -> cmbInstrumento -> clear();
			ui -> cmbInstrumento -> addItems(PreencherComboBox(indice));

            break;

        default:

            ui -> cmbInstrumento -> clear();
            ui -> cmbInstrumento -> addItem("Instrumento*");
    }
}

void frmCadastroInstrumentos::on_rbtUsado_clicked()
{
    estadoInstrumento = "Usado";
}

void frmCadastroInstrumentos::on_rbtNovo_clicked()
{
    estadoInstrumento = "Novo";
}

//--------------------------MÉTODOS DA UI----------------------------------//

void frmCadastroInstrumentos::CopiarArquivo(QString arquivo)
{
	QString caminhoDiretorio = "Fotos/Instrumentos";

	//Criando uma "instância" desse diretório
	QDir diretorio(caminhoDiretorio);

	//Se ele existir
	if(diretorio.exists())
	{
		QString nomeArquivo = ui -> txtNome -> text() + "-" + QTime::currentTime().toString();

		if(arquivo != caminhoDestino)
		{
			if(!QFile(caminhoDestino).exists())
			{
				caminhoDestino = caminhoDiretorio + "/" + nomeArquivo + ".jpg";

				//Irá copiar o arquivo o PictureBox para a pasta
				QFile::copy(arquivo, caminhoDestino);
			}
			else
			{
				QFile(caminhoDestino).remove();

				caminhoDestino = caminhoDiretorio + "/" + nomeArquivo + ".jpg";

				//Irá copiar o arquivo o PictureBox para a pasta
				QFile::copy(arquivo, caminhoDestino);
			}
		}
	}
}


QStringList frmCadastroInstrumentos::PreencherComboBox(int indice)
{
    QStringList instrumentos;

    switch(indice)
    {
        //Cordas
        case 1:

            instrumentos.clear();

            instrumentos <<  "Baixo" << "Bandolim" << "Banjo" << "Berimbau" <<
                             "Cavaquinho" << "Guitarra" << "Ukulele" << "Viola" <<
                             "Violino" << "Violão" << "Violoncelo";

            break;

        //Percussão
        case 2:

            instrumentos.clear();

            instrumentos << "Bateria" << "Cowbell" << "Castanhola" << "Caixa" <<
                            "Chimbau" << "Chocalho" << "Pandeiro" << "Pratos" <<
                            "Sino" << "Sinos tubulares" << "Surdo" <<"Triângulo" <<
                            "Tambor" << "Tímpano" << "Xilofone";

            break;

        //Sopro
        case 3:

            instrumentos.clear();

            instrumentos << "Flauta" << "Flauta de pan" << "Flauta baixo" <<
                            "Flauta doce" << "Gaita-de-fole" << "Ocarina" <<
                            "Quinticlave" << "Pífaro" << "Pife Brasileiro" <<
                            "Sarrusofone" << "Saxotrompa alto" << "Trombone" <<
                            "Trompetes";

            break;

        //Teclas
        case 4:

            instrumentos.clear();

            instrumentos << "Acordeão" << "Cravo" << "Órgão" << "Piano" <<
                            "Sintetizador" << "Sampler" << "Teclado";

            break;
    }

    return instrumentos;
}
