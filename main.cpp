#include <string>
#include <iostream>
#include <sstream>
#include <bits/stdc++.h>
#include "Editor.h"
int main(int argc, char *argv[])
{
	Editor ed;
	string name = "";
	if (argc > 1)
	{
		name = argv[1];
	}
	switch (argc)
	{
	case 1:
		cout << argc << endl;
		ed.loop();
		break;
	case 2:
		ed.init(name);
	default:
		break;
	}
	return 0;
}