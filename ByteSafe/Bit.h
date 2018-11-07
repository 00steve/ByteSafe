#pragma once
#include <iostream>

class Bit
{

private:
	static bool bigEndian;
	static int bi; //bit iterator
public:
	Bit();
	~Bit();


	static bool Get(const char b, const unsigned int i);

	static bool IsBigEndian();
	static bool IsBigEndian(bool bigEndian);
	static bool IsLittleEndian();
	static bool IsLittleEndian(bool littleEndian);

	static void Print(const char byte);
	static void Print(const std::string string);
};

