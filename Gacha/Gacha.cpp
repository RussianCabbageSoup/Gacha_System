#include <iostream>
#include <random>
#include <vector>
#include <conio.h>

using namespace std;

class GachaSystem {
private:

	vector<string> ThreeStarItem = { "Trash" };

	vector<string> FourStarItem = { "Церемониальный меч", "Меч Фавония", "Церемониальный двуручный меч", "Двуручный меч Фавония",
		"Гроза драконов", "Церемониальный мемуары", "Кодекс Фавония", "Церемониальный лук", "Боевой лук Фавония", "Драконий рык", 
		"Меч-флейта", "Дождерез", "Меч-колокол", "Копьё Фавония", "Око сознания", "Песнь Странника", "Ржавый лук", "Бесструнный"};

	vector<string> FourStarCharacter = { 
		"Айно", "Ифа", "Лань Янь", "Качина", "Ка Мин", "Шарлотта", "Линнет", "Мика", "Фарузан", "Кандакия", "Коллеи", "Юнь Цзинь",
		"Сиканоин Хэйдзо", "Горо" , "Тома", "Розария", "Сахароза", "Чун Юнь", "Беннет", "Нин Гуан", "Бэй Доу", "Эмбер", "Кэйа", "Лиза",
		"Далия", "Иансан", "Оророн", "Сетос", "Шеврёз", "Фремине", "Кавех", "Яо Яо", "Лайла", "Дори", "Куки Синобу", "Кирара",
		"Кудзё Сара", "Саю", "Янь Фэй", "Синь Янь", "Диона", "Ноэлль", "Фишль", "Син Цю", "Сян Лин", "Рэйзор", "Барбара" };

	vector<string> FiveStarCharacter = { "Мидзуки", "Тигнари", "Мона", "Дилюк", "Дэхья", "Кэ Цин", "Ци Ци", "Джинн"};

	vector<string> FiveStarItem = { "Небесный меч", "Волчья погибель", "Нефритовый Коршун", "Молитва Святым Ветрам", "Лук Амоса", 
		"Меч Сокола", "Небесное величие", "Небесная ось", "Небесный атлас", "Небесное крыло" };

	vector<int> FiveStarScore;
	vector <string> FiveStarDrop;

	int countFOUR = 0;
	int countFIVE = 0;
	int Rate = 0;

	double RateForFive() {
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

	double RateForFour() {
		if (countFOUR >= 8) {
			return 0.25;
		}
		else if (countFOUR >= 6) {
			return 0.11;
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

	GachaSystem(): gen(rd()), charDist(0.0, 1.0) {}

	void GetStat() {
		for (size_t i = 0; i < FiveStarScore.size(); i++) {
			cout << "  " << FiveStarDrop[i] << " - " << FiveStarScore[i] << endl;
		}
	}

	void SingleWish() {

		counter++;
		countFIVE++;
		countFOUR++;
		Rate++;

		double chance = charDist(gen);

		if (chance < RateForFive() || countFIVE == 90) {
			if (charDist(gen) < 0.5) {
				uniform_int_distribution<> dis(0, FiveStarCharacter.size() - 1);
				string drop = FiveStarCharacter[dis(gen)];
				cout << "5-Star " << drop;

				FiveStarDrop.push_back(drop);
				FiveStarScore.push_back(Rate);
				countFIVE = 0;
				Rate = 0;
			}
			else {
				uniform_int_distribution<> dis(0, FiveStarItem.size() - 1);
				string drop = FiveStarItem[dis(gen)];
				cout << "5-Star " << drop;

				FiveStarDrop.push_back(drop);
				FiveStarScore.push_back(Rate);
				countFIVE = 0;
				Rate = 0;
			}

		}
		else if (chance < RateForFour() || countFOUR == 10) {
			if (charDist(gen) < 0.5) {
				uniform_int_distribution<> dis(0, FourStarCharacter.size() - 1);
				cout << "4-Star " << FourStarCharacter[dis(gen)];
			}
			else {
				uniform_int_distribution<> dis(0, FourStarItem.size() - 1);
				cout << "4-Star	" << FourStarItem[dis(gen)];
			}

			countFOUR = 0;
		}
		else {
			cout << ThreeStarItem[0];
		}
	}

	void multiWish() {

		for (int i = 0; i < 10; i++) {
			SingleWish();
			cout << endl;
		}
	}
};

int main() {

	setlocale(LC_ALL, "Ru");
	cout << "SIMULATOR" << endl;
	cout << endl;
	GachaSystem Wish;

	cout << "Нажми (1), чтобы Помолится 1 раз\nНажми (2), чтобы Помолится 1 раз" << endl;

	while (true) {

		cout << endl;
		cout << "Всего скучено: " << Wish.counter << " (" << Wish.counter * 160 << " Примогемов)" << endl;
		cout << "5-Star лут: " << endl;
		Wish.GetStat();
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