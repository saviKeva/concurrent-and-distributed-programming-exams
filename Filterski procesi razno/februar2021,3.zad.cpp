//opadajuce sortira vrednosti
#include <iostream>
#include <limits.h>
using namespace std;

void process(){
    chan<int> in;
    chan<int> out;
    int input;
    int min = INT_MIN;

    while((input = in.receive())!=EOS){
        if(input<min){
            out.send(min);
            min = input;
        }else{
            out.send(input);
        }
    }
    out.send(min);
    out.send(EOS);
}