#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <cctype>
#include <Windows.h>
#include "deb.h"

using namespace std;


ifstream file_read; // ������ ��� ������ �����
ofstream file_write; // ������ ��� ������ � ����


vector<Students> data2; // ������ ���� ����������� ������ ���������
vector<Students> search; // ������ ������� �����������
vector<int> ind; // ������ �������� �������



string print_data(Students person, int r) { // ����� ���� ���������� � �������� � ����� �� ���� ���������
	if (person.return_exams(r) == "") // ���� ��� ���������, �������� ������ � ������� ������ \n
	{
		if (r == 1) // ��� ������ � ��������
			return  person.return_fio() + " | " + person.return_birth() + " | " + person.return_group() + " | " + person.return_tests(r);
		else // ��� ���������� ������ � ������ � ����
			return  person.return_fio() + " " + person.return_birth() + " " + person.return_group() + " " + person.return_tests(r);
	}
	else {
		if (r == 1)
			return  person.return_fio() + " | " + person.return_birth() + " | " + person.return_group() + " | " + person.return_exams(r) + " | " + person.return_tests(r);
		else
			return  person.return_fio() + " " + person.return_birth() + " " + person.return_group() + " " + person.return_exams(r) + " " + person.return_tests(r);

	}
}



vector<Students> alph(vector<Students> a) // ������� ���������� �� ���
{
	string s1, s2;
	vector<Students> b;
	int j;
	int c = a.size();
	while (b.size() != c) // ��������� �����, ���������� � ������ b � �������� �� ������� a ���������� � ������ �������� ����������
	{
		j = 0;
		for (int i = 1; i < a.size(); i++) {
			s1 = a[i].return_fio();
			s2 = a[j].return_fio();
			if (s1 < s2) j = i;
		}
		b.push_back(a[j]);
		a.erase(a.begin() + j);
	}

	return b;
}



Students set_person(string line) { // �������� ������� ������ Students �� ������ ������ line, ������ �� ����� ��� ���������

	string word;
	vector<string> allWords; // ������ ��� �������� ���� ���� ������

	Students person;
	stringstream str1(line); // ��������� ������ �� �����


	while (str1 >> word) {
		allWords.push_back(word); // ���������� ���� � ������
	}


	// ���� ����� ������ 5, �� ���� ���, ��� �������� � ������
	if (allWords.size() < 5) { 
		cout << "defect line" << " " << allWords.size() << endl;
		allWords.clear();

		return person;
	}


	person.set_fio(allWords[0], allWords[1], allWords[2]);
	person.set_birth(allWords[3]);
	person.set_group(allWords[4]);

	try { // ������� �������� �� ���������� ��������� ��������� � ����� 3
		for (int i = 5; i < allWords.size(); i = i + 3) 
		{
			if (allWords[i] == "+" || allWords[i] == "-") {
				if (allWords[i] == "+") person.set_test(true, allWords[i + 1], allWords[i + 2]);
				if (allWords[i] == "-") person.set_test(false, allWords[i + 1], allWords[i + 2]);
			}
			else {
				int grade = stoi(allWords[i]);
				if (grade >= 1 && grade <= 100) {

					person.set_exam(grade, allWords[i + 1], allWords[i + 2]);
				}
			}
		}
	}

	catch (...) {
		cout << endl << " error:\n incorrect filling of the table";
	}

	allWords.clear();
	return person; // ����������� ���������� ����������
}



void out(int r, string f) // ������� ������ ������������ ����
{
	if (r == 0)
	{
		cout << " 0 - exit" << endl;
		cout << " 1 - open" << endl;
	}
	if (r == 1)
	{
		cout << "~~ " << f << " ~~" << endl;
		cout << " 0 - exit" << endl;
		cout << " 2 - search for.." << endl;
		cout << " 3 - add" << endl;
		cout << " 4 - info" << endl;
		cout << " 5 - sort" << endl;
		cout << " 8 - -->file" << endl;
	}
	if (r == 2)
	{
		cout << "~~ " << f << " ~~" << endl;
		cout << " 0 - exit" << endl;
		cout << " 3 - add" << endl;
		cout << " 6 - rewrite" << endl;
		cout << " 7 - delete" << endl;
	}
}




int main()
{
	SetConsoleCP(1251); // ��� ��������� ������� ��������
	SetConsoleOutputCP(1251);

	string f;
	string S = "|------------------------------------------------------------------------------------------------------------|";
	int flag = 0;
	int flag1 = 0;
	int flag2 = 0;
	char g = 'q';

	int reflect = -1; // ���������� ��� ������ � �����������



	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	cout << " ~START~" << endl;

	cout << endl << S << endl << endl;

	out(flag, f);
	cout << "Enter: ";

	cin >> reflect;

	while (reflect != 0) { // ���������� ������ ��������� ��� ����� 0

		if (flag1 == 0)
			cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

		switch (reflect) {


		case 1: // �������� �����
		{

			cout << " ~ C:/example.txt ~ " << endl;
			cout << " Enter the file name: ";
			cin >> f;


			file_read.open(f);

			if (!file_read) // �������� ������������� �����
			{
				cout << " Wrong File name!" << endl;
				cout << f;
				f = "";
				break;
			}

			string line;
			while (getline(file_read, line)) {
				data2.push_back(set_person(line));
			}

			flag = 1;
			file_read.close();

			break;
		}

		case 2: // ����� �� ���� ������
		{
			string for_s;


			cout << "Lastname NM, or group or passed(+/-): " << endl;


			cin.ignore(); // ������������� ����������� ������ ��� ���������� ������ getline()
			getline(cin, for_s);
			stringstream str(for_s); // ��������� ������ �� �����
			vector<string> s;

			string name, fi, name2, f2, i2;
			while (str >> name) {
				s.push_back(name);
			}

			cout << endl << S << endl << endl;

			if (s.size() == 2) // � ����������� �� ����� s � �� ��������� ���������� ����� �� ���, ������ ��� ������|�����������
			{
				int cc = 1;
				try
				{
					for (int i = 0; i < data2.size(); i++) {

						stringstream str2(data2[i].return_fio());


						str2 >> name2;
						str2 >> f2;
						str2 >> i2;
						if (s[0] == name2 && s[1][0] == f2[0] && s[1][1] == i2[0]) {
							cout << cc << ". ";
							cc++;
							cout << print_data(data2[i], 1) << endl;
							search.push_back(data2[i]); // ���������� � ����� ������ ��������� �����������
							ind.push_back(i); // ���������� � ����� ������ �������� ��������� ����������� ��������� ������� data2
							cout << endl;
							flag1 = 1;

						}

					}
				}
				catch (...) {
					cout << "error: wrong NA or lastname" << endl;
				}
			}

			else if (s[0] == "+") {
				int cc = 1;
				for (int i = 0; i < data2.size(); i++) 
				{
					// ���� ���-�� ������� ��������� � ������� ��������� � ����� ���-���
					if (data2[i].passed_ex(45) == data2[i].r_ex() && data2[i].passed_tests() == data2[i].r_test()) {
						cout << cc << ". ";
						cc++;
						cout << print_data(data2[i], 1) << endl;
						search.push_back(data2[i]); // ���������� � ����� ������ ��������� �����������
						ind.push_back(i); // ���������� � ����� ������ �������� ��������� ����������� ��������� ������� data2
						cout << endl;

						flag1 = 1;
					}
				}
			}
			else if (s[0] == "-") {
				int cc = 1;
				for (int i = 0; i < data2.size(); i++) {

					if (data2[i].passed_ex(45) != data2[i].r_ex() || data2[i].passed_tests() != data2[i].r_test()) {
						cout << cc << ". ";
						cc++;
						cout << print_data(data2[i], 1) << endl;
						search.push_back(data2[i]); // ���������� � ����� ������ ��������� �����������
						ind.push_back(i); // ���������� � ����� ������ �������� ��������� ����������� ��������� ������� data2
						cout << endl;

						flag1 = 1;
					}
				}
			}

			else {
				int cc = 1;
				try
				{
					for (int i = 0; i < data2.size(); i++) {


						if (s[0] == data2[i].return_group()) {
							cout << cc << ". ";
							cc++;
							cout << print_data(data2[i], 1) << endl;

							search.push_back(data2[i]);
							ind.push_back(i);
							cout << endl;

							flag1 = 1;
						}

					}
				}
				catch (...) {
					cout << "error: wrong group" << endl;
				}
			}
			cout << S << endl;

			if (flag1 == 1) { //����1 ��������� ��� ����� �������� ����� �� �������� ��� � ������, � ������� � ��������� ����������� ������ ����� �������
				out(2, f);

				cout << "Enter: ";
				cin >> reflect;
			}

			break;
		}

		case 3: // ���������� � ���� ������ ����
		{
			cout << " LastN Name MiddleN date group gradeEx Exam dateEx gradeT Test dateT" << endl;
			string* lines = new string;
			cin.ignore();
			getline(cin, *lines);

			data2.push_back(set_person(*lines));

			delete lines;
			break;
		}


		case 4: // ����� ���� ���������
		{

			if (flag1 == 1 || flag2 == 1) {
				cout << " Complete the previous operation"; // ���� ���� �� ������, �������� �� ������ ������ �����, �������, �� ���� �� ����������, ���� �� ���������� ���������� �������
				flag1 = 0;
				flag2 = 0;
				break;
			}

			cout << endl << S << endl;

			for (int i = 0; i < data2.size(); i++) {
				cout << endl;
				cout << "~! " << data2[i].return_fio() << endl;

				cout << " " << data2[i].return_group();
				cout << " " << data2[i].return_birth() << endl;

				if (data2[i].return_exams(1) != "")
					cout << " " << data2[i].return_exams(1) << endl;
				if (data2[i].return_tests(1) != "")
					cout << " " << data2[i].return_tests(1) << endl;
			}
			break;
		}
		case 5:
		{
			if (flag1 == 1 || flag2 == 1) {
				cout << " Complete the previous operation"; // ���� ���� �� ������, �������� �� ������ ������ �����, �������, �� ���� �� ����������, ���� �� ���������� ���������� �������
				flag1 = 0;
				flag2 = 0;
				break;
			}

			data2 = alph(data2); // ���������� ��������� �� ����������� �������
			cout << endl << " --> Sorted (A-Z)" << endl;
			break;
		}


		case 6: // ��������� ������ ����������� ��������
		{
			if (g == 'y') // ���� ������������ ����� ���������� ������ � ���������� ��������, �� ��� ��������� ����� ������� �������� � ����� ��������� �� ������� search[]
			{
				cout << endl << endl << S << endl << endl;
				for (int i = 0; i < search.size(); i++)
					cout << i + 1 << ". " << print_data(search[i], 1) << endl << endl;
				cout << S << endl << endl;
			}

			if (flag2 == 0)
			{
				cout << "  Rewrite.." << endl;
				cout << " Choose number: ";
				int c;
				cin >> c;

				if (search.size() > c - 1) { // ���� ������ �������� ��� ������ �������

					cout << print_data(search[c - 1], 2) << endl;

					cout << "Repeit with changes" << endl;
					cin.ignore();

					string k;
					getline(cin, k);
					Students New = set_person(k); // �������� ���������� ������ �� ������ ���������� ���������� ������

					// �������� �� ������������� ���, ��� �������� � ������
					if (New.return_fio() != "" && New.return_birth() != "" && New.return_group() != "") 
						data2[ind[c - 1]] = New;
				}
				else {
					cout << " --> no such index" << endl;
					break;
				}
			}

			cout << " Continue?" << endl;
			cout << "y/n: ";
			char g;
			cin >> g;
			if (g == 'n') {
				flag1 = 0;
				ind.clear();
				search.clear();
				flag2 = 0;
			}
			else if (g == 'y')
			{
				cout << " --> ok. continue" << endl; // ������������� �����2, ����� � ����� �������� ����� ����� ����������� � ������� �����
				flag2 = 0;
			}
			else
			{
				cout << " --> no answer. Retry" << endl;
				flag2 = 1;
			}

			break;
		}


		case 7: {

			if (g == 'y') {
				cout << endl << endl << S << endl << endl;
				for (int i = 0; i < search.size(); i++)
					cout << i + 1 << ". " << print_data(search[i], 1) << endl << endl;
				cout << S << endl << endl;
			}


			if (flag2 == 0)
			{
				cout << endl << " DELETE" << endl;
				cout << " Choose number: ";
				int c;
				cin >> c;
				if (search.size() > c - 1) {

					data2.erase(data2.begin() + ind[c - 1]); // �������� ���������� �������� �� ��������� �������
					search.erase(search.begin() + c - 1); // �������� ���������� �������� �� ��������� �������
					ind.erase(ind.begin() + c - 1); // �������� ������� �������� ��������� �������
				}
				else {
					cout << " --> no such index" << endl;
					break;
				}
			}
			cout << " Continue?" << endl;
			cout << "y/n: ";

			cin >> g;
			if (g == 'n') {
				flag1 = 0;
				ind.clear();
				search.clear();
				flag2 = 0;
			}
			else if (g == 'y') // ������������� �����2, ����� � ����� �������� ����� ����� ����������� � ������� �����
			{
				cout << " --> ok. continue" << endl;
				flag2 = 0;
			}
			else
			{
				cout << " No answer. Retry" << endl;
				flag2 = 1;
			}

			break;
		}

		case 8: {
			if (flag1 == 1 || flag2 == 1) {
				cout << " Now impossible to save. Complete the previous operation" << endl; // ���� ���� �� ���������, ��������� ����, �� ��������, �� ���������� �� �����
				flag1 = 0;
				flag2 = 0;
				break;
			}
			file_write.open(f);

			if (file_write) // �������� �������� �����
			{
				for (int i = 0; i < data2.size(); i++)
				{
					file_write << print_data(data2[i], 2) << endl; // ���������� � ���� ���������
				}
				cout << " --> Saved" << endl;
			}
			else {
				cout << "Problem: can't open" << f << endl;
				;
			}

			file_write.close();
			break;
		}

		default:
			cout << " Unreadable!" << endl;

		}

		if (flag1 == 0)
		{
			cout << endl << S << endl << endl;
			out(flag, f);
			cout << "Enter: ";
		}

		if (flag1 == 0)
			cin >> reflect;

	}

	cout << endl << " --> Out." << endl;

	search.clear(); // ������� ��������
	ind.clear();
	data2.clear();
}