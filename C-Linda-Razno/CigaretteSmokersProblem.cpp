using namespace std;
#include <cstdlib>
#include <iostream>

void agent(){
    int n;
    while(1){
        int n = static_cast<int>((static_cast<double>(rand()) * 3) / RAND_MAX);
        //genersi ceo broj u rasponu od 0 do 3
        switch(n){
            case 0: 
                out("Paper");
                out("Tobacco");
                break;
            case 1:
                out("Tobacco");
                out("Matches");
                break;
            case 2:
                out("Matches");
                out("Paper");
                break;
        }
        in("OK");
    }
}
//watch - moze da dovede do zaposlenog cekanja :(
void smocker_with_matches(){
    while(1){
        in("Watch");
        if(rdp("Paper") && rdp("Tobacco")){
            in("Paper");
            in("Tobacco");
            enjoy();
            out("OK");
        }
        out("Watch");
    }
}

void smocker_with_paper(){
    while(1){
        in("Watch");
        if(rdp("Matches") && rdp("Tobacco")){
            in("Matches");
            in("Tobacco");
            enjoy();
            out("OK");
        }
        out("Watch");
    }
}

void smocker_with_tobacco(){
    while(1){
        in("Watch");
        if(rdp("Paper") && rdp("Matches")){
            in("Paper");
            in("Matches");
            enjoy();
            out("OK");
        }
        out("Watch");
    }
}

void initialize(){
    //pokretanje agenta i igraca
    eval(agent());
    eval(smocker_with_matches());
    eval(smocker_with_paper());
    eval(smocker_with_tobacco());
    //za mutex -> pocetni watch
    out("Watch");
}