using namespace std;

//igra se zavrsava kada bar jedan igrac objavi da ima
//sve 4 karte istog broja u raylicitim bojama
//jednu kartu stavi levo, drugu uzme iz spila desno

[Player(i:0...3)::PLAYER, Spil(i=0...3)::SPIL, Check(i:0...3)::CHECK, Room::ROOM]

//najvise 3 igraca mogu u 1 trenutku uzimati iz spilova
//da ne dodje do deadlocka

//SEMAFOR za izbegavanje deadlock-a
ROOM::
[

    int semaphoreValue = 3;
    *[
        semaphoreValue>0, Players(i)?waitingToMakeNextMove()->[
            semaphoreValue--;
        ]
        []
        Player(i)?bothSpilFinished()->[
            semaphoreValue++;
        ]
    ]
];

PLAYER::[
    cards(0...3):integer; //svaki igrac 4 karte na kraju
    card1(0...1):integer;
    card2(0..1):integer;

    int leftSpil = i;
    int rightSpil = (i+1)%4;

    int END = false;

    *[

        END == false ->[
            Room!wantingToMakeNextMove();
            /*card1[0] =...;//indeks 0 je boja
            card1[1] = ....; //indeks 1 je broj

            */
           //uzimam jednu iy svog spila
            card1 = cards(0);
            Spil(leftSpil)!putCard(card1);
            Spil(rigntSpil)!takeCard();
            Spil(rightSpil)?okToTakeCard(card2);

            //stavi kartu u spil
            cards(0)=card2;

            Spil(rightSpil)!OK;
            Spil(leftSpil)!OK;

            Room!bothSpilFinished;

            end:boolean;

            end = false;

            falseCnt:int;falseCnt =0;

            *[
                end==false->[
                    (j:o...3)Check(cards)?true->{
                        //da li imamo pobednika
                        end = true;
                        END = true;
                    }
                    (j:0..3)Check(cards)?false->[
                        falseCnt++;
                        falseCnt>=4 ->end = true;
                    //ako sva 4
                    //igraca potvrde da nemam pobednika
                    //iylayim iz *[end == false] petlje
                    //jer zelim da opet izvlacim i spustam
                    //karte
                    ]
                    
                ]

                END = true->[
                    //posalji svim igracima
                    //poruku da je igra gotova
                    Spil ! END;
                    END =false;
                ]
            ]
        ]

    ]


    SPIL::{
        card:int;
        leftPlayer:int;
        rightPlayer:int;
        leftPlayer = (i-1)%4;
        rightPlayer = i;

        cards(0...3)(0..1):integer;

        end:bool;
        end = false;

        *[
            end = false->[
                Player(rightPlayer)?putCard(card)->[
                    cards(0)=card;
                    //stavljam u levi spil card1;
                    Player(rightPlayer)?OK;
                ]
                []
                Player(leftPlayer)?takeCard->[
                    //uzimam kartu iz desnog spila
                    Player(leftPlayer)!okToTakeCard(card(0));
                    Player(leftPlayer)?OK;
                    //karta uspesno uzeta
                ]
                []
                (i=0...3)Player(i)?END->[
                    end = true;
                ]
            ]
        ]
    }
]

CHECK::[
    cards(0...3)(0...1);
    //svaki igrac ima 4 karte, 1 karta je niz od
    //dva elementa 
    //ovaj cards je niz od 2 elementa
    send:boolean;
    send = false;

    Player(i)?check(cards)->[
        //sve boje su raylicite
        (cards(0)(0)!=cards(1)(0) != cards(2)(0) != cards(3)(0)) &&
        //svi brojevi su isti
        (cards(0)(1)==cards(1)(1)==cards(2)(1)==cards(3)(1))->[
            send = true;
            int i =0;
            //petlja da svim igracima posaljem true;
            //ali onda bi ovo
            *[
                i<4->[
                    Player(i)!true;
                    i++;
                    //ali onda ovo falseCnt treba nekako
                    //da bude globalna promenljiva
                    //ne znam jel postoji to u CSP u
                ]
               
            ]
             send = false;
        ]
       
        []

        send ==false->[
            i<4->[
                Player(i)!false;
                i++;
                //ali onda ovo falseCnt treba nekako
                //da bude globalna promenljiva
                //ne znam jel postoji to u CSP u
            ]
        ]
    ]

]