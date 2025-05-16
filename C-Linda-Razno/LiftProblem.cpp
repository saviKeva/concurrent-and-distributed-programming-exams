using namespace std;
const int N=6;
void elevator(){
    int x;
    while(1){
        x = getFloor();

        //lift stigao na sprat x i spreman za izlaz
        //putnika
        out("off",x);
        //cekam da svi izadju iz lifta ->0

        in("stop",x,0);
        in("off",x);
        //cekam da lift  dodje na sprat i otvori se
        //svi iyasli -. out
        out("stop",x,0);


        out("on",x);
        //lift spreman za ulazak putnika
        in("start",x,0);
        in("on",x);
        //cekam da svi udju

        //svi sy ysli
        out("start",x,0);
    }
}

int getFloor(){
    int floorNumber;
    IN("floorNumber", &floorNumber);
    return floorNumber;
}



void passenger(unsigned ID,unsigned x,unsigned y){
    //x-sprat na kom sam
    //y - sprat na koji idem
    int s1, int s2;
    //s1 je brojac putnika koji su usli u lift
    if(x!=y){
        //putnik ceka da lift bude spreman ya ulazak na
        //spratu
        in("start", x, ?s1);
        //s1 trenutni broj putnika koji cekaju
        if(s1 == 0) out("floor", x);
        //ako sam prvi dosao na sprat
        //signal liftu da dodje na floor
        //poziv lifta
        out("start",x,s1+1);
        //putnik signaliyira da je usao u lift 
        //i povecava broj putnika u liftu

        in("on",x);
        //cekam da lift javi da su svi usli
        in("start", x, ?s1);
        //koliko ih je uslo
        in("stop", y, ?s2);
        //cekam da lift dodje na moj sprat
        //i preuzimam trenutni broj putnika
        //koji zele da izadju
        if(s2 == 0) out("floor", y);
        inp("floor", x);

        out("stop", y, s2+1);
        out("start", x, s1-1);
        out("on", x);
        in("off", y);
        in("stop", y, ?s2);
        inp("floor", y);
        out("stop", y, s2-1);
        out("off", y);
    }
}

void init(){
    int floorNum = N;
    int i;
    for(i=0; i < floorNum; i++){
    out("start", i, 0);
    out("stop", i, 0);
    }
    eval( elevator());
}