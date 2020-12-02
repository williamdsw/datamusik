//Definição do header
#ifndef INSTRUMENTO_H
#define INSTRUMENTO_H

#include "../Classes/Produto.h"

//Inclusão das bibliotecas
#include <QString>
#include <QDateTime>
#include <QtSql>

//definição da classe
class Instrumento : public Produto
{
    public:

		//Construtor com parâmetros
        Instrumento(QString nome, QString tipo, QString inst, QString estad,
                    QString marca, QString camft, QString infad,
                    QDateTime dataC, int quant, float preco);

		//Insere registro no banco
        QString Insere();

		//Altera registro no banco
        QString Altera(int id);
};

#endif // INSTRUMENTO_H
