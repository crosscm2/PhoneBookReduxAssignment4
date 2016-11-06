// PhoneBookReduxAssignment4CoreyCross.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip>
#include <conio.h>

using namespace std;

class phoneBook {
	char name[20], hm_phno[15], mb_phno[15];
public:
	void getdata();
	void showdata();
	char *getname() { return name; }
	char *getphno() { return hm_phno; }
	char *getmbno() { return mb_phno; }
	void update(char *nm, char *telno, char *mobno) {
		strcpy_s(name, nm);
		strcpy_s(hm_phno, telno);
		strcpy_s(mb_phno, mobno);
	}
};

void phoneBook::getdata() {
	cout << "\nEnter Full Name : ";
	cin >> name;
	cout << "Enter Home Phone No. : ";
	cin >> hm_phno;
	cout << "Enter Mobile Phone No. : ";
	cin >> mb_phno;
}

void phoneBook::showdata() {
	cout << "\n";
	cout << setw(20) << name;
	cout << setw(15) << hm_phno;
	cout << setw(15) << mb_phno;
}


void main() {
	phoneBook rec[100];
	fstream file;
	int jump;
	int cnt;
	char * filename;
	cout << "Please Enter PhoneBook File Path: " << "";
	cin >> filename;
	file.open(filename, ios::ate | ios::in | ios::out | ios::binary);
		char ch, nm[20], telno[6], mobno[6];
		int choice, found = 0;
		int count = 0; 
		while (1) {
			cout << "\n*****Phone Book*****\n";
			cout << "1) Add New Record\n";
			cout << "2) Display All Records\n";
			cout << "3) Search Telephone No.\n";
			cout << "4) Search Person Name\n";
			cout << "5) Update Telephone No.\n";
			cout << "6) Exit\n";
			cout << "Choose your choice : ";
			cin >> choice;
			switch (choice) {
			case 1: 
				for (int i = 0; i < count; i++) {
					int dup = 0;
					for (int j = 0; j<count; j++) {
						if (rec[j] == rec[i]) {
						cout << "A duplicate record exists." << endl;
					}
						else {
							rec[count].getdata();
							cin.get(ch);
							count++;
						}
					}
				}
				if (count == 99) {
					cout << "PhoneBook is overfilled,Please delete some entries.\n";
				}

				break;

			case 2: 
				jump = 0;
				jump = jump + 5;
				file.seekg(0, ios::beg);
				cout << "\n\nRecords in Phone Book\n";
				while (file) {
					file.read((char *)&rec, sizeof(rec));
					if (!file.eof())
						for (int k = jump - 5; k< jump; k++)
							rec[k].showdata(); 
					_getch();
				}
				file.clear();
				_getch();
				break;

			case 3: 
				cout << "\n\nEnter Name : ";
				cin >> nm;
				file.seekg(0, ios::beg);
				found = 0;
				while (file.read((char *)&rec, sizeof(rec)))
				{
					if (strcmp(nm, (*rec).getname()) == 0)
					{
						found = 1;
						(*rec).showdata();
					}
				}
				file.clear();
				if (found == 0)
				{
					cout << "\n\n---Record Not found---\n";
					_getch();
				}
				break;

			case 4: 
				cout << "\n\nEnter Telephone No : " << endl;
				cin >> telno;
				file.seekg(0, ios::beg);
				found = 0;
				while (file.read((char *)&rec, sizeof(rec)))
				{
					if (strcmp(telno, (*rec).getphno()) == 0)
					{
						found = 1;
						(*rec).showdata();
					}
				}
				file.clear();
				if (found == 0)
					cout << "\n\n---Record Not found---\n";
				_getch();
				break;

			case 5: 
				cout << "\n\nEnter Name : ";
				cin >> nm;
				file.seekg(0, ios::beg);
				found = 0;
				cnt = 0;
				while (file.read((char *)&rec, sizeof(rec)))
				{
					cnt++;
					if (strcmp(nm, (*rec).getname()) == 0)
					{
						found = 1;
						break;
					}
				}
				file.clear();
				if (found == 0)
					cout << "\n\n---Record Not found---\n";
				else
				{   
					int location = (cnt - 1) * sizeof(rec);
					cin.get(ch);
					if (file.eof())
						file.clear();

					cout << "Enter New Telephone No : ";
					cin >> telno;
					file.seekp(location);
					(*rec).update(nm, telno, mobno);
					file.write((char *)&rec, sizeof(rec));
					file.flush();
				}
				break;

			case 6:
				for (int i = 0; i<count; i++) {
					int dup = 0;
					for (int j = 0; j<count; j++) {
						if (rec[j] == rec[i]) {
							cout << "Write: Duplicate record exist." << endl;
						}
						else {
							file.write((char *)&rec[i], sizeof(rec));
						}
					}

				}
				break;



			}
		}
	out:
		file.close();

	}

