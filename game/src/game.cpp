/*
 * Name        : game.cpp
 * Author      : Kaloyan KRASTEV
 * Version     : 5
 * Copyright   : free
 * Description : study
 */

#include <algorithm>
#include <cassert>
#include <cfloat>
#include <chrono>
#include <climits>
#include <cmath>
#include <deque>
#include <fstream>
#include <mutex>
#include <ncurses.h>
#include <queue>
#include <set>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <unistd.h>

#include "include/gobo.h"

using namespace std;

struct Packet {
	int length;
	int width;
	int height;
};

std::mutex m;
std::queue<Packet> packet_queue;
int number_of_packets = 6;

void parcel_delivery() {
	// (2): The producer thread: Periodically put a new packet into a queue
	int counter = 0;
	while (counter < number_of_packets) {
		// Perform some long running task
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "sending packet ..." << std::endl;
		Packet new_packet { counter, counter + 1, counter + 2 };
		{
			std::lock_guard<std::mutex> l { m };
			packet_queue.push(new_packet);
			std::cout << packet_queue.size() << "packets in the queue" << std::endl;
		}
		counter++;
	}
}

void recipient() {
	int counter = 0;
	while (counter < number_of_packets) {
		std::cout << packet_queue.size() << "packets in the queue" << std::endl;
		{
			// (3): Lock the mutex and test if a packet was received
			std::lock_guard<std::mutex> l { m };
			if (!packet_queue.empty()) {
				Packet new_packet = packet_queue.front();
				packet_queue.pop();
				std::cout << "Received new packet with dimension: "
						<< new_packet.length << "; " << new_packet.width << "; "
						<< new_packet.height << std::endl;
				counter++;
			}
		}

		std::this_thread::sleep_for(std::chrono::seconds(3));
	}
}

float convert(int n, int s = 10) {
	float dec = 0;
	float i = 0, rem;

	while (n != 0) {
		rem = n % s;
		n /= s;
		dec += rem * pow(2, i);
		++i;
		cout << n << " " << dec << " " << i << " " << rem << endl;
	}

	return dec;
}

void printVector(vector<int> vint, const char*comment = "") {
	for (auto&itervint : vint) printf("%d, ", itervint);
	if (string(comment) == "") printf("\n");
	else printf("<%s>\n", comment);
	return;
}

bool funcomp(int i, int j) { return (abs(i) < abs(j)); }
bool work_with_vector() {
	/* vector init, sort and search */
	int vecsize = 10; // integer array
	int intarr[vecsize] = {13, -4, 7, -4, 11, 15, -8, -6, -21, 4};
    cout << 2 << 1 << endl;
	vector<int> vec; //(vecsize);
	vec.reserve(vecsize);
	vec.insert(vec.end(), intarr, intarr + vecsize);
	//auto*vecptr = vec.data(); cout << vecptr[0] << endl;

	printVector(vec, "init");
	sort(vec.begin(), vec.end(), funcomp);
	printVector(vec, "sort by <funcomp> function");

	int codingame = vec.front();
	if (codingame < 0) {

		sort(vec.begin(), vec.end());
		if (binary_search(vec.begin(), vec.end(), abs(codingame))) {

			codingame = abs(codingame);
		}
	}

	printf("<codingame-closest-distance> = %d\n", codingame);
	cout << "sise = " << vec.size() << ", capacity = " << vec.capacity() << endl;
	sort(vec.begin(), vec.end());
	vec.pop_back();

	printVector(vec, "sort + pop_back");

	cout << "sise = " << vec.size() << ", capacity = " << vec.capacity() << endl;
	return true;
}




template <class T>
void send(std::initializer_list<T> list) {
    for (auto elem : list) {
        std::cout << elem;
    }
    std::cout << std::endl;
}


template <class T>
void bubble(T a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = n - 1; i < j; j--) {
            if (a[j] < a[j - 1]) {
                swap(a[j], a[j - 1]);
}	}	}	}


template <typename T>
void size_in_bits(const char*name, const T&a, int con = 0) {
	size_t s = sizeof(a);
	cout << name << "(" << con << ") : " << s << " bytes\n";
	// return(sizeof(a) * 8);
}

int test(string a, string b) {
	return (a + b).length() > 3;
}

unsigned int fact(unsigned int n) {
	if (n <= 0) return 1;
	else return fact(n - 1) * n;
}


int main(void) {

	std::ofstream fout;
	fout.open("/home/kalo/Myxa/mode/c++/game/game.log", std::ios_base::app);
	fout << "game started\n";
	fout.close();

	const char*c = "codingame";
	//const char*maxc = myMax<const char*>("yes", "no");
	unsigned int dim = 5;
	string maxc[dim] = {"never", "no", "maybe", "yes", "sure"};
	bubble(maxc, dim);
	//while (0 < dim--) puts(maxc[dim].c_str());

	work_with_vector();


	string s(c);
	//const int len = s.length();
	//puts(to_string(len).c_str());

	gobo*gobj = new gobo(s);
	gobj->cpp_version(s);
	//s = "C++ version " + s;
	//puts(s.c_str());
	delete(gobj);


	return EXIT_SUCCESS;


	gobo *gobocop = new gobo("blrmmm");
	delete(gobocop);
	const int inti = 2.4;
	bool boo;
	const long lon = 4.4;
	char cha;
	short sho;
	const char*ccs = "llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll";
	const string ccss(ccs);
	float flo;
	double dob;
	long double wow;
	size_in_bits("const char*", ccs);
	size_in_bits("bool", boo);
	size_in_bits("char", cha, CHAR_BIT);
	size_in_bits("short", sho);
	size_in_bits("int", inti);
	size_in_bits("long", lon, LONG_BIT);
	size_in_bits("float", flo);
	size_in_bits("double", dob);
	size_in_bits("long double", wow);
	size_in_bits("string", ccss);

	return EXIT_SUCCESS;

	initscr();
	noecho();

	//int ch = getch();
	int a = puts(s.c_str());
	printw(std::to_string(a).c_str());
	printw(" ");
	printw(s.c_str());
	refresh(); /* Print it on to the real screen */
	//getch(); /* Wait for user input */
	return EXIT_SUCCESS;

//	return 0;

	/*
	 int b = 111;

	 try {
	 cin >> b;
	 } catch (...) {
	 cout << "cough" << endl;;
	 }
	 */


	std::thread producing_thread(parcel_delivery);
	std::thread consuming_thread(recipient);
	producing_thread.join();
	consuming_thread.join();

	static const string sequence = "|/-\\";

	int duration = 1e7;
	int duration_step = 8e4;
	int toto = duration / duration_step;
	for (int i = 1; i < toto; i++) {
		std::cout << "\r";
		std::cout << sequence[i % sequence.size()] << "  "
				<< (toto - i) * 100 / toto << " % left";
		std::cout << std::flush;
		usleep(duration_step);

		refresh();
	}
	/*
	 for (int i = 0; i < 111; ++i) {
	 string limit("fox%d", i);
	 cout << "\r" << i << flush;
	 // << " " << std::tolower(i) << " " << std::toupper(i) << ";";
	 usleep(3e5);
	 }
	 */

	endwin();
	return EXIT_SUCCESS;

	gobj->expo();
	//	delete gobj;

	string *getter = gobj->get();
	if (getter) {
		cout << "&s -> " << &getter << endl;
		cout << "s -> " << getter << endl;
		cout << "*s -> " << *getter << endl;
	} else {
		return EXIT_FAILURE;
	}
	delete gobj;

	int *x = new int[15];
	x[7] = 5;
	for (auto a = 0; a < 15; ++a) {
		cout << x << "&x -> " << &x[a] << " x -> " << x[a] << endl;
	}

	float i;

	float &r = i; // now the value of r has the same address in the memory as the value of i
	float *p = &i; // if p is the address where the value of i is written
	float *q = &r; // then the value of r is written at the same address p
	*p = 18.12;

	if (p == q)
		cout << "p == q" << endl;

	cout << q << endl << p << endl << &r << endl << *p << endl << r << endl << i
			<< endl;

	return EXIT_SUCCESS;
}
