#include <iostream>
#include <limits.h>
using namespace std;

const int n;
typedef struct Result{
    int min;
    int max;
}Result;

/*koristimo asinhronu komunikaciju
Ukupan broj poslatih poruka: 2*(n-1) */

chan<int> values;
chan<int> results[n-1];

//kod za proces u centru
void ProcessCoordinator(){
    int newValue, currentMin, currentMax;

    Result result;

    for(int i=0;i<N-1;i++){
        if(i==0){
            currentMin=currentMax=newValue;

        }else{
            if(newValue<currentMin){
                currentMin = newValue;
            }
            if(newValue>currentMax){
                currentMax = newValue;
            }
        }
    }
    result.min = currentMin;
    result.max = currentMax;

    //slanje min i max vrednosti svim procesima
    //ostalim


    //slanje min i max vrednosti
    //svim ostalim pocesima
    for(int i =0;i<n-1;i++){
        results[i].send(result);
    }
}