using namespace std;
const int Num = 4;
void philosopher(int id){

    int i;
    while(1){
        think();
        in("room ticket");
        in("chopstick",i);
        in("chopstick", (i+1)%Num);

        eat();

        out("chopstick", i);
        out("chopstick", (i+1)%Num);
        out("room ticket");

    }
}


void init(int id){
    int i;
    for(i=0;i<Num;i++){
        out("chopstick", i);
        eval(phill(i)); //pokretanje procesa filozofa
        if(i<(Num-1)) out("room ticket");
    }

}