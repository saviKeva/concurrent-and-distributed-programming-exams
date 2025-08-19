#include <iostream>
#include <limits.h>
using namespace std;

const int N=...;
enum op_kind{REQUEST,RELEASE};

typedef struct Philosopher{
    int clientid;
    op_kind kind;
    bool viljuska;
    //1 - leva, 0 - desna
    Philosopher(int cId,op_kind ok, bool fork){
        clientid = cId;
        kind = ok;
        viljuska = fork;
    }
};
chan<Philosopher> request;
chan<bool> reply[N];
class Coordinator{
    public:
    void run(){
        Philosopher p;
        int forks[N]={};
        
        queue<pair<int,int>> waiting;
        // 0 - slobodna viljuska
        //1 - zauzeta viljuska

        while(true){
            p = request.receive();
            int fork = p.viljuska? p.clientid:(p.clientid+1);
            if(p.kind == REQUEST){
                if(forks[fork] == 0){
                    forks[fork] = 1;
                    reply[p.clientid].send(true);
                }else{
                    waiting.push(make_pair(p.clientid,fork));
                }
            
            }else if(p.kind == RELEASE){
                forks[fork] = 0;
                while(!waiting.empty() && forks[waiting.front().second]==0){
                    reply[waiting.front().first](true);
                    waiting.pop();
                }
            }
        }
    }
};


void philosopher(int id){
    bool status;
    while(true){
        //svi filozofi osim nultog traze
        //levu pa desnu
        Philosopher pr =  Philosopher(id, REQUEST, id!=0);
        
        request.send(pr);
        status =  reply[id].receeive();
        pr.viljuska=(id==0);
        request.send(pr);
        status =  reply[id].receeive();

        //eat
        pr.viljuska=(id!=0);
        request.send(pr);
        pr.viljuska=(id==0);
        request.send(pr);
       
        
    }
}