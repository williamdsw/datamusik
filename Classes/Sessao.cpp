//Inclusão de headers
#include "Sessao.h"
#include "../Classes/Banco.h"

//Construtor
Sessao::Sessao(QString telas, int idusr, QDateTime inic, QDateTime term)
{
    _telas = telas;
    _idUsuario = idusr;
    _inicio = inic;
    _termino = term;
}

//Método para inserir no banco
void Sessao::Insere()
{
    Banco bd("datamusik");

    bd.Conecta();

    QSqlQuery query;

    QString sql = "INSERT INTO datamusik.sessao (id_usuario, inicio, termino, telas) "
                  "VALUES (:id_usuario, :inicio, :termino, :telas) ";

    query.prepare(sql);

    query.bindValue(":id_usuario", _idUsuario);
    query.bindValue(":inicio", _inicio);
    query.bindValue(":termino", _termino);
    query.bindValue(":telas", _telas);

    if(!query.exec())
    {
		QMessageBox::critical(NULL, "Alerta", "Erro ao cadastrar sessão\n" +
                                    query.lastError().text());
    }
}
