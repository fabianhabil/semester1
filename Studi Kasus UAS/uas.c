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
    system("cls");
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
    // Open file stream menggunakan mode write.
    FILE *fp = fopen("ligafabian.data", "w");
    for(int i = 0; i < count; i++){
        // Menimpa semua data yang di database dengan struct yang sudah diganti.
        fprintf(fp, "%s#%d#%d#%d#%d\n", Club[i].nama, Club[i].menang, Club[i].draw, Club[i].kalah, Club[i].points);
    }
    // Menutup file stream.
    fclose(fp);
}

// Prosedur untuk menambahkan history match yang sudah diinput user.
void entryHistoryMatch(char history[]){
    // Open file stream menggunakan mode append.
    FILE *fp = fopen("historyligafabian.data", "a");
    // Menambahkan history match yang baru ke database.
    fprintf(fp, "%s", history);
    // Menutup file stream.
    fclose(fp);
}

// Fungsi untuk mencari data sesuai dengan input user menggunakan Linear Searching
int linearSearch(char namaClub[]){
    for(int i = 0; i < count; i++){

        // Jika data ada di struct, akan mereturn nilai index dari struct tersebut.
        if(!strcmp(namaClub, Club[i].nama)){
            return i;
        }
    }
    // Jika tidak ada, akan mereturn -1 yang nantinya akan dihandle (tidak tertemu).
    return -1;
}

// Prosedur untuk menampilkan menu utama dan memilih fitur yang ada.
void menu(){
    unsigned short exit = 0;
    unsigned short option = 1;
    unsigned short valid = 1;
    // Akan terus melakukan loop hingga user exit dari program.
    do{
        system("cls");
        puts("--------------------------------------");
        puts("|       Liga Sepak Bola Fabian       |");
        puts("--------------------------------------");
        puts("| 1. Tambah Hasil Pertandingan       |");
        puts("| 2. Klasemen Liga                   |");
        puts("| 3. History Match                   |");
        puts("| 4. Exit                            |");
        puts("--------------------------------------");
        /* Jika option tidak valid dan tidak ada di menu, memberi tahu user
           bahwa input salah */
        if(!valid || option > 4 || option < 1){
            puts("Input Salah! Silahkan coba lagi!");
        }
        printf("Masukkan Pilihan: ");
        // Cek apakah input valid atau tidak.
        valid = scanf("%hu", &option);
        getchar();
        if(valid){
            // Handle jika input sesuai dengan menu.
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
                system("cls");
                puts("Terima kasih sudah berkunjung!");
                puts("Dibuat oleh Fabian Habil - 2501976503");
            }
        }
    }while(!exit);
}

// Prosedur untuk menambahkan match.
void tambahMatch(){
    system("cls");
    // Membuka file stream menggunakan mode read.
    FILE *fp = fopen("ligafabian.data", "r");
    int exit = 0;
    /* Deklarasikan kembali count menjadi 0, untuk setap barisnya nanti akan ditambah
    sehingga variabel count adalah banyaknya data yang ada di database. */
    count = 0;
    while(!feof(fp)){
        // Scan data yang ada di database sampai selesai.
        fscanf(fp, " %[^#]#%d#%d#%d#%d\n", Club[count].nama, &Club[count].menang, &Club[count].draw, &Club[count].kalah, &Club[count].points);
        count++;
    }
    // Menutup file stream.
    fclose(fp);
    // Loop akan terus jalan hingga user keluar dari menu 1.
    do{
        /* Melakukan bubble sort sehingga jika user sudah menambahkan pertandingan, point akan berubah.
           sehingga harus disort kembali. */
        bubbleSort();
        system("cls");
        // Print semua klasemen kembali, sehingga user tidak bingung.
        printKlasemen();
        char cari[50];
        char cari2[50];
        // User input club pertama yang akan dipilih.
        puts("Silahkan pilih Club yang ingin bertanding!");
        puts("Ketik Exit untuk keluar dari menu!");
        printf("Input: ");
        scanf(" %[^\n]", cari);
        getchar();
        // Jika user input exit, maka akan keluar dari menu 1.
        if(!strcmp(cari, "EXIT") || !strcmp(cari, "Exit") || !strcmp(cari,"exit")){
            exit = 1;
        }
        else{
            /* Mencari data yang diinput user, jika ada akan diassign ke variabel index
               namun jika tidak tertemu, user akan diberi tahu bahwa data tidak ada dan kembali ke 
               awal menu 2 */
            int index = linearSearch(cari);
            if(index == -1){
                printf("Club %s tidak ditemukkan! Silahkan coba lagi!\n\n", cari);
                enterToContinue();
            }
            else{
                // User input club ke 2.
                printf("%s dipilih! Ingin melawan?\n", Club[index].nama);
                printf("Input: ");
                scanf(" %[^\n]", cari2);
                getchar();
                /* Mencari data yang diinput user, jika ada akan diassign ke variabel index
                   namun jika tidak tertemu, user akan diberi tahu bahwa data tidak ada dan kembali ke 
                   awal menu 2 */
                int index2 = linearSearch(cari2);
                if(index2 == -1){
                    printf("Club %s tidak ditemukkan! Silahkan coba lagi!\n\n", cari2);
                    enterToContinue();
                }
                else{
                    system("cls");
                    // Memberi tahu user club yang akan bertanding, dan input skor sesuai format yang ada.
                    printf("%s VS %s\n", Club[index].nama, Club[index2].nama);
                    int skor1, skor2;
                    printf("Silahkan masukkan skor!\n");
                    printf("Contoh Input Skor 2 - 1\n");
                    scanf("%d - %d", &skor1, &skor2);
                    getchar();
                    char history[50];
                    /* Menggungakan sprintf untuk assign history match yang diinput user ke variabel history,
                       yang nantinya akan disimpan ke file history */
                    sprintf(history, "%s %d - %d %s\n", Club[index].nama, skor1, skor2, Club[index2].nama);
                    // Menulis history match ke file history dan diberi tahu ke user sesuai dengan input.
                    entryHistoryMatch(history);
                    printf("%s\n", history);
                    // Jika skor nya sama, kedua club akan ditambah jumlah draw dan point masing masing 1.
                    if(skor1 == skor2){
                        Club[index].draw++;
                        Club[index2].draw++;
                        Club[index].points += 1;
                        Club[index2].points += 1;
                    }
                    else{
                        /* Jika club 1 yang menang, club 1 akan diberi 3 poin dan ditambah kemenangannya 1
                           dan club 2 tidak akan diberi poin dan ditambah kekalahannya 1 */
                        if(skor1 > skor2){
                            Club[index].menang++;
                            Club[index].points += 3;
                            Club[index2].kalah++;
                        }
                        /* Jika club 2 yang menang, club 2 akan diberi 3 poin dan ditambah kemenangannya 1
                           dan club 1 tidak akan diberi poin dan ditambah kekalahannya 1 */
                        else{
                            Club[index].kalah++;
                            Club[index2].menang++;
                            Club[index2].points += 3;
                        }
                    }
                    // Prompt enter to continue.
                    enterToContinue();
                }
            }
        }
    }while(!exit);
    /* Menulis kembali struct yang sudah berubah ke database yang ada dan prompt enter to continue.
       lalu dikembalikan ke menu utama */
    entryNewData();
    enterToContinue();
}

// Prosedur untuk memperlihatkan klasemen liga.
void klasemenLiga(){
    system("cls");
    // Membuka file stream dengan mode read.
    FILE *fp = fopen("ligafabian.data", "r");
    /* Deklarasikan kembali count menjadi 0, untuk setap barisnya nanti akan ditambah
       sehingga variabel count adalah banyaknya data yang ada di database. */
    count = 0;
    while(!feof(fp)){
        fscanf(fp, " %[^#]#%d#%d#%d#%d\n", Club[count].nama, &Club[count].menang, &Club[count].draw, &Club[count].kalah, &Club[count].points);
        count++;
    }
    // Menutup file stream.
    fclose(fp);
    // Sorting dahulu, incase masih belum tersortir sesuai point, lalu menulis kembali di database dan output ke user.
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
    // Output semua data yang ada di struct.
    for(int i = 0; i < count; i++){
        printf("| %-2d | %-20s | %-8d | %-8d | %-8d | %-8d |\n", i + 1, Club[i].nama, Club[i].menang, Club[i].draw, Club[i].kalah, Club[i].points);
    }
    printf("-------------------------------------------------------------------------\n");
}

// Prosedur untuk output semua history match yang diinput user di database.
void printHistory(){
    system("cls");
    // Membuka file stream dengan mode read.
    FILE *fp = fopen("historyligafabian.data", "r");
    /* Deklarasikan kembali count menjadi 0, untuk setap barisnya nanti akan ditambah
       sehingga variabel count adalah banyaknya data yang ada di database. */
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
    // Output semua data yang ada di struct.
    for(int i = 0; i < count; i++){
        printf("| %-2d | %-50s |\n", i+1, Match[i].pertandingan);
    }
    // Menutup file stream.
    fclose(fp);
    printf("-----------------------------------------------------------\n");
    enterToContinue();
}