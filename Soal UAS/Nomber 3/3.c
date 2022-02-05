#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 2501976503 - Fabian Habil - UAS Algorithm & Programming No 3

// Deklarasi struct data logharian dengan length 100 data.
typedef struct log {
    char tanggal[20];
    char isilog[1000];
}Log;
Log logharian[100];

// Fungsi Prototype.
void menu();
void tambahLog();
void enterToContinue();
void showLog();
int linearSearch(char cari[], int count);

int main() {
    system("cls");
    menu();
}

void menu() {
    unsigned short exit = 0;
    unsigned short option = 1;
    unsigned short valid = 1;
    do {
        system("cls");
        puts("--------------------------------------");
        puts("|             Log Harian             |");
        puts("--------------------------------------");
        puts("| 1. Tambah Log Harian               |");
        puts("| 2. Tampilkan Log Harian            |");
        puts("| 3. Exit                            |");
        puts("--------------------------------------");
        /* Jika option tidak valid dan tidak ada di menu, memberi tahu user
           bahwa input salah */
        if (!valid || option > 3 || option < 1) {
            puts("Input Salah! Silahkan coba lagi!");
        }
        printf("Masukkan Pilihan: ");
        valid = scanf("%hu", &option);
        // Cek apakah input valid atau tidak.
        getchar();
        if (valid) {
            // Handle jika input sesuai dengan menu.
            if (option == 1) {
                tambahLog();
            }
            else if (option == 2) {
                showLog();
            }
            else if (option == 3) {
                exit = 1;
                system("cls");
                puts("Terima kasih sudah berkunjung!");
                puts("Dibuat oleh Fabian Habil - 2501976503");
            }
        }
    } while (!exit);
}

void tambahLog() {
    system("cls");
    FILE* fp = fopen("database.data", "a");
    char tanggal[20];
    char isilog[1000];
    printf("Silahkan masukkan tanggal log ini dibuat ");
    printf("Contoh format tanggal DD-MM-YYYY\n");
    printf("Input: ");
    scanf(" %[^\n]", tanggal);
    getchar();
    system("cls");
    printf("Log harian (%s)\n", tanggal);
    printf("Silahkan isi log! (Maksimal 1000 Karakter)\n");
    printf("Tekan Enter jika sudah selesai!\n");
    printf("Input: ");
    scanf(" %[^\n]", isilog);
    getchar();
    fprintf(fp, "%s#%s\n", tanggal, isilog);
    fclose(fp);
    printf("Data berhasil ditambahkan!\n");
    enterToContinue();
}


void showLog() {
    unsigned short exit = 0;
    char input[20];
    FILE* fp = fopen("database.data", "r");
    int count = 0;
    int index = 0;
    while (!feof(fp)) {
        fscanf(fp, " %[^#]#%[^\n]\n", logharian[count].tanggal, logharian[count].isilog);
        count++;
    }
    fclose(fp);
    do {
        system("cls");
        puts("--------------------------------------");
        puts("|          Data Log Harian           |");
        puts("--------------------------------------");
        for (int i = 0; i < count; i++) {
            printf("| %d. %-31s | \n", i + 1, logharian[i].tanggal);
        }
        puts("--------------------------------------");
        if (index == -1) {
            printf("Log harian tidak ditemukan!\n");
        }
        printf("Ketik Exit untuk keluar!\n");
        printf("Ingin melihat log harian tanggal berapa? ");
        scanf(" %[^\n]", input);
        index = linearSearch(input, count);
        getchar();
        if (!strcmp(input, "exit") || !strcmp(input, "Exit") || !strcmp(input, "EXIT")) {
            exit = 1;
        }
        if (index != -1) {
            system("cls");
            printf("Isi Log Harian Tanggal %s\n", logharian[index].tanggal);
            printf("%s\n\n", logharian[index].isilog);
            enterToContinue();
        }

    } while (!exit);
    enterToContinue();
}

void enterToContinue() {
    printf("Tekan Enter untuk melanjutkan!");
    getchar();
}

int linearSearch(char cari[], int count) {
    for (int i = 0; i < count; i++) {
        if (!strcmp(cari, logharian[i].tanggal)) {
            return i;
        }
    }
    return -1;
}