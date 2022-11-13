#include <iostream>
#include <string>
#include <time.h>
#include <cstdlib>
using namespace std;

string dadu[6];

// Struct Musuh Dan Pemain
struct musuh{
    int hp;
}slime = {5};

struct pemain{
    int hp;
    string kartu[10];

}orang = {{5}, {}};

// Prototipe Fungsi
void startPage();
void isiKartu(pemain &p);
void pasangDadu(pemain &p, int kedalaman);
void hapusKartu(pemain &p, string kartu);
void battleTurn(pemain &p, musuh &m);

// Fungsi untuk debugging
void printKartu(pemain &p){
    for (int i = 0; i < 10; i++){
        cout << p.kartu[i];
    }
}


int main() {
    // isiKartu(orang);
    // cout << orang.kartu[5];
    // while (orang.hp > 0 or slime.hp > 0){
        isiKartu(orang);
        pasangDadu(orang, 1);
        
        // Untuk mengecek apakah kartu yang dimiliki pemain sesuai ekspektasi setelah ditempel ke dadu
        printKartu(orang);
    // }

    return 0;
}

// Definisi Fungsi
// Fungsi Alur Permainan Utama
void startPage(){
    // Bagian Asyraf
}

void isiKartu(pemain &p){
    srand(time(0));
    for (int i = 0; i < 10; i++){
        if (!(p.kartu[i] == "Attack" or p.kartu[i] == "Defend" or p.kartu[i] == "Heal")){
            switch(rand() % 3){
                case 0:
                    p.kartu[i] = "Attack";
                    break;
                case 1:
                    p.kartu[i]  = "Defend";
                    break;
                case 2:
                    p.kartu[i] = "Heal";
                    break;
            }
        }
    }
}

void pasangDadu(pemain &p, int kedalaman){
    // Inisialisasi dadu
    int attack = 0, defend = 0, heal = 0;
    for (int i = 0; i < 6; i++){
        dadu[i] = "kosong";
    }

    // Menghitung jumlah kartu yang dimiliki pemain
    for (int i = 0; i < 10; i++){
        if (p.kartu[i] == "Attack"){
            attack++;
        } else if (p.kartu[i] == "Defend"){
            defend++;
        } else {
            heal++;
        }
    }

    // Menerima input kartu yang ingin ditempel ke dadu dari pemain
    cout << "Kartu yang kamu miliki:" << endl;
    cout << "1. Attack : " << attack << endl;
    cout << "2. Defend : " << defend << endl;
    cout << "3. Heal   : " << heal << endl;
    cout << "Masukkan enam kartu ke dadu (Contoh: Attack Defend Defend Heal Heal Heal): ";
    for (int i = 0; i < 6; i++){
        cin >> dadu[i];
    }

    // Validasi input yang diberikan pemain
    for (int i = 0; i < 6; i++){
        if (!(dadu[i] == "Attack" or dadu[i] == "Defend" or dadu[i] == "Heal")){
            cout << "Mohon masukkan nama kartu yang valid (Contoh: Attack, Defend, Heal)" << endl;
            pasangDadu(p, kedalaman + 1);
            break;
        }
    }
    int dadu_attack = 0, dadu_defend = 0, dadu_heal = 0;
    for (int i = 0; i < 6; i++){
        if (dadu[i] == "Attack"){
            dadu_attack++;
        } else if (dadu[i] == "Defend"){
            dadu_defend++;
        } else if(dadu[i] == "Heal"){
            dadu_heal++;
        }
    }
    for (int i = 0; i < 6; i++){
        if (dadu_attack > attack or dadu_defend > defend or dadu_heal > heal){
            cout << "Kamu tidak memiliki kartu yang cukup untuk menempel kartu yang kamu inginkan" << endl;
            pasangDadu(p, kedalaman + 1);
            break;
        }
    }

    // Hapus kartu milik pemain yang ditempelkan ke dadu jika ini adalah function call pertama, bukan function call secara rekursif
    if (kedalaman == 1){
        for (int i = 0; i < 6; i++){
            if (dadu[i] == "Attack"){
                hapusKartu(p, "Attack");
            } else if (dadu[i] == "Defend"){
                hapusKartu(p, "Defend");
            } else if (dadu[i] == "Heal"){
                hapusKartu(p, "Heal");
            }
        }
    }
}

void battleTurn(pemain &p, musuh &m){

}

// Fungsi Pembantu
void hapusKartu(pemain &p, string kartu){
    for (int i = 0; i < 10; i++){
        if (p.kartu[i] == kartu){
            p.kartu[i] = "kosong";
            break;
        }
    }
}