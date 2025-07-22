#include <iostream>
#include <limits.h>
using namespace std;
enum op_kind{WAIT, SIGNAL, WAITN, SIGNALN};
const int n =10;
typedef struct ProcessInfo{
    int clientId;
    op_kind opKind;
    int tockens;
};

chan<ProcessInfo> request;
chan<bool> reply[n];

class Semaphore{
    public:
    void run(){
        ProcessInfo pr;
        int n;
        op_kind kind;
        int clientID;
        int tockens = 0;
        queue<pair<int,int>> blockingQ;

        while(true){
            pr = request.receive();
            if(pr.opKind == WAIT){
                if(tockens<=0){
                    blockingQ.push(make_pair(clientId,1));
                }else{
                    tockens--;
                    reply[pr.clientID].send(true);
                }
            }else if(kind == WAITN){
                if(tockens<=pr.tockens-1){
                    blockingQ.push(make_pair(clientID,pr.tockens));
                }else{
                    tockens = tockens-pr.tockens;
                    reply[pr.clientId].send(true);
                }
            }else if(kind == SIGNAL){
                tockens++;
                if(!blockingQ.empty() && blockingQ().front().second == tockens){
                    tockens =0;
                    reply[blockingQ.front().first].send(true);
                    blockingQ.pop();

                }
            }else if(kind == SIGNALN){
                tockens+=n;
                while(!blockingQ.empty() && blockingQ.front().second<=tockens){
                    tockens -= blockingQ.front().second;
                    reply[blockingQ.front().first](true);
                    blockingQ.pop();
                }
            }
        }
    }
}






