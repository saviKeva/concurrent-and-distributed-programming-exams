using namespace std;
void client(int id){
    int index;

    in("client index", ?index);
    out("client index", index + 1);

    out("request",index,request);
    in("response", index, ?response);
}

void server(){
    int i=1, cnt =0, x;

    in("number of servers", ?x);
    //dohvati broj trenutno aktivnih servera
    out("number of servers", x+1);
    //uracunaj i mene kao aktivnog od ovog trena

    while(1){
        if(rdp("summing")){
            out("number of processed", cnt);
            rd("not summing");
            //blokiraj se dok ne procitas
            //da je sumiranje gotovo
        }else{
            in("server index", ?i);
            out("server index", ++i);
            //dohvati moj tiket servera
            in("request",i,?x);
            //cekam na dodeljenom procesu- tiketu (i) poruku
            out("response", i , f(x));
            //saljem odgovor istom procesu
            cnt++;
            //zahtev obradjen

        }
    }
}

void sumator(){
    int n, ukupno, j;

    in("not summing");
    out("summing");
    rd("number of servers", ?n);

    cnt = 0;

    for(int i=0;i<n;i++){
        in("number of processed", ?j);
        cnt += j;
    }

    in("summing");
    out("not summing");
}

void init(){
    out("number of servers", 0);
    out("client index", 0);
    out("server index",0);
    out("not summing");
    for(int i=0;i<10;i++)
        eval(server());
}