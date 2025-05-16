const int N = ...; //maks broj babuna na zici
int baboons =0;
int currentSide = 0; //0-leva strana; 1- desna strana
int waiting = -1;
int i =-1;
int j = 0;
int waitCnt=0; //cekajuci majmuni

void cross(){
    //fja za prelazenje
}

//dohvati sa pocetka ili dodaj na kraj
class FIFOQueue{

    public:
    void enqueue(int value){
        int rear;
        in("queue_rear", &rear);
        if(rear == -1){
            out("queue_front", 0);
        }
        out("queue", rear+1, value);
        out("queue_rear",rear+1);
    }

    void deque(){
        in("queue_front", &front);
        if(front>rear) return -1;
        int value;

        in("queue_front", &value);
        out("queue_front", front +1);
        return value;
    }

    int peek(){
        int value =-1;
        rdp("queue_front", &value);
        return value;
    }

};


FIFOQueue q = FIFOQueue();

void baboon(int side){
    in("baboons", &baboons);
    in("currentSide",&currentSide);
    in("waitCnt", waitCnt);
    if(baboons == 0  || (currentSide == side && baboons<N && waitCnt==0)){
        //broj onih koji cekaju sa druge strane mora da bude 0
        //dodje a1, prodje, dok je a1 na zici dosli su b1 i b2 blokirali se i uvecali waitCnt na 2
        //dodje a2, a1 nije jos prosao, baboons = 1, waitCnt =2; a2 ne prolazi jer je waitCnt==2  -->
        //a1 prodje pusti prvog sa svoje strane a to je a2
        out("baboons", baboons++);
        out("currentSide",(currentSide=side));
        out("waitCnt", waitCnt);

    }else{
        q.enqueue(side);
        
        out("baboons", baboons);
        out("currentSide", currentSide);
        out("waitCnt", waitCnt++);

        in("waiting", side);
        //cekam da se pojavi torka sa mojom stranom da bih mogla da nastavim dalje
    }

    cross();

    in("baboons", &baboons);
    out("baboons", baboons--);
    in("waitCnt", waitCnt);

    if(waitCnt>0){
        int currentSide =q.peek();

        if(currentSide == side && currentSide!=-1){
            //ako je sledeci zablokirani kretao sa iste strane
            //sada moze da krene jer je jedan prosao
            q.deque();
            //iybacujem ga iz liste cekajucih, povecavam countere
            //za broj majmuna na zici, smanjujem broj cekajucih
            //pa tek onda pustam yablokiranog koji ceka na waiting side
            out("baboons", baboons++);
            out("waitCnt", waitCnt--);
            out("waiting", side);
        }else if(baboons == 0){
            //ima zablokiranih i svi sa moje strane su presli
            //daj prednost drugoj strani
            //i pusti zablokirane da predju sa te strane
            
            out("currentSide", currentSide=!currentSide);

            int s = -1;

            while(true){
                int s = q.peek();
                if(s==(!side) && baboons<N){
                    q.deque();
                    out("waitCnt", waitCnt--);
                    out(baboons++);
                    out("waiting", !side);
                }

            }
    
        }
    }
}