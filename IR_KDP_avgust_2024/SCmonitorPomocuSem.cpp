//probudjene niti imaju prednost nad pridoslim nitima
//SC
 
//5 karakteristicnih situacija:
/*
1) ulazak u monitor
2) cekanje na uslovnoj promenljivoj
3) budjenje jednog procesa na uslovnoj promenljivoj
4) budjenje svih procesa na uslovnoj promenljivoj
5) izlazak iz monitora
*/


class SignalAndContinueMonitor{
    int condQueueSize = 0;

    Semaphore entryQueue = Semaphore(1);
    Semaphore condQueue = Semaphore(0);

    void monitorMethod(){
        //(1) ulazak u monitor

        entryQueue.wait();

        //(2) cekanje na uslovnoj promenljivoj

        condQueueSize++;
        entryQueue.signal();
        condQueue.wait();
        entryQueue.wait();

        //(3) budjenje jednog procesa na uslovnoj promenljivoj
        if(condQueueSize>0){
            condQueueSize--;
            condQueue.signal();
        }

        //(4) budjenje svih procesa na uslovnoj promenljivoj
        if(condQueueSize>0){
            for(int i=0;i<condQueueSize;i++){
                condQueue.signal();
            }
            condQueueSize = 0;
        }

        // (5) izlazak iz monitora
        entryQueue.signal();
    }
    
};

