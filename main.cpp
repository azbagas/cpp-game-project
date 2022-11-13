#include <iostream>
#include <string>
#include <time.h>
#include <cstdlib>
using namespace std;

string dadu[6];

// Struct Musuh Dan Pemain (TODO)
struct musuh{
    int hp;
    string aksi;
}slime = {5};

struct pemain{
    int hp;
    string aksi;
    string kartu[10];

}orang = {{5}, {}};

// Prototipe Fungsi
void startPage();
void isiKartu(pemain &p);
void pasangDadu(pemain &p, int kedalaman);
void hapusKartu(pemain &p, string kartu);
void printVisual(pemain &p, musuh &m, int turn);
string lemparDadu();
string aksiMusuh(int turn);
void interaksiAksi(pemain &p, musuh &m);
void battleTurn(pemain &p, musuh &m, int turn);

int main() {
    int turn = 0;
    while (orang.hp > 0 and slime.hp > 0){
        battleTurn(orang, slime, turn);
        turn++;
    }

    std::cout << "Game Selesai";

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
    std::cout << "Kartu yang kamu miliki:" << endl;
    std::cout << "1. Attack : " << attack << endl;
    std::cout << "2. Defend : " << defend << endl;
    std::cout << "3. Heal   : " << heal << endl;
    std::cout << "Masukkan enam kartu ke dadu (Contoh: Attack Defend Defend Heal Heal Heal): ";
    for (int i = 0; i < 6; i++){
        cin >> dadu[i];
    }

    // Validasi input yang diberikan pemain
    for (int i = 0; i < 6; i++){
        if (!(dadu[i] == "Attack" or dadu[i] == "Defend" or dadu[i] == "Heal")){
            std::cout << "Mohon masukkan nama kartu yang valid (Contoh: Attack, Defend, Heal)" << endl;
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
            std::cout << "Kamu tidak memiliki kartu yang cukup untuk menempel kartu yang kamu inginkan" << endl;
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

void printVisual(pemain &p, musuh &m, int turn){
    // Print text art musuh (TODO)
    // for (int i = 0; i < 10; i++){
    //     std::cout << text_art[i] << endl;
    // }
    std::cout << "Turn ke-" << turn + 1 << endl;
    std::cout << "HP musuh: " << m.hp << endl;
    std::cout << "HP pemain: " << p.hp << endl;
}

string lemparDadu(){
    srand(time(0));
    switch (rand() % 6){
        case 0:
            std::cout << "Dadu dilempar dan aksi yang dilakukan adalah: " << dadu[0] << endl;    
            return dadu[0];
        case 1:
            std::cout << "Dadu dilempar dan aksi yang dilakukan adalah: " << dadu[1] << endl;    
            return dadu[1];
        case 2:
            std::cout << "Dadu dilempar dan aksi yang dilakukan adalah: " << dadu[2] << endl;    
            return dadu[2];
        case 3:
            std::cout << "Dadu dilempar dan aksi yang dilakukan adalah: " << dadu[3] << endl;    
            return dadu[3];
        case 4:
            std::cout << "Dadu dilempar dan aksi yang dilakukan adalah: " << dadu[4] << endl;    
            return dadu[4];
        case 5:
            std::cout << "Dadu dilempar dan aksi yang dilakukan adalah: " << dadu[5];                
            return dadu[5];
    }
}

string aksiMusuh(int turn){
    switch (turn % 3){
        case 0:
            // Print text art untuk kartu attack (TODO)
            std::cout << "Aksi musuh berikutnya: Attack" << endl;
            return "Attack";
        case 1:
            // Print text art untuk kartu defend (TODO)
            std::cout << "Aksi musuh berikutnya: Defend" << endl;
            return "Defend";
        case 2:
            // Print text art untuk kartu heal (TODO)
            std::cout << "Aksi musuh berikutnya: Heal" << endl;
            return "Heal";
    }
}

void interaksiAksi(pemain &p, musuh &m){
    if (p.aksi == "Attack" and m.aksi == "Attack"){
        p.hp -= 2;
        m.hp -= 2;
    } else if (p.aksi == "Heal" and m.aksi == "Heal"){
        p.hp += 1;
        m.hp += 1;
    } else if (p.aksi == "Attack" and m.aksi == "Defend"){
        p.hp -= 1;
    } else if (p.aksi == "Attack" and m.aksi == "Heal"){
        m.hp -= 1;
    } else if (p.aksi == "Defend" and m.aksi == "Attack"){
        m.hp -= 1;
    } else if (p.aksi == "Heal" and m.aksi == "Attack"){
        p.hp -= 1;
    } else if (p.aksi == "Defend" and m.aksi == "Heal"){
        m.hp += 1;
    } else if (p.aksi == "Heal" and m.aksi == "Defend"){
        p.hp += 1;
    }
}

void battleTurn(pemain &p, musuh &m, int turn){
    isiKartu(p);
    printVisual(p, m, turn);

    m.aksi = aksiMusuh(turn);

    pasangDadu(p, 1);

    p.aksi = lemparDadu();

    interaksiAksi(p, m);
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