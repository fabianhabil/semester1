#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 2501976503 - Fabian Habil - UAS Algorithm & Programming No 2

// Deklarasi struct data mahasiswa dengan length 100 data.
typedef struct mahasiswa{
    char nama[50];
    char nim[20];
    int tugas, uts, uas, lulus;
}mahasiswa;
mahasiswa Mahasiswa[100];

// Variabel count untuk menghitung sekarang ada berapa jumlah data di database.
int count = 0;

// Fungsi Prototype
//procedure algorithm quicksort untuk sorting NIM secara ascending.
void quickSort(mahasiswa Mahasiswa[], int mulai, int akhir);

//function pembantu quicksort untuk mempartisi data.
int partition(mahasiswa Mahasiswa[], int mulai, int akhir);

// Prosedur untuk swap 2 struct.
void swap(mahasiswa *mahasiswaA, mahasiswa *mahasiswaB);

// Function algorithm binary search untuk search NIM.
int binarySearch(mahasiswa Mahasiswa[], char nim[], int kiri, int kanan);

int main(){
    char cari[20];
    printf("Silahkan masukkan nim yang akan dicari: ");
    scanf(" %[^\n]", cari);
    FILE *fp = fopen("database.data", "r");
    while(!feof(fp)){
        fscanf(fp, " %[^#]#%[^#]#%d#%d#%d#%d\n", Mahasiswa[count].nama, Mahasiswa[count].nim, &Mahasiswa[count].tugas, 
        &Mahasiswa[count].uts, &Mahasiswa[count].uas, &Mahasiswa[count].lulus);
        count++;
    }
    quickSort(Mahasiswa, 0, 15);
    for(int i = 0; i < count; i++){
        printf("%d %s %s %d %d %d %d\n", i+1, Mahasiswa[i].nama, Mahasiswa[i].nim, Mahasiswa[i].tugas, 
        Mahasiswa[i].uts, Mahasiswa[i].uas, Mahasiswa[i].lulus);
    }
    printf("%d\n", count);
}

// Prosedur untuk swap 2 struct.
void swap(mahasiswa *mahasiswaA, mahasiswa *mahasiswaB){
    mahasiswa temp = *mahasiswaA;
    *mahasiswaA = *mahasiswaB;
    *mahasiswaB = temp;
}

// Partisi untuk membantu procedure algorithm quicksort, sorting berdasarkan NIM.
int partition(mahasiswa Mahasiswa[], int mulai, int akhir){
    mahasiswa pivot = Mahasiswa[akhir];
    int i = (mulai - 1);

    for(int j = mulai; j <= akhir - 1; j++){
        if(strcmp(Mahasiswa[i].nim, pivot.nim) < 0){
            i++;
            swap(&Mahasiswa[i], &Mahasiswa[j]);
        }
    }
    swap(&Mahasiswa[i+1], &Mahasiswa[akhir]);
    return(i+1);
}

// Fungsi Algorithm utama untuk quicksort.
void quickSort(mahasiswa Mahasiswa[], int mulai, int akhir){
    if(mulai < akhir){
        int tengah = partition(Mahasiswa, mulai, akhir);
        quickSort(Mahasiswa, mulai, tengah - 1);
        quickSort(Mahasiswa, tengah + 1, akhir);
    }
}