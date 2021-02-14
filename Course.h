//Created by Jooyul Yoon

#ifndef COURSE_H
#define COURSE_H

#include <iostream>

using namespace std;

class Course
{
private:
	string crn;
	string name;
	string title;
	string time;
	string instructor;
	string loc;
public:
	//default constructor
	Course() { crn = "N/A"; name = "N/A", title = "N/A", time = "N/A", instructor = "N/A", loc = "N/A"; }

	//constructor
	Course(string input_crn, string input_name, string input_title, string input_times, string input_instructor, string input_loc)
	{
		crn    = input_crn;
		name = input_name;
		title = input_title;
		time = input_times;
		instructor = input_instructor;
		loc = input_loc;
	}

	void setCRN(string i)		{ crn = i; }
	void setName(string str)	{ name = str; }
	void setTitle(string str)	{ title = str; }
	void setTime(string str)	{ time = str; }
	void setInst(string str)	{ instructor = str; }
	void setLoc(string str)		{ loc = str; }

	//Assessors
	string getCRN() const		{ return crn; }
	string getName() const		{ return name; }
	string getTitle() const		{ return title; }
	string getTime() const		{ return time; }
	string getInst() const		{ return instructor; }
	string getLoc() const		{ return loc; }

	friend std::ifstream& operator>>(std::ifstream& in, Course &obj)
	{
		getline(in, obj.crn, ';');
		getline(in, obj.name, ';');
		getline(in, obj.title, ';');
		getline(in, obj.time, ';');
		getline(in, obj.instructor, ';');
		getline(in, obj.loc, '\n');

		return in;
	}

	friend std::ofstream& operator<<(std::ofstream &out, Course &obj)
	{
		if (obj.crn != "N/A")
		{
			out << '\n' << obj.crn << ';' << obj.name << ';' << obj.title << ';' << obj.time << ';' << obj.instructor << ';' << obj.loc ;
		}

		return out;
	}
};
#endif