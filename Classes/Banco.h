//Definição do header
#ifndef BANCO_H
#define BANCO_H

//Inclusão de classes
#include <QtSql>
#include <QMessageBox>
#include <QString>

//Definição da classe
class Banco
{
    public:

		//Construtor
        Banco(QString bd);

		//Conexão
        void Conecta();

		//Desconexão
        void Desconecta();

    protected:

		//Variáveis
        QString _usuario = "sultan",
                _senha = "sultan123@",
                _hostName = "localhost",
                _banco;
        int _porta = 5432;
};

#endif
