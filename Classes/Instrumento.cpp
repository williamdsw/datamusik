//inclusão de headers
#include "Instrumento.h"
#include <../Classes/Banco.h>

//Construtor
Instrumento::Instrumento(QString nome, QString tipo, QString inst, QString estad,
                         QString marca, QString camft, QString infad,
                         QDateTime dataC, int quant, float preco)
{
    _nome = nome;
    _tipo = tipo;
    _instrumento = inst;
    _estado = estad;
    _marca = marca;
    _caminhoFoto = camft;
    _informacoesAdicionais = infad;
    _dataCadastro = dataC;
    _quantidade = quant;
    _preco = preco;
}

//Método para inserir
QString Instrumento::Insere()
{
	//Instância do banco
    Banco bd("datamusik");

	//Conectando
    bd.Conecta();

	//Instância da query
    QSqlQuery query;

	//Comando SQL
    QString sql = "INSERT INTO datamusik.instrumento (nome, tipo, instrumento, estado, "
                                                     "data_cadastro, caminho_foto, "
                                                     "informacoes_adicionais, marca, "
                                                     "quantidade, preco) "
                  "VALUES (:nome, :tipo, :instrumento, :estado, :data_cadastro, "
						  ":caminho_foto, :informacoes_adicionais, :marca, "
						  ":quantidade, :preco)";

	//Preparando a query
    query.prepare(sql);

	//Setando os valores das colunas...
    query.bindValue(":nome", _nome);
    query.bindValue(":tipo", _tipo);
    query.bindValue(":instrumento", _instrumento);
    query.bindValue(":estado", _estado);
    query.bindValue(":data_cadastro", _dataCadastro);
    query.bindValue(":caminho_foto", _caminhoFoto);
    query.bindValue(":informacoes_adicionais", _informacoesAdicionais);
    query.bindValue(":marca", _marca);
    query.bindValue(":quantidade", _quantidade);
    query.bindValue(":preco", _preco);

	//Se executar...
    if(query.exec())
    {
        return "Instrumento cadastrado com sucesso!";
    }
    else
    {
        return "Erro ao cadastrar instrumento\n\n" + query.lastError().text();
    }

	//Desconectando
    bd.Desconecta();
}

//Método para alterar
QString Instrumento::Altera(int id)
{
	//Instância do banco
    Banco bd("datamusik");

	//Conectando
    bd.Conecta();

	//Instância da query
    QSqlQuery query;

	//Comando sql
    QString sql = "UPDATE datamusik.instrumento "
                  "SET "
                  "nome = :nome, "
                  "tipo = :tipo, "
                  "instrumento = :instrumento, "
                  "estado = :estado, "
                  "caminho_foto = :caminho_foto, "
                  "informacoes_adicionais = :informacoes_adicionais, "
                  "marca = :marca, "
                  "quantidade = :quantidade, "
                  "preco = :preco "
                  "WHERE id = :id";

	//Preparando a query
    query.prepare(sql);

	//Setando os valores das colunas
    query.bindValue(":nome", _nome);
    query.bindValue(":tipo", _tipo);
    query.bindValue(":instrumento", _instrumento);
    query.bindValue(":estado", _estado);
    query.bindValue(":caminho_foto", _caminhoFoto);
    query.bindValue(":informacoes_adicionais", _informacoesAdicionais);
    query.bindValue(":marca", _marca);
    query.bindValue(":quantidade", _quantidade);
    query.bindValue(":preco", _preco);
    query.bindValue(":id", id);

	//Se executar...
    if(query.exec())
    {
        return "Instrumento alterad com sucesso!";
    }
    else
    {
        return "Erro ao alterar instrumento\n\n" + query.lastError().text();
    }

	//Desconectando
    bd.Desconecta();
}
