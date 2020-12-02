//Definição do header
#ifndef CLASSEGENERICA_H
#define CLASSEGENERICA_H

//Inclusão de classes
#include <QString>
#include <QMessageBox>
#include <QtSql>

//Definição da classe
class ClasseGenerica
{
    public:

		//Construtor vazio
        ClasseGenerica();

		//Consultar dados no banco
        QSqlQuery Consulta(QString tabela);

		//Pesquisar dados no banco
        QSqlQuery Pesquisa(QString tabela, QString parametro, QString palavraChave);

		//Excluir registro do banco
        QString Excluir(QString tabela, int id);
};

#endif //CLASSEGENERICA_H
