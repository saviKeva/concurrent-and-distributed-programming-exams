//sinhronizacija na barijeri sa procesom koordinatorom
using namespace std;
const int n=100;
int arrive[n] = {0};
int nastavi[n] = {0};

void Worker(int id){
    while(true){
        //kod taska 
        arrive[id]=1;
        <await(nastavi(id)==1)>
        nastavi[id] = 0;
    }
}

void Coordinator(){
    while(true){
        for(int i=0;i<n;i++){
            <await(arrive[i] == 1)>
            arrive[i] = 0;
        }
        for(int i=0;i<n;i++){
            nastavi[i]=1;
        }
    }
}


/*Proces koji ceka na flag da bude postavljen na 1
treba da ga vrati na 0*/
/*Flag treba da bude postavljen samo ako je vracen na 0 */
/*
Radni proces da bude pstavljen samo ako je vracen na 0
*Radni proces brise nastavi, a Coordinator brise arrive
*/
/*
Coordinator treba da obrise (vrati na 0) arrive pre postavljanja 
continue
*/

void Worker(int id) {
    while (true) {
        //kod taska
        arrive[id]=1;
        arrive[id]=0; // Ovde premešteno
        <await(nastavi(id)==1)>
        nastavi[id] = 0;
    }
}

//barijera nece raditi korektno, koordinator ce videti
//da je arrive[id] == 0

//koordinator ce se zaglaviti u await(nastaci[i]==1) petlji

/*
Posledice na korektnost: Barijera može raditi nekorektno i dovesti do trka usled preklapanja iteracija. Razmotrimo sledeći scenario:
Svi radnici stignu na barijeru i koordinator ih oslobodi.
Neki radnici brzo završe svoj sledeći zadatak i stignu ponovo na barijeru, postavljajući arrive[id] = 1.
Drugi radnici još uvek nisu ni stigli do barijere iz prethodne iteracije.
Koordinator u svojoj petlji može prerano da vidi da su neke zastavice postavljene (od radnika koji su brži) i potencijalno zaključi da su svi stigli i oslobodi ih pre nego što su svi radnici iz prethodne iteracije uopšte stigli na barijeru. Ovo narušava suštinu barijere da svi procesi moraju da 
stignu pre nego što bilo koji nastavi.*/

void Worker(int id) {
    while (true) {
        //kod taska
        arrive[id]=1;
        <await(nastavi(id)==1)>
        arrive[id]=0; // Ovde premešteno
        nastavi[id] = 0;
    }
}