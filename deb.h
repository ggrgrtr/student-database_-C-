#include <string>
#include <iostream>
using namespace std;
#pragma once


const int MAX_EXAMS = 5;
const int MAX_TESTS = 10;

struct Exam // Структура одного экзамена конкретного студента
{
	int grade;
	string subject;
	string date;
};

struct Test // Структура одного зачета конкретного студента
{
	string subject;
	bool passed;
	string date;
};



class Students // Класс студентов
{
public:

	string return_group() {
		return group;
	}
	string return_fio() {
		return name + " " + surname + " " + last_name;
	}
	string return_birth() {
		return birth;
	}
	string return_tests(int r) // функция возвращения строки экзаменов в 2х вариантах, техническом и визуальном
	{
		string ts; // добавление в строку элементов экземпляра
		switch (r) {
		case 1: {
			for (int i = 0; i < test_c; i++) {
				if (tests[i].passed) ts.append("(+)");
				else ts.append("(-)");
				ts.append("_");

				ts.append(tests[i].subject);
				ts.append("_");
				ts.append(tests[i].date);

				if (i != test_c - 1) ts.append("  ");
			}
			break;
		}
		case 2: {
			for (int i = 0; i < test_c; i++) {
				if (tests[i].passed) ts.append("+");
				else ts.append("-");
				ts.append(" ");

				ts.append(tests[i].subject);
				ts.append(" ");
				ts.append(tests[i].date);

				if (i != test_c - 1) ts.append(" ");
			}
		}
		}

		return ts;
	}
	string return_exams(int r) // функция возвращения строки экзаменов в 2х вариантах, техническом и визуальном
	{
		string ex;
		switch (r) {
		case 1: {
			for (int i = 0; i < exam_c; i++) {
				ex.append(to_string(exams[i].grade)); // добавление в строку элементов экземпляра
				ex.append("_");
				ex.append(exams[i].subject);
				ex.append("_");
				ex.append(exams[i].date);

				if (i != exam_c - 1) ex.append("  ");

			}
			break;
		}
		case 2: {
			for (int i = 0; i < exam_c; i++) {
				ex.append(to_string(exams[i].grade));
				ex.append(" ");
				ex.append(exams[i].subject);
				ex.append(" ");
				ex.append(exams[i].date);

				if (i != exam_c - 1) ex.append(" ");

			}
		}
		}

		return ex;
	}

	void set_fio(string s1, string s2, string s3) {
		name = s1;
		surname = s2;
		last_name = s3;
	}
	void set_group(string s) {
		group = s;

	}
	void set_birth(string b) {
		birth = b;
	}

	void set_exam(int grade, string subject, string date)
	{
		if (exam_c >= MAX_EXAMS) { // проверка, если счетчик стал больше= максимальному количеству экзаменов в массиве
			cout << "limit: exam index" << endl;
			return; // прерывание функции
		}

		exams[exam_c].date = date;
		exams[exam_c].grade = grade;
		exams[exam_c].subject = subject;


		exam_c++;
	}

	void set_test(bool passed, string subject, string date)
	{
		if (test_c >= MAX_TESTS) { // проверка, если счетчик стал больше= максимальному количеству зачетов в массиве
			cout << "limit: test index" << endl;
			return;// прерывание функции
		}
		tests[test_c].date = date;
		tests[test_c].passed = passed;
		tests[test_c].subject = subject;

		test_c++;
	}

	int r_test() {
		return test_c;
	}
	int r_ex() {
		return exam_c;
	}
	int passed_ex(int gr) {// возвращает кол-во сданных экзаменов, где балл больше= gr
		int cc = 0;
		for (int i = 0; i < exam_c; i++)
			if (exams[i].grade >= gr) cc++;

		return cc;
	}

	int passed_tests() { //возвращает кол-во сданных тестов
		int cc = 0;
		for (int i = 0; i < test_c; i++) {
			if (tests[i].passed) cc++;
		}
		return cc;
	}

private: // все переменные приватны, доступ к ним можно получить только через функции

	string name;
	string surname;
	string last_name;
	string birth;
	string group;


	Exam exams[MAX_EXAMS]; // массив всех экзаменов конкретного студента
	int exam_c = 0;

	Test tests[MAX_TESTS]; // массив всех зачетов конкретного студента
	int test_c = 0;
};



