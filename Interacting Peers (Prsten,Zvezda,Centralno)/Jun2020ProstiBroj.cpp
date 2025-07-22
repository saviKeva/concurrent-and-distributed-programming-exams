#include <iostream>
#include <limits.h>
using namespace std;

const int N = ...;
const int m = ...;
const int EONAT = 20001;
chan values[N](int);

void process0()
{
    int array[m];
    for (int i = 0; i < m; i++)
    {
        array[i] = rand(1, 20000);
    }
    //alt shift f da formatiras kod
    for (int i = 0; i < m; i++)
    {
        //Po salje P1 niz
        values[1].send(array[i]);

    }
    values[1].send(EONAT); //posalji P1 oznaku za kraj niza

    bool end = false;

    int temp, index = 0;

    while(!end){
       temp =  values[0].receive();
       if(temp == EONAT) end = true;
       else array[index++] = temp;
       //primis niz bez svih
       //prostih brojeva
    }

     //novi krug: posaljes taj niz ka P1

    for(int i =0;i<index;i++){
        values[1].send(values[i]);
    }
    values[1].send(EONAT);

}

/*svaki proces ima prost broj za koji je zaduzen*/

void process(int id, int myNumber){
    int array[m];
    bool end = false;
    int temp;
    
    while(!end){
        temp = values[id].receive();
        if(temp == EONAT) end = true;
        else if (temp!=myNumber){
            values[(id+1)%N].send(temp);
        }
        //ako je temp = myNumber
        //samo ga necu proslediti
    }

    end = false;
    int index = 0;
    while(!end){
        temp = values[id].receive();
        if(temp == EONAT){
            end = true;
        }
        else{
            array[index++] = temp;
            if(id!=N-1) values[(id+1)%N].send(temp);
        }
    }


}
