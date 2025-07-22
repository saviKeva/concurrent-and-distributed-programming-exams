int ticket = 0, next = 0;

int myTicket = -1;
do{
swap(myTicket, ticket);
}while(myTicket ==-1);
int temp = myTicket + 1;
swap(temp, ticket);

while(next !== myTicket)yield();

// kriticna sekcija

temp = myTicket + 1;
swap(temp, next);