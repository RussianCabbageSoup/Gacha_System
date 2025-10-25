#include <iostream>
#include <random>
#include <vector>
#include <conio.h>

using namespace std;

class GachaSystem {
private:

	vector<string> ThreeStarItem = { "Trash" };

	vector<string> FourStarItem = { "sword", "claymore", "bow", "catalyst", "spear" };

	vector<string> FourStarCharacter = { "Xianlin", "Fischil", "Bennett" };

	vector<string> FiveStarCharacter = { "Mona", "Jean", "Diluc", "Clee" };

	int countFOUR = 0;
	int countFIVE = 0;

	double calForFive() {
		if (countFIVE >= 80) {
			return 0.28;
		}
		else if (countFIVE >= 75) {
			return 0.12;
		}
		else if (countFIVE >= 70) {
			return 0.066;
		}
		else {
			return 0.006;
		}
	}

	double calcForFour() {
		if (countFOUR >= 7) {
			return 0.33;
		}
		else if (countFOUR >= 5) {
			return 0.16;
		}
		else {
			return 0.051;
		}
	}

public:

	random_device rd;
	mt19937 gen;
	uniform_real_distribution<> charDist;

	int counter = 0;

	GachaSystem() : gen(rd()), charDist(0.0, 1.0) {}

	void SingleWish() {

		double chance = charDist(gen);

		if (chance < calForFive() || countFIVE == 89) {
			uniform_int_distribution<> dis(0, FiveStarCharacter.size() - 1);
			cout << "5-Star: " << FiveStarCharacter[dis(gen)];
			countFIVE = 0;
		}
		else if (chance < calcForFour() || countFOUR == 9) {
			if (charDist(gen) < 0.5) {
				uniform_int_distribution<> dis(0, FourStarCharacter.size() - 1);
				cout << "4-Star char: " << FourStarCharacter[dis(gen)];
			}
			else {
				uniform_int_distribution<> dis(0, FourStarItem.size() - 1);
				cout << "4-Star weap: " << FourStarItem[dis(gen)];
			}

			countFOUR = 0;
		}
		else {
			cout << ThreeStarItem[0];
		}

		counter++;
		countFIVE++;
		countFOUR++;
	}

	void multiWish() {

		for (int i = 0; i < 10; i++) {
			SingleWish();
			cout << endl;
		}
	}
};

int main() {

	cout << "SIMULATOR" << endl;
	GachaSystem Wish;

	cout << "(1) to single wish\n(2) to 10-wish" << endl;

	while (true) {

		cout << endl;
		cout << "Total Pulls: " << Wish.counter << endl;
		cout << "____________________" << endl;

		int type = _getch();
		cout << endl;

		if (type == '1') {
			Wish.SingleWish();
			cout << endl;
		}
		else if (type == '2') {
			Wish.multiWish();
			cout << endl;
		}

	}
}