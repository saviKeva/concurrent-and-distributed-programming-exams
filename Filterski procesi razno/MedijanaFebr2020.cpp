/*
Ideja: svaki proces ima tri promenljive
U dve cuva lokalni min i max
U jednoj input.
Trazis medijanu na nivou svakog procesa, srednju od tri vrednosti prosledis daje
*/

// ovo nisu globalne promenljive
chan<int> in;
chan<int> out;
void process()
{
    int input;
    int mem[2]={MAX_INT};

    //SHIFT + ALT + F ---> da lepo formatiras kod
    while ((input = in.receive()) != EOS)
    {
        if(mem[0]>=mem[1]){
            int temp = mem[0];
            mem[0] = mem[1];
            mem[1] = temp;
        }
        if(mem[0]<=input && input<=mem[1]){
            out.send(input);
        }else if(input<mem[0]){
            out.send(mem[0]);
            mem[0] = input;
        }else if(input>mem[1]){
            out.send(mem[1]);
            mem[1] = input;
        }
    }

    
    if(mem[0] == -1){
        input = in.receive();
        out.send(input);
    }

    out.send(EOS);
}
