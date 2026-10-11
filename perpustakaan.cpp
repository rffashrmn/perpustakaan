#include <iostream>
using namespace std;

const int biayaSewaPerHari = 1000;

struct Buku {
    int id;
    string judul;
    string penulis;
    bool dipinjam = false;
};

bool CekId(Buku* daftarBuku, int jumlahBuku, int idCari) {
    for (int i = 0; i < jumlahBuku; i++) {
        if (daftarBuku[i].id == idCari) {
            return true;
        }
    }
    return false;
}

void inputBuku(Buku*& daftarBuku, int &jumlahBuku) {
    int jumlahInput;
    cout << "\nBerapa jumlah buku yang ingin diinput? ";
    cin >> jumlahInput;

    if (jumlahInput <= 0) {
        cout << "Jumlah input harus lebih dari 0\n";
        return;
    }

    int ukuranBaru = jumlahBuku + jumlahInput;
    Buku* daftarBaru = new Buku[ukuranBaru];

    for (int i = 0; i < jumlahBuku; i++) {
        daftarBaru[i] = daftarBuku[i];
    }

    for (int i = jumlahBuku; i < ukuranBaru; i++) {
        cout << "\n--- Data Buku Ke-" << (i + 1) << " ---\n";
        
        int idTemp;
        bool idValid = false;

        do {
            cout << "Masukkan ID Buku (Angka > 0) : ";
            if (cin >> idTemp) {
                if (idTemp > 0 && !CekId(daftarBaru, i, idTemp)) {
                    idValid = true;
                } else if (CekId(daftarBaru, i, idTemp)) {
                    cout << "ID " << idTemp << " sudah digunakan! Masukkan ID lain\n\n";
                }
            }
        } while (!idValid);

        daftarBaru[i].id = idTemp;

        cin.ignore();

        cout << "Masukkan Judul Buku         : ";
        getline(cin, daftarBaru[i].judul);

        cout << "Masukkan Nama Penulis       : ";
        getline(cin, daftarBaru[i].penulis);

        daftarBaru[i].dipinjam = false;
    }

    delete[] daftarBuku;
    daftarBuku = daftarBaru;
    jumlahBuku = ukuranBaru;

    cout << "\n" << jumlahInput << " Data buku berhasil ditambahkan\n";
}

void urutkanBuku(Buku* daftarBuku, int jumlahBuku) {
    for (int i = 0; i < jumlahBuku - 1; i++) {
        for (int j = 0; j < jumlahBuku - 1 - i; j++) {
            if (daftarBuku[j].id > daftarBuku[j + 1].id) {
                Buku temp = daftarBuku[j];
                daftarBuku[j] = daftarBuku[j + 1];
                daftarBuku[j + 1] = temp;
            }
        }
    }
}

void tampilBuku(Buku* daftarBuku, int jumlahBuku) {
    if (jumlahBuku == 0) {
        cout << "\nBelum ada data buku. Silakan input buku terlebih dahulu\n";
        return;
    }

    cout << "\n=======================================================\n";
    cout << "                  DAFTAR BUKU PERPUSTAKAAN             \n";
    cout << "=======================================================\n";
    for (int i = 0; i < jumlahBuku; i++) {
        cout << "ID       : " << daftarBuku[i].id << "\n";
        cout << "Judul    : " << daftarBuku[i].judul << "\n";
        cout << "Penulis  : " << daftarBuku[i].penulis << "\n";
        cout << "Status   : " << (daftarBuku[i].dipinjam ? "[Dipinjam]" : "[Tersedia]") << "\n";
        cout << "-------------------------------------------------------\n";
    }
}

void pinjamBuku(Buku* daftarBuku, int jumlahBuku) {
    if (jumlahBuku == 0) {
        cout << "\nBelum ada buku yang tersedia\n";
        return;
    }

    int idCari;
    cout << "\nMasukkan ID Buku yang ingin dipinjam: ";
    cin >> idCari;

    bool ditemukan = false;
    for (int i = 0; i < jumlahBuku; i++) {
        if (daftarBuku[i].id == idCari) {
            ditemukan = true;
            if (daftarBuku[i].dipinjam) {
                cout << "\nMaaf, buku ini sedang dipinjam\n";
            } else {
                daftarBuku[i].dipinjam = true;

                cout << "\n=======================================\n";
                cout << "            RESI PEMINJAMAN            \n";
                cout << "=======================================\n";
                cout << "ID Buku        : " << daftarBuku[i].id << "\n";
                cout << "Judul Buku     : " << daftarBuku[i].judul << "\n";
                cout << "Penulis        : " << daftarBuku[i].penulis << "\n";
                cout << "Tarif Sewa     : Rp " << biayaSewaPerHari << " / hari\n";
                cout << "Status         : Berhasil Dipinjam\n";
                cout << "=======================================\n";
            }
            break;
        }
    }

    if (!ditemukan) {
        cout << "\nBuku dengan ID " << idCari << " tidak ditemukan\n";
    }
}

void kembalikanBuku(Buku* daftarBuku, int jumlahBuku) {
    if (jumlahBuku == 0) {
        cout << "\nBelum ada buku di perpustakaan\n";
        return;
    }

    int idCari;
    cout << "\nMasukkan ID Buku yang ingin dikembalikan: ";
    cin >> idCari;

    bool ditemukan = false;
    for (int i = 0; i < jumlahBuku; i++) {
        if (daftarBuku[i].id == idCari) {
            ditemukan = true;
            if (!daftarBuku[i].dipinjam) {
                cout << "\nBuku ini sedang tidak dipinjam\n";
            } else {
                int lamaSewa;
                
                do {
                    cout << "Masukkan lama peminjaman (dalam hari): ";
                    cin >> lamaSewa;

                    if (lamaSewa < 0) {
                        cout << "Lama peminjaman tidak bisa kurang dari 0 hari\n\n";
                    }
                } while (lamaSewa < 0);

                int totalBiaya = lamaSewa * biayaSewaPerHari;

                cout << "\n=======================================\n";
                cout << "           RESI PENGEMBALIAN           \n";
                cout << "=======================================\n";
                cout << "ID Buku        : " << daftarBuku[i].id << "\n";
                cout << "Judul Buku     : " << daftarBuku[i].judul << "\n";
                cout << "Lama Sewa      : " << lamaSewa << " Hari\n";
                cout << "Tarif          : Rp " << biayaSewaPerHari << " / hari\n";
                cout << "---------------------------------------\n";
                if (lamaSewa == 0) {
                    cout << "TOTAL BIAYA    : Rp 0 (Gratis)\n";
                } else {
                    cout << "TOTAL BIAYA    : Rp " << totalBiaya << "\n";
                }
                cout << "=======================================\n";

                daftarBuku[i].dipinjam = false;
                cout << "Buku berhasil dikembalikan\n";
            }
            break;
        }
    }

    if (!ditemukan) {
        cout << "\nBuku dengan ID " << idCari << " tidak ditemukan\n";
    }
}

int main() {
    Buku* daftarBuku = nullptr;
    int jumlahBuku = 0;
    int pilihan;

    do {
        cout << "\n=== SISTEM MANAJEMEN PERPUSTAKAAN ===\n";
        cout << "1. Input Data Buku\n";
        cout << "2. Tampilkan & Urutkan Buku (by ID)\n";
        cout << "3. Pinjam Buku\n";
        cout << "4. Kembalikan Buku & Hitung Biaya Sewa\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu (1-5): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                inputBuku(daftarBuku, jumlahBuku);
                break;
            case 2:
                urutkanBuku(daftarBuku, jumlahBuku);
                tampilBuku(daftarBuku, jumlahBuku);
                break;
            case 3:
                pinjamBuku(daftarBuku, jumlahBuku);
                break;
            case 4:
                kembalikanBuku(daftarBuku, jumlahBuku);
                break;
            case 5:
                break;
            default:
                cout << "\nPilihan tidak valid. Silakan pilih menu 1-5\n";
        }
    } while (pilihan != 5);

    return 0;
}