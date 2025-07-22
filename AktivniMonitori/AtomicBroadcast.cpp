const int cap = 10;
const int m = 8;
enum op_kind{PRODUCE,CONSUME};
typedef struct message{
    op_kind kind;
    int clientId;
    int pos;
    int value;

}msg;
mbx coordinator;
mbx readers[m];

bool allRead(int*RCnt){
    int temp=0;
    for(int i=0;i<cap;i++){
        if(RCnt[i]==m){
            temp++;
        }
    }
    if(temp == cap) return true;
    return false;
}
void Coordinator(){
    int wCnt;
    msg message;
    int Rcnt[cap] ={};
    int buff[cap] ={};
    int writeIndex=0;
    for(int k = 0;k<cap;k++){
        buff[k] =-1;

    }
    bool full = false;
    dequeue<msg> bufferR;
    dequeue<msg> bufferW;



    mbx_get(message,coordinator,inf,status);
    switch(message.kind){
        case CONSUME:
        if(full == true){
            if(Rcnt[message.pos]>=m){
                bufferR.push(message);
            }else{

                Rcnt[message.pos]++;
                message.value = buff[message.pos];
                mbx_put(message,readers[message.clientId]);

                if(Rcnt[message.pos]<m && !bufferR.empty()){
                    //ako ima cekajucih citalaca
                    //za ovu poziciju, sve ih pusti
                    for(int i=0;i<dequeue.size();i++){
                        if(dequeue[i].pos == message.pos && Rcnt[message.pos]){
                            mbx_put(message,readers[dequeue[i].clientId]);
                            dequeue.erase(i);
                            Rcnt[message.pos]++;
                        }
                    }
                    

                }
                
            }
        }
        if(allRead(Rcnt)){
            full ==true;
        }
        
        break;
        case PRODUCE:
        if(full == false){
            if(!bufferW.empty()){
                while(!bufferW.empty() && writeIndex<cap){
                    buff[writeIndex++] =bufferW.front().info;
                    mbx_put(bufferW.front(),writers[message.clientId]);
                    
                }
                if(!bufferR.empty() && bufferR.front().pos == writeIndex){
                    mbx_put(bufferR.front(), readers[bufferR.front().clientId]);
                    Rcnt[message.clientId]++;
                }
            }else{
                buff[writeIndex++] =message.value;
                mbx_put(message,writers[message.clientId]);
                    
            }
        }


    }

}