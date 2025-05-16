using namespace std;
#include <string>
#include <queue>
#include <map>

enum op_kind{STANDARD, LUXURY,ANY, RETURN };

class Request{
    public:
    int customerId;
    unsigned place;

    Request(int id, unsigned tiket):customerId(id),place(tiket){};

};
class Agency{
    public:
    queue<Request*> standardRequests;
    queue<Request*> luxuryRequests;
    queue<Request*> anyRequests;

    queue<Request*> returnRequest;

    map<int,int> rentedCars;
    int place =1;
    //FORICA: place nam sluzi kao tiket

};

Agency ag;
queue<int> standardCars;
queue<int> luxuryCars;

int rentCar(int CustomerId, op_kind which){
    region(ag){
        unsigned myPlace = ag.place ++;
        switch(which){
            case STANDARD:
                ag.standardRequests.push(new Request(CustomerId,myPlace));
                break;
            case LUXURY:
                ag.luxuryRequests.push(new Request(customerId, myPlace));
                break;
            case ANY:
                ag.anyRequests.push(new Request(CustomerId, myPlace));
                break;

        }
        //cekaj dok se u mapi za datog korisnika
        //ne pojavi nesto sto nije nula
        await(ag.rentedCars[customerId]);
    }
}

void returnCar(int customerId){
    region(ag){
        //moze da se desi da je dosao posle
        //nekog ko tek iznajmljuje auto
        unsigned myPlace = ag.place++;

        ag.returnRequests.push(new Request(CustomerId,myPlace));
        await(!ag.rentedCars[customerId]);
        //mora da saceka da vise nije u redu onih koji su trenutno rentirani
        //tj da kupac vrati auto
    }
}

void employee(){
    while(true){
        Request req;
        int request = 0;
        region(ag){
            //ako postoje zahtevi u redovima, radnik treba da se 
            //budi i da nesto radi
            await(ag.standardRequests.size() + ag.luxuryRequests.size()
             + ag.anyRequests.size() + ag.returnRequests.size()>0);
            
             //-1 je max vrednost jer je unsigned!!!
             //FORICA
             unsigned minPlace = -1;

            if(!ag.standardRequests.empty() && !standardCars.empty()
                && ag.standardRequest.front().place<minPlace){
                minPlace = ag.standardRequest.front().place;
                request = STANDARD;
        
            }
            if(!ag.luxuryRequests.empty() && !luxuryCars.empty()
                && ag.luxuryRequests.front().place<minPlace){
                minPlace = ag.luxuryRequests.front().place;
                request = LUXURY;
        
            }

            //ovde analogno dodati za return vehicles i any vehicles


            switch(request){
                case STANDARD:
                    req = ag.standardRequests.front();
                    ag.standardRequests.pop();
                    break;
                case LUXURY:
                    req = ag.luxuryRequests.front();
                    ag.luxuryRequests.pop();
                //analogno dodati za anyVehicle
                //analohno dodati ya ReturnVehicle

            }



        }

        region(ag){
            switch(request){
                case STANDARD:{
                    ag.rentedCars[req.customerId] = standardCars.front();
                    standardCars.pop();
                    break;
                }
                case LUXURY:{
                    ag.rentedCars[req.customerId] = luxuryCars.front();
                    luxuryCars.pop();
                    break;
                }
                case ANY:{
                    if(standardCars.empty() && luxuryCars.empty()){
                        await(!standardCars.empty() || !luxuryCars.empty());
                    }
                    if(standardCars.empty()){
                        ag.rentedCars[reg.customerId] = luxuryCars.front();
                        luxuryCars.pop();
                    }else{
                        ag.rentedCars[req.customerId] = standardCars.front();
                        standardCars.pop();
                    }
                    break;
                }
                case RETURN:{
                    int carId = ag.rentedCars[req.customerId] = standardCars.front();
                    a.rentedCars[req.customerId] = 0;
                    if(carId>20){
                        luxuryCars.push(carId);
                    }else{
                        standardCras.push(carId);
                    }
                    break;
                }
            }   
        }
    }
}

int main(){
    for(int i=0;i<20;i++){
        standardCars.push(i++);

    }

    for(int i =0;i<10;i++){
        luxuryCars.push(i+21);
    }
    return 0;
}



