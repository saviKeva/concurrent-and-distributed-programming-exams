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

queue<Vehicle> vehicles;
cond waitingPassengers;
cond waitingVehicles;
int numPassW;
int nextP;int nextV;
void vozilo(int id){
    while(true){
        int myTicket = nextV++;
        if(numPassW == 0 && !vehicles.empty()){
            waitingVehicles.wait(myTicket);
        }
        waitingPassengers.signal();

        if(!waitingPassenger.empty()){
            waitingPassenger.signal();
        }
    }
    

}

void posetilac(int id){
    Vehicle vc;
    int myTicket =next++;
    //walk
    if(vehiqles.empty() || !waitingPassenger.empty()){
        waitingPassengers.wait(myTicket);
    }
    waitingVehicles.signal();
    
    //drive

}

//doraditi ovo