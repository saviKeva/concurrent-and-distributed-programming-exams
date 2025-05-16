using namespace std;
#include <string>
#include <list>
#include <condition_variable>

typedef struct Date{
    int month;
    int day;
    int year;
    string time;
}Date;

typedef struct Flight{
    int id;
    string PilotName;
    Date datum;
    int available;
    bool reserve; //yes/no
}Flight;


list<Flight> lista;

class DirectFlight{
    
    public:
    //metode monitora 

    bool book(Date datum){
        Flight myFlight = findFlight(datum);
        bool book = false;
        if(myFlight.available>0){
            myFlight.available = myFlight.available -1;
            book = true;

        }else{
            book = false;
        }
        return book;
    }

    void cancel(Date date){
        Flight myFlight;
        myFlight = findFlight(date);
        myFlight.available = myFlight.available + 1;
    }

    bool Dateequal(Date d1, Date d2){
       bool yes = ((d1.day == d2.day) && d1.month == d2.month
        && d1.year == d2.year && d1.time.compare(d2.time));
    }
    Flight findFlight(Date date){
        Flight f1;
        f1.available = -1;   
        for(Flight f: lista){
            if(Dateequal(date,f.datum)){
                return f;
            }
        }
        return f1;
    }
};

//kombinovani let

class ConnectedFlight{
    DirectFlight relation1;
    DirectFlight relation2;

    public:
    bool book(Date date){
        bool result;
        result = relation1.book(date);
        if(result){
            //usepsno rezervisan prvi let
            //monitor 1 je slobodan
            result = relation1.book(date);
            if(result){
                result = relation2.book(date);
                if(!result){
                    //ako nisam uspela rezervisati drugi
                    //let
                    //otkayi prvi let
                    relation1.cancel(date);
                }
            }

        }
        return result; //vrati jesam li uspela rezervisati kartu
    }

    void cancel(Date date){
        //putnik sam resi 
        //da otkaye reyervisani 
        //kombinovani let
        relation1.cancel(date);
        relation2.cancel(date);
    }




};

//2. nacin

class DirectFlight1{

    condition_variable blocked;

    public:

    bool Dateequal(Date d1, Date d2){
        bool yes = ((d1.day == d2.day) && d1.month == d2.month
         && d1.year == d2.year && d1.time.compare(d2.time));
     }

    Flight findFlight(Date date){
        Flight f1;
        f1.available = -1;   
        for(Flight f: lista){
            if(Dateequal(date,f.datum)){
                return f;
            }
        }
        return f1;
    }

    bool book(Date date){
        Flight myFlight;
        myFlight = findFlight(date);
        if(myFlight.available>0){
            myFlight.available = myFlight.available-1;
        }else{
            //nema vise mesta
            if((!myFlight.reserve) || blocked.queue()){
            
               //nema vise reyervacija(sve su potvrdjene) u ovom trenutku ili
               //neko vec ceka na kartu
                return false;
            }else{
                //(myFlight.reserve && !blocked.queue)
                //samo ako niko ne ceka na bas tu kartu i neko trenutno rezervise kartu
                blocked.wait();
                //sw - uslov ce mozda biti 
                //promenjen, proveri ponovo
                //PROVERA DA LI SAM SE ODBOKIRALA ZATO STO sam otkazala reyervaciju
                //pa se pojavilo mesto
                //ili je neko samo potvrdio reyervaciju ---> return false;
                if(myFlight.available>0){
                    myFlight.available = myFlight.available-1;
                    return true;
                }else{
                    return false;
                }
            }
        }
    }

    void cancel(Date date){
        Flight myFlight;
        myFlight = findFlight(date);
        if(myFlight.available!=-1){
            myFlight.available = myFlight.available + 1;
            if(myFlight.reserve && blocked.queue()){
                blocked.signal();
            }
        }
    }

    bool reserve(Date date){
        Flight myFlight;
        myFlight = findFlight(date);
        if(myFlight.available>0){
            myFlight.available = myFlight.available-1;
            myFlight.reserve = true;
            return true;
        }else{
            return false;
        }
    }

    void confirmReservation(Date date){
        Flight myFlight;
        myFlight = findFlight(date);

        myFlight.reserve = false;

        blocked.signal();
    }

    void cancelReservation(Date date){
        Flight myFlight;
        myFlight = findFlight(date);
        myFlight.available =myFlight.available-1;
        myFlight.reserve = false;

    }


};

class ConnectedFlight1{

    private:

    DirectFlight1 relation1;
    DirectFlight1 relation2;

    public:

    bool book(Date date){
        bool result;
        result = relation1.reserve(date);
        //reyervisi prvi let
        if(result){
            result = relation2.book(date);
            //bukiraj drugi let

            if(!result){
                //ako nisam uspela bukirati 2.let, otkazi rezervaciju za prvi let
                relation1.cancelReservation(date);
            }else{
                //potvrdi rezervaciju ya prvi let
                relation1.confirmReservation(date);

            }
        }
        return result;
    }



    void cancel(Date date){
        relation1.cancel(date);
        relation2.cancel(date);
    }

};
