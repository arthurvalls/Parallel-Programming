# Atividade 1: <br>

3 - Sim, a ordem em que as threads são criadas não muda, porém há mudança na ordem de execução das threads, visto que por falta da sincronização das threads, todas acessam a variável ao mesmo tempo, dessa maneira a thread mais rápida finaliza primeiro. <br>

5 - A mensagem "terminou" aparece apenas quando todas as threads finalizam suas respectivas execuções, visto que a main agora aguarda todas as threads terminarem, através do método .join . <br>

# Atividade 2: <br>

1 - No programa OlaThread, diferente do programa HelloThread, as threads são criadas através da classe Ola que estende a classe Thread, ao invés de um runnable.  <br>

2 - Similarmente ao outro programa, percebemos como resultado que a a mensagem terminou é impressa após todas as threads finalizarem, devido ao método .join . <br>

# Atividade 3: <br>
**OBS: Para a atividade 3 e 4 considera-se que as linhas 17-23 já estão descomentadas e as linhas 27-33 já estão comentadas, porém no programa disponibilizado no zip no Classroom, o contrário é verdade.** <br>

1 - Percebe-se que a seção crítica do código é a main da thread, onde a varíavel S é acessada e manipulada por ambas as threads ao mesmo tempo. Espera-se que a saída do programa seja "Valor de s = 200000" <br>

2 - Visto que não há exclusão mútua na hora de acessar e manipular a varíavel, ambas as threads à acessam simultaneamente, o que acarreta uma condição de corrida, gerando valores diferentes do esperado. <br> 

# Atividade 4: <br>

3 - Sim, em todas as execuções foram impressos o valor esperado de 200000, visto que foi utilizado o método synchronized, ocasionando uma exclusão mútua entre as threads. <br>
