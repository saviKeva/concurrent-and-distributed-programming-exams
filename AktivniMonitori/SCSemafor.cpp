#include <iostream>
#include <limits.h>
using namespace std;

enum op_kind{WAIT, SIGNAL, WAITN, SIGNALN};
const int n =10;
typedef struct ProcessInfo{
    int clientId;
    op_kind opKind;
};

const int N = 10;
chan<ProcessInfo> request;
chan<bool> reply[N];


void ServerFIFOSemaphore(){
    int s = 0;

    ProcessInfo pr;
    queue blockedQueue;
    queue entryQueue;
    
    while(true){
        if(entryQueue.size()>0){
            reply[entryQueue.remove(0)].send(true);
            continue;
        }else{
            pr = request.receive();
        }

        switch(pr.opKind){
            case WAIT:
            if(s==0){
                blockedQueue.put(pr.clientId);

            }else{
                s--;
                reply[pr.clientId].send(true);
            }
            break;
            case SIGNAL:
            if(blockedQueue.size()==0){
                s++;
            }else{
                entryQueue.put(blockedQueue.remove(0));
            }
            break;
        }
    }
}