const int N = 100;
const int K = 20;

mbx passengers[N];
mbx rollerCoasteStart, rollerCoasterEnd;

typdef struct msg{
    int senderId;
}msg;


void passenger(int passengerId){
    msg message;
    bool status;

    while(true){

        //setamo po luna parku
        walkAround();

        //javljamo roler kosteru da zelimo da se vozimo

        message.senderId = passengerId;

        mbx_put(message, rollerCoasterStart);

        mbx_get(message, passengers[passengerId], INF, status); //cekam dok ne dobijem poruku od roler kostera da mogu da 

        passengerRide();

        mbx_get(message, passengers[passengerId], INF, status);

        mbx_put(message, rollerCoasterEnd);





    }
}


void rollerCoaster(){
    int ridingPassengers[K];
    /*pamti koji putnici su na trenutnoj voznji*/

    msg message;

    bool status;

    while(true){
        for(int i=0; i<K; i++){
            mbx_get(message, rollerCoasterStart, INF, status);

            ridingPassengers[i] = message.senderId;


        }

        for(int i=0;i<K;i++){
            /*javljam svim putnicma da mogu da krenu sa voznjom*/
            mbx_put(ridingPassengers[i],passengers[ridingPassengers[i]]);

        }

        for(int i=0;i<K;i++){
            mbx_get(message, rollerCoasterEnd, INF,status);
        }
    }
}


/*jedno sanduce na roler coaster u*/

const int N= ...;
const int K= ...;

mbx passengers[N];
mbx rollerCoaster;

typedef struct msg{
    int senderId;
    char* operation;

}msg;


void passenger(int passengerId){
    msg message;
    bool status;
    while(true){
        //setamo okolo po luna parku
        walkAround();
        message.senderId = passengerId;

        message.operation = "start";

        mbx_put(message, rollerCoaster);

        /*cekam odgovor od roler kostera*/

        mbx_get(message, passengers[passengerId], INF, status);

        /*roler koster treba da javi da je voznja gotova*/

        mbx_get(message, passengers[passengerId],INF,status);

        message.senderId = passengerId;

        message.operation = "end";

        mbx_put(message,rollerCoaster);

    }
}

void rollerCoaster(){
    int ridingPassengers[K];
    Queue<msg> buffer;
    msg message;
    bool status;
    while(true){
        for(int i=0;i<K;i++){
            if(buffer.empty()){
                mbx_get(message, rollerCoaster, INF, status);
            }else{
                message = buffer.delete();
            }

            ridingPassengers[i] = message.senderId;
        }

    }
    /*javi putnicima da mogu da pocnu voznju na roler kosteru*/

    for(int i=0;i<K;i++){
        mbx_put(ridingPassengers[i], passengers[ridingPassengers[i]]);

    }

    rollerCoasterRide();

    for(int i = 0;i<K;i++){
        mbx_get(message, rollerCoaster, INF,status);
        if(message.operation == "end"){
            i++;
        }else{
            buffer.insert(message);
        }
    }
}