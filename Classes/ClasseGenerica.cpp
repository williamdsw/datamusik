//Inclusão de headers
#include  "ClasseGenerica.h"
#include "../Classes/Banco.h"

//Construtor Vazio
ClasseGenerica::ClasseGenerica()
{}

//Método para excluir no banco
QString ClasseGenerica::Excluir(QString tabela, int id)
{
	//Instância do banco
    Banco bd("datamusik");

	//Conectando
    bd.Conecta();

	//Instância de uma query
    QSqlQuery query;

	//Comando sql
    QString sql = " DELETE FROM datamusik." + tabela +
                  " WHERE id = :id";

	//Preparando a query
    query.prepare(sql);

	//Setando o valor do campo "id"
    query.bindValue(":id", id);

	//Verificando se executou...
    if(query.exec())
    {
        return "Registro excluído com sucesso";
    }
    else
    {
        return "Erro ao excluir registro!\n\n" + query.lastError().text();
    }

	//Desconectando
    bd.Desconecta();
}

//Método para consultar dados
QSqlQuery ClasseGenerica::Consulta(QString tabela)
{
	//Instância do banco
    Banco bd("datamusik");

	//Conectando
    bd.Conecta();

	//Comando sql
    QString sql = "SELECT * FROM datamusik." + tabela;

	//Instância da query
    QSqlQuery query;

	//Preparando a query
    query.prepare(sql);

	//Se executar...
    if(query.exec())
    {
        return query;
    }
    else
    {
        QMessageBox::critical(NULL, "Erro", "Erro ao carregar dados!\n\n" +
                              query.lastError().text());
    }

	//Desconectando
    bd.Desconecta();
}

//Método para consultar pela pesquisa ao banco
QSqlQuery ClasseGenerica::Pesquisa(QString tabela, QString parametro,
                                   QString palavraChave)
{
	//Variáveis para verificar o valor e setar o comando SQL
    bool ok;
    QString sql = NULL;

	//Instância do banco
    Banco bd("datamusik");

	//Conectando
    bd.Conecta();

	//Se for Int ou Float, vai usar EQUALS. Se for String, vai usar LIKE
    if((palavraChave.toInt(&ok) || palavraChave.toFloat(&ok)) &&
	   (parametro == "id" || parametro == "quantidade" || parametro == "preco"))
    {
        sql = " SELECT * FROM datamusik."  + tabela +
              " WHERE " + parametro + " = " + palavraChave;
    }
    else
    {
        sql = " SELECT * FROM datamusik."  + tabela +
              " WHERE " + parametro + " LIKE " + "'" + palavraChave + "%'";
    }

	//Instância da query
    QSqlQuery query;

	//Preparando a query
    query.prepare(sql);

	//Se executar...
    if(query.exec())
    {
        return query;
    }
    else
    {
		//Verifica se tais campos não são nulos...
		if(!(query.isNull("id") || query.isNull("quantidade") ||
			 query.isNull("preco")))
        {
            QMessageBox::critical(NULL, "Erro", "Erro ao realizar pesquisa!\n\n" +
                                  query.lastError().text());
        }
    }

	//Desconectando...
    bd.Desconecta();
}
