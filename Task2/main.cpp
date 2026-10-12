#include <iostream>
#include <string>

using namespace std;

// ==========================================
// 1. INTERFACES (Komponen Mutable)
// ==========================================

class IWordInput {
public:
    virtual string getWord() = 0;
    virtual ~IWordInput() = default;
};

class IDictionaryValidator {
public:
    virtual bool isValidWord(const string& word) = 0;
    virtual ~IDictionaryValidator() = default;
};

class IDamageCalculator {
public:
    virtual int calculateDamage(const string& word) = 0;
    virtual ~IDamageCalculator() = default;
};

class IEnemy {
public:
    virtual void takeDamage(int damage) = 0;
    virtual void attackPlayer(int& playerHP) = 0;
    virtual bool isDead() = 0;
    virtual string getName() = 0;
    virtual ~IEnemy() = default;
};


// ==========================================
// 2. CONCRETE IMPLEMENTATIONS (Logika Spesifik)
// ==========================================

class ConsoleWordInput : public IWordInput {
public:
    string getWord() override {
        cout << "[INPUT] Pemain menyusun kata dari tile huruf.\n";
        return "MANTRA"; // Placeholder input
    }
};

class KBBIDictionaryValidator : public IDictionaryValidator {
public:
    bool isValidWord(const string& word) override {
        cout << "[VALIDATION] Memeriksa kata '" << word << "' di kamus KBBI... Valid!\n";
        return true; 
    }
};

class ChainReactionDamageCalculator : public IDamageCalculator {
public:
    int calculateDamage(const string& word) override {
        int damage = word.length() * 15;
        cout << "[CALCULATION] Menghitung chain reaction warna. Damage dihasilkan: " << damage << "\n";
        return damage;
    }
};

class GenderuwoEnemy : public IEnemy {
private:
    int hp = 100;
    string name = "Genderuwo";
public:
    void takeDamage(int damage) override {
        hp -= damage;
        cout << "[COMBAT] " << name << " menerima " << damage << " damage. HP tersisa: " << hp << "\n";
    }
    void attackPlayer(int& playerHP) override {
        int enemyDamage = 20;
        playerHP -= enemyDamage;
        cout << "[COMBAT] " << name << " menyerang balik! Pemain menerima " << enemyDamage << " damage. HP Pemain: " << playerHP << "\n";
    }
    bool isDead() override {
        return hp <= 0;
    }
    string getName() override {
        return name;
    }
};


// ==========================================
// 3. CORE LOOP (Invariant)
// ==========================================

class GameSession {
private:
    IWordInput* inputSystem;
    IDictionaryValidator* dictionary;
    IDamageCalculator* damageCalc;
    IEnemy* enemy;
    int playerHP;

public:
    GameSession(IWordInput* input, IDictionaryValidator* dict, IDamageCalculator* calc, IEnemy* en)
        : inputSystem(input), dictionary(dict), damageCalc(calc), enemy(en), playerHP(100) {}

    void runCombat() {
        cout << "=== BATTLE START: VS " << enemy->getName() << " ===\n";
        int round = 1;
        
        // Game Loop utama berlanjut sampai musuh mati atau player mati
        while (playerHP > 0 && !enemy->isDead()) {
            cout << "\n--- TURN " << round << " ---\n";
            
            // 1. Fase Input
            string word = inputSystem->getWord();
            
            // 2. Fase Validasi Kamus
            if (dictionary->isValidWord(word)) {
                
                // 3. Fase Perhitungan Damage
                int damage = damageCalc->calculateDamage(word);
                
                // 4. Fase Serangan Pemain
                enemy->takeDamage(damage);
            } else {
                cout << "[FAILED] Kata tidak valid. Serangan gagal.\n";
            }
            
            // 5. Fase Serangan Musuh (jika musuh belum mati)
            if (!enemy->isDead()) {
                enemy->attackPlayer(playerHP);
            }
            
            // 6. Resolusi Round
            round++;
            
            // Loop berhenti di turn 2 untuk keperluan demonstrasi tugas
            if (round > 2) break; 
        }
        
        cout << "\n=== BATTLE END ===\n";
        if (playerHP > 0) cout << "Pemain Menang!\n";
        else cout << "Pemain Kalah!\n";
    }
};

// ==========================================
// 4. MAIN ENTRY POINT
// ==========================================
int main() {
    // Inisialisasi komponen-komponen mutable
    ConsoleWordInput input;
    KBBIDictionaryValidator validator;
    ChainReactionDamageCalculator calculator;
    GenderuwoEnemy boss1;

    // Dependency Injection ke pengatur pusat
    GameSession session(&input, &validator, &calculator, &boss1);

    // Jalankan Game Loop
    session.runCombat();

    return 0;
}