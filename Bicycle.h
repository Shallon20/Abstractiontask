#pragma once
#ifndef BICYCLE
#define BICYCLE

#include <string>

using namespace std;

class Bicycle
{
public:
	void init(int id, string type, double price);
	int get_id() { return _id; }
	string get_type() { return _type; }
	double get_price() { return _price; }

private:
	int _id;
	string _type;
	double _price;
};

#endif