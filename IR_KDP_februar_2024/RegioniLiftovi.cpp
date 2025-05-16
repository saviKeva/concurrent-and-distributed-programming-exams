//uslovni kriticki regioni - putovanje liftom
using namespace std;
const int N=5;

class Floor{
    public:
    int peopleWantIn;
    int peopleWantOut;
    int id; int ticket; int nextI; int nextO;

    Floor(int num):id(num),peopleWantIn(0),peopleWantOut(0), ticket(0), next(0){};
};


class Lift{
    Floor* spratovi[] = new Floor[N]();
    int tickF; int nextFloor;

    public:
    Lift(){
        for(int i=0;i<N;i++){
            spratovi[i] = new Floor(i);
        }
    }
};

void person(){
    int myTicket = 0;
    int currentFloorIndex =rand()%N;
    int exitFloor;
    Lift lift;

    region(lift){
        Floor& cf = lift.spratovi[currentFloorIndex];
        myTicketIn = cf.ticketIn++;

        cf.peopleWantOut++;
        await(lift.nextFloor == currentFloorIndex && myTicket
        ==cF.nextIn);
        cf.peopleWantIn--;
        cf.nextIn++;
    }

    enter();

    region(lift){
        exitFloor = rand()%N;
        Floor& eF = lift.spratovi[exitFloor];
        eF.peopleWantOut++;
        myTicketOut = eF.ticketOut++;
        
        await(lift.nextFloor == exitFloor && myTicketOut = eF.nextO);

        eF.peopleWantOut--;
        eF.nextO++;
    }

    exit();



}

void lift(Lift& lift){
    int currFloorIndex = 0;
    bool goingUp = true;

    while(true){
        if(goingUp){
            region(lift){
                if(lift.nextFloor++ == N-1){
                    goingUp = false;
                }
            }
            
        }else{
            region(lift){
                if(lift.nextFloor-- == 0){
                    goingUp = true;
                }
            }
        }

        region(lift){
            Floor& floor = lift.spratovi[lift.nextFloor++];
            await(floor.peopleWantOut ==0);
            await(floor.peopleWantIn == 0);
        }
    }
}