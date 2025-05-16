void reader(){
    int id, num;

    while(1){
        in("id", ?id);
        out("id",id+1);
        in("ok_to_work", id);//samo jedan proces u sekciji

        in("readers_num", ?num);
        out("readers_num",num +1);

        out("ok_to_work", id+1);
        reading();

        in("readers_num", ?num);
        out("readers_num", num-1);

    }

    //citaac id =1
    //pisac id = 2
    //citalac id = 3

    //cit id=1 upise u readers num 1
    //vrati readers_num

    //dodje cit id = 2 blokira se na ok_to_work, pisac takodje blokiran na ok to work
    //cit 1 vrati ok_to+work i u njega upise 2
    //pisac se blokira na readersNum, 0
    //kad citalac 1 postavi readers_num na nula, pisac prolazi
    //itd..

    
    void writer(){
        int id;
        while(1){
            in("id", ?id);
            out("id", id+1);
            in("ok_to_work",id);

            //blokira se dok ne uspe da procita da je  readers_num = 0
            rd("readers_num",0);
            writing();
            out("ok_to_work", id+1);
        }
    }

    void init(){
        int i;
        out("id", 0);
        out("ok_to_work",0);
        out("readers_num",0);
        for(i=0;i<10;i++){
            eval(reader());
            eval(writer());
        }


    }
    
    //2. nacin

    //prednost za citaoce

    int numOfReaders = 12;
    int numOfWriters = 30;
    void reader2(int id){
        int rCnt;
        IN("rCnt"&rCnt);
        if(rCnt == 0){
            IN("database");
        }
        OUT("readCnt", rCnt+1);
        read();
        IN("readCnt", &rCnt);
        if(rCnt == 1){
            OUT("readCnt", &rCnt);

        }
        OUT("rCnt", rCnt-1);
    }

    void writer(int id){
        IN("database");
        write();
        OUT("database");
    }

    void init(){
        OUT("database");
        OUT("readCnt", 0);
        for(int i =0;i<numOfReaders,i++){
            EVAL(reader(i));

        }
        for(int i =0;i<numOfWriters,i++){
            EVAL(writer(i));

        }
    }