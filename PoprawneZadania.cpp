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

		std::thread thr1(wypisz_tekst, "Thread number <1> executing", 500);
		std::thread thr2(wypisz_tekst, "Thread number <2> executing", 500);
		std::thread thr3(wypisz_tekst, "Thread number <3> executing", 1000);

		thr1.join();
		thr2.join();
		thr3.join();

		/** b) Dokonaj pomiaru czasu pracy funkcji pracuj()
		*	Najpierw dwa razy wywołaj funkcję w sposób standardowy i zmierz czas.
		*   Następnie wykonaj te operacje równolegle (stwórz dwa nowe wątki bądź użyj jednego nowego wątku i wątku głównego) i dokonaj pomiaru czasu.
		*   Zaobserwuj korzyść czasową ze sposobu równoległego.
		*/

		system_clock::time_point start = system_clock::now();

		pracuj();
		pracuj();

		auto end = system_clock::now();

		auto fn_duration = duration_cast<seconds> (end - start).count();
		std::cout << std::endl << "Czas wykonania bez uzycia wielowatkowosci: " << fn_duration << " sekund" << std::endl << std::endl;

		start = system_clock::now();

		std::thread thr4(pracuj);

		pracuj();
		thr4.join();

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

		std::future<void> value_1 = std::async(std::launch::deferred, pracuj);
		std::future<void> value_2 = std::async(std::launch::deferred, pracuj);

		value_1.get();
		value_2.get();

		auto end = system_clock::now();

		auto fn_duration = duration_cast<seconds> (end - start).count();
		std::cout << std::endl << "Czas wykonania bez uzycia wielowatkowosci: " << fn_duration << " sekund" << std::endl << std::endl;

		start = system_clock::now();

		value_1 = std::async(std::launch::async, pracuj);
		value_2 = std::async(std::launch::async, pracuj);

		value_1.get();
		value_2.get();

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

		std::future<int> fn_value1 = std::async(std::launch::async, fib, 20);
		std::future<int> fn_value2 = std::async(std::launch::async, fib, 27);

		end = system_clock::now();

		std::cout << "Uzyskane wartosci fib" << std::endl;
		std::cout << "Thread 1: " << fn_value1.get() << std::endl;
		std::cout << "Thread 2: " << fn_value2.get() << std::endl;

		fn_duration = duration_cast<microseconds> (end - start).count();
		std::cout << std::endl << "Czas wykonania z podanym adresem funkcji: " << fn_duration << " mikrosekund" << std::endl << std::endl;

		//obiekt funkcyjny
		std::cout << "OBIEKT FUNKCYJNY" << std::endl;

		start = system_clock::now();

		std::future<int> obj_value1 = std::async(std::launch::async, fib_maker(), 20);
		std::future<int> obj_value2 = std::async(std::launch::async, fib_maker(), 27);

		end = system_clock::now();

		std::cout << "Uzyskane wartosci fib" << std::endl;
		std::cout << "Thread 1: " << obj_value1.get() << std::endl;
		std::cout << "Thread 2: " << obj_value2.get() << std::endl;

		fn_duration = duration_cast<microseconds> (end - start).count();
		std::cout << std::endl << "Czas wykonania z podanym obiektem funkcyjnym: " << fn_duration << " mikrosekund" << std::endl << std::endl;

		//lambda

		std::cout << "LAMBDA" << std::endl;

		start = system_clock::now();

		std::future<int> lmbd_value1 = std::async(std::launch::async, [](int n) {
			if (n < 3) return 1;
			else return fib(n - 1) + fib(n - 2); }, 20);

		std::future<int> lmbd_value2 = std::async(std::launch::async, [](int n) {
			if (n < 3) return 1;
			else return fib(n - 1) + fib(n - 2); }, 27);

		end = system_clock::now();

		std::cout << "Uzyskane wartosci fib" << std::endl;
		std::cout << "Thread 1: " << lmbd_value1.get() << std::endl;
		std::cout << "Thread 2: " << lmbd_value2.get() << std::endl;

		fn_duration = duration_cast<microseconds> (end - start).count();
		std::cout << std::endl << "Czas wykonania z podanym wyrazeniem lambda: " << fn_duration << " mikrosekund" << std::endl << std::endl;
	}




	else if (choice == 3)
	{

	//ZADANIE NR 3 - STD::PROMISE

		//a) Stworz obiekt typu promise, unikalny dla niego obiekt typu future, nowy watek wykorzystujacy funkcja
		// barrierThread o nazwie obiketu "thread1" oraz wymus czkeanie az watek zmieni wartosc obiektu future
		// w tym celu uzyj funkcje obiektu future o nazwie wait() dla typu warosci void jest ona rownoznaczna z 
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

		//Tutaj uzueplnij kod///////////////////////////////////////////////

		promise<void> barrierPromise;
		future<void> barrierFuture = barrierPromise.get_future();
		thread thread1(barrierThread, std::move(barrierPromise), SECONDS);
		barrierFuture.wait();

		//Tutaj uzueplnij kod//////////////////////////////////////////////

		std::cout << "Bariera zniesiona, czekamy ma zakonczenie paracy watku zewnatrzengo\n";
		thread1.join();

		//b)Napisz swoja funkcje liczacza za pomoca lambdy wartosc sumy wartosci w wektorze,
		// ktora pozniej przekazesz do zewnetrznego watku oraz popraw czesc kodu aby poprawnie wyswietlal sume 
		// przekazana przez obiekt future
		vector<int> vectorEx3 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

		//Tutaj popraw kod//////////////////////////////////////////////

		auto funkcja = [](promise<int> promSum, vector<int> vec) {
			int sumVal = 0;
			for (int i = 0; i < vec.size(); ++i) sumVal += vec.at(i);
			promSum.set_value(sumVal);
		};

		//Postaraj sie nie dodawac nowych linijek tylko dodawac i edytowac argumenty podanych juz funkcji
		//i metod oraz przypisywac wartosci

		promise<int> promiseSum;
		future<int> futureSum = promiseSum.get_future();
		thread thread2(funkcja, std::move(promiseSum), vectorEx3);
		std::cout << "Suma wektora to " << futureSum.get();
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

		std::packaged_task<std::string(std::string, char)> task1(cezarCypher), task2(cezarCypher);
		auto futurePT1 = task1.get_future(), futurePT2 = task2.get_future();
		std::thread thread3(std::move(task1), MESSEGEPT1, 2), thread4(std::move(task2), MESSEGE2PT2, 18);
		std::cout << "Wiadomosc:\n" << futurePT1.get() << futurePT2.get();
		thread3.join();
		thread4.join();

		//Tutaj popraw kod//////////////////////////////////////////////

		//b) Przy uzyciu lambdy stworz obiekt typu package_task ktore zwroci nowy wektor zawierajacy kwadraty 
		// elementow wektora wejsciowego nastepnie wyswietl wynik operacji przy pomocy obiektu future i metody get()

		vector<int> vectorEx4 = { 1, 2, 3, 4, 5 };

		//Tutaj napisz kod//////////////////////////////////////////////

		std::packaged_task<std::vector<int>(std::vector<int>)> task3([](std::vector<int> vec) {
			std::vector<int> newVec;
			for (auto val : vec) {
				newVec.push_back(val * val);
			}
			return newVec;
			});
		std::future<vector<int>> futureVector = task3.get_future();
		std::thread thread5(std::move(task3), vectorEx4);
		std::cout << std::endl;
		for (auto val : futureVector.get()) std::cout << val << " ";
		thread5.join();

		//Tutaj napisz kod//////////////////////////////////////////////
	}
	return 0;
}
