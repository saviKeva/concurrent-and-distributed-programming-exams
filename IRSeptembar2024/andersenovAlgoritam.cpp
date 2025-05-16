//coarse grain i fine grain andersen
//sa swap
 
using namespace std;

const int N=100;
int slot;

bool slots[N];

void worker(int id){
    while(true){
        <int mySlot = slot; slot = slot%N +1>
        <await(slots[mySlot])>
        //kr sekcija
        <slots[mySlot]=false; slots[mySlots%N + 1]=true>
        //nekriticna sekcija
    }
}

//swap(var1,var2):<temp = var1; var1 = var2; var2 = temp;>
//fine grain

const int N=100;
int slot = 0;
int flag[N]=false;

flag[0]=true;
void worker(int id){
    while(true){
        int mySlot = -1;
        swap(mySlot, (slot++)%N);

        while(flag[mySlot]==false) skip();

        //critical section

        flag[mySlot] = false;

        flag[(mySlot+1)%N] =true;

        //non critical section

    }
}