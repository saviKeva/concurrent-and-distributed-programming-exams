//neopadajuce -> saljes prvo manji
//rastuce sortira i izbacuje duplikate

chan<int> in1;
chan<int> in2;
chan<int> out;

void merge(){
    int val1,val2;

    val1 = in1.receive();
    val2 = in2.receive();

    /*Kad god treba da izbacis ceo niz a imas mrezu sa dva ulazna kanala imas 
    while petlju*/

    /*Kad treba da izbacis npr. jednu mininalnu vrednost i mrezu sa dva ulazna kanala
    ne treba ti while petlja*/
    /*sa kog si kanala posalo sa tog primas*/
    while(val1!=EOS && val2!=EOS){
        if(val1<val2){
            out.send(val1);
            v1 = in1.receive();

        }
        else if(v1<v2){
            out.send(v2);
            v2 = in2.receive();
        }else if(v1==v2){
            //izbaci duplikate
            //primi sa oba kanala
            out.send(v1);
            v1 = in1.receive();
            v2 = in2.receive();
        }

        while(v1!=EOS){
            out.send(v1);
        }

        while(v2!=EOS){
            out.send(v2);
        }

        out.send(EOS);
    }


}