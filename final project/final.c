/*  Kelompok 7 - lB75
    Fabian Habil Ramdhan - 2501976503
    Kadek Tania Taragita Yundra - 2501967461
    Muhammad Syauqi Frizman - 2501976453

    Class Management Program
    Sorting Algorithm menggunakan -> Quicksort
    Searching Algorithm menggunakan -> Binary Search
*/

#include <stdio.h>
#include <stdlib.h>
//buat handle string
#include <string.h> 

// Deklarasi Struct untuk mahasiswa
typedef struct database{
    char nim[100];
    char nama[100];
    int asg, mid, fin;
}Mahasiswa;

// adain variabel global count, buat ngecek ada berapa isi data yang di database
int count = 0;

// deklarasi struct sebanyak 1000 data
Mahasiswa mahasiswa[1000];

//menu header - Fabian
void menu();

//fitur pertama, add student - Tania
void addStudent();

//fitur kedua, entry score - Fabian
void entryScore();

//procedure bantuan untuk edit score - Fabian
void entrynewScore();

//fitur ketiga, tampilin data secara ascending - Syauqi
void showData();

//function algorithm binarysearch untuk search NIM - Fabian
int binarySearch(Mahasiswa mahasiswa[], char nim[], int kiri, int kanan);

//procedure algorithm quicksort untuk sorting secara ascending baik itu NIM, ASG, MID, atau FIN - Syauqi
void quickSort(Mahasiswa mahasiswa[], int mulai, int akhir, char tipe);

//function pembantu quicksort - Syauqi
int partition(Mahasiswa mahasiswa[], int mulai, int akhir, char tipe);

// Prosedur untuk swap 2 struct - Syauqi
void swap(Mahasiswa *mahasiswaA, Mahasiswa *mahasiswaB);

//procedure pause sebelum cls tampilan - Tania
void enterToContinue();

//procedure tampilin semua data - Tania
void output();

//procedure proses penginputan nilai ke dalam variabel - Fabian
void prosesInputNilai(int index, char tipe);

//procedure output khusus tapilin data mahasiswa yang dipilih - Tania
void outputNilai(int index);

//function main untuk menjalankan program - Fabian
int main(){
    system("cls");
    unsigned short exit = 0, option, valid;

    /* Open file stream saat pertama kali menjalankan program, jika tidak ada file, maka akan dibuat
    dan jika masih error, mengeluarkan file tidak ditemukan.*/
    FILE *fp = fopen("database.data", "a");
    if(fp == NULL) printf("File tidak ditemukan!\n");
    fclose(fp);

    //melakukan sorting ascending berdasarkan NIM
    quickSort(mahasiswa, 0, count, 'n');

    do{
        menu();
        printf("Pilih menu: ");
        valid = scanf("%hu", &option);
        getchar();

        // Validator Input
        if(valid){
            if(option == 0){
                system("cls");
                printf("Keluar...");
                exit = 1;
            }
            else if(option == 1){
                system("cls");
                addStudent();
            }
            else if(option == 2){
                system("cls");
                entryScore();
            }
            else if(option == 3){
                system("cls");
                showData();
            }
            else{
                system("cls");
                printf("Input invalid! Silahkan coba lagi!\n");
            }
        }
        else{
            system("cls");
            printf("Input invalid! Silahkan coba lagi!\n");
        }
    }while(!exit);
}

//hanya print header menu - Fabian
void menu(){
    printf("MENU PROGRAM\n");
    printf("1. Add Student\n");
    printf("2. Entry Score\n");
    printf("3. Show Data\n");
    printf("0. Exit\n");
    printf("=================\n");
}

//lakukan penambahan data baru ke dalam file "database.data" - Tania
void addStudent(){
    //deklarasi struct mahasiswa as mahasiswadd
    Mahasiswa mahasiswadd;

    //open stream serta menggunakan mode append
    FILE *fp = fopen("database.data", "a");

    //seragkaian baris kode meminta nilai untuk dimasukkan
    printf("Masukkan data anda\n");
    printf("==================\n");
    printf("NAME: ");
    scanf(" %[^\n]", mahasiswadd.nama);
    getchar();
    printf("NIM: ");
    scanf(" %s", mahasiswadd.nim);
    getchar();
    while(1){
        if(!(strlen(mahasiswadd.nim) <= 10)){
            printf("NIM Tidak boleh di atas 10 Karakter!\n");
            printf("NIM : ");
            scanf(" %s", mahasiswadd.nim);
            getchar();
        }
        else{
            break;
        }
    }
    //melakukan writing/printing nilai variable ke file "database.data"
    fprintf(fp, "%s#%s#%d#%d#%d\n", mahasiswadd.nama, mahasiswadd.nim, -1, -1, -1);
    fclose(fp);
    printf("Data sudah disimpan!\n");
    enterToContinue();
    system("cls");
}

// memasukkan input nilai ke dalam variable struct sementara - Fabian
void entryScore(){
    int exit = 0;
    char input_nim_opsi[100];
    char input_score_opsi[100];

    //file open mode read
    FILE *fp = fopen("database.data", "r");
    count = 0;
    
    //lakukan perulangan read/scanf hingga end of file, nilai akan di-assign ke masing-masing variable di struct
    while(!feof(fp)){
        fscanf(fp," %[^#]#%[^#]#%d#%d#%d\n", mahasiswa[count].nama, mahasiswa[count].nim, &mahasiswa[count].asg, &mahasiswa[count].mid, &mahasiswa[count].fin);
        count++;
    }

    //sorting ascending berdasarkan NIM
    quickSort(mahasiswa, 0, count-1, 'n');

    int index;

    // Loop hingga user input N dan keluar dari menu ini
    do{
        system("cls");
        
        //display semua data (sebelumnya sudah di-sorting ascending berdasarkan NIM)
        output();

        //memasukkan NIM
        printf("Silahkan pilih NIM siswa yang akan diubah!\n");
        printf("Ketik N untuk keluar!\n");
        printf("Input : ");
        scanf(" %s", input_nim_opsi);
        getchar();

        //if else variable input_nim_opsi
        //bila N maka keluar dari loop
        if(strcmp(input_nim_opsi, "N") == 0){
            exit = 1;
        }
        else{
            // Mencari index yang diinput user menggunakan binary search untuk diedit
            index = binarySearch(mahasiswa,  input_nim_opsi, 0, count);
            // Jika data tidak ditemukan
            if(index == -1){
                printf("Data tidak ditemukan! silahkan coba lagi\n");
                enterToContinue();
            }
            // Jika data ditemukan
            else{
                int exit_score = 0;
                do{
                    system("cls");
                    printf("| %-10s | %-30s | %-3s | %-3s | %-3s |\n", "NIM", "NAMA LENGKAP", "ASG", "MID", "FIN");
                    printf("%s\n", "-----------------------------------------------------------------");
                    
                    //memberikan validasi bahwa nama mahasiswa yang akan dirubah sudah sesuai NIM yang diinputkan
                    outputNilai(index);
                    printf("\n> Merubah nilai %s\n", mahasiswa[index].nama);

                    //memasukkan pilihan opsi score ASG/MID/FIN
                    printf("\nSilahkan pilih ASG atau MID atau FIN!\n");
                    printf("Ketik N untuk keluar!\n");
                    printf("Input : ");
                    scanf(" %s", input_score_opsi);
                    getchar();
                    if((strcmp(input_score_opsi, "ASG") == 0) || (strcmp(input_score_opsi, "MID") == 0) || (strcmp(input_score_opsi, "FIN") == 0) || (strcmp(input_score_opsi, "N") == 0)){
                        //jika N maka keluar dari loop
                        if(strcmp(input_score_opsi, "N") == 0){
                            exit_score = 1;
                        }
                        //memanggil procedure prosesInputNilai dengan argumen (index, 'a'), a -> asg, m -> mid, f -> fin
                        else if(strcmp(input_score_opsi, "ASG") == 0){
                            prosesInputNilai(index, 'a');
                        }
                        else if(strcmp(input_score_opsi, "MID") == 0){
                            prosesInputNilai(index, 'm');
                        }
                        else if(strcmp(input_score_opsi, "FIN") == 0){
                            prosesInputNilai(index, 'f');
                        }
                    }
                    else{
                        printf("Input salah! silahkan coba lagi!\n");
                    }
                }while(!exit_score);
                system("cls");
            }
        }
    }while(!exit);
    //close stream
    fclose(fp);
    
    //writing/timpa semua nilai yang ada pada struct
    entrynewScore();
    system("cls");
}

// Setelah edit data, kita akan menulis kembali data tersebut di database. - Fabian
void entrynewScore(){
    // Open file stream menggunakan mode writing (menimpa seluruh data).
    FILE *fp = fopen("database.data", "w");

   /* Loop dari 0 sampai count */
    for(int i = 0; i < count; i++){
        /* Terdapat edge case, jika di file tidak ada data sama sekali ternyata mendapatkan count = 1 karena "/0"
        dan akan tetap menulis di file database ## tetapi tidak ada data. Hal ini membuat program kita crash. Maka
        cara mengatasinya adalah jika count nya 1, kita cek apakah ada value nama menggunakan strlen, jika ada data
        tidak melakukan apa apa, namun jika tidak ada data. maka kita continue sehingga loop selesai dan tidak akan 
        fprintf yang di bawahnya.*/
        
        /* Namun jika count 1 dan ada datanya, bisa saja data hanya ada satu dan kita akan hapus, 
        maka kita cek apakah itu akan dihapus atau tidak, jika iya, kita continue dan tidak akan kita tulis di file.
        Jika tidak, tidak melakukan apa apa.*/
        if(count == 1){
            if(strlen(mahasiswa[i].nama) > 0);
            else continue;
        }
        fprintf(fp, "%s#%s#%d#%d#%d\n", mahasiswa[i].nama, mahasiswa[i].nim, mahasiswa[i].asg, mahasiswa[i].mid, mahasiswa[i].fin);
    }
    fclose(fp);
}

//menampilkan semua data yang ada pada "database.data" - Syauqi
void showData(){
    FILE *fp;
    fp = fopen("database.data", "r");
    if(fp == NULL){
        printf("File doesn't exist...");
        exit(1);
    }
    count = 0;

    //lakukan perulangan read/scanf hingga end of file, nilai akan di-assign ke masing-masing variable di struct
    while(!feof(fp)){
        fscanf(fp," %[^#]#%[^#]#%d#%d#%d\n",mahasiswa[count].nama, mahasiswa[count].nim, &mahasiswa[count].asg, &mahasiswa[count].mid, &mahasiswa[count].fin);
        count++;
    }

    //melakukan sorting ascending berdasarkan pilihan dari user
    char input_sorting[50];
    do{
        printf("Pilih pengurutan data (NIM, ASG, MID, or FIN)\n");
        printf("Ketik N untuk keluar!\n");
        printf("Input : ");
        scanf(" %[^\n]", input_sorting);
        getchar();

        if((strcmp(input_sorting, "NIM") == 0) || (strcmp(input_sorting, "ASG") == 0) || (strcmp(input_sorting, "MID") == 0) || (strcmp(input_sorting, "FIN") == 0) || (strcmp(input_sorting, "N") == 0)){
            if(strcmp(input_sorting, "N") == 0){
                break;
            }
            printf("Sorting berdasarkan %s!\n\n", input_sorting);
            //sorting ascending berdasarkan NIM
            if(strcmp(input_sorting, "NIM") == 0){
                quickSort(mahasiswa, 0, count-1, 'n');
                output();
            }
            //sorting ascending berdasarkan ASG
            else if(strcmp(input_sorting, "ASG") == 0){
                quickSort(mahasiswa, 0, count-1, 'a');
                output();
            }
            //sorting ascending berdasarkan MID
            else if(strcmp(input_sorting, "MID") == 0){
                quickSort(mahasiswa, 0, count-1, 'm');
                output();
            }
            //sorting ascending berdasarkan FIN
            else if(strcmp(input_sorting, "FIN") == 0){
                quickSort(mahasiswa,0, count-1, 'f');
                output();
            }
            enterToContinue();
            system("cls");
        }
        else{
            system("cls");
            printf("Input invalid! Silahkan coba lagi!\n");
        }
    }while(1);
    enterToContinue();
    system("cls");
    fclose(fp);
}

// algorithm search NIM - Fabian
int binarySearch(Mahasiswa mahasiswa[], char nim[], int kiri, int kanan){
    int tengah;
    while(kiri <= kanan){
        tengah = (kiri + kanan) / 2;
        if(strcmp(nim, mahasiswa[tengah].nim) == 0){
            return tengah;
        }
        if(strcmp(nim, mahasiswa[tengah].nim) < 0){
            kanan = tengah - 1;
        }
        if(strcmp(nim, mahasiswa[tengah].nim) > 0){
            kiri = tengah + 1;
        }
    }
    return -1;
}

// Prosedur untuk swap 2 struct - Syauqi
void swap(Mahasiswa *mahasiswaA, Mahasiswa *mahasiswaB){
    Mahasiswa temp = *mahasiswaA;
    *mahasiswaA = *mahasiswaB;
    *mahasiswaB = temp;
}

// Partisi buat pembantu procedure algorithm quicksort, sorting berdasarkan tipe yang dipilih oleh user - Syauqi
int partition(Mahasiswa mahasiswa[], int mulai, int akhir, char tipe){
    Mahasiswa pivot = mahasiswa[akhir];
    int i  = (mulai - 1);

    //sorting ascending berdasarkan NIM
    if(tipe == 'n'){
        for(int j = mulai; j <= akhir - 1; j++){
            if(strcmp(mahasiswa[j].nim, pivot.nim) < 0){
                i++;
                swap(&mahasiswa[i], &mahasiswa[j]);
            }
        }
    }
    //sorting ascending berdasarkan ASG
    else if(tipe == 'a'){
        for(int j = mulai; j <= akhir - 1; j++){
            if(mahasiswa[j].asg < pivot.asg){
                i++;
                swap(&mahasiswa[i], &mahasiswa[j]);
            }
        }
    }
    //sorting ascending berdasarkan MID
    else if(tipe == 'm'){
        for(int j = mulai; j <= akhir - 1; j++){
            if(mahasiswa[j].mid < pivot.mid){
                i++;
                swap(&mahasiswa[i], &mahasiswa[j]);
            }
        }
    }
    //sorting ascending berdasarkan FIN
    else if(tipe == 'f'){
        for(int j = mulai; j <= akhir - 1; j++){
            if(mahasiswa[j].fin < pivot.fin){
                i++;
                swap(&mahasiswa[i], &mahasiswa[j]);
            }
        }
    }
    swap(&mahasiswa[i + 1], &mahasiswa[akhir]);
    return(i+1);
}

// algorithm utama quicksort - Syauqi
void quickSort(Mahasiswa mahasiswa[], int mulai, int akhir, char tipe){
    if(mulai < akhir){
        int tengah = partition(mahasiswa, mulai, akhir, tipe);
        quickSort(mahasiswa, mulai, tengah - 1, tipe);
        quickSort(mahasiswa, tengah + 1, akhir, tipe);
    }
}

// Prompt enter to continue, user harus menekan enter untuk melanjutkan - Tania
void enterToContinue(){
    printf("Tekan Enter untuk melanjutkan...");
    getchar();
}

/* procedure tampilin semua data yang ada pada variabel struct mahasiswa
data ditampilkan sesuai pilihan dari user (sorting NIM/ASG/MID/FIN) - Tania */
void output(){
    printf("%s\n", "-----------------------------------------------------------------");
    printf("| %-10s | %-30s | %-3s | %-3s | %-3s |\n", "NIM", "NAMA LENGKAP", "ASG", "MID", "FIN");
    printf("%s\n", "-----------------------------------------------------------------");

    // Output sebanyak data yang ada sampai variabel count
    for(int i = 0; i < count; i++){
       /* Terdapat edge case, jika di file tidak ada data sama sekali ternyata mendapatkan count = 1 karena "/0" 
        dan akan tetap membaca adanya data. Hal ini Membuat UX menjadi kurang karena tidak ada data di database tetapi
        tetap mengoutput tabel kosong. Maka kita akan cek, jika count nya 1, kita cek apakah ada value menggunakan strlen, jika tidak ada data akan print "DATA MASIH KOSONG", namun jika ada data, akan print sebagai mana mestinya.*/
        if(count == 1){
            if(strlen(mahasiswa[i].nama) > 0){
                printf("| %-10s | %-30s | ", mahasiswa[i].nim, mahasiswa[i].nama);
                if(mahasiswa[i].asg == -1){
                    printf("%-3s | ", "N/A");
                }else{
                    printf("%-3d | ", mahasiswa[i].asg);
                }
                
                if(mahasiswa[i].mid == -1){
                    printf("%-3s | ", "N/A");
                }else{
                    printf("%-3d | ", mahasiswa[i].mid);
                }

                if(mahasiswa[i].fin == -1){
                    printf("%-3s |\n", "N/A");
                }else{
                    printf("%-3d |\n", mahasiswa[i].fin);
                }
            }
            else{
                printf("\t\t\t Data masih kosong\n");
            }
        }
        else{
            printf("| %-10s | %-30s | ", mahasiswa[i].nim, mahasiswa[i].nama);
            if(mahasiswa[i].asg == -1){
                printf("%-3s | ", "N/A");
            }else{
                printf("%-3d | ", mahasiswa[i].asg);
            }
                
            if(mahasiswa[i].mid == -1){
                printf("%-3s | ", "N/A");
            }else{
                printf("%-3d | ", mahasiswa[i].mid);
            }

            if(mahasiswa[i].fin == -1){
                printf("%-3s |\n", "N/A");
            }else{
                printf("%-3d |\n", mahasiswa[i].fin);
            }
        }
    }
    printf("%s\n", "-----------------------------------------------------------------");
    if(count == 1){
        if(strlen(mahasiswa[0].nama) > 0){
            printf("Total data tersedia: %d\n\n", count);
        }
        else{
            printf("Total data tersedia: %d\n\n", count - 1);
        }
    }
    else{
        printf("Total data tersedia: %d\n\n", count);
    }
}

/* Procedure untuk melakukan proses assigning (pemindahan) nilai sementara ke variabel struct. Dibuatkan
procedure agar tidak dilakukan penulisan kode yang berulang2 - Fabian */ 
void prosesInputNilai(int index, char tipe){
    int nilaitemp;
    printf("Silahkan masukkan nilainya: ");
    scanf("%d", &nilaitemp);
    getchar();
    //ASG
    if(tipe == 'a'){
        mahasiswa[index].asg = nilaitemp;
    }
    //MID
    else if(tipe == 'm'){
        mahasiswa[index].mid = nilaitemp;
    }
    //FIN
    else if(tipe == 'f'){
        mahasiswa[index].fin = nilaitemp;
    }
    //panggil procedure outputNilai agar menampilkan data yang hanya mahasiswa terkait saja
    outputNilai(index);
}

//panggil procedure outputNilai agar menampilkan data yang hanya mahasiswa terkait saja - Tania
void outputNilai(int index){
    printf("| %-10s | %-30s | ", mahasiswa[index].nim, mahasiswa[index].nama);
    if(mahasiswa[index].asg == -1){
        printf("%-3s | ", "N/A");
    }
    else{
        printf("%-3d | ", mahasiswa[index].asg);
    }
    if(mahasiswa[index].mid == -1){
        printf("%-3s | ", "N/A");
    }
    else{
        printf("%-3d | ", mahasiswa[index].mid);
    }
    if(mahasiswa[index].fin == -1){
        printf("%-3s | \n", "N/A");
    }
    else{
        printf("%-3d | \n", mahasiswa[index].fin);
    }
}