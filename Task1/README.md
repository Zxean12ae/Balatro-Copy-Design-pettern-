# Task 1 - Building a Balatro-Like Run

## Reflection Answers

**1. What is the invariant structure in your program?**
Struktur *invariant* (bagian yang tidak boleh berubah) dalam program ini adalah urutan eksekusi fase permainan di dalam fungsi `run()` pada kelas `RunSession`. Urutannya adalah: menghasilkan input, menghitung skor dasar, menghitung hadiah, memperbarui jumlah uang, menjalankan fase toko, dan maju ke ronde berikutnya. Urutan loop ini berjalan persis selama 3 ronde dan tidak boleh diotak-atik.

**2. Which parts are mutable?**
Bagian yang *mutable* (dapat diubah) adalah detail logika atau perilaku di balik setiap fase. Ini mencakup logika perhitungan di dalam kelas-kelas turunan yang mewarisi antarmuka `IInputGenerator`, `IScoringRule`, dan `IRewardRule`. Kelas `ShopSystem` juga merupakan bagian yang *mutable* karena teks penawaran atau logika pembeliannya dapat dimodifikasi secara bebas.

**3. When you replaced the InputGenerator, why didn't RunSession change?**
`RunSession` tidak perlu diubah karena program ini menerapkan prinsip *Dependency Inversion* dan pola *Strategy*. `RunSession` hanya berkomunikasi dengan antarmuka abstrak (`IInputGenerator`), bukan dengan kelas implementasi konkretnya. Saat `RandomInputGenerator` disuntikkan ke dalam `RunSession`, pengontrol utama tersebut hanya perlu memanggil metode virtual `generateInput()` tanpa perlu tahu bagaimana logika acak tersebut diproses di balik layar.

**4. What would happen if scoring logic was placed inside RunSession?**
Jika logika perhitungan skor dimasukkan langsung ke dalam `RunSession`, kita melanggar prinsip *Single Responsibility* dan *Open-Closed*. Jika suatu saat kita ingin mengubah aturan pemberian skor, kita terpaksa harus mengedit kode di dalam `RunSession`. Hal ini akan merusak *invariant* sistem, meningkatkan risiko terjadinya bug pada siklus loop utama, dan membuat kode sulit untuk dikembangkan atau digunakan ulang.