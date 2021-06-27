# JDart

###Compilador de Dart para JVM.

####Requisitos:
- OpenJDK 14
- Graphviz

Para instalar o OpenJDK 14 utilize os seguintes comandos:

```bash
$ sudo apt update
$ sudo apt install openjdk-14-jdk
```

Para instalar o Graphviz utilize os seguintes comandos:

```bash
$ sudo apt update
$ sudo apt install graphviz
```

OBS: O Graphviz é "opcional", pois só é utilizado para
conferir se a *AST* está gerando os nós corretos. É possivel
retirar o comando que invoca o Graphviz do arquivo makefile.

####Execução

Para compilar o compilador e o runtime é necessário compilar o código java
utilizando o comando:
```bash
$ make
```
Para executar o compilador preparamos um comando que já invoca o compilador
aplicando um dos codigos de exemplo existentes (Especificamente o codigo 4.dart).
```bash
$ make run
```
Para testar o código gerado execute:
```bash
$ make run_java
```

####Limpeza

Para apagar os arquivos gerados durante a execução utilize
o comando a seguir:
```bash
$ make clean
```





