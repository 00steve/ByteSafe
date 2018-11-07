#include "stdafx.h"
#include <cstdio>
#include <string>

using namespace std;

#include "ByteSafe.h"
int main()
{
	string key = "myKey";
	string message = "a long sentence. Eventually, this has to get to a zero string, like [0x00000000]\\n.I'm sure there are plenty of ways to zero this bitch out!";

	int length;
	char *output;

	ByteSafe b;
	b.Encode(message, key);
	b.Decode(key);
	b.PrintBlock();
	getchar();
	return 0;
}

