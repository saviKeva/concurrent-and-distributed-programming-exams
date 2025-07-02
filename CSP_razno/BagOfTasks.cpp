[Node(p:1...N)::node || Bag::bag]
/*Sled dogadjaja je uvek fiksan
    1) proces radnik trazi zadatak od torbe
    2)torba mu ga posalje
    3) proces radnik odradjuje zadatak
    4) proces radnik salje rezultat (u zavisnosti od varijante salje ili bazad torbi ili posebnom procesu kolektoru)
*/

node::
[
    double left, right, data;
    *[
        Bag!getTask();
        Bag?getData(left,right)->[
            CALCULATE;
            /*left-dobija vrednost x
            right - dobija vrednost x+dx */
        ]

        Bag!putResult(data);
    ]
]

bag::
[
    double Xmin, Xmax, dx, x, F=0, data;
    int N, i =0;

    INIT
    *[
        i<N,x<Xmax, Node(p)?getTask()->[
          
                /*p je identifikator procesa*/
                Node(p)!getData(x,x+dx);
                x+=dx;
            
        ]

        []

        i<N, Node(p)?putResult(data) -> [
            /*rezultat se cuva u promenljivoj F procesa bag*/
            F+=data;
            i++;
        ]
    ]
    STOP
]