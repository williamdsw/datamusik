CREATE TABLE datamusik.instrumento
(
    id SERIAL NOT NULL,
    nome VARCHAR(100) NOT NULL,
    tipo VARCHAR(30) NOT NULL,
    instrumento VARCHAR(30) NOT NULL,
    estado VARCHAR(15) NOT NULL,
    data_cadastro TIMESTAMP NOT NULL,
    marca VARCHAR(50) NULL,
    preco DECIMAL(10,2) NULL,
    quantidade INTEGER NULL
    caminho_foto VARCHAR NULL,
    informacoes_adicionais VARCHAR NULL
);

ALTER TABLE datamusik.instrumento
ADD CONSTRAINT pk_instrumento
PRIMARY KEY (id)
