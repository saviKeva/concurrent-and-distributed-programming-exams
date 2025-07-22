#include <iostream>
#include <limits.h>
using namespace std;

//saljemo svoju vrednost svim
//ostalim procesima sem sebi

/*primamo vrdnost od svih ostalih procesa
i racunamo lokalno min i max*/

chan<int> values[n];

void Process(int id){
    int value = ...;
    int newValue;
    int currentMax;
    int currentMin = currentMax = value;

    //saljem svoju vrednost svima

    for(int i=0;i<n;i++){
        if(i!=id){
            values[i].send(value);
        }
    }

    //primi od svih i racunamo lokalno min i max
    for(int i=0;i<n;i++){
        if(i!=id){
            values[i].receive(newValue);

            if(newValue<currentMin){
                currentMin = newValue;
            }

            if(newValue>currentMax){
                currentMax = newValue;
            }
        }
    }
}