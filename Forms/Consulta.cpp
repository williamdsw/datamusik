//Headers da classe
#include "Consulta.h"
#include "ui_frmConsulta.h"

//--------------------------CONSTRUTOR-DESTRUTOR DA UI----------------------//

//Construtor com parâmetro inicializado
frmConsulta::frmConsulta(QDialog *parent) : QDialog(parent),
											ui (new Ui::frmConsulta)
{
	ui -> setupUi(this);

	this -> setGeometry(QStyle::alignedRect
						(Qt::LeftToRight, Qt::AlignCenter, this -> size(),
						 qApp -> desktop() -> availableGeometry()));
}

//Destrutor
frmConsulta::~frmConsulta()
{
    //Deletando o ponteiro
    delete ui;
}

//--------------------------EVENTOS DA UI----------------------------------//

//Fechando o form
void frmConsulta::on_btnCancelar_clicked()
{
    close();
}

//Novo item
void frmConsulta::on_btnNovo_clicked()
{
    PreencheCampos("Novo");
}

//Editando item
void frmConsulta::on_btnEditar_clicked()
{
    PreencheCampos("Editar");
}

//Excluindo item
void frmConsulta::on_btnExcluir_clicked()
{
    ExcluirRegistro();
}

//Pesquisando no banco
void frmConsulta::on_txtPalavraChave_textChanged(const QString &arg1)
{
	(void)arg1;

	//Se o tem do ComboBox não for "Parâmetro"
    if(ui -> cmbParametro -> currentText() != "Parâmetro*")
    {
		//Pega o parâmetro escolhido do ComboBox
        QString parametro = ui -> cmbParametro -> currentText();

		//Pega a palavra chave do LineEdit
        QString palavraChave = ui -> txtPalavraChave -> text();

		//Instância da classe
        ClasseGenerica *cg = new ClasseGenerica();

		//Chamada do método
        cg -> Pesquisa(tabela, parametro, palavraChave);

		//Atualizando o table
        PreencheTable(cg -> Pesquisa(tabela, parametro, palavraChave), "Sim");

		delete cg;
    }

	//Se o LineEdit da palavra chave estiver vazia, irá resetar o Table
    if(ui -> txtPalavraChave -> text() == NULL)
    {
        QSqlQuery query;

        PreencheTable(query, "Não");
    }
}

//Quando o form fechar
void frmConsulta::closeEvent(QCloseEvent *event)
{
	(void)event;

	//"emit" serve como return para o slot?
	emit AdicionarForms(forms);
}

//Abrindo tela de dados
void frmConsulta::on_tblTabelaDados_doubleClicked(const QModelIndex &index)
{
	(void)index;
    PreencheCampos("Dados");
}

//--------------------------MÉTODOS DA UI----------------------------------//

//Preechendo Table de acordo com a tabela
void frmConsulta::PreencheTable(QSqlQuery query, QString pesquisa)
{
    //Instância da classe genérica
    ClasseGenerica *cg = new ClasseGenerica();

	//Se não for do tipo pesquisa, irá carregar todos os registros
    if(pesquisa == "Não")
    {
        query = cg -> Consulta(tabela);
    }

	//Setando a quantidade de colunas
    ui -> tblTabelaDados -> setColumnCount(query.record().count());

	//Setando a quantidade de linhas
    ui -> tblTabelaDados -> setRowCount(query.size());

	//Criando uma QStringList
    QStringList lista;

	//Rows - For para pegar a quantidade de itens (linhas)
    for(int i = 0; i < query.size(); i++)
    {
		//Enquanto tiver um próximo item
        while(query.next())
        {
			//Columns - For para pegar a quantidade de colunas da tabela
            for(int j = 0; j < query.record().count(); j++)
            {
				//Adiciona a QStringList o nome de cada tabela
                lista << query.record().fieldName(j);

				//Seta o item do Table como o valor correspondente
                ui -> tblTabelaDados -> setItem(i,j,
                                        new QTableWidgetItem(query.value(j).toString()));
            }

			//Necessário para voltar ao For à cima
            break;
        }
    }

	//Setando os "nomes" dos cabeçalhos (headers) das colunas
    ui -> tblTabelaDados -> setHorizontalHeaderLabels(lista);

	//Se não for "pesquisa" e se a palavra chave não for nula...
    if(pesquisa == "Não" && ui -> txtPalavraChave -> text() != NULL)
    {
		//Irá inserir tal item na lista
        lista.insert(0, "Parâmetro*");

		//Vai ordernar os itens da lista.
        std::sort(lista.begin(), lista.end());

		//Vai limpar itens duplicados
        lista.erase(std::unique(lista.begin(), lista.end()),
                lista.end());

		//Vai limpar itens do ComboBox
        ui -> cmbParametro -> clear();

		//E adicionar a lista novamente
        ui -> cmbParametro -> addItems(lista);
    }

	delete cg;
}

//Preenchendo telas de acordo com o botão escolhido
void frmConsulta::PreencheCampos(QString botao)
{
	//Variável para verificar se tem um item selecionado
    bool ok = false;

	//Criando um QStringList
    QStringList lista;

	/* Criando um QModelIndexList, que serve para pegar os
	   índices das Rows selecionadas */
	QModelIndexList linhasSelecionadas;

	//Vai receber o valor da primeira linha
    int linha;

	//Se tiver um item selecionado
    if(!ui -> tblTabelaDados -> selectionModel() -> selectedRows().isEmpty())
    {
        ok = true;

		//Pega as rows selecionadas da tabela
		linhasSelecionadas = ui -> tblTabelaDados -> selectionModel()
								-> selectedRows();

		//Pega o valor da primeira row selecionada
		linha = linhasSelecionadas.first().row();
    }

	//Defindo os tipos de consulta
    switch(consulta)
    {
        //Acessório
        case 0:
        {
			//Instância do form
            frmCadastroAcessorios *frm = new frmCadastroAcessorios();

			//Setando o modality
			frm -> setWindowModality(Qt::ApplicationModal);

			//Vai exibir a tela de cadastro
            if(botao == "Novo")
            {
				forms += "Cadastro de Acessórios\n";

                frm -> show();
            }
            else
            {
				//Se tiver um item selecionado
                if(ok)
                {
					//Com base no número de colunas, vai preencher um QStringList com itens
                    for(int i = 0; i < ui -> tblTabelaDados -> columnCount(); i++)
                    {
                        lista << ui -> tblTabelaDados -> item(linha, i) -> text();
                    }

					/* Preenchendo campos do form instânciado :
					 * Utilizar a "list" método "findChild<Componente*>("Nome")
					 */

                    //id
                    frm -> codigoAcessorio = lista.value(0);
                    frm -> findChild<QLineEdit*>("txtNome") -> setText(lista.value(1));
                    frm -> findChild<QComboBox*>("cmbTipo") -> setCurrentText(lista.value(2));
                    frm -> findChild<QComboBox*>("cmbInstrumento") -> setCurrentText(lista.value(3));
                    //lista.value(4) = Data cadastro
                    frm -> findChild<QLineEdit*>("txtPreco") -> setText(lista.value(5));
                    frm -> findChild<QLineEdit*>("txtQuantidade") -> setText(lista.value(6));
                    frm -> findChild<QPlainTextEdit*>("rtxInformacoes") -> setPlainText(lista.value(7));
					frm -> caminhoDestino = lista.value(8);
                    frm -> findChild<QLineEdit*>("txtMarca") -> setText(lista.value(9));

                    if(lista.value(8) != NULL)
                    {
                        //Criando uma imagem apartir desse caminho
                        QPixmap imagem(lista.value(8));

                        //Limpando o css do Label
                        frm -> findChild<QLabel*>("ptbImagem") -> setStyleSheet("");
                        frm -> findChild<QLabel*>("ptbImagem") -> setPixmap(imagem);
                        frm -> findChild<QLabel*>("ptbImagem") -> setScaledContents(true);
                    }

					//Setando conteúdos de texto caso for de edição ou exibição
                    if(botao == "Editar")
                    {
						forms += "Edição do Acessório\n";

                        frm -> setWindowTitle("Edição de dados do Acessório");
                        frm -> findChild<QLabel*>("lblCadastroAcessorios") ->
                                setText("EDIÇÃO DO ACESSÓRIO");
                    }
                    else
                    {
						forms += "Dados do Acessório\n";

                        frm -> setWindowTitle("Dados do Acessório");
                        frm -> findChild<QLabel*>("lblCadastroAcessorios") ->
                                setText("DADOS DO ACESSÓRIO");

                        frm -> findChild<QPushButton*>("btnConcluir") -> hide();
                        frm -> findChild<QPushButton*>("btnLimpar") -> hide();
						frm -> findChild<QPushButton*>("btnCarregar") -> hide();
                    }

					//Exibindo formulário
                    frm -> show();
                }
				else
				{
					QMessageBox::warning(this, "Atenção", "Você não escolheu nenhum item da tabela!");
				}
            }
        }

			break;

        //Instrumentos
        case 1:
        {
            frmCadastroInstrumentos *frm = new frmCadastroInstrumentos();

			//Setando o modality
			frm -> setWindowModality(Qt::ApplicationModal);

            if(botao == "Novo")
            {
				forms += "Cadastro de Instrumentos\n";

                frm -> show();
            }
            else
            {
                if(ok)
                {
                    for(int i = 0; i < ui -> tblTabelaDados -> columnCount(); i++)
                    {
                        lista << ui -> tblTabelaDados -> item(linha, i) -> text();
                    }

                    //id
                    frm -> codigoInstrumento = lista.value(0);
                    frm -> findChild<QLineEdit*>("txtNome") -> setText(lista.value(1));
                    frm -> findChild<QComboBox*>("cmbTipo") -> setCurrentText(lista.value(2));
                    frm -> findChild<QComboBox*>("cmbInstrumento") -> setCurrentText(lista.value(3));
                    //data cadastro = value(5)
                    frm -> findChild<QLineEdit*>("txtMarca") -> setText(lista.value(6));
                    frm -> findChild<QLineEdit*>("txtPreco") -> setText(lista.value(7));
                    frm -> findChild<QLineEdit*>("txtQuantidade") -> setText(lista.value(8));
					frm -> caminhoDestino = lista.value(9);
                    frm -> findChild<QPlainTextEdit*>("rtxInformacoes") -> setPlainText(lista.value(10));

                    if(lista.value(4) == "Usado")
                    {
                        frm -> findChild<QRadioButton*>("rbtUsado") -> setChecked(true);
                    }
                    else
                    {
                        frm -> findChild<QRadioButton*>("rbtNovo") -> setChecked(true);
                    }

                    //caminhio_imagem
                    if(lista.value(9) != NULL)
                    {
                        //Criando uma imagem apartir desse caminho
                        QPixmap imagem(lista.value(8));

                        //Limpando o css do Label
                        frm -> findChild<QLabel*>("ptbImagem") -> setStyleSheet("");
                        frm -> findChild<QLabel*>("ptbImagem") -> setPixmap(imagem);
                        frm -> findChild<QLabel*>("ptbImagem") -> setScaledContents(true);
                    }

                    if(botao == "Editar")
                    {
						forms += "Edição do Instrumento\n";

                        frm -> setWindowTitle("Edição de dados do Instrumento");
                        frm -> findChild<QLabel*>("lblCadastroInstrumentos") ->
                                setText("EDIÇÃO DO INSTRUMENTO");
                    }
                    else
                    {
						forms += "Dados do Acessório\n";

                        frm -> setWindowTitle("Dados do Instrumento");
                        frm -> findChild<QLabel*>("lblCadastroInstrumentos") ->
                                setText("DADOS DO INSTRUMENTO");

                        frm -> findChild<QPushButton*>("btnConcluir") -> hide();
                        frm -> findChild<QPushButton*>("btnLimpar") -> hide();
						frm -> findChild<QPushButton*>("btnCarregar") -> hide();
                    }

                    frm -> show();
                }
				else
				{
					QMessageBox::warning(this, "Atenção", "Você não escolheu nenhum item da tabela!");
				}
            }
        }

			break;

        //Mídias
        case 2:
        {
			frmCadastroMidia *frm = new frmCadastroMidia();

			//Setando o modality
			frm -> setWindowModality(Qt::ApplicationModal);

            if(botao == "Novo")
            {
				forms += "Cadastro de Mídias\n";

                frm -> show();
            }
            else
            {
                if(ok)
                {
                    for(int i = 0; i < ui -> tblTabelaDados -> columnCount(); i++)
                    {
                        lista << ui -> tblTabelaDados -> item(linha, i) -> text();
                    }

                    //id
                    frm -> codigoMidia = lista.value(0);
                    frm -> findChild<QLineEdit*>("txtNome") -> setText(lista.value(1));
                    frm -> findChild<QLineEdit*>("txtArtista") -> setText(lista.value(2));
                    frm -> findChild<QComboBox*>("cmbGenero") -> setCurrentText(lista.value(3));
                    frm -> findChild<QLineEdit*>("txtAnoLancamento") -> setText(lista.value(4));
                    frm -> findChild<QComboBox*>("cmbEstado") -> setCurrentText(lista.value(5));
					frm -> findChild<QComboBox*>("cmbTipo") -> setCurrentText(lista.value(6));
                    //data cadastro = value(7)
                    frm -> findChild<QLineEdit*>("txtDuracao") -> setText(lista.value(8));
                    frm -> findChild<QLineEdit*>("txtPreco") -> setText(lista.value(9));
                    frm -> findChild<QLineEdit*>("txtQuantidade") -> setText(lista.value(10));
					frm -> findChild<QComboBox*>("cmbIdioma") -> setCurrentText(lista.value(11));
                    frm -> findChild<QPlainTextEdit*>("rtxInformacoes") -> setPlainText(lista.value(12));
					frm -> caminhoDestino = lista.value(13);

                    //caminho_imagem
                    if(lista.value(13) != NULL)
                    {
                        //Criando uma imagem apartir desse caminho
						QPixmap imagem(lista.value(13));

                        //Limpando o css do Label
                        frm -> findChild<QLabel*>("ptbImagem") -> setStyleSheet("");
                        frm -> findChild<QLabel*>("ptbImagem") -> setPixmap(imagem);
                        frm -> findChild<QLabel*>("ptbImagem") -> setScaledContents(true);
                    }

                    if(botao == "Editar")
                    {
						forms += "Edição da Mídia\n";

                        frm -> setWindowTitle("Edição de dados da Mídia");
                        frm -> findChild<QLabel*>("lblCadastroMidia") ->
                                setText("EDIÇÃO DA MÍDIA");
                    }
                    else
                    {
						forms += "Dados da Mídia\n";

                        frm -> setWindowTitle("Dados da Mídia");
                        frm -> findChild<QLabel*>("lblCadastroMidia") ->
                                setText("DADOS DA MÍDIA");

                        frm -> findChild<QPushButton*>("btnConcluir") -> hide();
                        frm -> findChild<QPushButton*>("btnLimpar") -> hide();
						frm -> findChild<QPushButton*>("btnCarregar") -> hide();
                    }

                    frm -> show();
                }
				else
				{
					QMessageBox::warning(this, "Atenção", "Você não escolheu nenhum item da tabela!");
				}
            }
        }

			break;

        //Usuário
        case 3:
        {
            frmCadastroUsuario *frm = new frmCadastroUsuario();

			//Setando o modality
			frm -> setWindowModality(Qt::ApplicationModal);

            if(botao == "Novo")
            {
				forms += "Cadastro de Usuário\n";

                frm -> show();
            }
            else
            {
                if(ok)
                {
                    for(int i = 0; i < ui -> tblTabelaDados -> columnCount(); i++)
                    {
                        lista << ui -> tblTabelaDados -> item(linha, i) -> text();
                    }

                    //id
                    frm -> codigoUsuario = lista.value(0);
                    frm -> findChild<QLineEdit*>("txtNome") -> setText(lista.value(1));
                    frm -> findChild<QLineEdit*>("txtSenha") -> setText(lista.value(2));
                    frm -> findChild<QLineEdit*>("txtConfirmeSenha") -> setText(lista.value(2));
                    frm -> findChild<QComboBox*>("cmbPerfil") -> setCurrentText(lista.value(3));
                    //data cadastro = value(4)
					frm -> caminhoDestino = lista.value(5);

                    frm -> findChild<QLineEdit*>("txtSenha") -> setEchoMode(QLineEdit::Password);
                    frm -> findChild<QLineEdit*>("txtConfirmeSenha") -> setEchoMode(QLineEdit::Password);

					//Caminho Foto
					if(lista.value(5) != NULL)
					{
						//Criando uma imagem apartir desse caminho
						QPixmap imagem(lista.value(5));

						//Limpando o css do Label
						frm -> findChild<QLabel*>("ptbImagem") -> setStyleSheet("");
						frm -> findChild<QLabel*>("ptbImagem") -> setPixmap(imagem);
						frm -> findChild<QLabel*>("ptbImagem") -> setScaledContents(true);
					}

                    if(botao == "Editar")
                    {
						forms += "Edição do Usuário\n";

                        frm -> setWindowTitle("Edição de dados do Usuário");
                        frm -> findChild<QLabel*>("lblCadastroUsuario") ->
                                setText("EDIÇÃO DO USUÁRIO");
                    }
                    else
                    {
						forms += "Dados do Usuário\n";

                        frm -> setWindowTitle("Dados do Usuário");
                        frm -> findChild<QLabel*>("lblCadastroUsuario") ->
                                setText("DADOS DO USUÁRIO");

                        frm -> findChild<QPushButton*>("btnConcluir") -> hide();
                        frm -> findChild<QPushButton*>("btnLimpar") -> hide();
						frm -> findChild<QPushButton*>("btnCarregar") -> hide();
                    }

                    frm -> show();
                }
				else
				{
					QMessageBox::warning(this, "Atenção", "Você não escolheu nenhum item da tabela!");
				}
            }
        }

			break;

        //Sessão
        case 4:
        {
            if(ok)
            {
				forms += "Dados da Sessão\n";

				//Instância da classe
				Usuario *user = new Usuario();

				//Instância do form
                frmTelaSessao *frm = new frmTelaSessao();

				//Preenchendo a lista com dados da row
                for(int i = 0; i < ui -> tblTabelaDados -> columnCount(); i++)
                {
                    lista << ui -> tblTabelaDados -> item(linha, i) -> text();
                }

				//idSessao = 0
				//id do usuário
				QString idUsuario = lista.value(1);

				//Definindo o nome que será do QLabel
				QString nome = frm -> findChild<QLabel*>("lblUsuario") -> text();
				nome += user -> RetornaNome(idUsuario.toInt());

				//Nome para pegar a foto
				QString usuario = user -> RetornaNome(idUsuario.toInt());

				//Pegando as QString das datas
				QString inicio = lista.value(2);
				QString termino = lista.value(3);

				//Substituindo caracter "T"
				inicio.replace("T", " ");
				termino.replace("T", " ");

				//Criando datas
				QDateTime entrada;
				entrada = entrada.fromString(inicio, "yyyy-MM-dd hh:mm:ss");

				QDateTime saida;
				saida = saida.fromString(termino, "yyyy-MM-dd hh:mm:ss");

				//Definindo a diferença entre elas
				int minutos = (entrada.secsTo(saida) / 60);
				int segundos = (entrada.secsTo(saida) - (minutos * 60));
				int horas = minutos / 60;

				if(minutos > 0)
				{
					minutos -= 60;
				}

				//Definindo o Text dos QLabel de data
				inicio = frm -> findChild<QLabel*>("lblInicio") -> text() + inicio;
				termino = frm -> findChild<QLabel*>("lblTermino") -> text() + termino;

				//Definindo o Text do QLabel de tempo total
				QString tempoTotal = frm -> findChild<QLabel*>("lblTempo") -> text();
				tempoTotal += QString::number(horas) + ':' + QString::number(minutos) +
							  ':' + QString::number(segundos);

				//Pegando a String contendo as telas
				QString tela = lista.value(4);

				//Separando cada item pelo '\n' e colocando num List (!!!)
				QStringList telas = tela.split('\n', QString::KeepEmptyParts);

				//Vai limpar itens duplicados
				telas.erase(std::unique(telas.begin(), telas.end()), telas.end());

				//Setando o Text que irá ser do QLabel
				QString quantidadeTelas = frm -> findChild<QLabel*>("lblNumeroTelas") -> text();

				if(telas.count() > 0)
				{
					quantidadeTelas += QString::number(telas.count() - 1);
				}

				//Definindo os Texts dos componentes
				frm -> findChild<QLabel*>("lblUsuario") -> setText(nome);
				frm -> findChild<QLabel*>("lblInicio") -> setText(inicio);
				frm -> findChild<QLabel*>("lblTermino") -> setText(termino);
				frm -> findChild<QLabel*>("lblTempo") -> setText(tempoTotal);
				frm -> findChild<QLabel*>("lblNumeroTelas") -> setText(quantidadeTelas);
				frm -> findChild<QComboBox*>("cmbTelas") -> addItems(telas);

				//Criando uma query
				QSqlQuery query = user -> RetornaDados(usuario);

				//Criando uma imagem apartir desse caminho
				QString caminhoImagem;

				//Pegando a imagem do usuário
				while(query.next())
				{
					caminhoImagem = query.value(5).toString();
				}

				if(caminhoImagem != NULL)
				{
					//Criando uma imagem apartir desse caminho
					QPixmap imagem(caminhoImagem);

					//Limpando o css do Label
					frm -> findChild<QLabel*>("ptbImagem") -> setStyleSheet("");
					frm -> findChild<QLabel*>("ptbImagem") -> setPixmap(imagem);
					frm -> findChild<QLabel*>("ptbImagem") -> setScaledContents(true);
				}

				//Setando o modality
				frm -> setWindowModality(Qt::ApplicationModal);

				//Mostrando o form
                frm -> show();

				delete user;
            }
			else
			{
				QMessageBox::warning(this, "Atenção", "Você não escolheu nenhum item da tabela!");
			}
        }

			break;
	}
}

//Excluindo registro do banco
void frmConsulta::ExcluirRegistro()
{
	//Se tiver um item selecionado
    if(!ui -> tblTabelaDados -> selectionModel() -> selectedRows().isEmpty())
    {
		//Cria um QModelIndexList
		QModelIndexList linhasSelecionadas = ui -> tblTabelaDados -> selectionModel()
												-> selectedRows();
		//Pegando o valor da primeira Row Selecionada
		int linha = linhasSelecionadas.first().row();

		//Pegando o id
        int id = ui -> tblTabelaDados -> item(linha, 0) -> text().toInt();

		//Perguntando ao usuário se ele quer excluir o item mesmo..
		int resposta = QMessageBox::question(this, "Atenção", "Tem certeza",
											 QMessageBox::Yes, QMessageBox::No);

		//Caso sim, irá excluir
		if(resposta == QMessageBox::Yes)
		{
			//Instância da classe
			ClasseGenerica *cg = new ClasseGenerica();

			//Chamada do método numa QMessageBox
			QMessageBox::information(this, "", cg -> Excluir(tabela, id));

			//Criação de QSqlQuery vazia
			QSqlQuery query;

			//Atualizando Table
			PreencheTable(query, "Não");

			delete cg;
		}
		else
		{
			QMessageBox::information(this, "Atenção", "Operação cancelada pelo usuário");
		}
    }
    else
    {
        QMessageBox::warning(this, "Atenção", "Você não escolheu nenhum item da tabela!");
    }
}

void frmConsulta::Controle()
{
	//Concedendo permissões à botões
	if(consulta == 4 && perfil == "Administrador")
	{
		ui -> btnNovo -> hide();
		ui -> btnExcluir -> hide();
		ui -> btnEditar -> hide();
	}
	else
	{
		ui -> btnNovo -> show();
		ui -> btnExcluir -> show();
		ui -> btnEditar -> show();
	}

	if(perfil == "Parcial")
	{
		ui -> btnExcluir -> setDisabled(true);
		ui -> btnEditar -> setDisabled(true);
	}
}
