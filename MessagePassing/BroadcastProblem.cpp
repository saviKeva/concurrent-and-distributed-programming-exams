/*1. Resenje: kada imamo neusmeren graf: cvor ne moze da zna da li su njegovi susedi
vec primili poruku - zato svim susedima salje, iako je od jednog sigurno primio*/

const int N = ...;
mbx nodes[N]; //za svaki cvor u grafu -> jedno sanduce

void initiatorGraphNode(int nodeId){

    bool neighbors[N];
    msg message;
    bool status;
    int numOfNeighbors = 0;

    for(int j=0;j<N;j++){
        if(neighbors[j]){
            numOfNeighbors++;
        }
    }

    //cvor ceka da primi prvu poruku od 1 od svojih suseda
    mbx_get(message, nodes[nodeId], INF, status);


    //cvor prosledjuje poruku svim svojim susedima (pa cak i onom od kog je primio poruku)

    for(int j = 0;j<N;j++){
        if(neighbors[j]){
            mbx_put(message, nodes[j]);
        }
    }

    //cvor ceka da primi poruku od preostalih suseda
    //od kojih je nije primio. Ovo radimo jer su ove poruke visak. Na ovaj nacin cistimo djubre
    //iz postanskog sanduceta kako se naredni broadcast ne bi zaglavio
    for(int i =0;i<numOfNeighbors-1;i++){
        mbx_get(message, nodes[nodeId], INF, status);
    }
}

/*Resenje 2 - pocetni cvor ima informaciju o kompletnoj topologiji grafa, tako
da on moze da transformise graf u obuhvatno stablo (svi cvorovi budu povezani, ali
da nema petlji - ima minimalan broj grana, tj. svaki cvo ima minimalan broj suseda
tako da se dobije povezan aciklican graf). */

const int N = ...;
typedef struct msg{
    bool spanningTree[N][N];
    int senderId;
}msg;


mbx nodes[N];

void initiatorGraphNode(int nodeId){
    msg message;
    bool status;
    int firstNodeId = Math.floor(Math.random()*N);

    bool graph[N][N];

    //pretpostavimo: fja createSpanningTree izmeni originalnu matricu susenosti grafa tako sto izbaci grane 
    /*postavljajuci odgovarajuce elemente matrice na false*/
    message.spanningTree = createSpanningTree(graph);
    message.senderId = nodeId;

    mbx_put(message, nodes[firstNodeId]);

}


void regularGraphNode(int nodeId){
    msg message;
    bool status;

    //cvor ceka da primi poruku od 1 od suseda

    mbx_get(message, nodes[nodeId],INF, status);

    int nodeThatSentMeMessage = message.senderId;

    message.senderId = nodeId;
    /*da bi cvorovi kojima posaljemo poruku znali da smo im
    je mi poslali, i kako oni onda nama ne bi slali istu
    poruku nazad*/

    for(int j = 0;j<N;j++){
        if(message.spanningTree[nodeId][j] && j!=nodeThatSentMeMessage){
            mbx_put(message, nodes[j]);
            /*prosledjujem poruke svim susedima osim onog koji je meni poslao*/
        }
    }
}