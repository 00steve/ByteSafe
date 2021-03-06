// ByteSafe.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "ByteSafe.h"


char *ByteSafe::Add(char *input, unsigned int baseLength, char newByte, char keyByte) {
	//generate encryption values
	char offset = (baseLength * 255) % keyByte;
	unsigned int totalBits = baseLength * 8;

	//set index for the byte being stored
	unsigned int newBitIndex = 8;

	//loop through each bit that needs to be stored
	while (newBitIndex --> 0) {
		int bit = (newByte >> newBitIndex) & 1U;

		//move the bit pointer along based on the offset
		bPtr = bPtr + offset;
		//if the bit pointer points to an invalid bit, loop
		//it back around to point to a valid bit.
		while (bPtr >= totalBits) { bPtr -= totalBits; }

		//if the bit is a one, actually flip the bit that should be updated
		if (bit) input[bPtr / 8] = input[bPtr / 8] ^ (1 << bPtr % 8);
	}

	return input;
}





ByteSafe::ByteSafe() :
	data(new char[1]()),
	length(1),
	validLength(-1){
}

ByteSafe::~ByteSafe() {
	delete data;
}

void ByteSafe::Clear() {
	i = 0;
	while (i < length) {
		data[i] = 0;
		i++;
	}
}

bool ByteSafe::Decode(string key) {
	//char *x = new char[length]();
	//memcpy(x, data, sizeof(char)*length);

	//char c;
	//unsigned int kl = key.length();
	//unsigned int ki;
	//unsigned int messageLength = 0;
	//char *message = new char[0]();
	//bPtr = 0;
	//bSkp = 0;

	//string message = "";

	//i = 0;
	//ki = 0;
	//while (x) {
	//	c = message[i++];
	//	cout << c << " encoded with key[" << ki << "] " << key[ki] << endl;
	//	x = Add(x, length, c, key[ki]);
	//	++ki == kl ? 0 : ki;
	//	cout << endl;
	//}


	//cout << "data is valid : " << IsValid(x) << endl;
	return false;
}

bool ByteSafe::Encode(char *message, unsigned int messageLength, string key) {
	Clear();
	Reset();
	char *x = new char[length]();
	char c;//current char of message
	unsigned int kl = key.length();//key length
	unsigned int ki;//key index
	unsigned int pi;//print index

	while (i < messageLength) {
		if (!IsValid(x)) {
			bPtr = 0; bSkp = 0; i = 0; ki = 0;
			//increase size of x by one byte and start over
			delete x;
			x = new char[++length]();
			cout << "[INCREASE BLOCK SIZE] to " << length << endl;
		}
		//get the next character of the message to encode
		c = message[i++];

		x = Add(x, length, c, key[ki]);

		//print output to user
		cout << c << " encoded with key[" << ki << "] " << key[ki] << " -> ";
		pi = 0;
		while (pi < length) {
			cout << ":";
			Bit::Print(x[pi]);
			++pi;
		}

		//loop the key if it reaches the end
		//ki++ + 1 == kl ? 0 : ki;
		ki++;
		if (ki == kl) ki = 0;
		cout << endl;
	}


	cout << "data is valid : " << IsValid(x) << endl;
	data = x;
	return true;
}

bool ByteSafe::Encode(string message,string key) {
	unsigned int ml = message.length();
	char *m = new char[ml]();
	m = (char*)message.c_str();
	return Encode(m, ml, key);
}


/*using the length of the data block and the key we are going to try 
and decode using, run through the algorithm without any actual encoding
to find the starting bit to unravel this mess.*/
unsigned int ByteSafe::FindFinalBit(unsigned int baseLength, string key) {

	//unsigned int kl = key.length();//key length
	//unsigned int ki;//key index

	//while (i < messageLength) {

	//	//get the next character of the message to encode
	//	c = message[i++];

	//	x = Add(x, length, c, key[ki]);


	//	//loop the key if it reaches the end
	//	//ki++ + 1 == kl ? 0 : ki;
	//	ki++;
	//	if (ki == kl) ki = 0;
	//	cout << endl;
	//}


	//cout << "data is valid : " << IsValid(x) << endl;
	//data = x;
	//return true;



	return 0;
}

bool ByteSafe::IsValid(char *testData) {
	if (validLength != length) {
		invalidBlock = new char[length]();
		memset(invalidBlock, 0, sizeof invalidBlock);
		validLength = length;
	}
	return memcmp(invalidBlock, testData, length);
}

void ByteSafe::PrintBlock() {

}


void ByteSafe::Reset() {
	delete data;
	length = 7;
	data = new char[length]();
}