#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 2501976503 - Fabian Habil Ramdhan - LB75 - SasukeExpress Assignment
// Algoritma Searching -> Binary Search
// Algoritma Sorting -> Quick Sort

// Deklarasi Struct dan Variabel Global.
// Struct untuk menyimpan data pelanggan dengan length 1000 data.
typedef struct pelanggan{
    char nama[50];
    char alamat[50];
    char nohp[50];
}Pelanggan;
Pelanggan pelanggan[1000];

// Variabel count untuk menghitung sekarang ada berapa jumlah data di database.
int count = 0;
// Variabel delete untuk menghitung ada berapa banyak data yang dihapus.
int delete = 0;

// Fungsi dan Prosedur prototype.
void menu();
void menuOption(unsigned short option);
void enterToContinue();
int validasiHP(char noHP[]);
int binarySearch(Pelanggan pelanggan[], char cari[], int mulai, int akhir);
void quickSort(Pelanggan pelanggan[], int mulai, int akhir);
int partition(Pelanggan pelanggan[], int mulai, int akhir);
void swap(Pelanggan *pelangganA, Pelanggan *pelangganB);
void entryNewData();
void printSemuaPelanggan();
void printSemuaAlamat();
void tambahAlamat();
void editPelanggan();
void deleteAlamat();
void printAlamat();

// Fungsi main untuk menjalankan program.
int main(){
    system("cls");

    /* Open file stream saat pertama kali menjalankan program, jika tidak ada file, maka akan dibuat
    dan jika masih error, mengeluarkan file tidak ditemukan.*/
    FILE *fp = fopen("database.data", "a");
    if(fp == NULL) printf("File tidak ditemukan!\n");
    fclose(fp);
    menu();
}

// Prosedur untuk menampilkan utama dan memilih fitur yang ada.
void menu(){
    unsigned short exit = 0;
    unsigned short option = 0;
    unsigned short valid = 0;
    do{
        // Output Menu
        puts("--------------------------------------");
        puts("|           Sasuke Express           |");
        puts("--------------------------------------");
        puts("| 1. Tambah Alamat                   |");
        puts("| 2. Edit Info Pelanggan             |");
        puts("| 3. Delete Alamat                   |");
        puts("| 4. Print Alamat                    |");
        puts("| 5. Exit                            |");
        puts("--------------------------------------");
        printf("Masukkan Pilihan: ");
        
        /* Mendapatkan Input dari user, valid akan menjadi 1 jika input user benar
        namun jika input user salah, valid akan menjadi 0 */
        valid = scanf("%hu", &option);
        getchar();

        // Jika input benar, maka akan dicek. 
        if(valid){
            // Jika diantara 1 dan 4 akan dihandle oleh procedure menuOption
            if(option >= 1 && option <=4){
                system("cls");
                menuOption(option);
            }
            // Jika option 5, maka akan keluar dari program.
            else if(option == 5){
                system("cls");
                puts("Terima kasih sudah menggunakan program ini!");
                puts("Dibuat oleh Fabian Habil - 2501976503");
                exit = 1;
            }
            // Jika input angka tetai masih salah, akan dikasih tau masih salah dan dipaksa untuk input lagi
            else{
                system("cls");
                puts("Input salah! silahkan coba lagi!");
            }
        }
        else{
            system("cls");
            puts("Input salah! silahkan coba lagi!");
        }
    }while(!exit);
}

// Prosedur untuk handle input dan switch ke fungsi menu sesuai input user.
void menuOption(unsigned short option){
    switch(option){
        case 1:
            tambahAlamat();
            break;
        case 2:
            editPelanggan();
            break;
        case 3:
            deleteAlamat();
            break;
        case 4:
            printAlamat();
            break;
    }
}

// Prosedur untuk membuat prompt agar user menekan enter terlebih dahulu lalu melanjutkan program.
void enterToContinue(){
    printf("Tekan Enter untuk melanjutkan..");
    getchar();
}

/* Fungsi untuk validasi Nomor hp, kita akan loop dari awal string sampai akhir
dan cek jika ada selain angka akan mereturn value 0 (false), namun jika tidak ditemukan
selain angka, akan mereturn value 1 (true) */
int validasiHP(char noHP[]){
    for(int i = 0; i < strlen(noHP); i++){
        if(noHP[i] >= '0' && noHP[i] <= '9'){
            continue;
        }
        else{
            return 0;
        }
    }
    return 1;
}

// Fungsi untuk mencari data, menggunakan Binary Search, jika tidak ditemukan maka akan return -1
int binarySearch(Pelanggan pelanggan[], char cari[], int mulai, int akhir){
    int tengah;
    while(mulai <= akhir){
        tengah = (mulai + akhir) / 2;
        if(strcmp(cari, pelanggan[tengah].nama) == 0){
            return tengah;
        }
        if(strcmp(cari, pelanggan[tengah].nama) < 0){
            akhir = tengah - 1;
        }
        if(strcmp(cari, pelanggan[tengah].nama) > 0){
            mulai = tengah + 1;
        }
    }
    return -1;
}

// Fungsi untuk swap struct
void swap(Pelanggan *pelangganA, Pelanggan *pelangganB){
    Pelanggan temp = *pelangganA;
    *pelangganA = *pelangganB;
    *pelangganB = temp;
}

// Fungsi untuk partisi dan sortir untuk quicksort
int partition(Pelanggan pelanggan[], int mulai, int akhir){
    Pelanggan pivot = pelanggan[akhir];
    int i = mulai - 1;

    // Sorting berdasarkan nama
    for(int j = mulai; j <= akhir - 1; j++){
        if(strcmp(pelanggan[j].nama, pivot.nama) < 0){
            i++;
            /* Jika dibandingkan nama index kiri lebih besar dari index kanan 
            sesuai ascii, maka diswap. */
            swap(&pelanggan[j], &pelanggan[i]);
        }
    }
    // Swap partisi yang belum disort dengan yang sudah disort.
    swap(&pelanggan[i+1], &pelanggan[akhir]);
    return (i + 1);
}

// Prosedur untuk quicksort dengan memanggil fungsi partition untuk nilai tengah dan sortir.
void quickSort(Pelanggan pelanggan[], int mulai, int akhir){
    if (mulai < akhir){
        int tengah = partition(pelanggan, mulai , akhir);
        quickSort(pelanggan, 0, tengah - 1);
        quickSort(pelanggan, tengah + 1, akhir);
    }
}

// Prosedur untuk Menambahkan Alamat.
void tambahAlamat(){
    // Deklarasi struct pelangganadd untuk pelanggan yang akan ditambah ke database.
    Pelanggan pelangganadd;
    
    // Open stream file menggunakan mode append.
    FILE *fp = fopen("database.data", "a");

    // Input nama pelanggan.
    printf("Silahkan masukkan data anda!\n");
    printf("Nama: ");
    scanf(" %[^\n]", pelangganadd.nama);
    getchar();

    // Input Nomor telefon pelanggan.
    printf("Silahkan masukkan Nomor telefon anda!\n");
    printf("Nomor telefon: ");
    scanf(" %s", pelangganadd.nohp);
    getchar();

    /* Melakukan validasi, jika input user ada huruf dan bukan angka, akan return 0
    Namun jika input sudah benar angka semua, akan return 1 */

    int validasihp = validasiHP(pelangganadd.nohp);

    // Ketika validasihp masih salah, user akan diminta input terus sampai benar.
    while(!validasihp){
        printf("Nomor telefon masih salah! Pastikan hanya angka!\n");
        printf("Nomor telefon: ");
        scanf(" %s", pelangganadd.nohp);
        getchar();

        // validasihp lagi dari input yang baru.
        validasihp = validasiHP(pelangganadd.nohp);
    }

    // Input alamat pelanggan.
    printf("Silahkan masukkan alamat anda!\n");
    printf("Alamat: ");
    scanf(" %[^\n]", pelangganadd.alamat);
    getchar();

    // Untuk memasukkan data yang sudah diinput user ke file "database.data"
    fprintf(fp, "%s#%s#%s\n", pelangganadd.nama, pelangganadd.nohp, pelangganadd.alamat);
    
    /* Untuk memberi tahu bahwa data berhasil dimasukkan ke user, 
     dan ada prompt enter untuk melanjutkan. */
    printf("Data berhasil dimasukkan!\n\n");
    enterToContinue();
    system("cls");

    // Menutup file stream.
    fclose(fp);
}

// Prosedur untuk edit data pelanggan
void editPelanggan(){
    char tempnama[50];

    // Open stream file menggunakan mode read dan mendeklarasikan ulang count menjadi 0
    FILE *fp = fopen("database.data", "r");

    // Mendeklarasikan ulang variabel count menjadi 0, karena akan membaca kembali dari file.
    count = 0;

    // Scan dari file dan memasukkan ke struct.
    while(!feof(fp)){
        fscanf(fp, " %[^#]#%[^#]#%[^\n]\n", pelanggan[count].nama, pelanggan[count].nohp, pelanggan[count].alamat);
        count++;
    }

    do{
        // Sort pelanggan berdasarkan nama agar bisa melakukan binary search 
        quickSort(pelanggan, 0, count - 1);

        // Print semua pelanggan menggunakan procedure printSemuaPelanggan
        printSemuaPelanggan();

        // Input nama yang akan diedit, lalu dicari menggunakan binary search
        printf("Silahkan masukkan nama yang akan diganti datanya!\n");
        printf("Ketik N untuk keluar!\n");
        printf("Input: ");
        scanf(" %[^\n]", tempnama);
        getchar();

        // Mendapatkan data tersebut di index berapa menggunakan binary search.
        int index = binarySearch(pelanggan, tempnama, 0, count);

        // Jika user input N maka akan keluar dari menu edit pelanggan.
        if(strcmp(tempnama, "N") == 0) break;

        /* Jika index nya di bawah 0, maka function binarySearch tidak menemukan data di struct
        maka akan terus meminta input dari user. */
        while(index < 0){
            system("cls");

            // Print semua pelanggan menggunakan procedure printSemuaPelanggan
            printSemuaPelanggan();

            // Input kembali nama yang akan dicari menggunakan binary search.
            printf("Data tidak ditemukkan! Silahkan masukkan nama yang ada dan sesuai!\n");
            printf("Ketik N untuk keluar!\n");
            printf("Nama yang akan diganti: ");
            scanf(" %[^\n]", tempnama);
            getchar();

            /* Jika input N, maka akan keluar dari pemilihan data yang akan dirubah
            dan akan kembali input data yang akan di ubah */
            if(strcmp(tempnama, "N") == 0){
                system("cls");
                break;
            }

            // Mendapatkan data tersebut di index berapa menggunakan binary search.
            index = binarySearch(pelanggan, tempnama, 0, count);
        }
        system("cls");

        /* Jika index nya di atas sama dengan 0, maka function binarySearch  menemukan data di struct
        maka akan melanjutkan meminta input apa yang akan diganti, namun jika tidak sesuai dengan
        perintah, akan terus mengulang. */
        while(index >= 0){
            printf("> Merubah Nilai %s\n\n", pelanggan[index].nama);
            char option[50];
            char diganti[50];

            // Input apakah akan mengganti nama atau no hp, jika input N akan keluar.
            // Jika masih salah, akan dipaksa untuk input sampai benar.
            printf("Pilih Data apa yang ingin diganti (Nama, No HP)\n");
            printf("Ketik N untuk keluar!\n");
            printf("Input: ");
            scanf(" %[^\n]", option);
            getchar();

            // Jika input N, maka akan keluar.
            if(strcmp(option, "N") == 0) {
                system("cls");
                break;
            }

            // Jika input nama atau no hp
            if(strcmp(option, "Nama") == 0 || strcmp(option, "No HP") == 0){

                /* Input user dimasukan ke variabel diganti, nantinya akan
                dicopy sesuai dengan input user */
                printf("Diganti menjadi? ");
                scanf(" %[^\n]", diganti);
                getchar();

                /* Jika input nama, copy string dari variabel diganti ke 
                struct pelanggan nama sesuai index */
                if(strcmp(option, "Nama") == 0){
                    strcpy(pelanggan[index].nama, diganti);
                }

                /* Jika input no hp, copy string dari variabel diganti ke 
                struct pelanggan no hp sesuai index */
                else if(strcmp(option, "No HP") == 0){
                    strcpy(pelanggan[index].nohp, diganti);
                }

                /* Untuk memberi tahu bahwa data berhasil diedit  
                dan ada prompt enter untuk melanjutkan lalu break dari loop. */
                printf("Data berhasil dirubah!\n");
                enterToContinue();
                system("cls");
                break;
            }
            else{
                // Jika input salah, maka akan dioutput kepada user.
                system("cls");
                printf("Input salah! Silahkan coba lagi!\n\n");
            }
        };
    }while(1);
    system("cls");

    // Menutup file stream.
    fclose(fp);

    // Write / timpa semua nilai yang ada di struct (sudah diganti) ke database.
    entryNewData();
}

// Prosedur Untuk delete alamat yang sudah sampai
void deleteAlamat(){
    int option = 0;
    int valid = 1;

    // Open file stream menggunakan mode read.
    FILE *fp = fopen("database.data", "r");

    // Mendeklarasikan ulang variabel delete dan count menjadi 0, karena akan membaca kembali dari file.
    delete = 0;
    count = 0;
    do{

        // Membaca ulang data dari file.
        while(!feof(fp)){
            fscanf(fp, " %[^#]#%[^#]#%[^\n]\n", pelanggan[count].nama, pelanggan[count].nohp, pelanggan[count].alamat);
            count++;
        }

        // Sort pelanggan berdasarkan nama agar bisa melakukan binary search 
        quickSort(pelanggan, 0, count - 1);

        // Output semua alamat agar user tau akan memilih yang mana.
        printSemuaAlamat();

        // Jika input tidak valid atau user memilih lebih dari range data, maka akan diberi tahu input salah.
        if(!valid || option > count) printf("Input Salah!\n");
        printf("Ingin Merubah Nomor berapa?\n");
        printf("Ketik 0 untuk keluar!\n");
        printf("Input: ");

        /* Mendapatkan Input dari user, valid akan menjadi 1 jika input user benar
        namun jika input user salah, valid akan menjadi 0 */
        // Input data mana yang akan dihapus menggunakan nomber yang dioutput di kode.
        valid = scanf("%d", &option);
        getchar();

        // Jika input benar, maka akan dicek.
        if(valid){
            
            // Jika input 0, maka akan keluar dari procedure.
            if(option == 0){
                break;
                system("cls");
            }
            else{
                // Jika input lebih besar dari data yang ada, akan meminta kembali input.
                if(option > count){
                    system("cls");
                }
                else{
                    /* Jika input Y, maka akan didelete, ide nya adalah mengganti value namanya menjadi "00NULL"
                    kenapa "00NULL" karena string tersebut jika disort akan muncul paling awal sehingga memudahkan kita nantinya
                    untuk menulis kembali data yang ada di struct ke file kita. Lalu kita increment variabel delete tadi.*/

                    /* Membuat loop jika user input Y maka akan delete, jika N untuk keluar. Namun jika selain keduanya, akan terus
                    meminta input dari user*/
                    while(1){
                        // Memberi prompt untuk user, Y untuk hapus N untuk cancel.
                        printf("\nAnda akan menghapus alamat %s\n", pelanggan[option-1].alamat);
                        printf("Anda Yakin? Y / N\n");
                        printf("Input: ");
                        char lanjut[5];
                        scanf("%s", lanjut);
                        getchar();
                        if(strcmp(lanjut, "Y") == 0){
                            strcpy(pelanggan[option-1].nama, "00NULL");
                            delete++;
                            printf("Alamat %s berhasil dihapus!\n", pelanggan[option-1].alamat);
                            break;
                        }
                        else if(strcmp(lanjut, "N") == 0){
                            break;
                        }
                        else{
                            system("cls");
                            printf("Input Salah!\n");
                        }
                    }
                    // Jika input N, maka akan keluar dari loop.
                    // Prompt Enter to Continue.
                    enterToContinue();
                    system("cls");
                }
            }
        }
        else{
            // Memberi tahu user jika input salah.
            printf("Input Salah!\n");
            system("cls");
        }
    }while(1);

    // Prompt Enter to Continue.
    enterToContinue();
    system("cls");

    /* Kita akan memasukkan data yang baru dari struct yang ada dan sudah dihapus ke file
    yang ada,*/
    fclose(fp);

    /* Write / timpa semua nilai yang ada di struct (sudah diganti) ke database.
    lalu kita declare ulang delete menjadi 0*/
    entryNewData();
    delete = 0;

    // Set semua struct menjadi 0 menggunakan memset.
    memset(pelanggan , 0, sizeof(pelanggan));
}

// Prosedur untuk menampilkan semua alamat
void printAlamat(){
    // Open file stream menggunakan mode read.
    FILE *fp = fopen("database.data", "r");
    
    // Mendeklarasikan ulang variabel count menjadi 0, karena akan membaca kembali dari file.
    count = 0;
    while(!feof(fp)){
        fscanf(fp, " %[^#]#%[^#]#%[^\n]\n", pelanggan[count].nama, pelanggan[count].nohp, pelanggan[count].alamat);
        count++;
    }

    // Sort pelanggan berdasarkan nama agar outputnya enak dilihat.
    quickSort(pelanggan, 0, count - 1);

    // Print semua pelanggan dan enter to continue setelahnya.
    printSemuaPelanggan();
    enterToContinue();
    system("cls");

    // Menutup file stream.
    fclose(fp);
}

// Prosedur untuk output semua data pelanggan yang ada di database.
void printSemuaPelanggan(){
    printf("---------------------------------------------------------------------------");
    printf("-------------------------");
    printf("\n");
    printf("| %-2s | %-20s | %-50s | %-15s |\n", "No", "Nama", "Alamat", "Nomor Telefon");
    printf("---------------------------------------------------------------------------");
    printf("-------------------------");
    printf("\n");

    // Output sebanyak data yang ada sampai variabel count
    for(int i = delete; i < count; i++){
        /* Terdapat edge case, jika di file tidak ada data sama sekali ternyata mendapatkan count = 1 karena "/0" 
        dan akan tetap membaca adanya data. Hal ini Membuat UX menjadi kurang karena tidak ada data di database tetapi
        tetap mengoutput tabel kosong. Maka kita akan cek, jika count nya 1, kita cek apakah ada value menggunakan strlen
        jika tidak ada data akan print "DATA MASIH KOSONG", namun jika ada data, akan print sebagai mana mestinya.*/
        if(count == 1){
            if(strlen(pelanggan[i].nama) > 0){
                printf("| %-2d | %-20s | %-50s | %-15s |\n", i+1, pelanggan[i].nama, pelanggan[i].alamat, pelanggan[i].nohp);
            }
            else{
                printf("\t\t\t\t\tDATA MASIH KOSONG!\n");
            }
        }
        else{
            printf("| %-2d | %-20s | %-50s | %-15s |\n", i+1, pelanggan[i].nama, pelanggan[i].alamat, pelanggan[i].nohp);
        }
    }
    printf("---------------------------------------------------------------------------");
    printf("-------------------------");
    printf("\n");
    printf("Total data yang tersedia %d\n", count - delete);
    printf("\n");
}

// Prosedur untuk output semua alamat yang ada di database.
void printSemuaAlamat(){
    printf("-----------------------------------------------------------");
    printf("\n");
    printf("| %-2s | %-50s |\n", "No", "Alamat");
    printf("-----------------------------------------------------------");
    printf("\n");

    // Output sebanyak data yang ada sampai variabel count
    for(int i = delete; i < count; i++){
        if(count == 1){
            if(strlen(pelanggan[i].nama) > 0){
                printf("| %-2d | %-50s |\n", i+1, pelanggan[i].alamat);
            }
            else{
                printf("\t\t    DATA MASIH KOSONG!\n");
            }
        }
        else{
            printf("| %-2d | %-50s |\n", i+1, pelanggan[i].alamat);
        }
    }
    printf("-----------------------------------------------------------\n");
    printf("Total data yang tersedia %d\n", count - delete);
    printf("\n");
}

// Setelah edit data, kita akan menulis kembali data tersebut di database.
void entryNewData(){
    // Open file stream menggunakan mode writing (menimpa seluruh data).
    FILE *fp = fopen("database.data", "w");

    /* Loop dari delete sampai count, kenapa dari delete? karena jika kita mempunyai 5 data dan
    delete 2 data, kita set data nama yang didelete menjadi "00NULL" dan disort, "00NULL" ini akan muncul
    di awal karena disort. Maka kita data yang akan ditulis kembali dari index 2, karena index 0 dan 1 akan dihapus dan
    mempunyai value "00NULL" maka karena dari itu kita memulai loop dari delete sampai count.*/
    for(int i = delete; i < count; i++){
        /* Terdapat edge case, jika di file tidak ada data sama sekali ternyata mendapatkan count = 1 karena "/0" 
        dan akan tetap menulis di file database ## tetapi tidak ada data. Hal ini membuat program kita crash. Maka
        cara mengatasinya adalah jika count nya 1, kita cek apakah ada value nama menggunakan strlen, jika ada data
        tidak melakukan apa apa, namun jika tidak ada data. maka kita continue sehingga loop selesai dan tidak akan 
        fprintf yang di bawahnya.*/
        
        /* Namun jika count 1 dan ada datanya, bisa saja data hanya ada satu dan kita akan hapus, 
        maka kita cek apakah itu akan dihapus atau tidak, jika iya, kita continue dan tidak akan kita tulis di file.
        Jika tidak, tidak melakukan apa apa.*/
        if(count == 1){
            if(strlen(pelanggan[i].nama) > 0){
                if(strcmp(pelanggan[i].nama, "00NULL") == 0) continue;
                else;
            }
            else continue;
        }
        fprintf(fp, "%s#%s#%s\n", pelanggan[i].nama, pelanggan[i].nohp, pelanggan[i].alamat);
    }
    fclose(fp);
}