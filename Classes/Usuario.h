//Definição do header
#ifndef USUARIO_H
#define USUARIO_H

//Inclusão de Bibliotecas
#include <QString>
#include <QDateTime>
#include <QtSql>
#include <QMessageBox>

//Definição da classe
class Usuario
{
    private:

        //variáveis
        QString _nome, _senha, _perfil, _caminhoFoto;
        QDateTime _dataCadastro;

    public:

        Usuario();

        //Construtor
        Usuario(QString nome, QString senha, QString perfil, QString camft,
                QDateTime dataC);

        //Método para inserir no banco
        QString Insere();

        //Método para alterar no banco
        QString Altera(int id);

        //Método para autenticar usuário
        bool Autentica(QString usuario, QString senha);

		//Método para verificar se já existe um usuário
		bool VerificaNome(QString nome);

		bool VerificaAdministrador();

		//Método para retornar id e perfil
		QSqlQuery RetornaDados(QString nome);

		//Método para pegar o nome
		QString RetornaNome(int id);
};

#endif //USUARIO_H
