//proces koji je pre uputio zahtev za pristup resursu
//pre treba da bude opsluzen
using namespace std;
#include <queue>
enum op_kind{START_READ, END_READ, START_WRITE, END_WRITE};
channel request(int clientID, op_kind operationKind);
channel reply[N](dummyType);


void ServerRW(){
    int clientId;
    op_kind kind;
    int rCnt=0;
    int wCnt=0;

    std::queue<int,op_kind> blockedQueue;

    while(true){
        receive request(clientId, kind);

        switch(kind){
            case START_READ:
                if((wCnt!=0)|| !blockedQueue.empty()){
                    blockedQueue.push(make_pair(clientId, START_READ));

                }else{
                    send reply[clientId](kind);
                    rCnt++;
                }
            case END_READ:
                rCnt--;
                if(rCnt ==0 && blockedQueue.size()>0){
                    //nema vise onih koji citaju ali ima
                    //blokiranih pisaca 
                    //sledeci nikako
                    //ne moze biti citalac
                    blockedQueue.pop();
                    //ovde pop uzima sa pocetka reda
                    wCnt++
                    //pusti pisca
                    send reply[clientId](kind);


                }

            case START_WRITE:
                if(rCnt>0 || wCnt>0 || blockedQueue.size()>0){
                    blockedQueue.push(make_pair(clientId,kind));


                }else{
                    wCnt++;
                    send reply[clientId](kind);

                }
            case END_WRITE:
                wCnt--;

                if(blockedQueue.size()>0){
                    if(blockedQueue.front().second() == START_READ){
                        //dokle god su u redu blokiranih sve sami citaoci
                        //pustaj ih sve, kad naidjes na prvog pisca
                        //izadji iz petlje
                        while(blockedQueue.front().second()
                    =="START READ"){
                            int cId = blockedQueue.front().first();
                            op_kind kind = blockedQueue.front().second();

                            blockedQueue.pop();
                            //ukloni iz reda cekajucih
                            send reply[cId](kind);
                            rdCnt++;

                        }
                    }else if(blockedQueue.front().second()==START_WRITE){
                        int cId = blockedQueue.front().first();

                        op_kind kind = blockedQueue.front().second();

                        blockedQueue.pop();
                        //ukloni pisca iy reda za cekanje
                        wCnt++;

                        send reply[cId](kind);

                    }
                }

        }
    }

    
}


void Client(int clientId, op_kind operacija){
    op_kind result;
    send request(clientId, op_kind);
    receive reply[clientId](result);
}
