#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 2501976503 - Fabian Habil - UAS Algorithm & Programming No 2

// Deklarasi struct data mahasiswa dengan length 100 data.
typedef struct mahasiswa {
    char nama[100];
    char nim[100];
    int tugas, uts, uas, lulus;
}Mahasiswa;
Mahasiswa mahasiswa[100];


// Fungsi Prototype
//procedure algorithm quicksort untuk sorting NIM secara ascending.
void quickSort(Mahasiswa mahasiswa[], int mulai, int akhir);

//function pembantu quicksort untuk mempartisi data.
int partition(Mahasiswa mahasiswa[], int mulai, int akhir);

// Prosedur untuk swap 2 struct.
void swap(Mahasiswa* mahasiswaA, Mahasiswa* mahasiswaB);

// Function algorithm binary search untuk search NIM.
int binarySearch(char nim[], int kiri, int kanan);

int main() {
    system("cls");
    char cari[20];
    printf("Silahkan masukkan nim yang akan dicari: ");
    scanf(" %[^\n]", cari);
    getchar();
    // Variabel count untuk menghitung sekarang ada berapa jumlah data di database.
    int count = 0;
    FILE* fp = fopen("database.data", "r");
    while (!feof(fp)) {
        fscanf(fp, " %[^#]#%[^#]#%d#%d#%d#%d\n", &mahasiswa[count].nama, &mahasiswa[count].nim, &mahasiswa[count].tugas,
               &mahasiswa[count].uts, &mahasiswa[count].uas, &mahasiswa[count].lulus);
        count++;
    }
    quickSort(mahasiswa, 0, count - 1);
    int index = binarySearch(cari, 0, count);
    if (index == -1) {
        printf("Mahasiswa tidak ditemukan!\n");
    }
    else {
        printf("Nama Mahasiswa : %s\n", mahasiswa[index].nama);
        printf("Nim Mahasiswa: %s\n", mahasiswa[index].nim);
        printf("Nilai Tugas Mahasiswa: %d\n", mahasiswa[index].tugas);
        printf("Nilai UTS Mahasiswa: %d\n", mahasiswa[index].uts);
        printf("Nilai UAS Mahasiswa: %d\n", mahasiswa[index].uas);
        if (!mahasiswa[index].lulus) {
            printf("Mahasiswa tidak lulus mata kuliah ini!\n");
        }
        else {
            printf("Mahasiswa lulus mata kuliah ini!\n");
        }
    }
}

// Prosedur untuk swap 2 struct.
void swap(Mahasiswa* mahasiswaA, Mahasiswa* mahasiswaB) {
    Mahasiswa temp = *mahasiswaA;
    *mahasiswaA = *mahasiswaB;
    *mahasiswaB = temp;
}

// Partisi untuk membantu procedure algorithm quicksort, sorting berdasarkan NIM.
int partition(Mahasiswa mahasiswa[], int mulai, int akhir) {
    Mahasiswa pivot = mahasiswa[akhir];
    int i = (mulai - 1);

    //sorting ascending berdasarkan NIM
    for (int j = mulai; j <= akhir - 1; j++) {
        if (strcmp(mahasiswa[j].nim, pivot.nim) < 0) {
            i++;
            swap(&mahasiswa[i], &mahasiswa[j]);
        }
    }

    swap(&mahasiswa[i + 1], &mahasiswa[akhir]);
    return(i + 1);
}

// Fungsi Algorithm utama untuk quicksort.
void quickSort(Mahasiswa mahasiswa[], int mulai, int akhir) {
    if (mulai < akhir) {
        int tengah = partition(mahasiswa, mulai, akhir);
        quickSort(mahasiswa, mulai, tengah - 1);
        quickSort(mahasiswa, tengah + 1, akhir);
    }
}

// Fungsi Binary Search untuk searching.
int binarySearch(char nim[], int kiri, int kanan) {
    int tengah;
    while (kiri <= kanan) {
        tengah = (kiri + kanan) / 2;
        if (strcmp(nim, mahasiswa[tengah].nim) == 0) {
            return tengah;
        }
        if (strcmp(nim, mahasiswa[tengah].nim) < 0) {
            kanan = tengah - 1;
        }
        if (strcmp(nim, mahasiswa[tengah].nim) > 0) {
            kiri = tengah + 1;
        }
    }
    return -1;
}