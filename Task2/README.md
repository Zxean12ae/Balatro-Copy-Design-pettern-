# Task 2 - Develop Your Own Core Loop: Mystic Word RPG

## 1. Core Loop
Urutan fase dalam game puzzle RPG ini berjalan secara berurutan pada setiap gilirannya:
1. **Word Input Phase:** Pemain merangkai huruf menjadi sebuah kata.
2. **Validation Phase:** Sistem memvalidasi apakah kata tersebut ada di dalam kamus KBBI.
3. **Damage Calculation Phase:** Sistem menghitung *damage* berdasarkan panjang kata dan *color-matched chain reaction*.
4. **Player Attack Phase:** *Damage* diberikan kepada musuh (misalnya: Genderuwo atau Bubo).
5. **Enemy Turn Phase:** Musuh membalas serangan kepada pemain.
6. **Round Resolution:** Pengecekan kondisi menang/kalah dan pergantian giliran.

## 2. Invariants
1. **Langkah mana yang urutannya TIDAK BOLEH berubah?**
   Urutan Input -> Validasi -> Kalkulasi Damage -> Serangan Pemain -> Serangan Musuh. Validasi harus terjadi sebelum kalkulasi, dan pemain harus menyerang sebelum musuh membalas.
2. **Komponen apa yang wajib ada agar game berfungsi?**
   Kelas pengatur utama (`GameSession`), *generator* input kata, validator kamus, kalkulator *damage*, dan entitas musuh.
3. **Apa yang rusak jika urutannya diubah?**
   Jika kalkulasi *damage* berjalan sebelum validasi KBBI, pemain bisa memberikan *damage* menggunakan kata acak yang tidak bermakna. Jika musuh menyerang sebelum pemain, inisiatif giliran RPG akan hancur dan *gameplay loop* menjadi tidak seimbang.

## 3. Mutable Elements
1. **Dictionary Validator (Logika Validasi):** Bebas diubah. Saat ini menggunakan validasi KBBI, tapi ke depannya bisa diganti dengan kamus bahasa Inggris, kamus bahasa Jawa, atau sistem validasi lokal sederhana tanpa merusak alur *game*.
2. **Damage Calculator (Rumus Serangan):** Bebas diubah. Mekanik *color-matched chain reaction* bisa dimodifikasi menjadi perhitungan *damage* statis, penambahan *critical hit*, atau *elemental multiplier* tanpa menyentuh *core loop*.
3. **Enemy AI/Behavior:** Bebas diubah. Jenis musuh, status *health*, dan pola serangan (misal: serangan area atau *debuff*) bisa diganti-ganti cukup dengan membuat kelas musuh baru.

---

## 4. Reflection Answers

**1. Apa struktur invariant dari game kamu?**
Struktur *invariant* di dalam proyek ini adalah *core loop* pertarungan berbasis kata yang diatur sepenuhnya oleh kelas `GameSession`. Urutan fase yang tidak boleh berubah ini dimulai dari pemain merangkai kata, lalu kata tersebut divalidasi keabsahannya. Setelah kata terbukti valid, sistem menghitung *output damage* pemain berdasarkan panjang kata dan kombinasi warna. *Damage* kemudian dieksekusi ke musuh, diikuti dengan fase balasan di mana musuh menyerang pemain, dan diakhiri dengan resolusi giliran. Urutan eksekusi ini bersifat absolut dan direpresentasikan sebagai pemanggilan fungsi yang berurutan di dalam *loop* utama.

**2. Bagian mana yang mutable?**
Bagian yang *mutable* adalah implementasi detail dari setiap fase tersebut. Antarmuka seperti `IWordInput`, `IDictionaryValidator`, `IDamageCalculator`, dan `IEnemy` dirancang untuk menyembunyikan logika spesifik. Sebagai contoh, mekanisme kamus yang memeriksa kata baku (KBBI), rumus perhitungan *damage* yang menyertakan pengali berantai (*chain reaction*), serta jenis musuh (*Genderuwo* atau bos lainnya) adalah komponen *mutable*. Logika di dalam komponen-komponen ini bebas dibongkar-pasang, diperbarui, atau diganti total melalui kelas turunan baru.

**3. Jika ingin menambah fitur baru, kelas mana yang akan berubah?**
Jika ada fitur baru, kelas yang berubah bergantung pada domain fitur tersebut, namun dipastikan bukan kelas `GameSession`. Misalnya, jika saya ingin menambahkan mekanik "kata slang" atau kamus bahasa daerah, saya hanya perlu membuat kelas baru yang mengimplementasikan antarmuka `IDictionaryValidator` tanpa mengubah kelas lainnya. Jika ada tambahan efek racun pada musuh, saya hanya akan memodifikasi kelas konkret dari antarmuka `IEnemy`. Prinsip *Open-Closed* memastikan ekstensi dilakukan dengan menambahkan kelas baru, bukan mengedit pengatur utama.

**4. Jika urutan loop diubah, apa yang akan rusak?**
Mengubah urutan *loop* di dalam `GameSession` akan merusak integritas mekanik RPG dan logika kausalitas permainan. Jika validasi dipindahkan setelah serangan, sistem akan mengeksekusi *damage* dari *string* acak sebelum tahu itu kata yang sah atau bukan, sehingga menghancurkan konsep permainan susun kata. Jika giliran musuh diletakkan sebelum kalkulasi *damage* pemain, musuh mungkin membunuh pemain sebelum aksi pemain pada giliran tersebut sempat terdaftar, menciptakan pengalaman *gameplay* yang cacat, *bug* pada sinkronisasi status HP, dan putusnya alur permainan.