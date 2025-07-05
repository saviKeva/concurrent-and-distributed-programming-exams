using namespace std;
#import <string>;

const int N=10; 
//sw disciplina - posetioci i vozila
//vozilo moze da primi jednog putnika
class Passenger{
    int id;
    string ime;
    
}
class Vehicle{
    int id;
    bool busy;
};


cond waitingPassengers;
cond[5] waitingVehiclesE;
cond[5] waitingVehiclesOut;
int numPassW;
int ticketP;int ticketV;
int nextP, int nextV;
int numPE=0;
void vozilo(int id){
    while(true){
        
        if(numPassW == 0 && !vehicles.empty()){
            waitingVehiclesE[id].wait();
        }
        waitingPassengers.signal();

        while(numPE!=N){
            waitingPassengersOut[id].wait();
        }

        numPE =0;
        numPassW=0;
        i++;

        
    }
    

}
int i=0;
void posetilac(int id){
    Vehicle vc;
    int myTicket =ticket++;
    //walk
    numPassW++;
    while(myTicket!=nextP){
        
        if(numPassW == 1){
            waitingVehicles[i].signal();
        }
        waitingPassengers.wait(myTicket);
    }
    numPassW--;
    nextP++;
    numPE++;
    if(numPE<N && waitingVehiqles.empty() || !waitingPassenger.empty()){
        waitingPassengers.signal();
    }else{
        waitingPassengersOut[i].signal();
        /*numPE =0;
        numPassW=0;
        i++;*/
        
    }
    
    
    //drive

    
    

}

//doraditi ovo