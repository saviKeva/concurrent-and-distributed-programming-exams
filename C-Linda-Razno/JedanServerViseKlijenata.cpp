using namespace std;

void server(){
    int index = 1;
    while(1){
        in("request", index, ?req);

        //index da bi zahtev koji pe stigne bio pre opsluzen

        //...obrada

        out("response", index++, response);
    }
}

void client(int id){
    int index;

    //...

    in("server index",?index );
    out("server index", index+1);
    //svako procita svoj tiket

    //posalji zahtev
    out("request",index, request);

    //cekam odgovor na svom tiketu
    in("response", index, ?response);

    //...
}

void init(){
    //pocetni tiket
    out("server index", 1);
    //pokreni server
    eval(server());
    //pokreni klijente
    for(int i =0;i<10;i++){
        eval(client());
    }
}