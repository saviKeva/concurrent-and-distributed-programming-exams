[Philosopher(i:0...4)::philospopher || Fork(i:0..4)::fork
|| Room::room]

/*i je privatni identifikator svakog filozofa*/

philosopher::
[
    int leftFork = i;
    int rightFork = (i+1)%5;

    *[
        true -> [
            THINK;

            Room!wantingToEat();
            Fork(leftFork)!takingFork();
            Fork(rightFork)!takingFork();

            EAT;

            Fork(leftFork)!returningFork();
            Fork(rightFork)!returningFork();
            Room!bothForksReturned();
        ]
    ]
]

fork::
[
    int leftPhilosopher = (i-1)%5;
    int rightPhilosopher = i ;

    *[
        Philosopher(leftPhilosopher)?takingFork()->[
            Philosopher(leftPhilosopher)?returningFork();
            /*ne obradjuju se dalji zahtevi za uzimanjem viljuske
            dokle god se viljuska ne vrati*/

            /*bezuslovno cekam - blokiram se dok ne primim poruku*/
        ]

        []

        Philosopher(rightPhilosopher)?takingFork()->[
            Philosopher(rightPhilosopher)?returningFork();
        ]
    ]
]

room::
[
    int semaphoreValue = 4;
    /*inicijalno 4 filozofa mogu da uzmu viljuske - da se izbegne deadlock*/
    *[
        semaphoreValue>0, Philosopher(i)?wantingToEat()->[
            semaphoreValue--;
        ]

        []

        Philosopher(i)?bothForksReturned() -> [
            semaphoreValue++;
        ]
    ]
]


