#pragma once

#include <iostream>
#include <random>
#include <vector>
#include <conio.h>
#include <iomanip>
#include <algorithm>
#include <string>

class Banner_System {
protected:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> charDist;

    const std::vector<std::string> three_star_item = { "Trash" };

    const std::vector<std::string> four_star_item = {
        "Ceremonial Sword", "Favonius Sword", "Ceremonial Greatsword", "Favonius Greatsword",
        "Dragon's Thunder", "Ceremonial Memoirs", "Favonius Codex", "Ceremonial Bow", "Favonius Warbow", "Dragon's Roar",
        "Sword-Flute", "Raincutter", "Sword-Bell", "Favonius Lance", "Eye of Perception", "Wanderer's Song", "Rusty Bow", "Stringless" };

    const std::vector<std::string> four_star_character = {
        "Aino", "Ifa", "Lan Yan", "Kachina", "Ka Min", "Charlotte", "Lynette", "Mika", "Faruzan", "Candace", "Collei", "Yun Jin",
        "Shikanoin Heizou", "Gorou", "Thoma", "Rosaria", "Sucrose", "Chongyun", "Bennett", "Ningguang", "Beidou", "Amber", "Kaeya", "Lisa",
        "Dahlia", "Yanxiao", "Ororon", "Sethos", "Chevreuse", "Freminet", "Kaveh", "Yaoyao", "Layla", "Dori", "Kuki Shinobu", "Kirara",
        "Kujou Sara", "Sayu", "Yanfei", "Xinyan", "Diona", "Noelle", "Fischl", "Xingqiu", "Xiangling", "Razor", "Barbara" };

    const std::vector<std::string> five_star_character = { "Mizuki", "Tighnari", "Mona", "Diluc", "Dehya", "Keqing", "Qiqi", "Jean" };

    const std::vector<std::string> five_star_item = {
        "Skyward Sword", "Wolf's Gravestone", "Jade Cutter", "Prayer to the Sacred Winds", "Amos' Bow",
        "Falcon Sword", "Skyward Pride", "Skyward Spine", "Skyward Atlas", "Skyward Wing" };

    struct dynamic {
        struct lists {
            std::vector <std::pair<std::string, int>> five_star_drop;
            std::vector <std::pair<std::string, long>> four_star_drop;
            std::vector<std::pair<std::string, int>> character_drop;
            std::vector<std::string> inventory;
        };
        struct counters {
            int countForFourStar = 0;
            int countForFiveStar = 0;
            long currency_1 = 0;
            long currency_2 = 0;
            int totalPullCounter = 0;
        };
    };

    dynamic::lists drop_list;
    dynamic::counters counter;

    struct basis_params {
        struct probability {
            static constexpr double baseFiveStarChance = 0.0063;
            static constexpr double baseFourStarChance = 0.051;
            static constexpr double baseEqualChance = 0.5;
            static constexpr double baseEventCharChance = 0.585;
            static constexpr std::pair<double, double> factor_pity = { 0.057, 4.15 };
            static constexpr double factor_default = 0.000015;

            static constexpr double baseChance_eventItem = 0.008;
        };
        struct limits {
            static constexpr int startPityValue = 74;
            static constexpr int fiveStarLimit = 90;
            static constexpr int fourStarLimit = 10;
            static constexpr int constLimit = 6;

            static constexpr int startPityItem = 65;
            static constexpr int fiveStarItemLimit = 80;
        };
        struct currency{
            static constexpr int baseBlessForFiveStar = 10;
            static constexpr int baseBlessForFourStar = 2;
            static constexpr int limitBlessForFiveStar = 25;
            static constexpr int limitBlessForFourStar = 5;
            static constexpr int starDustValue = 18;
        };
    };

    bool checkDuplicate(std::string drop) {
        bool duplicate = false;
        bool isLastConst = false;
        size_t index;

        for (size_t i = 0; i < drop_list.character_drop.size(); i++) {
            if (drop == drop_list.character_drop[i].first) {
                duplicate = true;
                index = i;
                break;
            }
        }
        if (!duplicate) {
            drop_list.character_drop.push_back({ drop, 0 });
        }
        else {
            if (drop_list.character_drop[index].second < basis_params::limits::constLimit) { drop_list.character_drop[index].second++; }
            else isLastConst = true;
        }
        return isLastConst;
    }

public:

    Banner_System() : gen(rd()), charDist(0.0, 1.0) {}

    std::pair<int, int> getCurrentPity() {
        return { counter.countForFiveStar, counter.countForFourStar };
    }

    int getPulls() {
        return counter.totalPullCounter;
    }

    void getCurrency() {
        std::cout << "Star Bless: " << counter.currency_1 << " (" << counter.currency_1 / 5.0 << ")" << std::endl;
        std::cout << "Stardust: " << counter.currency_2 << std::endl;
    }

    void getInventory() {
        if (!drop_list.inventory.empty()) {
            for (size_t i = 1; i < drop_list.inventory.size() + 1; i++) {
                std::cout << std::setw(30) << drop_list.inventory[i - 1];
                if (i % 3 == 0) std::cout << std::endl;
            }
        }
        else {
            std::cout << "You haven't obtained any items" << std::endl;
        }
        std::cout << std::endl;
    }

    void constellation() {
        if (!drop_list.character_drop.empty()) {
            std::sort(drop_list.character_drop.begin(), drop_list.character_drop.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
                return a.second > b.second; });

            for (size_t i = 1; i < drop_list.character_drop.size() + 1; i++) {
                std::cout << std::setw(30) << drop_list.character_drop[i - 1].first << " " << drop_list.character_drop[i - 1].second;
                if (i != 0 && i % 3 == 0) std::cout << std::endl;
            }
        }
        else {
            std::cout << "You don't have any characters yet" << std::endl;
        }
    }

    void getStatistic(bool debug = false) {

        double avrFiveStar = 0;
        double avrFourStar = 0;

        std::vector<int> distFiveStar(basis_params::limits::fiveStarLimit, 0);
        std::vector<int> distFourStar(basis_params::limits::fourStarLimit, 0);

        if (!drop_list.five_star_drop.empty()) {
            for (size_t i = 1; i < drop_list.five_star_drop.size() + 1; i++) {
                if (!debug) {
                    std::cout << std::setw(30) << drop_list.five_star_drop[i - 1].first << " - " << std::setw(2) << drop_list.five_star_drop[i - 1].second;
                    if (i != 0 && i % 3 == 0) std::cout << std::endl;
                }
                avrFiveStar += drop_list.five_star_drop[i - 1].second;
            }
            avrFiveStar /= (double)drop_list.five_star_drop.size();
            std::cout << std::endl;

            for (size_t i = 0; i < drop_list.five_star_drop.size(); i++) {
                distFiveStar[drop_list.five_star_drop[i].second - 1]++;
            }
        }
        else {
            std::cout << "You haven't obtained any 5-star drops yet" << std::endl;
        }

        if (!drop_list.four_star_drop.empty()) {
            for (size_t i = 1; i < drop_list.four_star_drop.size() + 1; i++) {
                avrFourStar += drop_list.four_star_drop[i - 1].second;
            }
            avrFourStar /= (double)drop_list.four_star_drop.size();
            for (size_t i = 0; i < drop_list.four_star_drop.size(); i++) {
                if (!(drop_list.four_star_drop[i].second > basis_params::limits::fourStarLimit)) {
                    distFourStar[drop_list.four_star_drop[i].second - 1]++;
                }
            }
        }

        std::cout << std::endl;
        std::cout << std::setw(15) << "Average for five star: " << avrFiveStar << std::endl;
        std::cout << std::setw(15) << "Average for four star: " << avrFourStar << std::endl;

        if (debug) {
            std::cout << std::endl;
            std::cout << std::setw(18) << "Distribution for five star:" << std::endl;
            std::cout << std::endl;

            for (size_t i = 1; i < distFiveStar.size() + 1; i++) {
                long sum = 0;
                for (size_t j = 0; j < distFiveStar.size(); j++) { sum += distFiveStar[j]; }

                std::cout << std::setw(12) << i << ": " << std::setw(7) << distFiveStar[i - 1];
                if (i != 0 && i % 5 == 0) std::cout << std::endl;
            }

            std::cout << std::endl;
            std::cout << std::setw(18) << "Distribution for four star:" << std::endl;
            std::cout << std::endl;

            for (size_t i = 1; i < distFourStar.size() + 1; i++) {
                long sum = 0;
                for (size_t j = 0; j < distFourStar.size(); j++) { sum += distFourStar[j]; }

                std::cout << std::setw(15) << i << ": " << std::setw(8) << distFourStar[i - 1];
                if (i != 0 && i % 2 == 0) std::cout << std::endl;
            }
        }

        if (!debug) {
            std::cout << std::endl;
            std::cout << "Total pulls: " << getPulls() << " (" << getPulls() * 160 << " Primogems)" << std::endl;
            getCurrency();
        }
    }
};

class Default_Banner : public Banner_System {
private:
    double calcProbability(int currentPull, bool isPity) {
        if (isPity) {
            return basis_params::probability::factor_pity.first * currentPull - basis_params::probability::factor_pity.second;
        }
        else {
            return  basis_params::probability::baseFiveStarChance + (basis_params::probability::factor_default * currentPull);
        }
    }

    double rateForFiveStar(int currentPull) {
        if (currentPull >= basis_params::limits::fiveStarLimit) { return 1.0; }
        if (currentPull >= basis_params::limits::startPityValue) { return calcProbability(currentPull, true); }
        else { return calcProbability(currentPull, false); }
    }

    double rateForFourStar(int currentPull) {
        if (currentPull >= basis_params::limits::fourStarLimit) { return 1.0; }
        else { return basis_params::probability::baseFourStarChance; }
    }
public:
    void singleWish(bool debug = false) {

        counter.totalPullCounter++;
        counter.countForFiveStar++;
        counter.countForFourStar++;

        double chance = charDist(gen);
        //std::cout << rateForFiveStar(numeric_space.countForFiveStar) << " ";
        if (chance < rateForFiveStar(counter.countForFiveStar)) {
            // Character or Item1
            if (charDist(gen) < basis_params::probability::baseEqualChance) {
                std::uniform_int_distribution<size_t> dis(0, five_star_character.size() - 1);
                std::string drop = five_star_character[dis(gen)];
                if (!debug) { std::cout << "\033[33m5-STAR " << drop << "\033[0m"; }

                if (!debug) {
                    if (checkDuplicate(drop)) counter.currency_1 += basis_params::currency::limitBlessForFiveStar;
                    else counter.currency_1 += basis_params::currency::baseBlessForFiveStar;
                }

                drop_list.five_star_drop.push_back({ drop, counter.countForFiveStar });

                counter.countForFiveStar = 0;
            }
            else {
                std::uniform_int_distribution<size_t> dis(0, five_star_item.size() - 1);
                std::string drop = five_star_item[dis(gen)];
                if (!debug) { std::cout << "\033[33m5-STAR " << drop << "\033[0m"; }

                counter.currency_1 += basis_params::currency::baseBlessForFiveStar;
                drop_list.five_star_drop.push_back({ drop, counter.countForFiveStar });
                drop_list.inventory.push_back(drop);
                counter.countForFiveStar = 0;
            }

        }
        else if (chance < rateForFourStar(counter.countForFourStar)) {
            // Character or Item
            if (charDist(gen) < basis_params::probability::baseEqualChance) {
                std::uniform_int_distribution<size_t> dis(0, four_star_character.size() - 1);
                std::string drop = four_star_character[dis(gen)];
                if (!debug) { std::cout << "\033[35m4-Star " << drop << "\033[0m"; }

                if (!debug) {
                    if (checkDuplicate(drop)) counter.currency_1 += basis_params::currency::limitBlessForFourStar;
                    else counter.currency_1 += basis_params::currency::baseBlessForFourStar;
                }
                drop_list.four_star_drop.push_back({ drop, counter.countForFourStar });
            }
            else {
                std::uniform_int_distribution<size_t> dis(0, four_star_item.size() - 1);
                std::string drop = four_star_item[dis(gen)];
                if (!debug) { std::cout << "\033[35m4-Star " << drop << "\033[0m"; }

                counter.currency_1 += basis_params::currency::baseBlessForFourStar;
                drop_list.inventory.push_back(drop);
                drop_list.four_star_drop.push_back({ drop, counter.countForFourStar });
            }

            counter.countForFourStar = 0;
        }
        else {
            if (!debug) { std::cout << "\033[36m" << three_star_item[0] << "\033[0m"; }
            counter.currency_2 += basis_params::currency::starDustValue;
        }
    }

    void multiWish(long n, bool debug = false) {
        for (long i = 0; i < n; i++) {
            singleWish(debug);
            if (!debug) { std::cout << std::endl; }
        }
    }
};

class Event_CharacterBanner : public Banner_System {
private:
    const std::string eventFiveStar = "EVENT";
    const std::vector<std::string> eventFourStar = { "event1", "event2", "event3" };

    bool gotDefaultFiveStar = false;
    bool gotDefaultFourStar = false;

    double calcProbability(int currentPull, bool isPity) {
        if (isPity) {
            return basis_params::probability::factor_pity.first * currentPull - basis_params::probability::factor_pity.second;
        }
        else {
            return  basis_params::probability::baseFiveStarChance + (basis_params::probability::factor_default * currentPull);
        }
    }

    double rateForFiveStar(int currentPull) {
        if (currentPull >= basis_params::limits::fiveStarLimit) { return 1.0; }
        if (currentPull >= basis_params::limits::startPityValue) { return calcProbability(currentPull, true); }
        else { return calcProbability(currentPull, false); }
    }

    double rateForFourStar(int currentPull) {
        if (currentPull >= basis_params::limits::fourStarLimit) { return 1.0; }
        else { return basis_params::probability::baseFourStarChance; }
    }

public:

    void singleWish(bool debug = false) {

        counter.totalPullCounter++;
        counter.countForFiveStar++;
        counter.countForFourStar++;

        double chance = charDist(gen);
        //std::cout << rateForFiveStar(numeric_space.countForFiveStar) << " ";
        if (chance < rateForFiveStar(counter.countForFiveStar)) {
            if (charDist(gen) < basis_params::probability::baseEventCharChance || gotDefaultFiveStar) {

                if (!debug) { std::cout << "\033[33m5-STAR " << eventFiveStar << "\033[0m"; }

                if (!debug) {
                    if (checkDuplicate(eventFiveStar)) counter.currency_1 += basis_params::currency::limitBlessForFiveStar;
                    else counter.currency_1 += basis_params::currency::baseBlessForFiveStar;
                }

                drop_list.five_star_drop.push_back({ eventFiveStar, counter.countForFiveStar });

                counter.countForFiveStar = 0;
                gotDefaultFiveStar = false;
            }
            else {
                std::uniform_int_distribution<size_t> dis(0, five_star_character.size() - 1);
                std::string drop = five_star_character[dis(gen)];
                if (!debug) { std::cout << "\033[33m5-STAR " << drop << "\033[0m"; }

                if (!debug) {
                    if (checkDuplicate(drop)) counter.currency_1 += basis_params::currency::limitBlessForFiveStar;
                    else counter.currency_1 += basis_params::currency::baseBlessForFiveStar;
                }

                drop_list.five_star_drop.push_back({ drop, counter.countForFiveStar });

                counter.countForFiveStar = 0;
                gotDefaultFiveStar = true;
            }

        }
        else if (chance < rateForFourStar(counter.countForFourStar)) {
            if (charDist(gen) < basis_params::probability::baseEqualChance || gotDefaultFourStar) {
                std::uniform_int_distribution<size_t> dis(0, eventFourStar.size() - 1);
                std::string drop = eventFourStar[dis(gen)];

                if (!debug) { std::cout << "\033[35m4-Star " << drop << "\033[0m"; }

                if (!debug) {
                    if (checkDuplicate(drop)) counter.currency_1 += basis_params::currency::limitBlessForFourStar;
                    else counter.currency_1 += basis_params::currency::baseBlessForFourStar;
                }

                drop_list.four_star_drop.push_back({ drop, counter.countForFourStar });
                gotDefaultFourStar = false;
            }
            else {
                if (charDist(gen) < basis_params::probability::baseEqualChance) {
                    std::uniform_int_distribution<size_t> dis(0, four_star_character.size() - 1);
                    std::string drop = four_star_character[dis(gen)];
                    if (!debug) { std::cout << "\033[35m4-Star " << drop << "\033[0m"; }

                    if (!debug) {
                        if (checkDuplicate(drop)) counter.currency_1 += basis_params::currency::limitBlessForFourStar;
                        else counter.currency_1 += basis_params::currency::baseBlessForFourStar;
                    }
                    drop_list.four_star_drop.push_back({ drop, counter.countForFourStar });
                }
                else {
                    std::uniform_int_distribution<size_t> dis(0, four_star_item.size() - 1);
                    std::string drop = four_star_item[dis(gen)];
                    if (!debug) { std::cout << "\033[35m4-Star " << drop << "\033[0m"; }

                    counter.currency_1 += basis_params::currency::baseBlessForFourStar;
                    drop_list.inventory.push_back(drop);
                    drop_list.four_star_drop.push_back({ drop, counter.countForFourStar });
                }

                gotDefaultFourStar = true;
            }
            counter.countForFourStar = 0;
        }
        else {
            if (!debug) { std::cout << "\033[36m" << three_star_item[0] << "\033[0m"; }
            counter.currency_2 += basis_params::currency::starDustValue;
        }
    }

    void multiWish(long n, bool debug = false) {
        for (long i = 0; i < n; i++) {
            singleWish(debug);
            if (!debug) { std::cout << std::endl; }
        }
    }
};

class Event_WeaponBanner {

};

class Debug_System {
private:

    Default_Banner object_1;
    Event_CharacterBanner object_2;

    bool isDefault;

    void distTest() {
        long n;
        std::cout << "> "; std::cin >> n;

        if (isDefault) {
            object_1.multiWish(n, true);
            object_1.getStatistic(true);
        }
        else {
            object_2.multiWish(n, true);
            object_2.getStatistic(true);
        }
    }
public:

    Debug_System(bool v) : isDefault(v) {}

    void start() {
        std::string command;
        while (true) {
            std::cout << ">> "; std::getline(std::cin, command);
            std::cout << std::endl;

            if (command == "exit") { break; }
            else if (command == "mw") { distTest(); }
            else { std::cout << "command not found\n" << std::endl; }
        }
        command.clear();
    }
};

static constexpr int ESC_KEY = 27;
int start_banner();

int start_EventBanner() {

    Event_CharacterBanner eventBanner;

    std::cout << "\n|| EVENT BANNER ||\n\n";
    std::cout << "(1) Wish once\n(2) Wish 10 times\n(3) View inventory\n(4) View statistics" << std::endl;

    while (true) {
        std::cout << std::endl;
        std::pair<int, int> current_pity = eventBanner.getCurrentPity();
        std::cout << "Pity 5-Star: " << current_pity.first << std::endl;
        std::cout << "Pity 4-Star: " << current_pity.second << std::endl;

        std::cout << "____________________\n" << std::endl;

        bool correctKey = false;

        while (!correctKey) {
            int click = _getch();

            switch (click) {
            case('1'):
                eventBanner.singleWish();
                std::cout << std::endl;
                correctKey = true;
                break;

            case('2'):
                eventBanner.multiWish(10);
                correctKey = true;
                break;
            
            case('3'):
                eventBanner.getInventory();
                correctKey = true;
                break;
            
            case('4'):
                std::cout << "Constellations: " << std::endl;
                eventBanner.constellation();

                std::cout << std::endl;

                std::cout << "Statistics: " << std::endl;
                eventBanner.getStatistic();
                correctKey = true;
                break;
            
            case(ESC_KEY): return 0;
            // debug
            case('0'):
                if (click == '0') {
                    int doubleCheck = _getch();
                    if (doubleCheck == '0') {
                        std::cout << "// debug //" << std::endl;
                        std::cout << std::endl;
                        Debug_System init(false);
                        init.start();
                    }
                }
                correctKey = true;
                break;
            }
        }
    }
    return 0;
}

int start_DefaultBanner() {

    Default_Banner defaultBanner;

    std::cout << "\n|| DEFAULT BANNER ||\n\n";
    std::cout << "(1) Wish once\n(2) Wish 10 times\n(3) View inventory\n(4) View statistics" << std::endl;

    while (true) {

        std::cout << std::endl;
        std::pair<int, int> current_pity = defaultBanner.getCurrentPity();
        std::cout << "Pity 5-Star: " << current_pity.first << std::endl;
        std::cout << "Pity 4-Star: " << current_pity.second << std::endl;

        std::cout << "____________________\n" << std::endl;

        bool correctKey = false;

        while (!correctKey) {
            int click = _getch();

            switch (click) {
            case('1'):
                defaultBanner.singleWish();
                std::cout << std::endl;
                correctKey = true;
                break;

            case('2'):
                defaultBanner.multiWish(10);
                correctKey = true;
                break;

            case('3'):
                defaultBanner.getInventory();
                correctKey = true;
                break;

            case('4'):
                std::cout << "Constellations: " << std::endl;
                defaultBanner.constellation();
                std::cout << std::endl;

                std::cout << "Statistics: " << std::endl;
                defaultBanner.getStatistic();
                correctKey = true;
                break;

            case(ESC_KEY): return 0;
                // debug
            case('0'):
                int doubleCheck = _getch();

                if (doubleCheck == '0') {
                    std::cout << "// debug //" << std::endl;
                    std::cout << std::endl;
                    Debug_System init(true);
                    init.start();
                }
                correctKey = true;
                break;
            }
        }
    }
    return 0;
}

int start_banner() {
    std::cout << "\nBANNER SIMULATOR" << std::endl;

    while (true) {
        std::cout << "\n(1) Event Banner\n(2) Default Banner" << std::endl;

        bool correctKey = false;

        while (!correctKey) {
            int click = _getch();

            switch (click) {
            case('1'): start_EventBanner(); correctKey = true; break;
            case('2'): start_DefaultBanner(); correctKey = true; break;
            case(ESC_KEY): return 0;
            }
        }
    }
}
