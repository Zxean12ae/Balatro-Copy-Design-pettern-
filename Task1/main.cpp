#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// ==========================================
// 1. INTERFACES (Kompnen Mutable)
// ==========================================

class IInputGenerator {
public:
    virtual int generateInput() = 0;
    virtual ~IInputGenerator() = default;
};

class IScoringRule {
public:
    virtual int computeScore(int input) = 0;
    virtual ~IScoringRule() = default;
};

class IRewardRule {
public:
    virtual int computeReward(int baseScore) = 0;
    virtual ~IRewardRule() = default;
};

// ==========================================
// 2. CONCRETE IMPLEMENTATIONS (Modifikasi)
// ==========================================

// Modifikasi 1: Kelas RandomInputGenerator[cite: 4]
class RandomInputGenerator : public IInputGenerator {
public:
    int generateInput() override {
        return (rand() % 5) + 1; // Menghasilkan angka acak 1-5
    }
};

class SimpleScoringRule : public IScoringRule {
public:
    int computeScore(int input) override {
        return input * 10; // Logika skor dasar sederhana
    }
};

// Modifikasi 2: Logika reward tidak sama dengan base score[cite: 4]
class BonusRewardRule : public IRewardRule {
public:
    int computeReward(int baseScore) override {
        return baseScore + 2; // Hadiah = skor dasar + 2[cite: 4]
    }
};

// Kelas ShopSystem untuk mencetak penawaran toko[cite: 2]
class ShopSystem {
public:
    void printOffer(int currentMoney) {
        cout << "[SHOP] offered: Bonus (+2) cost 20\n";
        cout << "[SHOP] skipped\n";
    }
};

// ==========================================
// 3. CORE LOOP (Invariant)
// ==========================================

class RunSession {
private:
    IInputGenerator* inputGen;
    IScoringRule* scoringRule;
    IRewardRule* rewardRule;
    ShopSystem* shopSystem;
    int money;

public:
    // Dependency Injection
    RunSession(IInputGenerator* ig, IScoringRule* sr, IRewardRule* rr, ShopSystem* ss)
        : inputGen(ig), scoringRule(sr), rewardRule(rr), shopSystem(ss), money(0) {}

    void run() {
        cout << "=== RUN START ===\n";
        
        // Loop berjalan tepat 3 ronde[cite: 3]
        for (int round = 1; round <= 3; ++round) {
            cout << "\nRound " << round << "\n";
            
            // 1. Panggil fungsi dari IInputGenerator[cite: 1]
            int input = inputGen->generateInput();
            cout << "[PLAY] input generated: " << input << "\n";
            
            // 2. Panggil fungsi dari IScoringRule[cite: 1]
            int baseScore = scoringRule->computeScore(input);
            cout << "[SCORE] base score: " << baseScore << "\n";
            
            // 3. Panggil fungsi dari IRewardRule[cite: 1]
            int reward = rewardRule->computeReward(baseScore);
            
            // 4. Update variabel uang[cite: 1]
            money += reward;
            cout << "[REWARD] gain: " << reward << " | money: " << money << "\n";
            
            // 5. Panggil fungsi dari ShopSystem[cite: 1]
            shopSystem->printOffer(money);
            
            // 6. Lanjut ronde (Otomatis terjadi dalam loop for)[cite: 2]
        }
        
        cout << "\n=== RUN END ===\n";
        cout << "Final money: " << money << "\n"; // Mencetak output uang akhir[cite: 3]
    }
};

// ==========================================
// 4. MAIN ENTRY POINT
// ==========================================
int main() {
    srand(time(0));

    // Menginisialisasi komponen
    RandomInputGenerator randomInput; 
    SimpleScoringRule simpleScore;
    BonusRewardRule bonusReward; 
    ShopSystem shop;

    // Menyuntikkan komponen ke dalam RunSession
    RunSession gameSession(&randomInput, &simpleScore, &bonusReward, &shop);

    // Menjalankan game
    gameSession.run();

    return 0;
}