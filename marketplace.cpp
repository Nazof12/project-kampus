#include <iostream>
#include <iomanip>
#include <string>
#include <fstream> 

using namespace std;

const string FILE_AKUN = "database_user.txt";

struct Barang {
    string nama;
    int jumlah;
    double hargaSatuan;
    double subTotal;
};

// ==========================================
// FITUR AUTENTIKASI (LOGIN & REGISTRASI)
// ==========================================

// Fungsi untuk mengecek apakah file akun ada dan memiliki data
bool cekAkunTerdaftar() {
    ifstream file(FILE_AKUN);
    if (!file) return false;

    string u, p;
    if (file >> u >> p) {
        return true;
    }
    return false;
}

// Fungsi untuk registrasi pembuatan akun baru
void registrasiAkun() {
    ofstream file(FILE_AKUN);
    string username, password;

    cout << "==================================================" << endl;
    cout << "               HALAMAN REGISTRASI                 " << endl;
    cout << "==================================================" << endl;
    cout << "Buat Username (Tanpa Spasi) : "; cin >> username;
    cout << "Buat Password (Tanpa Spasi) : "; cin >> password;

    file << username << " " << password;
    file.close();

    cout << "\nRegistrasi Berhasil! Akun Anda disimpan secara permanen." << endl;
    cout << "Tekan Enter untuk kembali...";
    cin.ignore(); cin.get();
    system("cls");
}

// Fungsi proses validasi login dengan batasan 3x percobaan
bool prosesLogin() {
    if (!cekAkunTerdaftar()) {
        cout << "Error: Belum ada akun yang terdaftar! Silakan registrasi terlebih dahulu.\n" << endl;
        cout << "Tekan Enter untuk kembali...";
        cin.ignore(); cin.get();
        system("cls");
        return false;
    }

    ifstream file(FILE_AKUN);
    string usernameTerdaftar, passwordTerdaftar;
    string inputUser, inputPass;

    file >> usernameTerdaftar >> passwordTerdaftar;
    file.close();

    int percobaan = 3;
    while (percobaan > 0) {
        cout << "==================================================" << endl;
        cout << "               HALAMAN LOGIN USER                 " << endl;
        cout << "==================================================" << endl;
        cout << "Masukkan Username : "; cin >> inputUser;
        cout << "Masukkan Password : "; cin >> inputPass;

        if (inputUser == usernameTerdaftar && inputPass == passwordTerdaftar) {
            cout << "\nLogin Sukses! Selamat datang, " << inputUser << ".\n" << endl;
            cout << "Tekan Enter untuk masuk ke Marketplace...";
            cin.ignore(); cin.get();
            system("cls");
            return true;
        }
        else {
            percobaan--;
            system("cls");
            if (percobaan > 0) {
                cout << "Username atau Password salah! Sisa percobaan: " << percobaan << "\n" << endl;
            }
            else {
                cout << "Akses Ditolak! Anda salah memasukkan password sebanyak 3 kali.\n" << endl;
                cout << "Tekan Enter untuk kembali ke menu awal...";
                cin.ignore(); cin.get();
                system("cls");
            }
        }
    }
    return false;
}

// ==========================================
// FUNCTIONS FOR CHECKOUT SYSTEM
// ==========================================
double hitungTotal(Barang daftar[], int jumlahBarang) {
    double total = 0;
    for (int i = 0; i < jumlahBarang; i++) {
        daftar[i].subTotal = daftar[i].jumlah * daftar[i].hargaSatuan;
        total += daftar[i].subTotal;
    }
    return total;
}

void tampilkanRincian(Barang daftar[], int jumlahBarang, double total, double diskon, double pajak, double totalAkhir) {
    cout << "\n==============================================" << endl;
    cout << "               RINCIAN BELANJA                " << endl;
    cout << "==============================================" << endl;
    cout << left << setw(22) << "Nama Barang"
        << setw(8) << "Jumlah"
        << setw(15) << "Harga Satuan"
        << "Subtotal" << endl;
    cout << "----------------------------------------------" << endl;

    for (int i = 0; i < jumlahBarang; i++) {
        cout << left << setw(22) << (daftar[i].nama.length() > 20 ? daftar[i].nama.substr(0, 17) + "..." : daftar[i].nama)
            << setw(8) << daftar[i].jumlah
            << "Rp " << setw(12) << fixed << setprecision(0) << daftar[i].hargaSatuan
            << "Rp " << fixed << setprecision(0) << daftar[i].subTotal << endl;
    }

    cout << "----------------------------------------------" << endl;
    cout << left << setw(30) << "Total Sebelum Diskon :" << "Rp " << fixed << setprecision(0) << total << endl;
    cout << left << setw(30) << "Diskon (10% jika >= 500rb) :" << "Rp " << fixed << setprecision(0) << diskon << endl;
    cout << left << setw(30) << "Pajak 10% :" << "Rp " << fixed << setprecision(0) << pajak << endl;
    cout << left << setw(30) << "TOTAL AKHIR :" << "Rp " << fixed << setprecision(0) << totalAkhir << endl;
    cout << "==============================================" << endl;
}

void prosesPembayaran(double totalAkhir) {
    double bayar, kembalian;
    cout << "\nMasukkan jumlah uang dibayar: Rp ";
    cin >> bayar;

    while (bayar < totalAkhir) {
        cout << "Uang kurang! Masukkan lagi: Rp ";
        cin >> bayar;
    }

    kembalian = bayar - totalAkhir;
    cout << "Pembayaran berhasil!" << endl;
    cout << "Kembalian Anda: Rp " << fixed << setprecision(0) << kembalian << endl;
}

// ==========================================
// MAIN PROGRAM
// ==========================================
int main() {
    int menuAwal;
    bool loginSukses = false;

    // LOOP MENU UTAMAA AUTENTIKASI (LOGIN/REGIS)
    do {
        cout << "==================================================" << endl;
        cout << "            SELAMAT DATANG DI APP TOKO            " << endl;
        cout << "==================================================" << endl;
        cout << "1. Login" << endl;
        cout << "2. Registrasi Akun Baru" << endl;
        cout << "3. Keluar Aplikasi" << endl;
        cout << "==================================================" << endl;
        cout << "Pilih Menu (1-3): "; cin >> menuAwal;
        system("cls");

        switch (menuAwal) {
        case 1:
            if (prosesLogin()) {
                loginSukses = true; // Flag diaktifkan untuk tembus ke sistem utama
            }
            break;
        case 2:
            registrasiAkun();
            break;
        case 3:
            cout << "Terima kasih! Sampai jumpa kembali." << endl;
            return 0; // Langsung hentikan total program jika pilih keluar
        default:
            cout << "Pilihan tidak valid! Silakan masukkan angka 1-3.\n" << endl;
        }

        // Jika berhasil login, break dari loop menu awal dan lanjut ke bawah
        if (loginSukses) {
            break;
        }

    } while (menuAwal != 3);


    // ===========================================================
    // SISTEM UTAMA MARKETPLACE (Hanya terbuka jika loginSukses)
    // ===========================================================

    string produk[10] = {
        "Botol Minum Stainless", "Lampu LED Strip RGB", "Wireless Earbuds",
        "Rak Sepatu Susun 5", "Power Bank 20.000mAh", "Keyboard Mechanical",
        "Blender Portable USB", "Tas Ransel Anti Air", "Kamera CCTV WiFi", "Meja Laptop Lipat"
    };

    int harga[10] = { 89000, 65000, 249000, 135000, 279000, 499000, 159000, 219000, 325000, 179000 };
    int pilihan;

    do {
        cout << "==================================================" << endl;
        cout << "                 MARKET PLACE ONLINE              " << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "1. Lihat & Beli Produk" << endl;
        cout << "2. Keluar / Logout" << endl;
        cout << "==================================================" << endl;
        cout << "Pilihan Menu : "; cin >> pilihan;
        system("cls");

        switch (pilihan) {
        case 1: {
            cout << "================== LIST PRODUK ===================" << endl;
            cout << left << setw(5) << "No" << setw(25) << "Nama Produk" << setw(15) << "Harga" << endl;
            cout << "--------------------------------------------------" << endl;

            for (int i = 0; i < 10; i++) {
                cout << left << setw(5) << i + 1 << setw(25) << produk[i] << "Rp " << harga[i] << endl;
            }
            cout << "==================================================" << endl;

            const int MAKS_BARANG = 10;
            Barang daftarBarang[MAKS_BARANG];
            int jumlahInput;
            double total, diskon = 0, pajak, totalAkhir;

            cout << "\n===== FITUR CHECKOUT TOKO =====" << endl;
            cout << "Masukkan jumlah jenis produk yang ingin dibeli: ";
            cin >> jumlahInput;

            while (jumlahInput < 1 || jumlahInput > MAKS_BARANG) {
                cout << "Jumlah tidak valid! Masukkan lagi (1-10): ";
                cin >> jumlahInput;
            }

            for (int i = 0; i < jumlahInput; i++) {
                int nomorProduk;
                cout << "\nBarang ke-" << i + 1 << endl;
                cout << "Masukkan Nomor Produk dari Katalog (1-10): ";
                cin >> nomorProduk;

                while (nomorProduk < 1 || nomorProduk > 10) {
                    cout << "Nomor produk tidak ada! Masukkan lagi (1-10): ";
                    cin >> nomorProduk;
                }

                daftarBarang[i].nama = produk[nomorProduk - 1];
                daftarBarang[i].hargaSatuan = harga[nomorProduk - 1];

                cout << "Nama Produk   : " << daftarBarang[i].nama << endl;
                cout << "Harga Satuan  : Rp " << daftarBarang[i].hargaSatuan << endl;
                cout << "Jumlah Beli   : ";
                cin >> daftarBarang[i].jumlah;
            }

            total = hitungTotal(daftarBarang, jumlahInput);
            if (total >= 500000) {
                diskon = total * 0.10;
            }
            pajak = (total - diskon) * 0.10;
            totalAkhir = (total - diskon) + pajak;

            tampilkanRincian(daftarBarang, jumlahInput, total, diskon, pajak, totalAkhir);
            prosesPembayaran(totalAkhir);

            // FITUR PENGIRIMAN BARANG
            string asal, tujuan;
            string kurir[3] = { "JNE", "J&T", "SiCepat" };
            int opsi, estimasi = 0;

            cin.ignore();
            cout << "\n==============================================" << endl;
            cout << "           SISTEM PENGIRIMAN BARANG           " << endl;
            cout << "==============================================" << endl;
            cout << "Masukkan kota asal   : "; getline(cin, asal);
            cout << "Masukkan kota tujuan : "; getline(cin, tujuan);

            cout << "\nPilih Kurir :" << endl;
            for (int i = 0; i < 3; i++) {
                cout << i + 1 << ". " << kurir[i] << endl;
            }
            cout << "Pilihan : "; cin >> opsi;

            if (opsi == 1) estimasi = 3;
            else if (opsi == 2) estimasi = 2;
            else if (opsi == 3) estimasi = 1;
            else {
                cout << "Kurir tidak valid, default JNE (3 hari)." << endl;
                opsi = 1;
                estimasi = 3;
            }

            cout << "\n=== PENGIRIMAN DIKONFIRMASI ===" << endl;
            cout << "Asal            : " << asal << endl;
            cout << "Tujuan          : " << tujuan << endl;
            cout << "Kurir           : " << kurir[opsi - 1] << endl;
            cout << "Estimasi Sampai : " << estimasi << " hari\n" << endl;

            cout << "Tekan Enter untuk kembali ke menu utama...";
            cin.ignore(); cin.get();
            system("cls");
            break;
        }
        case 2:
            cout << "Log Out Berhasil. Menutup Marketplace...\n" << endl;
            break;
        default:
            cout << "Pilihan Lu Gada Jir. Coba lagi.\n" << endl;
        }
    } while (pilihan != 2);

    return 0;
}
