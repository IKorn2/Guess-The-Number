#define CURL_STATICLIB
#include <iostream>
#include <Windows.h>
#include <string>
#include <sstream>
#include "Colorful text.h"
#include "curl.h"

using namespace std;

#ifdef max
#undef max
#endif

enum Menu_ch {
	START_BTN = 1,
	LANGUAGE_BTN,
	EXIT_BTN

};

enum Lng_ch {
	ENGLISH = 1,
	UKRAINIAN
};

enum Start_game_ch {
	DEFAULT_GAME = 1,
	CHAPTER_CHANGE
};

enum Stage_ch {
	FIRST_STAGE = 1,
	SECOND_STAGE
};

enum Final_ch {
	TRY_AGAIN_BTN = 1,
	QUIT_BTN
};

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
	((string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

void random_org_generator(unsigned int& number, unsigned short int lng, unsigned int max) {
	CURL* curl;
	CURLcode res;
	string readBuffer;

	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();

	if (curl)
	{
		string url = "https://www.random.org/integers/?num=1&min=1&max=" + to_string(max) + "&col=1&base=10&format=plain&rnd=new";

		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

		res = curl_easy_perform(curl);

		if (res != CURLE_OK)
		{
			switch (lng)
			{
			case ENGLISH:
				cerr << dye::bright_white_on_red("Network connection error: ") << dye::bright_white_on_red(curl_easy_strerror(res)) << endl;
				break;
			case UKRAINIAN:
				cerr << dye::bright_white_on_red("Помилка підключення до мережі: ") << dye::bright_white_on_red(curl_easy_strerror(res)) << endl;
				break;
			}
			exit(2);
		}
		else
		{
			istringstream iss(readBuffer);
			string line;
			while (getline(iss, line))
			{
				number = stoi(line);
			}
		}
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
}

void char_error(unsigned short int lng) {
	switch (lng)
	{
	case ENGLISH:
		cerr << dye::bright_white_on_red("Input Error. Try again.") << endl;
		system("pause");
		break;
	case UKRAINIAN:
		cerr << dye::bright_white_on_red("Помилка введення. Спробуйте ще раз.") << endl;
		system("pause");
		break;
	}
}

void num_error(unsigned short int lng) {
	switch (lng)
	{
	case ENGLISH:
		cerr << dye::bright_white_on_red("Invalid character. Use numbers within the specified range to navigate the menu.") << endl;
		system("pause");
		break;
	case UKRAINIAN:
		cerr << dye::bright_white_on_red("Неправильний символ. Для навігації по меню використовуйте цифри в заданому діапазоні.") << endl;
		system("pause");
		break;
	}
}

void text_menu_start(unsigned short int& choice, unsigned short int lng) {
	bool loop = true;
	do
	{
		switch (lng)
		{
		case ENGLISH:
			cout << "\t\t\t" << dye::light_red_on_bright_white("Welcome to \"Guess My Number\"") << endl; Sleep(100);
			cout << dye::green("1)") << " " << dye::red("Start the game") << endl; Sleep(100);
			cout << dye::green("2)") << " " << dye::red("Language") << endl; Sleep(100);
			cout << dye::green("3)") << " " << dye::red("Exit the game") << endl; Sleep(100);
			cout << dye::bright_white("Choice:") << " ";
			break;
		case UKRAINIAN:
			cout << "\t\t\t" << dye::light_red_on_bright_white("Вітаємо у \"Вгадай Моє Число\"") << endl; Sleep(100);
			cout << dye::green("1)") << " " << dye::red("Розпочати гру") << endl; Sleep(100);
			cout << dye::green("2)") << " " << dye::red("Мова") << endl; Sleep(100);
			cout << dye::green("3)") << " " << dye::red("Вийти з гри") << endl; Sleep(100);
			cout << dye::bright_white("Вибір:") << " ";
			break;
		}
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			loop = true;
			char_error(lng);
		}
		else if (choice < START_BTN || choice > EXIT_BTN) {
			num_error(lng);
			loop = true;
		}
		else
		{
			loop = false;
		}
		system("cls");
	} while (loop);
}

void first_stage(unsigned short int lng, unsigned int& first_counter) {
	system("cls");
	bool loop = true;
	unsigned int dice_res = 0, user_res = 0;
	switch (lng)
	{
	case ENGLISH:
		cout << "\t\t\t" << dye::light_red_on_bright_white("\"Guess My Number\"") << dye::bright_white(" — First Stage") << endl; Sleep(100);
		cout << dye::bright_white_on_yellow("INFO:"); Sleep(100); cout << dye::yellow(" This game is pure fortune.\n"); Sleep(100);
		cout << dye::yellow("In the first stage, I will roll a dice, "); Sleep(100);
		cout << dye::yellow("and you have to guess the number (from 1 to 6) "); Sleep(100);
		cout << dye::yellow("that you think has come up.\n"); Sleep(100);
		cout << dye::yellow("Try to do it in the least number of attempts "); Sleep(100);
		cout << dye::yellow("(after each attempt, the dice are rolled again).\n"); Sleep(100);
		break;
	case UKRAINIAN:
		cout << "\t\t\t" << dye::light_red_on_bright_white("\"Вгадай Моє Число\"") << dye::bright_white(" — Перший етап") << endl; Sleep(100);
		cout << dye::bright_white_on_yellow("Довідка:"); Sleep(100); cout << dye::yellow(" Ця гра — чиста фортуна.\n"); Sleep(100);
		cout << dye::yellow("На першому етапі я кидатиму гральний кубик, "); Sleep(100);
		cout << dye::yellow("а ви повинні вгадати число (від 1 до 6), "); Sleep(100);
		cout << dye::yellow("яке, на вашу думку, випало.\n"); Sleep(100);
		cout << dye::yellow("Постарайтеся зробити це за найменшу кількість спроб "); Sleep(100);
		cout << dye::yellow("(після кожної спроби кубик кидається знову).\n"); Sleep(100);
		break;
	}
	do
	{
		++first_counter;
		switch (lng)
		{
		case ENGLISH:
			cout << dye::green("(Attempt: ") << dye::green(first_counter) << dye::green(")") << dye::red(" Guess the number.") << endl;
			cout << dye::bright_white("Your answer:") << " ";
			break;
		case UKRAINIAN:
			cout << dye::green("(Спроба: ") << dye::green(first_counter) << dye::green(")") << dye::red(" Вгадай число.") << endl;
			cout << dye::bright_white("Ваша відповідь:") << " ";
			break;
		}
		cin >> user_res;
		random_org_generator(dice_res, lng, 6);
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			loop = true;
			char_error(lng);
		}
		else if (user_res < 1 || user_res > 6) {
			num_error(lng);
			loop = true;
		}
		else {
			if (first_counter == 1 && user_res == dice_res)
			{
				switch (lng)
				{
				case ENGLISH:
					cout << dye::yellow("Wow, that was fast. Well done.") << endl;
					break;
				case UKRAINIAN:
					cout << dye::yellow("Ого, так швидко. Молодець") << endl;
					break;
				}
				system("pause");
				loop = false;
			}
			else if (user_res == dice_res)
			{
				switch (lng)
				{
				case ENGLISH:
					cout << dye::yellow("Well done, good job.") << endl;
					break;
				case UKRAINIAN:
					cout << dye::yellow("Молодець, гарна робота.") << endl;
					break;
				}
				system("pause");
				loop = false;
			}
			else
			{
				switch (lng)
				{
				case ENGLISH:
					cout << dye::yellow("No. Answer: ") << dice_res << endl;
					break;
				case UKRAINIAN:
					cout << dye::yellow("Ні. Відповідь: ") << dice_res << endl;
					break;
				}
				loop = true;
			}
		}
	} while (loop);
}

void second_stage(unsigned short int lng, unsigned int& second_counter) {
	system("cls");
	bool loop = true;
	unsigned int dice_res = 0, user_res = 0;
	switch (lng)
	{
	case ENGLISH:
		cout << "\t\t\t" << dye::light_red_on_bright_white("\"Guess My Number\"") << dye::bright_white(" — Second Stage") << endl; Sleep(100);
		cout << dye::bright_white_on_yellow("INFO:"); Sleep(100); cout << dye::yellow(" This game is pure fortune.\n"); Sleep(100);
		cout << dye::yellow("Now I'm going to think of any number between 1 and 100, "); Sleep(100);
		cout << dye::yellow("and you have to guess it. \n"); Sleep(100);
		cout << dye::yellow("Don't worry, I'm going to help you a little bit.\n"); Sleep(100);
		cout << dye::yellow("Try to do it in the least number of attempts.\n"); Sleep(100);
		break;
	case UKRAINIAN:
		cout << "\t\t\t" << dye::light_red_on_bright_white("\"Вгадай Моє Число\"") << dye::bright_white(" — Другий етап") << endl; Sleep(100);
		cout << dye::bright_white_on_yellow("Довідка:"); Sleep(100); cout << dye::yellow(" Ця гра — чиста фортуна.\n"); Sleep(100);
		cout << dye::yellow("Тепер я загадаю будь-яке число від 1 до 100, "); Sleep(100);
		cout << dye::yellow("а ви повинні вгадати його.\n"); Sleep(100);
		cout << dye::yellow("Не бійтеся, я трохи допоможу.\n"); Sleep(100);
		cout << dye::yellow("Постарайтеся зробити це за найменшу кількість спроб.\n"); Sleep(100);
		break;
	}
	random_org_generator(dice_res, lng, 100);
	do
	{
		++second_counter;
		switch (lng)
		{
		case ENGLISH:
			cout << dye::green("(Attempt: ") << dye::green(second_counter) << dye::green(")") << dye::red(" Guess the number.") << endl;
			cout << dye::bright_white("Your answer:") << " ";
			break;
		case UKRAINIAN:
			cout << dye::green("(Спроба: ") << dye::green(second_counter) << dye::green(")") << dye::red(" Вгадай число.") << endl;
			cout << dye::bright_white("Ваша відповідь:") << " ";
			break;
		}
		cin >> user_res;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			loop = true;
			char_error(lng);
		}
		else if (user_res < 1 || user_res > 100) {
			num_error(lng);
			loop = true;
		}
		else {
			if (second_counter == 1 && user_res == dice_res)
			{
				switch (lng)
				{
				case ENGLISH:
					cout << dye::yellow("Wow, that was fast. Well done.") << endl;
					break;
				case UKRAINIAN:
					cout << dye::yellow("Ого, так швидко. Молодець") << endl;
					break;
					system("pause");
				}
				loop = false;
			}
			else if (user_res == dice_res)
			{
				switch (lng)
				{
				case ENGLISH:
					cout << dye::yellow("Well done, good job.") << endl;
					break;
				case UKRAINIAN:
					cout << dye::yellow("Молодець, гарна робота.") << endl;
					break;
				}
				system("pause");
				loop = false;
			}
			else if (user_res > dice_res)
			{
				switch (lng)
				{
				case ENGLISH:
					cout << dye::red("\tLower") << endl;
					break;
				case UKRAINIAN:
					cout << dye::red("\tМенше") << endl;
					break;
				}
				loop = true;
			}
			else
			{
				switch (lng)
				{
				case ENGLISH:
					cout << dye::green("\tHigher") << endl;
					break;
				case UKRAINIAN:
					cout << dye::green("\tБільше") << endl;
					break;
				}
				loop = true;
			}
		}
	} while (loop);
}

void stats(unsigned int first_counter, unsigned int second_counter, unsigned short int lng) {
	if (second_counter == 0)
	{
		switch (lng)
		{
		case ENGLISH:
			cout << dye::bright_white_on_yellow("Your attempts :") << " " << dye::yellow(first_counter) << endl;
			break;
		case UKRAINIAN:
			cout << dye::bright_white_on_yellow("Ваші спроби :") << " " << dye::yellow(first_counter) << endl;
			break;
		}
	}
	else if (first_counter == 0)
	{
		switch (lng)
		{
		case ENGLISH:
			cout << dye::bright_white_on_yellow("Your attempts :") << " " << dye::yellow(second_counter) << endl;
			break;
		case UKRAINIAN:
			cout << dye::bright_white_on_yellow("Ваші спроби :") << " " << dye::yellow(second_counter) << endl;
			break;
		}
	}
	else
	{
		switch (lng)
		{
		case ENGLISH:
			cout << dye::bright_white_on_yellow("Your attempts :") << " " << dye::yellow(first_counter + second_counter) << endl;
			cout << dye::bright_white_on_yellow("First stage :") << " " << dye::yellow(first_counter) << endl;
			cout << dye::bright_white_on_yellow("Second stage :") << " " << dye::yellow(second_counter) << endl;
			break;
		case UKRAINIAN:
			cout << dye::bright_white_on_yellow("Ваші спроби :") << " " << dye::yellow(first_counter + second_counter) << endl;
			cout << dye::bright_white_on_yellow("Перший етап :") << " " << dye::yellow(first_counter) << endl;
			cout << dye::bright_white_on_yellow("Другий етап :") << " " << dye::yellow(second_counter) << endl;
			break;
		}
	}
}

void start_game(unsigned short int lng, unsigned int& first_counter, unsigned int& second_counter) {
	bool loop = true;
	short unsigned int choice = 0;
	do
	{
		switch (lng)
		{
		case ENGLISH:
			cout << "\t\t\t" << dye::light_red_on_bright_white("\"Guess My Number\"") << endl; Sleep(100);
			cout << dye::green("1)") << " " << dye::red("Default game") << endl; Sleep(100);
			cout << dye::green("2)") << " " << dye::red("Select a stage") << endl; Sleep(100);
			cout << dye::bright_white("Choice:") << " ";
			break;
		case UKRAINIAN:
			cout << "\t\t\t" << dye::light_red_on_bright_white("\"Вгадай Моє Число\"") << endl; Sleep(100);
			cout << dye::green("1)") << " " << dye::red("Звичайна гра") << endl; Sleep(100);
			cout << dye::green("2)") << " " << dye::red("Вибрати етап") << endl; Sleep(100);
			cout << dye::bright_white("Вибір:") << " ";
			break;
		}
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			loop = true;
			char_error(lng);
		}
		else if (choice < START_BTN || choice > EXIT_BTN) {
			num_error(lng);
			loop = true;
		}
		else
		{
			switch (choice)
			{
			case DEFAULT_GAME:
				first_stage(lng, first_counter);
				second_stage(lng, second_counter);
				stats(first_counter, second_counter, lng);
				loop = false;
				break;
			case CHAPTER_CHANGE:
				system("cls");
				switch (lng)
				{
				case ENGLISH:
					cout << "\t\t\t" << dye::light_red_on_bright_white("\"Guess My Number\"") << endl; Sleep(100);
					cout << dye::green("1)") << " " << dye::red("First stage") << endl; Sleep(100);
					cout << dye::green("2)") << " " << dye::red("Second stage") << endl; Sleep(100);
					cout << dye::bright_white("Choice:") << " ";
					break;
				case UKRAINIAN:
					cout << "\t\t\t" << dye::light_red_on_bright_white("\"Вгадай Моє Число\"") << endl; Sleep(100);
					cout << dye::green("1)") << " " << dye::red("Перший етап") << endl; Sleep(100);
					cout << dye::green("2)") << " " << dye::red("Другий етап") << endl; Sleep(100);
					cout << dye::bright_white("Вибір:") << " ";
					break;
				}
				cin >> choice;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					loop = true;
					char_error(lng);
				}
				else if (choice < FIRST_STAGE || choice > SECOND_STAGE) {
					num_error(lng);
					loop = true;
				}
				else {
					switch (choice)
					{
					case FIRST_STAGE:
						first_stage(lng, first_counter);
						stats(first_counter, second_counter, lng);
						break;
					case SECOND_STAGE:
						second_stage(lng, second_counter);
						stats(first_counter, second_counter, lng);
						break;
					}
				}
				loop = false;
			}
			break;
		}
		system("cls");
	} while (loop);
}

void language_change(unsigned short int& lng) {
	bool loop = true;
	unsigned short int prev_lng = lng;

	do
	{
		system("cls");
		switch (lng)
		{
		case ENGLISH:
			cout << "\t\t\t" << dye::light_red_on_bright_white("Guess My Number") << endl << "\t\tChange Language" << endl; Sleep(100);
			break;
		case UKRAINIAN:
			cout << "\t\t\t" << dye::light_red_on_bright_white("Вгадай Моє Число") << endl << "\t\tЗміна мови" << endl; Sleep(100);
			break;
		}
		cout << dye::green("1)") << " " << dye::red("English") << endl; Sleep(100);
		cout << dye::green("2)") << " " << dye::red("Українська") << endl; Sleep(100);
		switch (lng)
		{
		case ENGLISH:
			cout << dye::bright_white("Choice:") << " ";
			break;
		case UKRAINIAN:
			cout << dye::bright_white("Вибір:") << " ";
			break;
		}
		cin >> lng;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			lng = prev_lng;
			char_error(lng);
			loop = true;
			system("pause");
		}
		else if (lng >= ENGLISH && lng <= UKRAINIAN)
		{
			loop = false;
		}
		else
		{
			lng = prev_lng;
			num_error(lng);
			loop = true;
		}
		system("cls");
	} while (loop);
}

int final_choice(unsigned short int lng) {
	unsigned short int choice = 0;
	bool loop = true;
	while (loop)
	{
		switch (lng)
		{
		case ENGLISH:
			cout << dye::green("1)") << " " << dye::red("Try again") << endl; Sleep(100);
			cout << dye::green("2)") << " " << dye::red("Quit the game") << endl; Sleep(100);
			cout << dye::bright_white("Choice:") << " ";
			break;
		case UKRAINIAN:
			cout << dye::green("1)") << " " << dye::red("Спробувати ще") << endl; Sleep(100);
			cout << dye::green("2)") << " " << dye::red("Вийти з гри") << endl; Sleep(100);
			cout << dye::bright_white("Вибір:") << " ";
			break;
		}
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			loop = true;
			char_error(lng);
		}
		else if (choice < TRY_AGAIN_BTN || choice > QUIT_BTN) {
			num_error(lng);
			loop = true;
		}
		else {
			switch (choice)
			{
			case TRY_AGAIN_BTN:
				loop = true;
				system("cls");
				return false;
				break;
			case QUIT_BTN:
				loop = false;
				return true;
				break;
			}
		}
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);//For UA language
	unsigned short int choice = 0, lng = ENGLISH;
	unsigned int ans = 0;
	bool exit = true;
	unsigned int first_counter = 0, second_counter = 0;//score counter
	random_org_generator(ans, lng, 2);//Internet connection checker
	do
	{
		first_counter = second_counter = 0;
		text_menu_start(choice, lng);
		switch (choice)
		{
		case START_BTN:
			start_game(lng, first_counter, second_counter);
			exit = final_choice(lng);
			break;
		case LANGUAGE_BTN:
			language_change(lng);
			exit = false;
			break;
		case EXIT_BTN:
			exit = true;
			break;
		}
	} while (!exit);
	return 0;
}