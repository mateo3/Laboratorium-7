#include stdio.h
#include stdlib.h
#include unistd.h
#include time.h
#include mpi.h
#define REZERWA 80

#define PARKING 1
#define START 2
#define JAZDA 3
#define KONIEC_JAZDY 4
#define KATASTROFA 5
#define TANKUJ 800
int paliwo = 800;
int PARKUJ=1, NIE_PARKUJ=0;
int liczba_procesow;
int nr_procesu;
int ilosc_pociagow;
int ilosc_miejsc=6;
int ilosc_zajetych_miejsc=0;
int tag=1;
int wyslij[2];
int odbierz[2];
MPI_Status mpi_status;
void Wyslij(int nr_pociagu, int stan)
{
wyslij[0]=nr_poaciagu;
wyslij[1]=stan;
MPI_Send(&wyslij, 2, MPI_INT, 0, tag, MPI_COMM_WORLD);
sleep(1);
}
void Stacja(int liczba_procesow){
int nr_pociagu,status;
ilosc_pociagow = liczba_procesow - 1;
if(rand()%2==1){
printf(Pociag startujen);
}
else{
printf(Niestety pociag musi zostać podany kontrolin);
}
printf(Dysponujemy %d miejscami w na stacjin, ilosc_miejsc);
sleep(2);
while(ilosc_miejsc = ilosc_pociagow){
MPI_Recv(&odbierz,2,MPI_INT,MPI_ANY_SOURCE,tag,MPI_COMM_WORLD, &mpi_status);
nr_pociagu=odbierz[0];
status=odbierz[1];
if(status==1){
printf(Pociag %d stoi na stacjin, nr_pociagu);
}if(status==2){
printf(Pociag %d pozwolenie na start z miejsca nr %dn, nr_pociagu,ilosc_zajetych_miejsc);
ilosc_zajetych_miejsc--;
}
if(status==3){
printf(Pociag %d jedzien, nr_pociagu);
}
if(status==4){
if(ilosc_zajetych_miejscilosc_miejsc){
ilosc_zajetych_miejsc++;
MPI_Send(&PARKUJ, 1, MPI_INT, nr_pociagu, tag, MPI_COMM_WORLD);
}
else{
MPI_Send(&NIE_PARKUJ, 1, MPI_INT, nr_pociagu, tag, MPI_COMM_WORLD);
}
}
if(status==5){
ilosc_pociagow--;
printf(Ilosc pociagow %dn, ilosc_pociagow);
}
}
}
void Pociag(){
int stan,suma,i;
stan=JAZDA;
while(1){
if(stan==1){
if(rand()%2==1){
stan=START;
paliwo=TANKUJ;
printf(Prosze o pozwolenie na wyjazd ze stacji, pociag %dn,nr_procesu);
Wyslij(nr_procesu,stan);
}
else{
Wyslij(nr_procesu,stan);
}
}
else if(stan==2){
printf(Wyjechalem, pociag %dn,nr_procesu);
stan=JAZDA;
Wyslij(nr_procesu,stan);
}
else if(stan==3){
paliwo-=rand()%500;
if(paliwo=REZERWA){
stan=KONIEC_JAZDY;
printf(Prosze o pozwolenie na przjazd na stacjen);
Wyslij(nr_procesu,stan);
}
else{
for(i=0; rand()%10000;i++);
}
}
else if(stan==4){
int temp;
MPI_Recv(&temp, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &mpi_status);
if(temp==PARKUJ){
stan=PARKING;
printf(Pociag %d odstawiony na stacjen, nr_procesu);
}
else{
paliwo-=rand()%500;
if(paliwo0){
Wyslij(nr_procesu,stan);
}
else{
stan=KATASTROFA;
printf(Skonczylo mi sie paliwo, POCIAG UNIERUCHOMIONYn);
Wyslij(nr_procesu,stan);
return; 
}
}
}
}
}
int main(int argc, char argv[]){
 MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&nr_procesu);
    MPI_Comm_size(MPI_COMM_WORLD,&liczba_procesow);
    srand(time(NULL));
    if(nr_procesu == 0)
    Stacja(liczba_procesow);
    else
    Pociag();
    MPI_Finalize();
    return 0;
} 