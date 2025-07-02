method::
*[
    char c;
    West?c->East!c;
]

2. dve ** zameni sa jednim ^

method::
*[
    char c;
    West?c->[
        c!='*' -> [
            East!c;
        ]

        []

        c == '*' -> [
            c!='*'->[
                East!'*';
                East!c;
            ]

            []

            c = '*' -> East!'^';
            
        ]
    ]
]