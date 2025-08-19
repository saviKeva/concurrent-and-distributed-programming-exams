//randevu - ne kreiraju se nove niti za svaki poziv 
//procedure
//vec se se sve izvrsava u okviru jedne niti
//pozivi procedura se izvrsavaju sekvencijalno
//u okviru jedne niti
//ovde je korisna alternativna komanda
//serverski proces se blokira na "in" dok ne stigne zatev od nekog klijenta
//a klijentski proces ce biti blokiran sve dok serverski proces ne dodje do "ni"

typdef struct DinningPhiloRendezvousServer{

    //deklaracija procedura koje se koriste

    void dohvatiViljuske(int idF);
    void vratiViljuske(int idF);
    
    const int N = 5;
    bool jedu[N] ={false};
    int i;

    while(true){
        in

        dohvatiViljuske(i) and !jedu[(i-1)%N<0? ((i-1)%N +N) :(i-1)%N] and 
        !jedu[(i+1)%N] ->[
            jedu[i] = true;
        ]

        [];

        vratiViljuske(i) ->[
            jedu[i] = false;
        ]

        ni
    }


}DinningPhiloRendezvousServer;

void Philososhper(int id){
    while(true){
        //think
        server.dohvatiViljuske(i);
        //eat
        server.vratiViljuske(i);
    }
}

