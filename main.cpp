#include <iostream>
#include <string>
#include <time.h>
#include <cstdlib>
#include <conio.h>
#include <unistd.h>
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
void instruction();
void playGame();
void isiKartu(pemain &p);
void pasangDadu(pemain &p);
void hapusKartu(pemain &p, string kartu);
void printVisual(pemain &p, musuh &m, int turn);
string lemparDadu();
string aksiMusuh();
void interaksiAksi(pemain &p, musuh &m);
void battleTurn(pemain &p, musuh &m, int turn);

int main() {
    startPage();
    return 0;
}

// Definisi Fungsi
// Fungsi Alur Permainan Utama
void startPage(){
    cout << "==========================" << endl;
	cout << "      MAGIC  DUNGEON      " << endl;
	cout << "--------------------------" << endl;
	cout << "  Turn Based  Combat RPG  " << endl;
	cout << endl;
	cout << "       *" << endl;
	cout << "       ***" << endl;
	cout << "        ***" << endl;
	cout << "         ***" << endl;
	cout << "          ***" << endl;
	cout << "           ***" << endl;
	cout << "            ***" << endl;
	cout << "          *********" << endl;
	cout << "           *********" << endl;
	cout << "               ***" << endl;
	cout << "                ***" << endl;
	cout << endl;
	cout << "--------------------------" << endl;
	cout << "--Press Any Key to Play!--" << endl;
	cout << "==========================" << endl;
	getch();
	system("cls");
	playGame();
    	cout << endl;
    	cout << "=============================" << endl;
	cout << "    Thank you for playing!   " << endl;
	cout << "-----------------------------" << endl;
	cout << "         Project By:         " << endl << endl;
	cout << "  David Lois                 " << endl;
	cout << "  Azhar Bagaskara            " << endl;
	cout << "  Asyraf Nur Ardliansyah     " << endl;
	cout << "=============================" << endl;
}

void instruction() {
    system("cls");
    cout << "Instruksi Permainan" << endl << endl;
    cout << "Pada setiap turn, pemain diberi 10 kartu\ndengan tiga macam tipe aksi (Attack, Defend, dan Heal) dengan jumlah\nmasing-masing acak." << endl << endl;
    cout << "Pemain akan diminta memilih 6 kartu dari kartu tadi\nyang nantinya akan dipasang pada dadu untuk menentukan aksi yang dilakukan pada turn tersebut." << endl << endl;
    cout << "Aksi pemain akan ditentukan melalui pelemparan dadu." << endl << endl;
    cout << "Press any key to continue...";
    getch();
}

void playGame() {
    instruction();
    system("cls");
    cout << "PROLOG" << endl << endl;
    cout << "Kamu adalah manusia terpilih yang memiliki Demon Eye.\nDengan Demon Eye, kamu bisa melihat satu turn ke depan saat melawan musuh.\nOleh karena itu, kamu ditugaskan oleh Guildmaster untuk membasmi monster yang ada di Magic Dungeon." << endl << endl;
    cout << "Press any key to continue...";
    getch();
    
    int turn = 0;
    while (orang.hp > 0 and slime.hp > 0){
        battleTurn(orang, slime, turn);
        turn++;
    }

    if (slime.hp <= 0) {
        cout << "\nYOU WIN!" << endl;
    }
    else {
        cout << "\nYOU LOSE :P" << endl;
    }

    std::cout << "Game Selesai" << endl;
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

void pasangDadu(pemain &p, musuh &m, int turn, string aksi_musuh){
    // Inisialisasi dadu
    for (int i = 0; i < 6; i++){
        dadu[i] = "kosong";
    }
    
    // Inisialisasi jumlah masing-masing kartu yang akan ditempelkan ke dadu
    int dadu_attack = 0, dadu_defend = 0, dadu_heal = 0;

    // Inisialisasi kartu yang dimiliki pemain
    int attack = 0, defend = 0, heal = 0;
    
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
    
    while (true) {
        // cek_jumlah_kartu berfungsi untuk mengecek total semua kartu yang diinput user
        //      agar tidak lebih dari 6
        // cek_kecukupan_kartu berfungsi untuk mengecek kecukupan masing-masing kartu
        //      agar tidak lebih dari jumlah kartu yang dimiliki
        bool cek_jumlah_kartu = true, cek_kecukupan_kartu = true;

        // Menerima input kartu yang ingin ditempel ke dadu dari pemain
        std::cout << "Kartu yang kamu miliki:" << endl;
        std::cout << "1. Attack : " << attack << endl;
        std::cout << "2. Defend : " << defend << endl;
        std::cout << "3. Heal   : " << heal << endl;
        std::cout << "-----------------------------" << endl;

        std::cout << "Masukkan enam kartu ke dadu:" << endl;
        cout << "Attack : "; cin >> dadu_attack;
        cout << "Defend : "; cin >> dadu_defend;
        cout << "Heal   : "; cin >> dadu_heal;

        // Cek
        if (dadu_attack + dadu_defend + dadu_heal != 6) {
            std::cout << "WARNING! Jumlah kartu yang kamu tempelkan ke dadu tidak valid" << endl;
            cek_jumlah_kartu = false;
        }

        if (dadu_attack > attack or dadu_defend > defend or dadu_heal > heal){
            std::cout << "WARNING! Kamu tidak memiliki kartu yang cukup untuk menempel kartu yang kamu inginkan" << endl;
            cek_kecukupan_kartu = false;
        }

        // Decision
        if (cek_jumlah_kartu == true && cek_kecukupan_kartu == true) {
            break;
        }

        cout << "Press any key to continue...";
        getch();
        system("cls");

        // Kalo salah ngeprint ulang tampilannya
        printVisual(p, m, turn);
        std::cout << "Aksi musuh berikutnya adalah: " << aksi_musuh << endl;
    }

    // Memasang kartu ke dadu
    int i = 0;
    for (i = 0; i < dadu_attack; i++) {
        dadu[i] = "Attack";
    }
    for (i = i; i < dadu_defend + dadu_attack; i++) {
        dadu[i] = "Defend";
    }
    for (i = i; i < dadu_defend + dadu_attack + dadu_heal; i++) {
        dadu[i] = "Heal";
    }

    // Menghapus kartu yang dimiliki pemain karena sudah terpasang di dadu
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

void printVisual(pemain &p, musuh &m, int turn){
    std::cout << "`;-.          ___,\n"
"  `.`\\_...._/`.-'`\n"
"    \\        /      ,\n"
"    /()   () \\    .' `-._\n"
"   |)  .    ()\\  /   _.'\n"
"   \\  -'-     ,; '. <\n"
"    ;.__     ,;|   > /\n"
"   / ,    / ,  |.-'.-'\n"
"  (_/    (_/ ,;|.<`\n"
"    \\    ,     ;-`\n"
"     >   \\    /\n"
"    (_,-'`> .'\n"
"         (_,'\n";
    std::cout << "== Turn ke-" << turn + 1 << " ==" << endl;
    std::cout << "HP musuh: " << m.hp << endl;
    std::cout << "HP pemain: " << p.hp << endl;
    std::cout << "-----------------------------" << endl;
}

string lemparDadu(){
    srand(time(0));
    cout << "Mengocok dadu..." << endl;
    for (int i = 0; i < 6; i++) {
        usleep(10000 + (i * 90000));
        switch (dadu[i][0]){
            case 'A':
                cout << "*----*" << endl;
                cout << "| ATT|" << endl;
                cout << "*----*" << endl;
                break;
            case 'D':
                cout << "*----*" << endl;
                cout << "| DEF|" << endl;
                cout << "*----*" << endl;
                break;
            case 'H':
                cout << "*----*" << endl;
                cout << "|HEAL|" << endl;
                cout << "*----*" << endl;
                break;
            default:
                break;
        }
    }
    usleep(510000);
    cout << "=============================" << endl;
    int rand_num = rand() % 6;
    switch (dadu[rand_num][0]){
            case 'A':
                cout << "*----*" << endl;
                cout << "| ATT|" << endl;
                cout << "*----*" << endl;
                break;
            case 'D':
                cout << "*----*" << endl;
                cout << "| DEF|" << endl;
                cout << "*----*" << endl;
                break;
            case 'H':
                cout << "*----*" << endl;
                cout << "|HEAL|" << endl;
                cout << "*----*" << endl;
                break;
            default:
                break;
        }
    cout << endl;
    

    switch (rand_num){
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
            std::cout << "Dadu dilempar dan aksi yang dilakukan adalah: " << dadu[5] << endl;            
            return dadu[5];
        default:
            return "";
    }
}

string aksiMusuh(){
    srand(time(0));
    switch (rand() % 3){
        case 0:
            // Print text art untuk kartu attack (TODO)
            std::cout << "Aksi musuh berikutnya: Attack" << endl;
            std::cout << "-----------------------------" << endl;
            return "Attack";
        case 1:
            // Print text art untuk kartu defend (TODO)
            std::cout << "Aksi musuh berikutnya: Defend" << endl;
            std::cout << "-----------------------------" << endl;
            return "Defend";
        case 2:
            // Print text art untuk kartu heal (TODO)
            std::cout << "Aksi musuh berikutnya: Heal" << endl;
            std::cout << "-----------------------------" << endl;
            return "Heal";
        default:
            return "";
    }
}

void interaksiAksi(pemain &p, musuh &m){
    if (p.aksi == "Attack" and m.aksi == "Attack"){
        p.hp -= 2;
        m.hp -= 2;
        std::cout << "Musuh (HP -2): no u" << endl;
        std::cout << "Kamu (HP -2): no u" << endl;
    } else if (p.aksi == "Heal" and m.aksi == "Heal"){
        p.hp += 1;
        m.hp += 1;
        std::cout << "Musuh (HP +1): haha ez" << endl;
        std::cout << "Kamu (HP +1): haha ez" << endl;
    } else if (p.aksi == "Attack" and m.aksi == "Defend"){
        p.hp -= 1;
        std::cout << "Musuh: lol u sux" << endl;
        std::cout << "Kamu (HP -1): noo u sux moar :(" << endl;
    } else if (p.aksi == "Attack" and m.aksi == "Heal"){
        m.hp -= 1;
        std::cout << "Musuh (HP -1): noo u sux moar" << endl;
        std::cout << "Kamu: lol u sux" << endl;
    } else if (p.aksi == "Defend" and m.aksi == "Attack"){
        m.hp -= 1;
        std::cout << "Musuh (HP -1): :(((((" << endl;
        std::cout << "Kamu: soo dum dum" << endl;
    } else if (p.aksi == "Heal" and m.aksi == "Attack"){
        p.hp -= 1;
        std::cout << "Musuh: soo dum dum" << endl;
        std::cout << "Kamu (HP -1): :(((((" << endl;
    } else if (p.aksi == "Defend" and m.aksi == "Heal"){
        m.hp += 1;
        std::cout << "Musuh (HP +1): haha ez ggwp" << endl;
        std::cout << "Kamu: u haxxx" << endl;
    } else if (p.aksi == "Heal" and m.aksi == "Defend"){
        p.hp += 1;
        std::cout << "Musuh: u haxxx" << endl;
        std::cout << "Kamu (HP +1): haha ez ggwp" << endl;
    }
}

void battleTurn(pemain &p, musuh &m, int turn){
    system("cls");
    isiKartu(p);
    printVisual(p, m, turn);

    m.aksi = aksiMusuh();

    pasangDadu(p, m, turn, m.aksi);

    p.aksi = lemparDadu();

    interaksiAksi(p, m);
    std::cout << "-----------------------------" << endl;

    cout << "Press any key to continue...";
    getch();
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
