CREATE TABLE datamusik.midia
(
    id SERIAL NOT NULL,
    nome VARCHAR(100) NOT NULL,
    artista VARCHAR(50) NOT NULL,
    genero VARCHAR(50) NOT NULL,
    ano_lancamento INTEGER NOT NULL,
    estado VARCHAR(15) NOT NULL,
    tipo VARCHAR(15) NOT NULL,
    data_cadastro TIMESTAMP NOT NULL,
    duracao VARCHAR(20) NULL,
    preco DECIMAL(10,2) NULL,
    quantidade INTEGER NULL,
    idioma varchar(50),
    informacoes_adicionais VARCHAR NULL,
    caminho_foto VARCHAR NULL
);

ALTER TABLE datamusik.midia
ADD CONSTRAINT pk_midia
PRIMARY KEY (id)
