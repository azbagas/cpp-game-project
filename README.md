# C++ Game Project
Tugas akhir untuk mata kuliah Praktikum Pemrograman
## Gameflow Dan Progres
Game ini akan memiliki alur permainan seperti berikut:
1. Homepage
   - Latar belakang: Kamu adalah manusia terpilih yang memiliki demon eye.
                     Dengan demon eye tersebut kamu bisa melihat satu turn
                     ke depan saat melawan musuh. Oleh karena itu, kamu
                     ditugaskan oleh ketua guild untuk membasmi monster
                     yang ada di Magic Dungeon.
   - Aturan permainan: ...
   - Difficulty select (Normal/Hard (opsional))

2. Data pemain dan musuh
   - Data musuh:
     - Text art -> array of string
     - Nama = "Slime"
     - HP = 5
   - Data pemain:
     - HP
     - Kartu yang dimiliki (A/C/H)
     - Pairing ke dadu

3. Logic per-turn
   1. Pemain akan mendapatkan kartu random (A/C/H) sehingga
      jumlah kartu yang dimiliki berjumlah 10.
   2. Setiap turn berkelipatan 3 pemain berhak mendapatkan opsi reshuffle
      untuk mengacak ulang kartu yang didapatkan (opsional).
   3. Pemain diminta untuk memasangkan 6 kartu ke dalam dadu.
   4. Dadu di-roll (random) lalu kartu yang muncul menjadi action yang akan dilakukan.
   5. Action pemain dan action musuh (Setiap turn action yang dilakukan berurut (A -> C -> H)) 
      akan dilakukan secara bersamaan (masuk function).
   6. Langkah-langkah di atas akan terus berjalan hingga kondisi HP pemain <= 0 atau HP musuh <= 0.
   7. Jika HP musuh <= 0 maka game menang, sedangkan jika HP pemain <= 0 maka game over.

Keterangan:
- A: Attack
- C: Counter
- H: Heal
-----------------------------------------------------------------------------------------
Pembagian tugas:
- Bagas   : data -> logic per-turn
- David   : logic per-turn
- Asyraf  : Hompage -> logic per-turn

To Do #1
1. Ganti cara masukkan kartu menggunakan angka saja. Contoh: 
   - Attack: (input)
   - Defend: (input)
   - Heal: (input)
2. Tampilan musuh
3. Tampilan homepage
4. Aksi musuh berikutnya di-random
5. Implementasikan delay output setelah hasil pelemparan dadu
6. Implementasikan clearscreen setelah delay 
7. Tampilan lemparan (opsional)
__________
|        |
| attack |
|________|