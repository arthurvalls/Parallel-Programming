Respostas Laboratório 1: 

Questão 1) Sim, há mudanças na ordem de execução das threads, 
visto que a ordem de execução depende da maneira de como o sistema operacional escalonará as threads.

Questão 2) Percebe-se que a ordem de execução permanece a mesma,
porém através do argumento "ident" utilizado para distinguir uma thread da outra,
conseguimos visualizar a ordem de execução dos "hello world" de cada thread.

Questão 3) Sim, o programa funcionou, alocando espaço na memória e preenchendo os argumentos,
os convertendo de ponteiro pra void e no struct fazendo a conversão de volta para
o tipo que foi definido para a estrutura.

Questão 4) Nas questões anteriores percebemos que em várias das execuções, a thread principal não foi a última a terminar. 
O que foi consertado nesta questão ao utilizarmos a função join da biblioteca pthread, que faz com que a thread principal aguarde as outras terminarem.


