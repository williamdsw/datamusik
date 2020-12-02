//inclusão de headers
#include "Midia.h"
#include <../Classes/Banco.h>

//Construtor
Midia::Midia(QString nome, QString artis, QString gener, QString estad, QString tipo,
             QString durac, QString idiom, QString infad, QString camft, int ano,
             int quant,  float preco, QDateTime data)
{
    _nome = nome;
    _artista = artis;
    _genero = gener;
    _estado = estad;
    _tipo = tipo;
    _duracao = durac;
    _idioma = idiom;
    _informacoesAdicionais = infad;
    _caminhoFoto = camft;
    _anoLancamento = ano;
    _dataCadastro = data;
    _quantidade = quant;
    _preco = preco;
}

//Método para inserir
QString Midia::Insere()
{
	//Instância do banco
    Banco bd("datamusik");

	//Conectando...
    bd.Conecta();

	//Instância da query
    QSqlQuery query;

	//Comando SQL
    QString sql = "INSERT INTO datamusik.midia (nome, artista, genero, estado, tipo, "
											   "duracao, idioma, informacoes_adicionais, "
											   "caminho_foto, ano_lancamento, "
											   "data_cadastro, quantidade, preco) "
                  "VALUES (:nome, :artista, :genero, :estado, :tipo, :duracao, :idioma, "
                          ":informacoes_adicionais, :caminho_foto, :ano_lancamento, "
                          ":data_cadastro, :quantidade, :preco) ";

	//Preparando a query
    query.prepare(sql);

	//Setando valores das colunas
    query.bindValue(":nome", _nome);
    query.bindValue(":artista", _artista);
    query.bindValue(":genero", _genero);
    query.bindValue(":estado", _estado);
    query.bindValue(":tipo", _tipo);
    query.bindValue(":duracao", _duracao);
    query.bindValue(":idioma", _idioma);
    query.bindValue(":informacoes_adicionais", _informacoesAdicionais);
    query.bindValue(":caminho_foto", _caminhoFoto);
    query.bindValue(":ano_lancamento", _anoLancamento);
    query.bindValue(":data_cadastro", _dataCadastro);
    query.bindValue(":quantidade", _quantidade);
    query.bindValue(":preco", _preco);

	//Se executar...
    if(query.exec())
    {
        return "Mídia cadastrada com sucesso!";
    }
    else
    {
        return "Erro ao cadastrar mídia\n\n" + query.lastError().text();
    }

	//Desconectando...
    bd.Desconecta();
}

//Método para alterar
QString Midia::Altera(int id)
{
	//Instância do banco
    Banco bd("datamusik");

	//Conectando ao banco
    bd.Conecta();

	//Instância da query
    QSqlQuery query;

	//Comando SQL
    QString sql = "UPDATE datamusik.midia "
                  "SET "
                  "nome = :nome,"
                  "artista = :artista, "
                  "genero = :genero, "
                  "estado = :estado,"
                  "tipo = :tipo, "
                  "duracao = :duracao, "
                  "idioma = :idioma, "
                  "informacoes_adicionais = :informacoes_adicionais, "
                  "caminho_foto = :caminho_foto, "
                  "ano_lancamento = :ano_lancamento, "
                  "quantidade = :quantidade, "
                  "preco = :preco "
                  "WHERE id = :id";

	//Preparando a query
    query.prepare(sql);

	//Setando os parâmetros
    query.bindValue(":nome", _nome);
    query.bindValue(":artista", _artista);
    query.bindValue(":genero", _genero);
    query.bindValue(":estado", _estado);
    query.bindValue(":tipo", _tipo);
    query.bindValue(":duracao", _duracao);
    query.bindValue(":idioma", _idioma);
    query.bindValue(":informacoes_adicionais", _informacoesAdicionais);
    query.bindValue(":caminho_foto", _caminhoFoto);
    query.bindValue(":ano_lancamento", _anoLancamento);
    query.bindValue(":quantidade", _quantidade);
    query.bindValue(":preco", _preco);
    query.bindValue(":id", id);

	//Se executar
    if(query.exec())
    {
        return "Mídia alterada com sucesso!";
    }
    else
    {
        return "Erro ao alterar mídia\n\n" + query.lastError().text();
    }

	//Desconetando
    bd.Desconecta();
}
