//Definição do header
#ifndef ACESSORIO_H
#define ACESSORIO_H

#include "../Classes/Produto.h"

//Inclusão de biblioteca
#include <QString>
#include <QDateTime>
#include <QtSql>

//Definição da classe
class Acessorio : public Produto
{
    public:

        //Construtor
        Acessorio(QString nome, QString tipo, QString inst, QString marca,
                  QString camft, QString infad,
                  QDateTime dataC, int quant, float preco);

		QString Insere();

		QString Altera(int id);
};

#endif // ACESSORIO_H
