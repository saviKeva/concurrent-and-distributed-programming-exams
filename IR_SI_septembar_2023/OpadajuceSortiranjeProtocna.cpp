chan<int> in;
chan<int> out;

//2,11,1,7

void process(){
    int input;
    int min = MAX_INT;

    while((input=in.receive())!=EOS){
        if(input<min){
            out.send(min);
            min = input;
        }else{
            out.send(input);
        }
        out.send(min);
        out.send(EOS);

    }

    out.send(min);
    out.send(EOS);

}

/*
Dodje 2 -> 2 je manje od MAX INT -> prosledi MAX_INT -> min = 2
Dodje 11 -> 11 !< 2 -> posalji 11, min i dalje 2
Dodje 7 -> 7 !< 2 -> posalji 7, min i dalje 2
Dodje 1 -> 1<2 ->posalji 2, min je sada 1
Na kraju posalji 
*/