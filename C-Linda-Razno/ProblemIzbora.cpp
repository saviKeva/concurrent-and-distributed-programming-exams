using namespace std;
#include <cstdlib>
#include <iostream>

void Player(int id){
    int PID;
    int coin, coinl, coinr;
    int end, winner;

    in("PID", ?PID);

    do{
        PID++;
        //PID mi govori koja je runda u pitanju
        coin = (int)(rand()*2)/RAND_MAX;
        //2 puta iybacujem svoj novcic
        //u prostor torki
        //da bi druga dva igraca mogla da ga dohvate
        out("RESULT", id, PID, coin);
        out("RESULT", id, PID, coin);
        //dohvati sta su druga dva igraca dobila
        in("RESULT", (id+1)%3,PID,?coinr);
        in("RESULT", (id+2)%3, PID, ?coinl);

        end = !((coin == coinl) && (coin == coinr) && (coinl == coinr));
        winner = (coin!=coinl) &&(coin!=coinr);

    }while(!end);
}

void init(){
    out("PID",0);
    out("PID",0);
    out("PID",0);
    eval(Player(0));
    eval(Player(1));
    eval(Player(2));
}