#include <string>
#include <iostream>
#include "Document.h"
class Editor{
	private:
	Document document;
	vector<string> split(string str, char splitBy);
	void handle(string line);
	public:
	Editor();
	void init(string &);
	void loop();
};
