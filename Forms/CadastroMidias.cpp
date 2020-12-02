//inclusão de headers
#include "CadastroMidias.h"
#include "ui_frmCadastroMidias.h"
#include "../Classes/Midia.h"

//--------------------------CONSTRUTOR-DESTRUTOR DA UI----------------------------------//

//Construtor
frmCadastroMidia::frmCadastroMidia(QWidget *parent) : QWidget(parent),
                                                      ui(new Ui::frmCadastroMidia)
{
    ui -> setupUi(this);

	this -> setGeometry(QStyle::alignedRect
						(Qt::LeftToRight, Qt::AlignCenter, this -> size(),
						 qApp -> desktop() -> availableGeometry()));
}

//Destrutor
frmCadastroMidia::~frmCadastroMidia()
{
    delete ui;
}

//--------------------------EVENTOS DA UI----------------------------------//

//Fechar formúlario
void frmCadastroMidia::on_btnCancelar_clicked()
{
    //Fechando formulário
    this -> close();
}

//Cadastrar acessório
void frmCadastroMidia::on_btnConcluir_clicked()
{

    //Se os campos forem válidos, irá cadastrar
    if(ui -> txtNome -> text() != NULL && ui -> txtArtista -> text() != NULL &&
       ui -> cmbTipo -> currentText() != "Tipo da Mídia*" &&
       ui -> cmbGenero -> currentText() != "Gênero*" &&
       ui -> cmbEstado -> currentText() != "Estado da Mídia**" &&
       ui -> txtAnoLancamento -> text() != NULL &&
       ui -> txtAnoLancamento -> text().length() == 4)
    {
        //Se estiver uma foto escolhida, será criada a pasta e a cópia dela
		if(!caminhoFonte.isNull())
        {
			CopiarArquivo(caminhoFonte);
        }

        Midia *mid = new Midia(ui -> txtNome -> text(), ui -> txtArtista -> text(),
                               ui -> cmbGenero -> currentText(),
                               ui -> cmbEstado ->currentText(),
                               ui -> cmbTipo -> currentText(),
                               ui -> txtDuracao -> text(),
                               ui -> cmbIdioma -> currentText(),
                               ui -> rtxInformacoes -> toPlainText(),
							   caminhoDestino,
                               ui -> txtAnoLancamento -> text().toInt(),
                               ui -> txtQuantidade -> text().toInt(),
                               ui -> txtPreco -> text().toFloat(),
                               QDateTime::currentDateTime());

        //Verificando se é cadastro ou edição
        if(codigoMidia == NULL)
        {
            //Retornando a mensagem de cadastro
            QMessageBox::information(this, "", mid -> Insere());
        }
        else
        {
            QMessageBox::information(this, "", mid -> Altera(codigoMidia.toInt()));
        }

        delete mid;
    }
    else
    {
        QMessageBox::warning(this, "Atenção", "Você não preencheu os campos principais!");
    }
}

//Limpando campos
void frmCadastroMidia::on_btnLimpar_clicked()
{
    //TextBox - LineEdit
    ui -> txtNome -> setText("Nome*");
    ui -> txtArtista -> setText("Artista*");
    ui -> txtAnoLancamento -> setText("Ano de Lançamento*");
    ui -> txtDuracao -> setText("Duração");
    ui -> txtPreco -> setText("Preço");
    ui -> txtQuantidade -> setText("Quantidade");
    ui -> txtPreco -> setStyleSheet("background-color : rgba(0,0,0,100)");
    ui -> txtQuantidade -> setStyleSheet("background-color : rgba(0,0,0,100)");

    //ComboBox
    ui -> cmbEstado -> setCurrentIndex(0);
    ui -> cmbTipo -> setCurrentIndex(0);
    ui -> cmbEstado -> setCurrentIndex(0);
    ui -> cmbIdioma -> setCurrentIndex(0);

    //RichTextBox - QPlainText
    ui -> rtxInformacoes -> setPlainText("Informações Adicionais");

    //QLabel aka "Picture Box"
    QPixmap img;
    ui -> ptbImagem -> setPixmap(img);
    ui -> ptbImagem -> setStyleSheet("border-image: url(:/Imagens/Others/DVD.png) "
                                     "0 0 0 0 stretch stretch;");
}

//Verificando valor da String
void frmCadastroMidia::on_txtPreco_editingFinished()
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

	//unused variables...
	(void)valor;
}

//Verificando valor da String
void frmCadastroMidia::on_txtQuantidade_editingFinished()
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
			ui -> txtQuantidade -> setStyleSheet("background-color: rgb(0, 102, 0)");
        }
    }

	(void)valor;
}

//Verificando valor da String
void frmCadastroMidia::on_txtAnoLancamento_editingFinished()
{
    bool ok;

    int ano = ui -> txtAnoLancamento -> text().toInt(&ok);

    //Modificando as cores da LineEdit
    if(ui -> txtAnoLancamento -> text() != "Ano de Lancaçemento*")
    {
        if(!ok && ui -> txtAnoLancamento -> text().length() != 4)
        {
			ui -> txtAnoLancamento -> setStyleSheet("background-color: rgb(153,0,0)");
        }
        else
        {
			ui -> txtAnoLancamento -> setStyleSheet("background-color: rgb(0, 102, 0)");
        }
    }

	(void)ano;
}

//Carregando arquivo no label
void frmCadastroMidia::on_btnCarregar_clicked()
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

//--------------------------MÉTODOS DA UI----------------------------------//

void frmCadastroMidia::CopiarArquivo(QString arquivo)
{
	QString caminhoDiretorio = "Fotos/Midias";

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
