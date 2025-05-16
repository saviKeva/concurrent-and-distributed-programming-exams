//H20 - SC disciplina
using namespace std;
#include <condition_variable>

class Molecule{
    int hidroS[2];
    int oxy;

    public:
    int hCnt=0;
    int oCnt=0;
    int consumed=0;
    void addO(int id){
        oxy = id;
        oCnt++;
    }
    void addH(int id){
        if(!hidroS[0]){
            hidroS[0]=id;
        }else{
            hidroS[1] = id;
        }
        hCnt++;
    }
    bool compiled(){
        //pp da id-evi idu od 0
        if(hidroS[0] && hidroS[1] && oxy ){
            return true;
        }else{
            return false;
        }
    }
};

class H20{
    int turnO=0, nextO =0;
    int turnH=0,nextH=0;

    condition_variable h_waiting, o_waiting;
    condition_variable compiledM;
    condition_variable ox_waiting;
    Molecule current;

    Molecule oxyReady(int id){
        int myTurn = turnO++;
        if(myTurn>nextO){
            o_waiting.wait(myTurn);
        }

        while(current.hCnt!=2){
            ox_waiting.wait();
        }

        current.addO(id);
        Molecule my_molecule = current;
        compiledM.signal();
        compiledM.signal();

        nextO++;
        o_waiting.signal();
        return my_molecule;

    }
    Molecule hydrogen(int id){
        int myTurn = turnH++;
        if(myTurn>nextH){
            h_waiting.wait(myTurn);
        }

        current.addH(id);
        bool flag = false;
        if(current.hCnt==2){
            flag = true;
            ox_waiting.signal();
        }else{
            nextH++;
            h_waiting.signal();
        }

        if(!current.compiled()){
            compiledM.wait();
        }

        Molecule my_molecule = current;
        
        if(flag){
            nextH++;
            h_waiting.signal();
        }
        return my_molecule;

}