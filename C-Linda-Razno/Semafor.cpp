using namespace std;
#include <string>

void signal(string sem){
    out(sem);
}

void wait(string sem){
    in(sem);
}

void init(string sem, unsigned int val){
    //incijalno val procesa moze da prodje
    for(int i =0;i<val;i++){
        out(sem);
        
    }
}