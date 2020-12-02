CREATE TABLE datamusik.sessao
(
    id SERIAL NOT NULL,
    id_usuario INTEGER NOT NULL,
    inicio TIMESTAMP NOT NULL,
    termino TIMESTAMP NOT NULL,
    telas TEXT[] NOT NULL
);

ALTER TABLE datamusik.sessao
ADD CONSTRAINT pk_sessao
PRIMARY KEY (id);

ALTER TABLE datamusik.sessao
ADD CONSTRAINT fk_usuario
FOREIGN KEY (id_usuario)
REFERENCES datamusik.usuario(id);
