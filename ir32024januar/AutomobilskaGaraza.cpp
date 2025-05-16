//bey iygladnjivanja
using namespace std;
#include <string>
#include <list>
#include <condition_variable>
#include <semaphore>
#include <thread>

const int N=500;
const int K=...;

std::array<std::counting_semaphore, 2*N+1> sems;

int capacity = N;
int entering =0;int exiting = 0; int enterTail = 0;int enterHead = 0; int exitTail = 0;int exitHead = 0;
bool priority = true;
//true -> izlaz; false-ulaz ; oni koji izlaze imaju prioritet

int passed = 0;

sem& mutex = sems[2*N]; //poslednji semafor je mutex

void initSems(){
    for(auto & sem:sems){
        sem = counting_semaphore(0);
    }
}

bool requestEntrance(){
    mutex.wait();
    if(capacity - entering<=0){
        //nema mesta idi na drugi parking
        mutex.signal();
        return false;
    }

    ++entering; //oni koji zele da udju

    if(entering == 1 && exiting ==0 ){
        //slobodan prolaz
        mutex.signal();
        return true;
    }
    int semIndex = enterTail;
    enterTail = (enterTail+1)%N;
    mutex.signal();
    sems[semIndex].wait();

    return true;
}

void signal(){
    int semIndex =-1;
    bool hasCapacity = (capacity - exiting)<N;
    bool signalEnter = (entering>0 && hasCapacity) && (!priority || exiting ==0);
    bool signalExit = (exiting>0) && (priority || !hasCapacity) ||( entering ==0);

    if(signalExit){
        //2. polovina niza su sve semafori za izlaz, sem poslednjeg mutex-a, zato nije N+1
        semIndex = exitHead + N;
        exitHead = (exitHead+1)%N;

    }else if(signalEnter){
        //1. polovina niza su semafori za ulaz
        semIndex = enterHead;
        enterHead = (enterHead+1)%N;
    }
    if(semIndex>=0){

        if(priority!=signalExit){
            //promenio se prioritet
            //resetuje se brojac uyastopnih automobila koji ulaye/izlaye
            passed = 0;
        }else{
            ++passed;
        }
        if(passed == K){
            passed = 0;
            priority = !priority;
        }

        //passed i priority da se spreci iygladnjivanje
        sems[semIndex].signal();
    }

}

void requestExit(){
    mutex.wait();
    ++capacity;
    ++exiting;
    if(entering ==0 && exiting == 1){
        mutex.signal();
        return;
    }
    int semIndex = exitTail + N;
    //semafori za izlaz su u drugoj polovini niza
    exitTail = (exitTail+1)%N;
    mutex.signal();
    sems[semIndex].wait();
}