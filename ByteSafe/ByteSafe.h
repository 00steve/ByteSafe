#pragma once
#include <string>
#include <iostream>
#include "Bit.h"

using namespace std;

class ByteSafe {
private:
	//all of the variables used to loop through the data
	unsigned int bPtr;	//the current bit pointer
	unsigned int bSkp;	//the current amount of bits to skip

	char *data;
	unsigned int i;
	char *invalidBlock;
	unsigned int length;
	unsigned int validLength;

protected:
	char *Add(char *input, unsigned int baseLength, char newByte, char keyByte);
	void Clear();
	unsigned int FindFinalBit(unsigned int baseLength, string key);
	bool IsValid(char *testData);
	void Reset();

public:
	ByteSafe();
	~ByteSafe();

	bool Decode(string key);
	bool Encode(char *message, unsigned int messageLength, string key);
	bool Encode(string message,string key);

	void PrintBlock();
};