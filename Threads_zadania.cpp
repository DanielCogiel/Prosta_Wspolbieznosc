#include <iostream>
#include <thread>
#include <future>
#include <chrono>

using namespace std;
using namespace chrono;

void wypisz_tekst(std::string napis, int n)
{
	for (int i = 0; i < n; i++)
		std::cout << napis << std::endl;
}

void pracuj()
{
	std::cout << "Rozpoczynam prace." << std::endl;
	std::this_thread::sleep_for(seconds(3));
	std::cout << "Koncze prace." << std::endl;
}

int fib(int n)
{
	if (n < 3) return 1;
	else return fib(n - 1) + fib(n - 2);
}

struct fib_maker
{
	int operator()(int n)
	{
		if (n < 3) return 1;
		else return fib(n - 1) + fib(n - 2);
	}
};

int main()
{
	//Wybór zadania
	int choice = 0;
	std::cout << "Podaj nr zadania: ";
	std::cin >> choice;
	std::system("cls");

	if (choice == 1)
	{   //ZADANIE NR 1 - STD::THREAD

		/** a) Sprawdź, jak wygląda równoległa praca kilku wątków na raz.
		*   W tym celu utwórz 3 wątki przy pomocy std::thread, które będą wypisywać na ekran daną liczbę słów linijka po linijce.
		*   Możesz użyć gotowej funkcji wypisz_tekst().
		*   Nie zapomnij o użyciu join()!!!
		*/

		//tu wpisz kod

		/** b) Dokonaj pomiaru czasu pracy funkcji pracuj()
		*	Najpierw dwa razy wywołaj funkcję w sposób standardowy i zmierz czas.
		*   Następnie wykonaj te operacje równolegle (stwórz dwa nowe wątki bądź użyj jednego nowego wątku i wątku głównego) i dokonaj pomiaru czasu.
		*   Zaobserwuj korzyść czasową ze sposobu równoległego.
		*/

		system_clock::time_point start = system_clock::now();

		//tu wpisz kod

		auto end = system_clock::now();

		auto fn_duration = duration_cast<seconds> (end - start).count();
		std::cout << std::endl << "Czas wykonania bez uzycia wielowatkowosci: " << fn_duration << " sekund" << std::endl << std::endl;

		start = system_clock::now();

		//tu wpisz kod

		end = system_clock::now();

		fn_duration = duration_cast<seconds> (end - start).count();
		std::cout << std::endl << "Czas wykonania z uzyciem wielowatkowosci: " << fn_duration << " sekund" << std::endl << std::endl;
	}

	else if (choice == 2)
	{	// ZADANIE NR 2 - STD::ASYNC

		/** a) Uzyskaj ten sam rezultat, co w zadaniu 1b, używając std::async.
		*   Utwórz obiekty std::future i użyj std::async z odpowiednią polityką uruchamiania.
		*   Za każdym razem użyj nowych wątków (nie wywołuj funkcji pracuj() w main()).
		*/

		system_clock::time_point start = system_clock::now();

		//tu wpisz kod

		auto end = system_clock::now();

		auto fn_duration = duration_cast<seconds> (end - start).count();
		std::cout << std::endl << "Czas wykonania bez uzycia wielowatkowosci: " << fn_duration << " sekund" << std::endl << std::endl;

		start = system_clock::now();

		//tu wpisz kod

		end = system_clock::now();

		fn_duration = duration_cast<seconds> (end - start).count();
		std::cout << std::endl << "Czas wykonania z uzyciem wielowatkowosci: " << fn_duration << " sekund" << std::endl << std::endl;

		/** b) Użyj std::async na trzy różne sposoby, przekazując funkcję, obiekt funkcyjny i wyrażenie lambda.
		*   Zaobserwuj, które podejście jest najbardziej korzystne czasowo.
		*   Dla każdego sposobu utwórz dwa wątki.
		*/

		//funkcja
		std::cout << "ADRES FUNKCJI" << std::endl;

		start = system_clock::now();

		//tu wpisz kod

		end = system_clock::now();

		std::cout << "Uzyskane wartosci fib" << std::endl;
		//std::cout << "Thread 1: " << fn_value1.get() << std::endl;
		//std::cout << "Thread 2: " << fn_value2.get() << std::endl;

		fn_duration = duration_cast<microseconds> (end - start).count();
		std::cout << std::endl << "Czas wykonania z podanym adresem funkcji: " << fn_duration << " mikrosekund" << std::endl << std::endl;

		//obiekt funkcyjny
		std::cout << "OBIEKT FUNKCYJNY" << std::endl;

		start = system_clock::now();

		//tu wpisz kod

		end = system_clock::now();

		std::cout << "Uzyskane wartosci fib" << std::endl;
		//std::cout << "Thread 1: " << obj_value1.get() << std::endl;
		//std::cout << "Thread 2: " << obj_value2.get() << std::endl;

		fn_duration = duration_cast<microseconds> (end - start).count();
		std::cout << std::endl << "Czas wykonania z podanym obiektem funkcyjnym: " << fn_duration << " mikrosekund" << std::endl << std::endl;

		//lambda
		std::cout << "LAMBDA" << std::endl;

		start = system_clock::now();

		//tu wpisz kod

		end = system_clock::now();

		std::cout << "Uzyskane wartosci fib" << std::endl;
		//std::cout << "Thread 1: " << lmbd_value1.get() << std::endl;
		//std::cout << "Thread 2: " << lmbd_value2.get() << std::endl;

		fn_duration = duration_cast<microseconds> (end - start).count();
		std::cout << std::endl << "Czas wykonania z podanym wyrazeniem lambda: " << fn_duration << " mikrosekund" << std::endl << std::endl;
	}




	else if (choice == 3)
	{

	//ZADANIE NR 3 - STD::PROMISE

		//a) Stworz obiekt typu promise, unikalny dla niego obiekt typu future, nowy watek wykorzystujacy funkcja
		// barrierThread o nazwie obiektu "thread1" oraz wymus czekanie az watek zmieni wartosc obiektu future
		// w tym celu uzyj funkcje obiektu future o nazwie wait() dla typu wartosci void, jest ona rownoznaczna z 
		// funkcja get()

		const int SECONDS = 2;
		auto barrierThread = [](std::promise<void> promise_obj, int timeToWait)
		{
			for (auto i = 0; i < timeToWait; ++i) {
				this_thread::sleep_for(seconds(1));
				std::cout << "Czekasz juz " << +i + 1 << " sekund" <<
					", kontynuacja czekania az zostanie zniesiona bariera...\n";
			}
			promise_obj.set_value();
			for (auto i = 0; i < timeToWait; ++i) {
				std::this_thread::sleep_for(seconds(1));
				std::cout << "Czekasz juz " << i + 1 << " sekund" <<
					", kontynuacja czekania az watek zakonczy prace...\n";
			}
		};

		std::cout << "Bedziesz musial(a) poczekac przez " << 2 * SECONDS << " sekund, czy jestes na to gotow(y/a)? Jesli tak:  ";
		std::system("pause");

		//tu wpisz kod

		std::cout << "Bariera zniesiona, czekamy ma zakonczenie paracy watku zewnatrzengo\n";
		//thread1.join();

		//b)Napisz swoja funkcje liczacza za pomoca lambdy wartosc sumy wartosci w wektorze,
		// ktora pozniej przekazesz do zewnetrznego watku oraz popraw czesc kodu aby poprawnie wyswietlal sume 
		// przekazana przez obiekt future
		vector<int> vectorEx3 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

		//Tutaj popraw kod//////////////////////////////////////////////

		auto funkcja = []() {};

		//Postaraj sie nie dodawac nowych linijek tylko dodawac i edytowac argumenty podanych juz funkcji
		//i metod oraz przypisywac wartosci

		promise<int> promiseSum;
		future<int> futureSum;
		thread thread2(funkcja);
		cout << "Suma wektora to " << futureSum.get();
		thread2.join();

		//Tutaj popraw kod//////////////////////////////////////////////
	}
	else if (choice == 4)
	{
	//ZADANIE NR 4 - STD::PACKAGED_TASK
	 
		//a) Wykorzystujac funkcje szyfru cezara sprobuj odkodowac ponizsza wiadomosc znajdujaca sie w dwoch czesciach.
		//Pierwsza czesc wiadomosci zostala zaszyfrowana z kluczem 23, a druga z kluczem 7 - obie za pomoca szyfru Cezara.
		//Podpowiedz: aby odkodowac szyfr cezara tym samym algorytmem ktorym zakodowalismy wiadomosc wystarczy ja ponownie
		//zaszyfrowac z kluczem wstecznym, ktory mozna obliczyc jako ilosc liter (tutaj przyjelismy 25) minus klucz pierwotny

		auto cezarCypher = [](std::string inputSentance, char key) {
			if (key < 0) key = -1 * key;
			auto smallLetter = [](int val) {if (val >= 65 && val < 90) return true; else return false; };
			auto bigLetter = [](int val) {if (val >= 97 && val < 122) return true; else return false; };
			for (auto& sign : inputSentance) {
				if (bigLetter(sign)) {
					sign += key;
					if (!bigLetter(sign)) sign -= 25;
				}
				if (smallLetter(sign)) {
					sign += key;
					if (!smallLetter(sign)) sign -= 25;
				}
				std::this_thread::sleep_for(std::chrono::milliseconds(20));
			}
			return inputSentance;
		};

		const std::string MESSEGEPT1 = "-X hxig rm qkxi hxjxnclm?\n- Rcl qxk rwjim, zc zjc uwkxugxqz.\n- H qgc azwrx hxi F.\n- \"Fcjxnxlm\", lgc \"Bzcjxnglm\".\n- Zc am?\n- \"Fcjxnxlmmmm\".",
			MESSEGE2PT2 = "\n- Bhr? H qh ilkl tveps \"Kzlshwpuv\".";

		//Tutaj popraw kod///////////////////////////////////////////////
		//Postaraj sie nie dodawac nowych linijek tylko dodawac i edytowac argumenty podanych juz funkcji
		//i metod oraz przypisywac wartosci

		std::packaged_task<std::string> task1(), task2();
		std::future<std::string> futurePT1, futurePT2;
		//std::thread thread3(std::move(task1)), thread4(std::move(task2));
		//std::cout << "Message:\n" << futurePT1.get() << futurePT2.get();
		//thread3.join();
		//thread4.join();
		
		//Tutaj popraw kod//////////////////////////////////////////////

		//b) Przy uzyciu lambdy stworz obiekt typu package_task ktore zwroci nowy wektor zawierajacy kwadraty 
		// elementow wektora wejsciowego nastepnie wyswietl wynik operacji przy pomocy obiektu future i metody get()

		vector<int> vectorEx4 = { 1, 2, 3, 4, 5 };

		//Tutaj napisz kod//////////////////////////////////////////////

		

		//Tutaj napisz kod//////////////////////////////////////////////
	}
	return 0;
}
