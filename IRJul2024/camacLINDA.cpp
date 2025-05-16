using namespace std;

const int cap = 6;

void camac(){
    for(int i=0;i<cap;i++){
        out("boatReadyIn");
    }

    in("boatGo");

    for(int i=0;i<cap;i++){
        out("boatFinishedRide");
    }

    in("boatAllExited");
    //  ride ....

}

void womanE(){
    int wCnt=0;
    int mCnt=0;
    int cCnt =0;
    int total = 0;
    int total = 0;
    bool again = true;
    int myId=-1;
    while(again){
        in("boatReadyIn");
        

        in("womanCnt",&wCnt);

        in("manCnt",& mCnt);
        out("manCnt", mCnt);

        in("childrenCnt", &cCnt);
        out("childrenCnt", cCnt);

        total = mCnt + wCnt + cCnt;

        if(total<cap-1 ||((total=cap-1) && mCnt>=2)){
            out("womanCnt", wCnt++);
            total++;
            again =false;
            out("next",myId++);
            if(total == cap){
                out("boatGo");
            }else{
                out("womanCnt", wCnt);
                //int wcCnt;
                // rdp("waitChEnter",&wcCnt);
                // if((mCnt + wCnt)>0 && (wcCnt>0)){
                //     out("wChGo");
                // }
            }
        }else{
            int num;
            out("childrenCnt", cCnt);
            //pusti neku drugu osobu ako ti vec ne mozes
            out("BoatReadyIn");
        }
    }

    
}

void manE(){
    int wCnt=0;
    int mCnt=0;
    int cCnt =0;
    int total = 0;
    int total = 0;
    bool again = false;
    in("boatReadyIn");

    while(again){
        in("womanCnt",wCnt);

        out("womanCnt", mCnt);

        in("manCnt", mCnt);
        

        in("childrenCnt", cCnt);
        out("childrenCnt", cCnt);

        total = mCnt + wCnt + cCnt;

        if(total<cap){
            out("manCnt", cCnt++);
            total++;
            if(total == cap){
                out("boatGo");
            }
        }else{
            out("manCnt", cCnt);
            out("boatReadyIn");
        }
    }

}


void childE(){
    int wCnt=0;
    int mCnt=0;
    int cCnt =0;
    int total = 0;
    int total = 0;
    bool again = true;

    while(again){
        in("boatReadyIn");

        in("womanCnt",wCnt);
        out("womanCnt", wCnt);

        in("manCnt", mCnt);
        out("manCnt", mCnt);

        in("childrenCnt", cCnt);
        

        total = mCnt + wCnt + cCnt;


        if((total<cap-1 ||((total=cap-1) && mCnt>=2)) && 
        mCnt+wCnt>0){
            out("childrenCnt", cCnt++);
            total++;
            if(total == cap){
                out("boatGo");
            }
            again= false;
        }else{
            //int num;
            out("childrenCnt", cCnt);
            out("boatReadyIn");
            // in("waitChEnter",num);
            // out("waitChEnter", num+1);
            // in("wChGo");
        }
    }
    
}

void manExit(){
    in("boatFinishRide");
     int wCnt=0;
    int mCnt=0;
    int cCnt =0;
    int total = 0;
    int total = 0;
    bool again = false;

    while(again){
        in("womanCnt",wCnt);

        out("womanCnt", mCnt);

        in("manCnt", mCnt);
        

        in("childrenCnt", cCnt);
        out("childrenCnt", cCnt);

        total = mCnt + wCnt + cCnt;

        if(mCnt + wCnt ==1 && cCnt>0){
            continue;

        }else{
            again = false;
            total--;
            out("manCnt",mCnt--);
            if(total==0){
                out("boatAllExited");
            }
        }
    }
    
}

void womanExit(){
    in("boatFinishRide");
     int wCnt=0;
    int mCnt=0;
    int cCnt =0;
    int total = 0;
    int total = 0;
    bool again = false;

    while(again){
        in("womanCnt",&wCnt);


        in("manCnt", &mCnt);
        out("manCnt",mCnt);

        in("childrenCnt", &cCnt);
        out("childrenCnt", cCnt);

        total = mCnt + wCnt + cCnt;

        if(wCnt + mCnt ==1 && cCnt>0){
            continue;

        }else{
            again = false;
            total--;
            out("womanCnt",wCnt--);
            if(total==0){
                out("boatAllExited");
            }
        }
    }
    
}

void childE(){
    int cCnt =0;

    in("boatFinishRide");

    in("childrenCnt",&cCnt);
    out("childrenCnt",cCnt--);

    
}