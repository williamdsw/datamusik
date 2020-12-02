//Inclusão de headers
#include "CadastroUsuario.h"
#include "ui_frmCadastroUsuario.h"
#include <../Classes/Usuario.h>

//--------------------------CONSTRUTOR-DESTRUTOR DA UI----------------------//

//Construtor com parâmetro inicializado
frmCadastroUsuario::frmCadastroUsuario(QWidget *parent) :QWidget(parent),
                                                         ui(new Ui::frmCadastroUsuario)
{
	//Setando ui do form
    ui -> setupUi(this);

	//Setando posição na tela
	this -> setGeometry(QStyle::alignedRect
						(Qt::LeftToRight, Qt::AlignCenter, this -> size(),
						 qApp -> desktop() -> availableGeometry()));

	//Escondendo Label
    ui -> lblIndicadorSenha -> hide();

	Usuario *user = new Usuario();

	//Se tiver um adm cadastrado já...
	if(user -> VerificaAdministrador())
	{
		ui -> cmbPerfil -> removeItem(1);
	}

	delete user;
}

//Destrutor
frmCadastroUsuario::~frmCadastroUsuario()
{
    //Deletando o ponteiro
    delete ui;
}

//--------------------------EVENTOS DA UI----------------------------------//

//Fechar formúlario
void frmCadastroUsuario::on_btnCancelar_clicked()
{
    //Fechando formulário
    this -> close();
}

//Cadastrar acessório
void frmCadastroUsuario::on_btnConcluir_clicked()
{
    //Se os campos forem válidos, irá cadastrar
    if(ui -> txtNome -> text() != NULL && ui -> txtSenha -> text() != NULL &&
       ui -> txtConfirmeSenha -> text() != NULL &&
       ui -> cmbPerfil -> currentText() != "Perfil de usuário*")
    {
		if(nomeConfirmado)
		{
			if(senhaConfirmada)
			{
				if(ui -> lblIndicadorSenha -> text() != "Senha fraca!")
				{
					//Se estiver uma foto escolhida, será criada a pasta e a cópia dela
					if(!caminhoFonte.isNull())
					{
						CopiarArquivo(caminhoFonte);
					}


					Usuario *user = new Usuario(ui -> txtNome -> text(),
												ui -> txtSenha -> text(),
												ui -> cmbPerfil -> currentText(),
												caminhoDestino,
												QDateTime::currentDateTime());

					//Verificando se é cadastro ou edição
					if(codigoUsuario == NULL)
					{
						//Retornando a mensagem de cadastro
						QMessageBox::information(this, "", user -> Insere());
					}
					else
					{
						QMessageBox::information(this, "", user -> Altera(codigoUsuario.toInt()));
					}

					delete user;
				}
				else
				{
					QMessageBox::warning(this, "Atenção", "Senha muito fraca! Insira outra senha!");
				}
			}
			else
			{
				QMessageBox::warning(this, "Atenção", "A senha confirmada não está correta!");
			}
		}
		else
		{
			QMessageBox::warning(this, "Atenção", "Já existe um usuário com esse nome");
		}
    }
    else
    {
        QMessageBox::warning(this, "Atenção", "Você não preencheu os campos principais!");
    }
}

//Limpando campos
void frmCadastroUsuario::on_btnLimpar_clicked()
{
    //TextBox - LineEdit
    ui -> txtNome -> setText("Nome*");
    ui -> txtSenha -> setText("Senha*");
    ui -> txtSenha -> setEchoMode(QLineEdit::Normal);
    ui -> txtConfirmeSenha -> setText("Confirme a senha*");
    ui -> txtConfirmeSenha -> setEchoMode(QLineEdit::Normal);
    ui -> txtConfirmeSenha -> setStyleSheet("background-color : rgba(0,0,0,100)");

    //ComboBox
    ui -> cmbPerfil -> setCurrentIndex(0);

    //QLabel aka "Picture Box"
    QPixmap img;
    ui -> ptbImagem -> setPixmap(img);
    ui -> ptbImagem -> setStyleSheet("border-image: url(:/Imagens/Others/Funcionario.png) "
                                     "0 0 0 0 stretch stretch;");
}

//Carregando arquivo no label
void frmCadastroUsuario::on_btnCarregar_clicked()
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

//Verificando quando texto da LineEdit é alterado
void frmCadastroUsuario::on_txtSenha_textChanged(const QString &arg1)
{
	(void)arg1;

    //Setando TextBox - LineEdit para receber caracteres de Senha
    ui -> txtSenha -> setEchoMode(QLineEdit::EchoMode::Password);

    if(ui -> txtSenha -> text() != NULL)
    {
        //"habilitando" o label
        ui -> lblIndicadorSenha -> show();

		if(VerificaSenha(ui -> txtSenha -> text()))
        {
            ui -> lblIndicadorSenha -> setText("Senha forte!");
        }
        else
        {
            ui -> lblIndicadorSenha -> setText("Senha fraca!");
        }
    }
    else
    {
        ui -> lblIndicadorSenha -> hide();
    }
}

//Verificando quando texto da LineEdit é alterado
void frmCadastroUsuario::on_txtConfirmeSenha_textChanged(const QString &arg1)
{
	(void)arg1;

    //Setando TextBox - LineEdit para receber caracteres de Senha
    ui -> txtConfirmeSenha -> setEchoMode(QLineEdit::EchoMode::Password);

    if(ui -> txtConfirmeSenha -> text() == ui -> txtSenha -> text())
    {
        senhaConfirmada = true;

		ui -> txtConfirmeSenha -> setStyleSheet("background-color: rgba(0, 102, 0)");
    }
    else
    {
        senhaConfirmada = false;

        ui -> txtConfirmeSenha -> setStyleSheet("background-color: rgba(225, 0, 0)");
    }
}

//Verificando nome do usuário
void frmCadastroUsuario::on_txtNome_editingFinished()
{
	Usuario user;

	if(codigoUsuario == NULL)
	{
		if(user.VerificaNome(ui -> txtNome -> text()))
		{
			QMessageBox::warning(this, "Atenção", "Já existe um usuário com esse nome!"
											  "\nEscolha outro!");

			nomeConfirmado = false;
		}
		else
		{
			nomeConfirmado = true;
		}
	}
}

//--------------------------MÉTODOS DA UI----------------------------------//

void frmCadastroUsuario::CopiarArquivo(QString arquivo)
{
	QString caminhoDiretorio = "Fotos/Usuarios";

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


//Verificando a senha
bool frmCadastroUsuario::VerificaSenha(QString senha)
{
    //Declarando Regex's
    QRegularExpression regTamanhoMinusculo("[a-z]");
    QRegularExpression regTamanhoMaiusculo("[A-Z]");
    QRegularExpression regTamanhoNumeros("[0-9]");
    QRegularExpression regTamanhoEspeciais("[^a-zA-Z0-9]");

    //Verificando cada condição para ter uma senha forte
    if(senha.length() < 8)
        return false;

    if(!senha.contains(regTamanhoMinusculo))
        return false;

    if(!senha.contains(regTamanhoMaiusculo))
        return false;

    if(!senha.contains(regTamanhoEspeciais))
        return false;

    if(!senha.contains(regTamanhoNumeros))
        return false;

    return true;
}
