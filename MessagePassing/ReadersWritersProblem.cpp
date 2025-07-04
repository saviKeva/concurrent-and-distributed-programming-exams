/*RW Problem - koordinator ima dva sanduceta*/

const int R = ... ;
const int W = ...;
typedef struct msg{
    int senderId;
    char* operation;
}msg;

mbx reades[R];

void reader(int readerId){
    msg message;
    bool status;

    while(true){
        message.senderId = readerId;
        message.operation = "startRead";

        mbx_put(message, startCoordinator);

        mbx_get(message, readers[readerId], INF,status);

        read();

        /*ne moramo u ovom koraku da javljamo da je u pitanju proces zavrsetka citanja 
        jer ce proces koordinator znati na osnovu brojaca citalaca i pisaca ko mu je 
        javio da je zavrsio - citalac ili pisac*/

        mbx_put(message, endCoordinator);
    }
}


//svaki pisac ima svoje sanduce

mbx writers[W];

void writer(int writerId){
    msg message;
    bool status;
    while(true){
        message.senderId = writerId;
        message.operation = "start";
        mbx_put(message, startCoordinator);

        mbx_get(message, writers[readerId], INF,status);

        write();

        mbx_put(message, endCoordinator);
    }
}

/*brojac citalaca nece biti azuriran sve dok ne dodje pisac koji zeli da pise
ali to nije ni bitno, program ce raditi, samo brojaci ne oslikavaju trenutno
stanje*/

mbx startCoordinator, endCoordinator;

void coordinator(){
    msg messageStart, messageEnd;
    msg emptyMessage;
    bool status;

    int numOfReaders=0;
    int numOfWriters = 0;

    while(true){
        mbx_get(messageStart, startCoordinator, INF, status);

        if(messageStart.operation == "startRead"){
            /*ako hoce citalac da cita a neki pisac pise, citalac mora da saceka da pisac zavrsi*/
            if(numOfWriters>0){
                mbx_get(messageEnd, endCoorinator, INF, status);
                numOfWriters--;
            }

            //citalac moze da cita pa mu javljamo da pocne

            numOfReaders++;

            mbx_put(emptyMessage, readers[messageStart.senderId]);

        }else if(messageStart.operation == "startWrite"){
            /*ako pisac hoce da pise, a vec postoji neki pisac koji pise, ovaj novi mora da saceka da prosli zavrsi*/

            if(numOfWriters>0){
                mbx_get(messageEnd, endCoordinator, INF, status);
                numOfWriters--;
            }

            while(numOfWriters>0){
                mbx_get(messageEnd, endCoordinator, INF, status);
                numOfWriters--;
            }
            /*pisac moze da pocne pa mu javljamo da krene*/
            numOfWriters++;
            mbx_put(emptyMessage, writers[messageStart.senderId]);
        }
    }
}


//Resenje 2
const int R = .... ;
const int W = .... ;
/*imamo 1 proces i vise sanducica (koordinator ima 2). Necemo brojati pisca koji
pise pomocu brojaca, vec cemo odmah da ga sacekamo da zavrsi. Takodje cemo isprazniti uvek poruke o 
zavrsetku od citaoca, da bi nam brojac citalaca uvek bio azuran i pokazivao trenutno stanje*/

typdef struct msg{
    int senderId;
    char* operation;
}msg;


//svaki citalac ima svoje postansko sanduce

mbx reader[R];

void reader(int readerId){
    msg message;
    bool status;

    while(true){
        message.senderId = readerId;
        message.operation = "startRead";

        mbx_put(message, startCoordinator);
        mbx_get(message, readers[readerId], INF, status);
        read();

        
    }
}

/*svaki pisac ima svoje sanduce*/

mbx writers[W];

void writer(int writerId){
    msg message;
    bool status;
    while(true){
        message.senderId = writerId;
        message.operation = "startWrite";

        mbx_put(message, startCoordinator);
        mbx_get(message, writers[readerId]);

        write();

        mbx_put(message, endCoordinator);
    }
}


mbx startCoordinator, endCoordinator;

void coordinator(){
    msg messageStart, messageEnd;
    msg emptyMessage;

    bool status;

    int numOfReaders = 0;

    while(true){
        mbx_get(messageStart, startCoordinator, INF, status);
        if(messageStart.operation == "startRead"){
            /*citalac sigurno moze da cita jer pisca dole cekamo da zavrsi odmah nakon sto mu
            javimo da pocen, tako da ne moze da se dogodi da udjemo u ovu granu, a da pisac pise*/
            numOfReaders++;
            mbx_put(emptyMessage, readers[messageStart.senderId]);

        }else if(messageStart.operation == "startWrite"){
            while(numOfReaders>0){
                mbx_get(messageEnd, endCoordinator, INF, status);
                numOfReaders--;
            }

            mbx_put(emptyMessage, writers[messageStart.senderId]);
            mbx_get(messageEnd, endCoordinator, INF, status);
        }

        status = true;
        /*da li su neki citaoci vec zavrsili u medjuvremenu od kad amo im iznad javili
        da pocnu da citaju i onda cistimo sanduce u koje su oni poslali poruke da su gotovi kako
        bi smo u brojacu numOfReaders cuvali zaista trenutan broj citalaca*/
        while(status){
            mbx_get(messageEnd, endCoordinator,0, status);
            if(status){
                numOfReaders--;
            }

        }
    }
}

/3. nacin: *1 proces cita iz samo jednog sanduceta. Lici na aktivne monitore (imaju samo jedan ulazni kanal i 1 tok kontrole)*/

const int R  = ... ;
const int W = ... ;

typedef struct msg{
    int senderId;
    const char* operation;
}msg;

//svaki citalac ima svoje sanduce

mbx readers[R];

void Reader(int readerId){
    msg message;
    bool status;

    while(true){
        message.senderId = readerId;
        message.operation = "startRead";
        mbx_put(message, coordinator);

        read();

        message.senderId = readerId;
        message.operation = "endRead";
        mbx_put(message, coordinator);
    }
}

mbx writers[W];

void Writer(int writeId){
    msg message;
    bool status;

    while(true){
        message.senderId = readerId;
        message.operation = "startWrite";

        mbx_put(message,coordinator);

        mbx_get(message, writers[wrierID], INF, status);

        write();

        message.senderId = readerId;
        message.operation = "endWrite";

        mbx_put(message, coordinator);
    }
}

mbx coordinator;

void Coordinator(){
    msg message;
    msg emptyMessage;
    bool status;

    int numOfReaders = 0;
    int numOfWriters = 0;
    Queue<msg> buffer;

    while(true){
        if((buffer.size()>0 && (buffer.get(0).operation == "startRead" &&
    numOfWriters==0)) || (buffer.get(0).operation == "startWrite" && numOfReaders+numOfWriters == 0)){
            message = buffer.remove(0);
        }else{
            /*ako nema poruka u baferu ili ako ima ali naredni zahtev iz bafera ne moze trenutno da se izvrsi,
            cekamo da primimo novu poruku od citaoca ili pisca*/
            mbx_get(message, coordinator, INF,status);


        }

        switch(message.operation){
            case "startRead":
                if(numOfWriters>0 || buffer.size()>0){
                    buffer.insert(message);
                }else{
                    numOfReaders ++;
                    mbx_put(message, readers[message.senderId]);
                }
                break;
            case "startWrite":
                if(numOfWriters + numOfReaders>0){
                    buffer.insert(message);
                }else{
                    numOfWriters++;
                    mbx_put(message, writers[message.senderId]);
                }
                break;
            case "endRead":
                numOfReaders --;
                break;
            case "endRead":
                numOfWriters--;
                break;
        }
    }
}

