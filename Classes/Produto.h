#pragma once

//Inclusão de biblioteca
#include <QString>
#include <QDateTime>
#include <QtSql>

//Definição da classe
class Produto
{
	protected:

		//Variáveis
		QString _nome, _tipo, _instrumento, _estado, _marca, _caminhoFoto, _informacoesAdicionais;
		QDateTime _dataCadastro;
		int _quantidade;
		float _preco;

	public:

		virtual QString Insere() = 0;
		virtual QString Altera(int id) = 0;
};
