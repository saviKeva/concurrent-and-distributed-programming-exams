#include <iostream>
#include <limits.h>
using namespace std;

chan<int> inputChannel1;
chan<int> inputChannel2;
chan<int> outputChannel;

void process(){
    int value1,int value2;
    value1 = inputChannel1.receive();
    value2 = inputChannel2.receive();

    if(value1 == EOS){
        outputChannel.send(value2);

    }else if(value2 == EOS){
        outputChannel.send(value1);
    }else{
        if(value1<value2){
            outputChannel.send(value1);
        }else{
            outputChannel.send(value2);
        }
    }
}

