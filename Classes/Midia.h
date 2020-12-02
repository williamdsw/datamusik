//Definição do header
#ifndef MIDIA_H
#define MIDIA_H

#include "../Classes/Produto.h"

//inclusão de bibliotecas
#include <QString>
#include <QDateTime>
#include <QtSql>

//definição da classe
class Midia : public Produto
{
    private:

        //Variáveis
		QString _artista, _genero, _duracao, _idioma;
		int _anoLancamento;

    public:

		//Construtor com parâmetros
        Midia(QString nome, QString artis, QString gener, QString estad, QString tipo,
              QString durac, QString idiom, QString infad, QString camft, int ano,
              int quant,  float preco, QDateTime data);

		//Insere no banco
        QString Insere();

		//altera dados no banco
        QString Altera(int id);
};

#endif // MIDIA_H
