#include <iostream>
#include <iomanip>
using namespace std;

int main() {

    string produk[10] = {
        "Botol Minum Stainless Steel 750ml",
        "Lampu LED Strip RGB 5 Meter",
        "Wireless Earbuds Bluetooth",
        "Rak Sepatu Susun 5 Tingkat",
        "Power Bank 20.000mAh",
        "Keyboard Mechanical Gaming",
        "Blender Portable USB",
        "Tas Ransel Anti Air",
        "Kamera CCTV WiFi Indoor",
        "Meja Laptop Lipat" };

    int harga[10] = {
        89000,
        65000,
        249000,
        135000,
        279000,
        499000,
        159000,
        219000,
        325000,
        179000 };

	
    int pilihan;

    do {
    	cout << "                                                  " << endl;
        cout << "==================================================" << endl;
        cout << "                 MARKET PLACE ONLINE              " << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "1. Lihat Produk" << endl;							//buat fitur
        cout << "2. Keluar" << endl;
        cout << "==================================================" << endl;
        cout << "Pilihan Menu : "; cin >> pilihan;
		system ("cls");				//buat clear sistem sebelumnya
		
        switch (pilihan) {
        case 1:
            cout << "================== LIST PRODUK ===================" << endl;
            cout << left << setw(5) << "No" << setw(35) << "Nama Produk" << setw(15) << "Harga" << endl;
            cout << "--------------------------------------------------" << endl;

            for (int i = 0; i < 10; i++) {
                cout << left << setw(5) << i + 1 << setw(35) << produk[i] << "Rp " << harga[i] << endl;
            }
            break;

        case 2:
            cout << "TERIMA KASIH TELAH MENGGUNAKAN MARKETPLACE" << endl;
            break;

        default:
            cout << "Pilihan Lu Gada Jir" << endl;
        }

    } while (pilihan != 2);
    return 0;
}
