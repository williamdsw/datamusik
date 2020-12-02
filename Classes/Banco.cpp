//Inclusão do header
#include "Banco.h"

//Instância do Banco
QSqlDatabase meuBanco = QSqlDatabase::addDatabase("QPSQL");

//Construtor
Banco::Banco(QString bd)
{
    _banco = bd;
}

//Método para conectar
void Banco::Conecta()
{
    //Setando parâmetros de conexão do banco
    meuBanco.setDatabaseName(_banco);

    meuBanco.setHostName(_hostName);

    meuBanco.setUserName(_usuario);

    meuBanco.setPassword(_senha);

    meuBanco.setPort(_porta);

    //Abrindo a conexão
    meuBanco.open();

    //Verificando se o banco está não aberto, irá lançar uma mensagem
    if(!meuBanco.isOpen())
    {
        QMessageBox::critical(NULL, "Erro na conexão do banco",
                              meuBanco.lastError().text());
    }
}

//Método para desconectar
void Banco::Desconecta()
{
    meuBanco.close();
}
