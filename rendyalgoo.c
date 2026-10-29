#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_TRANSAKSI 10
#define JUMLAH_PERALATAN 5

typedef struct {
    char nama[100];
    int harga;
} Peralatan;

typedef struct {
    char namaPenyewa[100];
    int indeks;
    int jumlah;
    int hari;
    long long subtotal;
    long long diskon;
    long long total;
    int persenDiskon;
} Transaksi;

Peralatan alat[JUMLAH_PERALATAN] = {
    {"Tenda Kapasitas 4 Orang", 50000},
    {"Sleeping Bag", 15000},
    {"Kompor Portable", 20000},
    {"Matras Camping", 10000},
    {"Lampu Camping", 12000}
};

Transaksi riwayat[MAX_TRANSAKSI];
int jumlahTransaksi = 0;

int inputAngka(char pesan[], int min, int max) {
    char buffer[100];
    char *akhir;
    long angka;

    while (1) {
        printf("%s", pesan);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
            continue;

        angka = strtol(buffer, &akhir, 10);

        while (isspace((unsigned char)*akhir))
            akhir++;

        if (akhir == buffer || *akhir != '\0' ||
            angka < min || angka > max) {
            printf("Input tidak valid! Coba lagi.\n");
        } else {
            return (int)angka;
        }
    }
}

void tampilkanPeralatan(void) {
    int i;

    printf("\n========== DAFTAR PERALATAN ==========\n");

    for (i = 0; i < JUMLAH_PERALATAN; i++) {
        printf("%d. %-28s Rp%d/hari\n",
               i + 1, alat[i].nama, alat[i].harga);
    }
}

void tampilkanStruk(Transaksi t) {
    printf("\n========================================\n");
    printf("           ADVENTURE CAMP\n");
    printf("            STRUK PENYEWAAN\n");
    printf("========================================\n");
    printf("Nama Penyewa   : %s\n", t.namaPenyewa);
    printf("Peralatan      : %s\n", alat[t.indeks].nama);
    printf("Harga per Hari : Rp%d\n", alat[t.indeks].harga);
    printf("Jumlah Unit    : %d\n", t.jumlah);
    printf("Lama Sewa      : %d hari\n", t.hari);
    printf("----------------------------------------\n");
    printf("Subtotal       : Rp%lld\n", t.subtotal);
    printf("Diskon (%d%%)    : Rp%lld\n",
           t.persenDiskon, t.diskon);
    printf("----------------------------------------\n");
    printf("TOTAL BAYAR    : Rp%lld\n", t.total);
    printf("========================================\n");
}

void sewaPeralatan(void) {
    Transaksi t;
    int pilihan;
    int i;

    if (jumlahTransaksi >= MAX_TRANSAKSI) {
        printf("\nRiwayat transaksi sudah penuh!\n");
        return;
    }

    printf("\nNama penyewa: ");
    fgets(t.namaPenyewa, sizeof(t.namaPenyewa), stdin);
    t.namaPenyewa[strcspn(t.namaPenyewa, "\n")] = '\0';

    while (strlen(t.namaPenyewa) == 0) {
        printf("Nama tidak boleh kosong. Masukkan nama: ");
        fgets(t.namaPenyewa, sizeof(t.namaPenyewa), stdin);
        t.namaPenyewa[strcspn(t.namaPenyewa, "\n")] = '\0';
    }

    tampilkanPeralatan();

    pilihan = inputAngka("Pilih peralatan [1-5]: ", 1, 5);
    t.indeks = pilihan - 1;

    t.jumlah = inputAngka("Jumlah unit: ", 1, 1000000);
    t.hari = inputAngka("Lama sewa (hari): ", 1, 1000000);

    t.subtotal = (long long)alat[t.indeks].harga *
                 t.jumlah * t.hari;

    if (t.hari >= 5) {
        t.persenDiskon = 15;
    } else if (t.hari >= 3) {
        t.persenDiskon = 10;
    } else {
        t.persenDiskon = 0;
    }

    t.diskon = t.subtotal * t.persenDiskon / 100;
    t.total = t.subtotal - t.diskon;

    riwayat[jumlahTransaksi] = t;
    jumlahTransaksi++;

    tampilkanStruk(t);

    printf("Terima kasih telah menggunakan Adventure Camp!\n");
}

void tampilkanRiwayat(void) {
    int i;
    long long pendapatan = 0;

    printf("\n========== RIWAYAT TRANSAKSI ==========\n");

    if (jumlahTransaksi == 0) {
        printf("Belum ada transaksi penyewaan.\n");
        return;
    }

    for (i = 0; i < jumlahTransaksi; i++) {
        printf("\nTransaksi ke-%d\n", i + 1);
        printf("Nama      : %s\n",
               riwayat[i].namaPenyewa);
        printf("Peralatan : %s\n",
               alat[riwayat[i].indeks].nama);
        printf("Jumlah    : %d unit\n",
               riwayat[i].jumlah);
        printf("Lama sewa : %d hari\n",
               riwayat[i].hari);
        printf("Total     : Rp%lld\n",
               riwayat[i].total);

        pendapatan += riwayat[i].total;
    }

    printf("\nJumlah Transaksi : %d\n", jumlahTransaksi);
    printf("Total Pendapatan : Rp%lld\n", pendapatan);
}

int main(void) {
    int menu;

    do {
        printf("\n========================================\n");
        printf("           ADVENTURE CAMP\n");
        printf("      SISTEM PENYEWAAN PERALATAN\n");
        printf("========================================\n");
        printf("1. Lihat Daftar Peralatan\n");
        printf("2. Sewa Peralatan\n");
        printf("3. Lihat Riwayat Transaksi\n");
        printf("4. Keluar\n");
        printf("========================================\n");

        menu = inputAngka("Pilih menu [1-4]: ", 1, 4);

        switch (menu) {
            case 1:
                tampilkanPeralatan();
                break;

            case 2:
                sewaPeralatan();
                break;

            case 3:
                tampilkanRiwayat();
                break;

            case 4:
                printf("\nTerima kasih telah menggunakan "
                       "Adventure Camp!\n");
                break;
        }

    } while (menu != 4);

    return 0;
}
