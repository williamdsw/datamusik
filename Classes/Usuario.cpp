//Inclusão de header
#include "Usuario.h"
#include "../Classes/Banco.h"

//Construtor vazio
Usuario::Usuario()
{}

//Construtor com parâmetros
Usuario::Usuario(QString nome, QString senha, QString perfil,
                 QString camft, QDateTime dataC)
{
    _nome = nome;
    _senha = senha;
    _perfil = perfil;
    _caminhoFoto = camft;
    _dataCadastro = dataC;
}

//Método para inserir no banco
QString Usuario::Insere()
{
    //Instância do banco
    Banco bd("datamusik");

    //Conectando ao banco
    bd.Conecta();

    //Criando uma query
    QSqlQuery query;

    //Definindo o comando sql
    QString sql = "INSERT INTO datamusik.usuario (nome, senha, perfil, "
                                                 "caminho_foto, data_cadastro) "
                  //"VALUES (:nome, crypt(:senha, gen_salt('md5')), "
                          //":perfil, :caminho_foto, :data_cadastro) ";
                  "VALUES (:nome, :senha, :perfil, :caminho_foto, :data_cadastro) ";

    //"Preparando" a query
    query.prepare(sql);

    //Atribuindo os parâmetros
    query.bindValue(":nome", _nome);
    query.bindValue(":senha", _senha);
    query.bindValue(":perfil", _perfil);
    query.bindValue(":caminho_foto", _caminhoFoto);
    query.bindValue(":data_cadastro", _dataCadastro);

    //Verificando se a query foi executada com sucesso
    if(query.exec())
    {
        return "Usuário cadastrado com sucesso!";
    }
    else
    {
        return "Erro ao cadastrar usuário!\n\n" + query.lastError().text();
    }

    //Desconectando do banco
    bd.Desconecta();
}

//Método para alterar no banco
QString Usuario::Altera(int id)
{
    //Instância do banco
    Banco bd("datamusik");

    //Conectando ao banco
    bd.Conecta();

    //Criando uma query
    QSqlQuery query;

    //Definindo o comando sql
    QString sql = "UPDATE datamusik.usuario "
                  "SET "
                  //"senha = crypt(:senha, gen_salt('md5'), "
                  "senha = :senha, "
                  "perfil = :perfil, "
				  "caminho_foto = :caminho_foto "
                  "WHERE id = :id";

    //"Preparando" a query
    query.prepare(sql);

    //Atribuindo os parâmetros
    query.bindValue(":senha", _senha);
    query.bindValue(":perfil", _perfil);
    query.bindValue(":data_cadastro", _dataCadastro);
	query.bindValue(":caminho_foto", _caminhoFoto);
    query.bindValue(":id", id);

    //Verificando se a query foi executada com sucesso
    if(query.exec())
    {
        return "Usuário editado com sucesso!";
    }
    else
    {
        return "Erro ao editar usuário!\n\n" + query.lastError().text();
    }

    //Desconectando do banco
    bd.Desconecta();
}

//Método para autenticar usuário no sistema
bool Usuario::Autentica(QString nome, QString senha)
{
    //Instância do banco
    Banco bd("datamusik");

    //Conectando
    bd.Conecta();

    //Criando uma query
    QSqlQuery query;

    //Criando o comando sql
    QString sql = "SELECT id FROM datamusik.usuario "
                  "WHERE nome = :nome "
                  //"AND senha = crypt(:senha, senha)";
                  "AND senha = :senha";

    //"Preparando" o comando sql
    query.prepare(sql);

    //Atribuindo os parâmetros
    query.bindValue(":nome", nome);
    query.bindValue(":senha", senha);

    //Executando a query
    query.exec();

    //Se tiver um próximo resultado, irá retornar true
    if(query.next())
    {
        return true;
    }
    else
    {
        return false;
    }

    //desconectando do banco
    bd.Desconecta();
}

//Método para verificar já tem alguém cadastrado com tal nome
bool Usuario::VerificaNome(QString nome)
{
	//Instância do banco
	Banco bd("datamusik");

	//Conectando
	bd.Conecta();

	//Criando uma query
	QSqlQuery query;

	//Criando o comando sql
	QString sql = "SELECT * FROM datamusik.usuario "
				  "WHERE nome = :nome";

	//"Preparando" o comando sql
	query.prepare(sql);

	//Atribuindo os parâmetros
	query.bindValue(":nome", nome);

	//Executando a query
	query.exec();

	//Se tiver um próximo resultado, irá retornar true
	if(query.next())
	{
		return true;
	}
	else
	{
		return false;
	}

	//desconectando do banco
	bd.Desconecta();
}

//Verificando se já existe um adm
bool Usuario::VerificaAdministrador()
{
	//Instância do banco
	Banco bd("datamusik");

	//Conectando
	bd.Conecta();

	//Criando uma query
	QSqlQuery query;

	//Criando o comando sql
	QString sql = "SELECT * FROM datamusik.usuario "
				  "WHERE perfil = :perfil";

	//"Preparando" o comando sql
	query.prepare(sql);

	//Atribuindo os parâmetros
	query.bindValue(":perfil", "Administrador");

	//Executando a query
	query.exec();

	//Se tiver um próximo resultado, irá retornar true
	while(query.exec())
	{
		if(query.numRowsAffected() == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//desconectando do banco
	bd.Desconecta();
}

//Método para retornar dados como perfil e id de acordo com o nome
QSqlQuery Usuario::RetornaDados(QString nome)
{
	//Instância do banco
	Banco bd("datamusik");

	//Conectando...
	bd.Conecta();

	//Instância da query
	QSqlQuery query;

	//Comando SQL
	QString sql = "SELECT * FROM datamusik.usuario "
				  "WHERE nome = :nome";

	//Preparando a query
	query.prepare(sql);

	//Passando os parâmetros
	query.bindValue(":nome", nome);

	//Se executar
	if(query.exec())
	{
		return query;
	}
	else
	{
		QMessageBox::critical(NULL, "Erro", "Erro ao consultar dados!\n\n" +
							  query.lastError().text());
	}

	//Desconectando
	bd.Desconecta();
}

//Método para retornar o nome
QString Usuario::RetornaNome(int id)
{
	//Instância do banco
	Banco bd("datamusik");

	//Conectando...
	bd.Conecta();

	//Instância da query
	QSqlQuery query;

	//Comando SQL
	QString sql = "SELECT nome FROM datamusik.usuario "
				  "WHERE id = :id";

	//Preparando a query
	query.prepare(sql);

	//Passando os parâmetros
	query.bindValue(":id", id);

	//Se executar
	if(query.exec())
	{
		QString nome;

		while(query.next())
		{
			nome = query.value(0).toString();
		}

		return nome;
	}
	else
	{
		return "Erro ao consultar dados!\n\n" + query.lastError().text();
	}

	//Desconectando
	bd.Desconecta();
}
