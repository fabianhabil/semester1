#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 2501976503 - Fabian Habil Ramdhan - Studi Kasus UAS Algorithm & Programming - LB75
// Algorithma Searching -> Linear Search
// Algorithma Sorting -> Bubble Sort
/* Alasan saya memilih Linear dan Bubble adalah karena sedikitnya data yang ada, karena data nya
   hanya ada 10 club saja, jadi saya memilih Linear Search dan Bubble Sort di program saya*/

// Deklarasi Struct dan Variabel Global
/* Struct club untuk menyimpan data Club dengan length 12 data, karena di database ada 10 data.
   Kenapa 12 data? saya sengaja melebihkan dari data yang ada untuk menghindari bug dan error. */
typedef struct club{
    char nama[50];
    int menang;
    int kalah;
    int draw;
    int points;
}club;
club Club[12];

/* Struct match untuk menyimpan data history match yang sudah diinput user
   dengan length 100 data. */
typedef struct match{
    char pertandingan[100];
}match;
match Match[100];

// Variabel count untuk menghitung sekarang ada berapa jumlah data di database.
int count = 0;

// Fungsi dan Prosedur Prototype.
void enterToContinue();
void swap(club *ClubA, club *ClubB);
void bubbleSort();
void entryNewData();
void entryHistoryMatch(char history[]);
int linearSearch(char namaClub[]);
void menu();
void tambahMatch();
void klasemenLiga();
void printKlasemen();
void printHistory();

// Fungsi Main.
int main(){
    system("clear");
    menu();
}

// Prosedur untuk membuat prompt agar user menekan enter terlebih dahulu lalu melanjutkan program.
void enterToContinue(){
    printf("Tekan Enter untuk melanjutkan!");
    getchar();
}

// Prosedur untuk swap 2 struct
void swap(club *ClubA, club *ClubB){
    club temp = *ClubA;
    *ClubA = *ClubB;
    *ClubB = temp;
}

// Prosedur untuk sort club berdasarkan points menggunakan Bubble Sort
void bubbleSort(){
    for(int i = 0; i < count; i++){
        for(int j = 0; j < count - i - 1; j++){
            if(Club[j].points < Club[j+1].points){
                swap(&Club[j], &Club[j+1]);
            }
        }
    }
}

// Prosedur untuk menulis kembali data yang sudah disort secara point ke file database.
void entryNewData(){
    FILE *fp = fopen("ligafabian.data", "w");
    for(int i = 0; i < count; i++){
        fprintf(fp, "%s#%d#%d#%d#%d\n", Club[i].nama, Club[i].menang, Club[i].draw, Club[i].kalah, Club[i].points);
    }
    fclose(fp);
}

// Prosedur untuk menambahkan history match yang sudah diinput user.
void entryHistoryMatch(char history[]){
    FILE *fp = fopen("historyligafabian.data", "a");
    fprintf(fp, "%s", history);
    fclose(fp);
}

// Fungsi untuk mencari data sesuai dengan input user menggunakan Linear Searching
int linearSearch(char namaClub[]){
    for(int i = 0; i < count; i++){
        if(!strcmp(namaClub, Club[i].nama)){
            return i;
        }
    }
    return -1;
}

// Prosedur untuk menampilkan menu utama dan memilih fitur yang ada.
void menu(){
    unsigned short exit = 0;
    unsigned short option = 1;
    unsigned short valid = 1;
    do{
        system("clear");
        puts("--------------------------------------");
        puts("|      Liga Sepak Bola Indonesia     |");
        puts("--------------------------------------");
        puts("| 1. Tambah Hasil Pertandingan       |");
        puts("| 2. Klasemen Liga                   |");
        puts("| 3. History Match                   |");
        puts("| 4. Exit                            |");
        puts("--------------------------------------");
        if(!valid || option > 4 || option < 1){
            puts("Input Salah! Silahkan coba lagi!");
        }
        printf("Masukkan Pilihan: ");
        valid = scanf("%hu", &option);
        getchar();
        if(valid){
            if(option == 1){
                tambahMatch();
            }
            else if(option == 2){
                klasemenLiga();
            }
            else if(option == 3){
                printHistory();
            }
            else if(option == 4){
                exit = 1;
                system("clear");
                puts("Terima kasih sudah berkunjung!");
                puts("Dibuat oleh Fabian Habil - 2501976503");
            }
        }
    }while(!exit);
}

// Prosedur untuk menambahkan match.
void tambahMatch(){
    system("clear");
    FILE *fp = fopen("ligafabian.data", "r");
    int exit = 0;
    count = 0;
    while(!feof(fp)){
        // fscanf(fp, " %[^#]#%[^#]#%[^\n]\n", Club[count].nama, Club[count].nohp, Club[count].alamat);
        fscanf(fp, " %[^#]#%d#%d#%d#%d\n", Club[count].nama, &Club[count].menang, &Club[count].draw, &Club[count].kalah, &Club[count].points);
        count++;
    }
    fclose(fp);
    do{
        bubbleSort();
        system("clear");
        printKlasemen();
        char cari[50];
        char cari2[50];
        puts("Silahkan pilih Club yang ingin bertanding!");
        puts("Ketik Exit untuk keluar dari menu!");
        printf("Input: ");
        scanf(" %[^\n]", cari);
        getchar();
        if(!strcmp(cari, "EXIT") || !strcmp(cari, "Exit") || !strcmp(cari,"exit")){
            exit = 1;
        }
        else{
            int index = linearSearch(cari);
            if(index == -1){
                printf("Club %s tidak ditemukkan! Silahkan coba lagi!\n\n", cari);
                enterToContinue();
            }
            else{
                printf("%s dipilih! Ingin melawan?\n", Club[index].nama);
                printf("Input: ");
                scanf(" %[^\n]", cari2);
                getchar();
                int index2 = linearSearch(cari2);
                if(index2 == -1){
                    printf("Club %s tidak ditemukkan! Silahkan coba lagi!\n\n", cari2);
                    enterToContinue();
                }
                else{
                    system("clear");
                    printf("%s VS %s\n", Club[index].nama, Club[index2].nama);
                    int skor1, skor2;
                    printf("Silahkan masukkan skor!\n");
                    printf("Contoh Input Skor 2 - 1\n");
                    scanf("%d - %d", &skor1, &skor2);
                    getchar();
                    char history[50];
                    sprintf(history, "%s %d - %d %s\n", Club[index].nama, skor1, skor2, Club[index2].nama);
                    entryHistoryMatch(history);
                    printf("%s\n", history);
                    if(skor1 == skor2){
                        Club[index].draw++;
                        Club[index2].draw++;
                        Club[index].points += 1;
                        Club[index2].points += 1;
                    }
                    else{
                        if(skor1 > skor2){
                            Club[index].menang++;
                            Club[index].points += 3;
                            Club[index2].kalah++;
                        }
                        else{
                            Club[index].kalah++;
                            Club[index2].menang++;
                            Club[index2].points += 3;
                        }
                    }
                    enterToContinue();
                }
            }
        }
    }while(!exit);
    entryNewData();
    enterToContinue();
}

// Prosedur untuk memperlihatkan klasemen liga.
void klasemenLiga(){
    system("clear");
    FILE *fp = fopen("ligafabian.data", "r");
    count = 0;
    while(!feof(fp)){
        fscanf(fp, " %[^#]#%d#%d#%d#%d\n", Club[count].nama, &Club[count].menang, &Club[count].draw, &Club[count].kalah, &Club[count].points);
        count++;
    }
    fclose(fp);
    bubbleSort();
    entryNewData();
    printKlasemen();
    enterToContinue();
}

// Prosedur untuk output semua data pelanggan yang ada di database.
void printKlasemen(){
    printf("-------------------------------------------------------------------------\n");
    printf("|                         KLASEMEN LIGA FABIAN                          |\n");
    printf("-------------------------------------------------------------------------\n");
    printf("| %-2s | %-20s | %-8s | %-8s | %-8s | %-8s |\n", "No", "Nama Club", "Menang", "Draw", "Kalah", "Points");
    printf("-------------------------------------------------------------------------\n");
    for(int i = 0; i < count; i++){
        printf("| %-2d | %-20s | %-8d | %-8d | %-8d | %-8d |\n", i + 1, Club[i].nama, Club[i].menang, Club[i].draw, Club[i].kalah, Club[i].points);
    }
    printf("-------------------------------------------------------------------------\n");
}

// Prosedur untuk output semua history match yang diinput user di database.
void printHistory(){
    FILE *fp = fopen("historyligafabian.data", "r");
    count = 0;
    while(!feof(fp)){
        fscanf(fp, " %[^\n]\n", Match[count].pertandingan);
        count++;
    }
    printf("-----------------------------------------------------------\n");
    printf("|                HISTORY MATCH LIGA FABIAN                |\n");
    printf("-----------------------------------------------------------\n");
    printf("| %-2s | %-50s |\n", "No", "Match");
    printf("-----------------------------------------------------------\n");
    for(int i = 0; i < count; i++){
        printf("| %-2d | %-50s |\n", i+1, Match[i].pertandingan);
    }
    fclose(fp);
    printf("-----------------------------------------------------------\n");
    enterToContinue();
}