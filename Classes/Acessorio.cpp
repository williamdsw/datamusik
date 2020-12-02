//Inclusão de headers
#include "Acessorio.h"
#include <../Classes/Banco.h>

//Construtor
Acessorio::Acessorio(QString nome, QString tipo, QString inst,
                     QString marca, QString camft, QString infad,
                     QDateTime dataC, int quant, float preco)
{
    _nome = nome;
    _tipo = tipo;
    _instrumento = inst;
    _marca = marca;
    _caminhoFoto = camft;
    _informacoesAdicionais = infad;
    _dataCadastro = dataC;
    _quantidade = quant;
    _preco = preco;
}

//Método para inserir
QString Acessorio::Insere()
{
    //Instância do banco
    Banco bd("datamusik");

    //Conectando ao banco
    bd.Conecta();

    //Instânciando uma Query
    QSqlQuery query;

    //String que contém comandos SQL
    QString sql = "INSERT INTO datamusik.acessorio (nome, tipo, instrumento, data_cadastro, "
                                                   "caminho_foto, informacoes_adicionais, "
                                                   "marca, quantidade, preco) "
                  "values (:nome, :tipo, :instrumento, :data_cadastro, :caminho_foto, "
                          ":informacoes_adicionais, :marca, :quantidade, :preco)";

    //Preparando a query com parâmetros
    query.prepare(sql);

    //"Adicionando" os valores
    query.bindValue(":nome", _nome);
    query.bindValue(":tipo", _tipo);
    query.bindValue(":instrumento", _instrumento);
    query.bindValue(":data_cadastro", _dataCadastro);
    query.bindValue(":caminho_foto", _caminhoFoto);
    query.bindValue(":informacoes_adicionais", _informacoesAdicionais);
    query.bindValue(":marca", _marca);
    query.bindValue(":quantidade", _quantidade);
    query.bindValue(":preco", _preco);

    //Executando a Query e retornando uma mensagem
    if(query.exec())
    {
        return "Acessório cadastrado com sucesso!";
    }
    else
    {
        return "Erro ao cadastrar acessório\n\n" + query.lastError().text();
    }

    //Desconectando do banco
    bd.Desconecta();
}

//Método para alterar registro
QString Acessorio::Altera(int id)
{
    Banco bd("datamusik");

    bd.Conecta();

    QSqlQuery query;

    QString sql = "UPDATE datamusik.acessorio "
                  "SET "
                  "nome = :nome, "
                  "tipo = :tipo, "
                  "instrumento = :instrumento, "
                  "caminho_foto = :caminho_foto, "
                  "informacoes_adicionais = :informacoes_adicionais, "
                  "marca = :marca, "
                  "quantidade = :quantidade, "
                  "preco = :preco "
                  "WHERE id = :id";

    query.prepare(sql);

    query.bindValue(":nome", _nome);
    query.bindValue(":tipo", _tipo);
    query.bindValue(":instrumento", _instrumento);
    query.bindValue(":caminho_foto", _caminhoFoto);
    query.bindValue(":informacoes_adicionais", _informacoesAdicionais);
    query.bindValue(":marca", _marca);
    query.bindValue(":quantidade", _quantidade);
    query.bindValue(":preco", _preco);
    query.bindValue(":id", id);

    if(query.exec())
    {
        return "Acessório alterado com sucesso!";
    }
    else
    {
        return "Erro ao alterar acessório\n\n" + query.lastError().text();
    }

    bd.Desconecta();
}
