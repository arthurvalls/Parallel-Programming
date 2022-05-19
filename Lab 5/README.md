# Atividade 1: <br>

2) Sim, o programa funcionou como esperado, printando a mensagem "bye" depois de printar dois "hello". <br>

3) Ao alterar o número de threads A para 1, o programa não termina, isso acontece pois além da thread A executar antes da B começar, nós temos apenas 1 thread A agora,
ou seja, a variável global x nunca atingirá o valor = 2. <br>

5) Alterando o número de threads B para 2, e fazendo as devidas alterações para que o programa continue funcionando, 2 casos foram observados na saída do meu programa: <br>

  I) Ambas as threads B são executadas após as threads A e dessa maneira o programa funciona normalmente e finaliza; <br>

  II) Apenas uma thread B finaliza printando "bye", pois o programa possui apenas um sinal de desbloqueio, logo apenas uma thread B é desbloqueada, e o programa não finaliza. <br>

# Atividade 2: <br>

2) Sim, em todas as execuções foram printados dois "bye" após a thread B printar "hello". <br>

# Atividade 3: <br>

2) Não, em algumas execuções foram printados os números 9, 19 e 23 pela thread B.

3-4) Sim, podemos substituir pois, quando usamos o if ele verifica a condição apenas uma vez, enquanto com while ele sempre verifica, 
logo a lógica da aplicação foi atendida todas as vezes. <br>
