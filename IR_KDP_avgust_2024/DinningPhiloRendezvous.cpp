//randevu - ne kreiraju se nove niti za svaki poziv 
//procedure
//vec se se sve izvrsava u okviru jedne niti
//pozivi procedura se izvrsavaju sekvencijalno
//u okviru jedne niti
//ovde je korisna alternativna komanda
//serverski proces se blokira na "in" dok ne stigne zatev od nekog klijenta
//a klijentski proces ce biti blokiran sve dok serverski proces ne dodje do "ni"

typdef struct DinningPhiloRendezvousModule{

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


}DinningPhiloRendezvousModule;

