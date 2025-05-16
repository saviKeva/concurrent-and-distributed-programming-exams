//test and set coarse and fine grain

//COARSE GRAIN
bool TS(bool lock){
    //uzima staru bool vrednost i vraca je, ujedno nedeljivo postavlja vrednost na true
    <bool initial = lock; lock = true; return initial;>
}

//FINE GRAIN - test and test and set 

bool lock = false; //inicijalno false da moze jedan proces da udje, yajednicka promenljiva za sve procese

void TS(){
    bool initialLock = true;//lokalna za svaki proces

    while(true){

        while(lock == true) skip;
        swap(lock, initialLock); 
        //kad udje prvi proces u lock upise true, a u initiallock false,
        //pre nego sto prvi proces zavrsi i postavi lock na false
        //dodju drugi i treci i vide da je lock true i tu se vrte, prvi u medjuvremenu postavi lock na false, drugi proces zameni lock
        //i initialLock i sada je u initial lock false a u lock true
        //treci proces dodje, i on ima u initialLock true, a i u lock = true, pa ce onda drugi proces proci, a 
        //treci ce se vrteti u ovoj petlji
        while(initialLock == true){
            while(lock == true){
                skip;
            }

        }
        lock = false;
    }
}

