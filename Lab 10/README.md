# Laboratório 10

## Atividade 1 <br>

a) Percebe-se para que o código funcione corretamente é necessário que os semáforos sejam inicializados com o valor igual a 1. <br>

b) Para este código, nota-se que é essencial a existência de 4 semáforos para que haja a sincronização entre as threads leitoras consigo mesmas e escritoras também consigo mesmas, e também haja a sincronização entre as escritoras e leitoras.  <br>

c) Exemplos abaixo.

Execução com 3 leitores e 3 escritores:<br>

```
Escritor 1 quer escrever!
Escritor 1 está escrevendo!
Escritor 3 quer escrever!
Leitor 1 quer ler!
Escritor 3 está escrevendo!
Escritor 3 terminou de escrever!
Leitor 2 quer ler!
Escritor 2 quer escrever!
Escritor 2 está escrevendo!
Escritor 1 terminou de escrever!
Escritor 2 terminou de escrever!
Leitor 1 está lendo!
Leitor 2 está lendo!
Leitor 3 quer ler!
Leitor 3 está lendo!
Escritor 3 quer escrever!
Escritor 1 quer escrever!
Escritor 2 quer escrever!
Leitor 1 terminou de ler!
Leitor 1 quer ler!
Leitor 2 terminou de ler!
Leitor 2 quer ler!
Leitor 3 terminou de ler!
Leitor 3 quer ler!
Escritor 3 está escrevendo!
Escritor 3 terminou de escrever!
Escritor 1 está escrevendo!
Escritor 1 terminou de escrever!
Escritor 2 está escrevendo!
Escritor 2 terminou de escrever!
Leitor 1 está lendo!
Leitor 2 está lendo!
Leitor 3 está lendo!
Escritor 3 quer escrever!
Escritor 1 quer escrever!
Escritor 2 quer escrever!
Leitor 1 terminou de ler!
Leitor 1 quer ler!
Leitor 2 terminou de ler!
Leitor 2 quer ler!
Leitor 3 terminou de ler!
Leitor 3 quer ler!
Escritor 3 está escrevendo!
Escritor 3 terminou de escrever!
Escritor 1 está escrevendo!
Escritor 1 terminou de escrever!
Escritor 2 está escrevendo!
Escritor 2 terminou de escrever!
Leitor 1 está lendo!
Leitor 3 está lendo!
Leitor 2 está lendo!
Escritor 3 quer escrever!
Escritor 1 quer escrever!
Escritor 2 quer escrever!
Leitor 3 terminou de ler!
Leitor 3 quer ler!
Leitor 1 terminou de ler!
Leitor 1 quer ler!
Leitor 2 terminou de ler!
Leitor 2 quer ler!
Escritor 3 está escrevendo!
Escritor 3 terminou de escrever!
Escritor 1 está escrevendo!
Escritor 1 terminou de escrever!
Escritor 2 está escrevendo!
Escritor 2 terminou de escrever!
Leitor 3 está lendo!
Leitor 1 está lendo!
Leitor 2 está lendo!
Escritor 3 quer escrever!
Escritor 1 quer escrever!
Escritor 2 quer escrever!
Leitor 3 terminou de ler!
Leitor 3 quer ler!
Leitor 1 terminou de ler!
Leitor 1 quer ler!
Leitor 2 terminou de ler!
Leitor 2 quer ler!
Escritor 3 está escrevendo!
Escritor 3 terminou de escrever!
Escritor 1 está escrevendo!
Escritor 1 terminou de escrever!
Escritor 2 está escrevendo!
Escritor 2 terminou de escrever!
Leitor 3 está lendo!
Leitor 1 está lendo!
Leitor 2 está lendo!

``` 

<br> Execução com 2 leitores e 3 escritores:

```
Escritor 1 quer escrever!
Escritor 3 quer escrever!
Leitor 1 quer ler!
Leitor 2 quer ler!
Escritor 1 está escrevendo!
Escritor 1 terminou de escrever!
Escritor 3 está escrevendo!
Escritor 3 terminou de escrever!
Escritor 2 quer escrever!
Leitor 1 está lendo!
Escritor 3 quer escrever!
Escritor 1 quer escrever!
Leitor 1 terminou de ler!
Leitor 1 quer ler!
Escritor 2 está escrevendo!
Escritor 2 terminou de escrever!
Escritor 3 está escrevendo!
Escritor 3 terminou de escrever!
Escritor 1 está escrevendo!
Escritor 1 terminou de escrever!
Leitor 2 está lendo!
Leitor 1 está lendo!
Escritor 2 quer escrever!
Escritor 3 quer escrever!
Escritor 1 quer escrever!
Leitor 2 terminou de ler!
Leitor 2 quer ler!
Leitor 1 terminou de ler!
Leitor 1 quer ler!
Escritor 2 está escrevendo!
Escritor 2 terminou de escrever!
Escritor 3 está escrevendo!
Escritor 3 terminou de escrever!
Escritor 1 está escrevendo!
Escritor 1 terminou de escrever!
Leitor 2 está lendo!
Leitor 1 está lendo!
Escritor 2 quer escrever!
Escritor 3 quer escrever!
Escritor 1 quer escrever!
Leitor 2 terminou de ler!
Leitor 2 quer ler!
Leitor 1 terminou de ler!
Leitor 1 quer ler!
Escritor 2 está escrevendo!
Escritor 2 terminou de escrever!
Escritor 3 está escrevendo!
Escritor 3 terminou de escrever!
Escritor 1 está escrevendo!
Escritor 1 terminou de escrever!
Leitor 2 está lendo!
Leitor 1 está lendo!
Escritor 2 quer escrever!
Escritor 3 quer escrever!
Escritor 1 quer escrever!
Leitor 1 terminou de ler!
Leitor 1 quer ler!
Leitor 2 terminou de ler!
Leitor 2 quer ler!
Escritor 2 está escrevendo!
Escritor 2 terminou de escrever!
Escritor 3 está escrevendo!
Escritor 3 terminou de escrever!
Escritor 1 está escrevendo!
Escritor 1 terminou de escrever!
Leitor 1 está lendo!
Leitor 2 está lendo!
```
