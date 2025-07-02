/*svaki proces ima jedan elemnt skupa, skup sortiran rastuce*/
/*u pocetku nema sadrzaj ni jedan proces*/


[S(i:1...100)::set]

set::
[
    int n = ...;

    *[
        /*
        Ako ovde nas proces S(i) primi signal has(n)
        od procesa S(i-1), znamo da se sigurno nije izvrsio
        insert u proces S(i) sto znaci da proces S(i)
        ne sadrzi nijedan broj i zato odmah odgovara procesu S(0)
        sa false
        */
        S(i-1)?has(n)->[
            S(0)!false;
        ]

        []

        S(i-1)?insert(n) -> *[
            int m;
            S(i-1)?has(m)->[
                m<=n ->[
                    S(0)!(m==n);
                ]

                []

                m>n ->[
                    S(i+1)!has(m);
                ]
            ]
            []

            S(i-1)?insert(m)->[
                /*
                onom narednom u nizu prosledi vrednost koju ja 
                trenutno drzim (n), a ja cu kod sebe sacuvati m
                m-vrednost koja treba da se ubaci, manja od one koju
                ja imam
                */
                m<n ->[
                    S(i+1)!insert(n);
                    n=m;
                ]

                []

                /*ako je element m vec u skupu
                necemo da ga umecemo
                */
               m==n -> [
                SKIP;
               ]

               []

               /*ako je element koji treba da
               se ubaci veci od mene, prosledi ga sledecem
               procesu u nizu*/
               m>n->[
                S(i+1)!insert(m);
               ]
            ]
        ]
    ]
]


