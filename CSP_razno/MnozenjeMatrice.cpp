[M(i:1...3,0)::west || M(0,j:1..3)::north || M(i:1..3,4)::east
|| M(i:1..3,j:1..3)::center ]

north::
*[
    true->[
        M(1,j)!0;
    ]
]

east::
*[
    double x;
    M(i,3)?x->[
        SKIP;
    ]
]

center::
*[
    double x;
    M(i,3)?x -> [
        SKIP
    ]
]

center::
*[
    double x;
    M(i,j-1)?x -> [
        M(i,j+1)!x;
        double sum;
        M(i-1, j)?sum;
        M(i+1,j)!(A(i,j)*x+sum);
    ]
]

