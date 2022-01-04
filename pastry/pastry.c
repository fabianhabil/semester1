#include <stdio.h>
#include <stdlib.h>

//  2501976503 - Fabian Habil Ramdhan - Pastry Program - LB75
long long int jumlahtagihan = 0;

void enterToContinue(){
    getchar();
    printf("Tekan Enter untuk melanjutkan");
    getchar();
}

void kasir(){
    long long int bayar = 0;
    unsigned short option = 0;
    unsigned short valid = 0;
    unsigned short exit = 0;
    do{
        puts("--------------------------------------");
        puts("|               Kasir                |");
        puts("--------------------------------------");
        puts("| 1. Bayar                           |");
        puts("| 2. Exit                            |");
        puts("--------------------------------------");
        printf("Total belanja sekarang : Rp%lld\n", jumlahtagihan);
        printf("Masukkan Pilihan : ");
        valid = scanf("%hu", &option);
        getchar();
        system("cls");
        if(valid == 1 && (option >= 1 && option <= 2)){
            if(option == 1){
                if(jumlahtagihan == 0){
                    printf("Jumlah total belanja anda masih 0, silakan belanja dahulu!\n");
                }
                else{
                    printf("Jumlah total belanja anda sekarang adalah = Rp%lld\n", jumlahtagihan);
                    printf("Silahkan masukkan jumlah uang yang akan anda bayarkan : Rp");
                    scanf("%lld", &bayar);
                    jumlahtagihan -= bayar;
                    if(jumlahtagihan > 0){
                        printf("Jumlah total belanja anda sekarang adalah = Rp%lld\n", jumlahtagihan);
                    }
                    else{
                        printf("Total belanja sudah dibayar semua! Kembalian anda adalah : Rp%lld\n", jumlahtagihan * -1);
                        jumlahtagihan = 0;
                    }
                    enterToContinue();
                }
            }
            if(option == 2){
                exit = 1;
            }
        }
        else{
            printf("Menu tidak ditemukkan!, Silahkan coba lagi!\n");
        }
    }while(!exit);
}

void menuMinuman(){
    unsigned short exit = 0;
    unsigned short option = 0;
    int howmany = 0;
    unsigned short valid = 0;
    do{
        puts("--------------------------------------");
        puts("|            Menu Minuman            |");
        puts("--------------------------------------");
        puts("| 1. Espresso (18000)                |");
        puts("| 2. Cafe Latte (25000)              |");
        puts("| 3. Cappuccino (25000)              |");
        puts("| 4. Exit                            |");
        puts("--------------------------------------");
        printf("Total belanja sekarang : Rp%lld\n", jumlahtagihan);
        printf("Masukkan Pilihan : ");
        valid = scanf("%hu", &option);
        getchar();
        system("cls");
        if((option >= 1 && option <= 4) && valid == 1){
            if(option == 1){
                printf("Espresso (18000) dipilih, berapa banyak? "); scanf("%d", &howmany);
                jumlahtagihan = jumlahtagihan + (howmany * 18000);
                printf("Total belanja sekarang : Rp%lld\n", jumlahtagihan);
                enterToContinue();
                system("cls");
            }
            else if(option == 2){
                printf("Cafe Latte (25000) dipilih, berapa banyak? "); scanf("%d", &howmany);
                jumlahtagihan = jumlahtagihan + (howmany * 25000);
                printf("Total belanja sekarang : Rp%lld\n", jumlahtagihan);
                enterToContinue();
                system("cls");
            }
            else if(option == 3){
                printf("Cappuccino (25000) dipilih, berapa banyak? "); scanf("%d", &howmany);
                jumlahtagihan = jumlahtagihan + (howmany * 25000);
                printf("Total belanja sekarang : Rp%lld\n", jumlahtagihan);
                enterToContinue();
                system("cls");
            }
            else if(option == 4){
                exit = 1;
            }
        }
        else{
            printf("Menu tidak ditemukan, silahkan coba lagi!\n");
        }
    } while(!exit);
}

void menuMakanan(){
    unsigned short exit = 0;
    unsigned short option = 0;
    int howmany = 0;
    unsigned short valid = 0;
    do{
        puts("--------------------------------------");
        puts("|            Menu Makanan            |");
        puts("--------------------------------------");
        puts("| 1. Croissant Almond (25000)        |");
        puts("| 2. Smoke Beef Croissant (27500)    |");
        puts("| 3. Croffle (27000)                 |");
        puts("| 4. Apple Buff (22000)              |");
        puts("| 5. Pie Apple (25000)               |");
        puts("| 6. Exit                            |");
        puts("--------------------------------------");
        printf("Total belanja sekarang : Rp%lld\n", jumlahtagihan);
        printf("Masukkan Pilihan : ");
        valid = scanf("%hu", &option);
        getchar();
        system("cls");
        if((option >= 1 && option <= 6) && valid == 1){
            if(option == 1){
                printf("Croissant Almond (25000) dipilih, berapa banyak? "); scanf("%d", &howmany);
                jumlahtagihan = jumlahtagihan + (howmany * 25000);
                printf("Total belanja sekarang : Rp%lld\n", jumlahtagihan);
                enterToContinue();
                system("cls");
            }
            else if(option == 2){
                printf("Smoke Beef Croissant (27500) dipilih, berapa banyak? "); scanf("%d", &howmany);
                jumlahtagihan = jumlahtagihan + (howmany * 27500);
                printf("Total belanja sekarang : Rp%lld\n", jumlahtagihan);
                enterToContinue();
                system("cls");
            }
            else if(option == 3){
                printf("Croffle (27000) dipilih, berapa banyak? "); scanf("%d", &howmany);
                jumlahtagihan = jumlahtagihan + (howmany * 27000);
                printf("Total belanja sekarang : Rp%lld\n", jumlahtagihan);
                enterToContinue();
                system("cls");
            }
            else if(option == 4){
                printf("Apple Buff (22000) dipilih, berapa banyak? "); scanf("%d", &howmany);
                jumlahtagihan = jumlahtagihan + (howmany * 22000);
                printf("Total belanja sekarang : Rp%lld\n", jumlahtagihan);
                enterToContinue();
                system("cls");
            }
            else if(option == 5){
                printf("Pie Apple (25000) dipilih, berapa banyak? "); scanf("%d", &howmany);
                jumlahtagihan = jumlahtagihan + (howmany * 25000);
                printf("Total belanja sekarang : Rp%lld\n", jumlahtagihan);
                enterToContinue();
                system("cls");
            }
            else if(option == 6){
                exit = 1;
            }
        }
        else{
            printf("Menu tidak ditemukan, silahkan coba lagi!\n");
        }
    } while(!exit);
}

void menuOption(unsigned short option){
    switch(option){
        case 1:
            menuMakanan();
            break;
        case 2:
            menuMinuman();
            break;
        case 3:
            kasir();
            break;
    }
}

void menu(){
    unsigned short exit = 0;
    unsigned short option = 0;
    unsigned short valid = 0;
    do{
        puts("--------------------------------------");
        puts("|         Toko Pastry Maria          |");
        puts("|  1. Menu Makanan                   |");
        puts("|  2. Menu Minuman                   |");
        puts("|  3. Kasir                          |");
        puts("|  4. Keluar                         |");
        puts("--------------------------------------");
        printf("Total belanja sekarang : Rp%lld\n", jumlahtagihan);
        printf("Masukkan Pilihan : "); 
        valid = scanf("%hu", &option);
        getchar();
        if(valid == 1){
            switch(option){
                case 1:
                    system("cls");
                    menuOption(option);
                    break;
                case 2:
                    system("cls");
                    menuOption(option);
                    break;
                case 3:
                    system("cls");
                    menuOption(option);
                    break;
                case 4:
                    if(jumlahtagihan > 0){
                        system("cls");
                        puts("Tagihan belum dibayar! Silahkan bayar dahulu di kasir!");
                    }
                    else{ 
                        puts("Terima kasih sudah berkunjung!");
                        exit = 1;
                    }
                    break;
                default:
                    system("cls");
                    puts("Input Salah! silahkan coba lagi!");
            }
        }
        else{
            system("cls");
            puts("Input Salah! silahkan coba lagi!");
        }
    } while(exit != 1);
}

int main(){
    menu();
}