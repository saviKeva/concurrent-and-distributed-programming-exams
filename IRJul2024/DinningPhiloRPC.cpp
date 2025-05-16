//server
//RPC - remote procedure calls - za svaki zahtev
//se kreira nova nit + se na serveru
//nalaze procedure koje klijent poziva (ili neki interfejs)
//pretpostavka da je ovo monitor SC
const int numPh=10;
typedef struct RPCModule{
    //deklaracija procedura koje se koriste
    int state[5]={0};
    //0-thinking,1-hungry,2-eating
    sem sem[5] ={0};

    sem mutex =0 ;

    const int nPh=5;

    void get_fork(int id);
    void put_fork(int id);
    void test(int id);

    int right(int id);
    int left(int id);
    void server(){
        while(true){
            //primi svaki zahtev i obradi ga u novoj niti

        }

    }

    //definicije procedura koje klijenti koriste

    
    void put_fork(int id){
        mutex.wait();
        state[id] = 1; //hungry
        test(id);
        mutex.signal();
        sem[id].wait();
    }

    int left(int id){
        return id;
    }

    int right(int id){
        return (id+1 +nPh)%nPh;
    }

    void put_fork(int id){
        mutex.wait();
        state[id] = 0; //thinking
        test(right(id));
        test(left(id));
        mutex.signal();
    }

    void test(int i){
        if(state[i]==1 && state[(left(i))]!=2 &&
            state[right(i)]!=2
        ){
            //levi i desni ne jedu
            state[i]=2;
            sem[i].signal();
        }
    }
   
}