/*Resenje 1 - svaka viljuska je svoj proces i svaka viljuska vodi racuna o sebi, pa nam ne treba 
proces koordinator. Svaka viljuska cita iz 2 postanska sanduceta. Mrtvu blokadu cemo izbeci tako sto ce svi
filozofi prvo traziti levu pa desnu viljusku, dok ce poslednji filozof jedini traziti prvo desnu pa levu - da izbegnemo
deadlock  */
const int N = 5; 
typedef struct msg{
    int senderId;
}msg;


mbx philosophers[N];
mbx getFork[N];
void Philosopher(int id){
    int firstFork, secondFork;
    msg message, responseMessage;
    bool status;

    if(id == N-1){
        firstFork = 0;
        secondFork = id;
    }else{
        fistFork = id;
        secondFork = id+1;
    }

    while(true){
        think();

        //filozof trazi viljuske

        message.senderId = id;
        mbx_put(message, getFork[firstFork]);

        mbx_get(responseMessage, philosophers[id], INF,status);

        mbx_put(message, getFork[secondFork]);

        mbx_get(responseMessage, philosophers[id], INF, status);

        eat();

        // filozof javlja da je gotov sa jelom

        mbx_put(message, returnFork[firstFork]);
        mbx_put(message, returnFork[secondFork]);



    }
}

/*za svku viljusku 2 sanduceta -> jedno u koje stizu poruke od filozofa koji zele da dobiju tu viljusku.
Ovo smo uradili da bismo mogli u fji Fork da razlikujemo dva tipa poruka*/

mbx getFork[N], returnFork[N];

void Fork(int id){
    msg message;
    bool status;

    while(true){
        //cekamo da filozof zatrazi viljusku
        mbx_get(message, getFork[id], INF, status);

        //javljamo filozofu da moze da koristi viljusku

        mbx_put(message, philosophers[message.senderId]);

        //cekamo da filozof vrati viljusku

        mbx_get(message, returnFork[id], INF, status);
    }
}


/*Resenje 2 - jedna viljuska moze da cita iz samo jednog sanduceta*/

const int N = 5;

typdef struct msg{
    int senderId;
    const char* operation;
}


mbx philosophers[N];
void Philosopher(int id){
    int firstFork, secondFork;
    msg message, responseMessage;
    bool status;

    if(id ==N-1){
        firstFork = 0;
        secondFork = id;

    }else{
        firstFork = id;
        secondFork = id + 1;

    }

    while(true){
        think();

        //filozof trazi viljuske

        message.senderId = id;

        message.operation = "startEating";

        mbx_put(message, forks[firstFork]);

        mbx_get(responseMessage, philosophers[id], INF, status);

        mbx_put(message, forks[secondFork]);

        mbx_get(responseMessage, philosophers[id], INF, status);

        eat();

        message.senderId = id;

        message.operation = "endEating";

        mbx_put(message,forks[firstFork] );

        mbx_put(message, forks[secondFork]);

    }
}

mbx forks[N];

void Forks(int id){
    msg message;
    bool status;
    msg philosopherWaiting = NULL;

    while(true){
        if(philosopherWaiting == NULL){
            /*u ovu granu ulazimo ako nema filozofa koji
            ceka ovu viljusku od kad je prosli filozof nju 
            koristio, cekamo da neki filozof zatrazi viljusku*/
            mbx_get(message, forks[id], INF,status);
        }else{
            /*u ovu granu ulazimo ako ima filozofa koji ceka ovu viljusku
            od kad je prosli filozof nju koristion, pa hocemo njemu
            da je damo na koriscenje*/
            message = philosopherWaiting;
            philosopherWaiting = NULL;
        }

        /*javljamo filozofu da moze da koristi viljusku*/
        mbx_put(message, philosophers[message.senderId]);

        /*ako je message,operation == startEating to znaci da je neki 
        filozof zatrazio viljusku dok je neki drugi koristi*/

        /*ako je endEating, filozof koji je koristio viljusku
        javlja da je gotov*/
        mbx_get(message, forks[id], INF, status);

        if(message.operation == "startEating"){
            philosopherWaiting = message;
            mbx_get(message, forks[id], INF, status);
        }
    }
}