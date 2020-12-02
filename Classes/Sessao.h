//Definição do header
#ifndef SESSAO_H
#define SESSAO_H

//Inclusão das bibliotecas
#include <QString>
#include <QDateTime>
#include <QtSql>
#include <QMessageBox>

//Definição da classe
class Sessao
{
    private:

        //Variáveis
		QString _telas;
        int _idUsuario;
        QDateTime _inicio, _termino;

    public:

        //Construtor
		Sessao(QString telas, int idusr, QDateTime inic, QDateTime term);

        //Método para inserir no banco
        void Insere();
};

#endif //SESSAO_H
