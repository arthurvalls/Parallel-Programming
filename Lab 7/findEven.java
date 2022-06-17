// Laboratório 7 - Computação Concorrente
// Nome: Arthur Valls da Costa Silva
// DRE: 120177470

import java.util.ArrayList;

//classe da estrutura de dados (recurso) compartilhado entre as threads
class S {
    //recurso compartilhado
    private ArrayList<Integer> array;
    private int r;

    //construtor
    public S(ArrayList<Integer> array) {
        this.array = array;
        this.r = 0;
    }


    public int even() {
        return this.r;
    }

    public int get(int i) {
        return this.array.get(i);
    }

    public synchronized void numEven() {
        this.r++;
    }

    public int dim() {
        return this.array.size();
    }

}

//classe que estende Thread e implementa a tarefa de cada thread do programa
class T extends Thread {
    //objeto compartilhado com outras threads
    S s;
    //identificador da thread
    private int id;

    //construtor
    public T(int tid, S s) {
        this.id = tid;
        this.s = s;
    }

    //metodo main da thread
    public void run() {
        //System.out.println("Thread " + this.id + " iniciou!");
        for (int i = id; i < this.s.dim(); i += findEven.N) {
            if ((this.s.get(i)) % 2 == 0) {
                s.numEven();
            }
            //System.out.println("Thread " + this.id + " terminou!");
        }
    }
}


//classe da aplicacao
public class findEven {
    static final int dim = 50000;
    static final int N = 3;

    public static void main(String[] args) {

        Thread[] threads = new Thread[N];


        var array = new ArrayList<Integer>();
        for (int i = 0; i < dim; i++) {
            array.add(i);
        }
        S s = new S(array);


        //cria as threads da aplicacao
        for (int i = 0; i < threads.length; i++) {
            threads[i] = new T(i, s);
        }

        //inicia as threads
        for (int i = 0; i < threads.length; i++) {
            threads[i].start();
        }

        //espera pelo termino de todas as threads
        for (int i = 0; i < threads.length; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                return;
            }
        }

        System.out.println("Valor de s = " + s.even());
    }
}
