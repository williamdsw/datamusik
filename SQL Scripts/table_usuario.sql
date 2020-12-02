CREATE TABLE datamusik.usuario
(
    id SERIAL NOT NULL,
    nome VARCHAR(100) NOT NULL,
    cpf VARCHAR(15) NOT NULL,
    senha VARCHAR(20) NOT NULL,
    perfil VARCHAR(15) NOT NULL,
    data_cadastro TIMESTAMP NOT NULL,
    caminho_foto VARCHAR(30) NULL
);

ALTER TABLE datamusik.usuario
ADD CONSTRAINT pk_usuario
PRIMARY KEY (id);
