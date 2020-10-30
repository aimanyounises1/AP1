#include <string>
#include <iostream>
#include <vector>
using namespace std;
class Document{
	private:
	std::vector <string> lines;
	int currentLine;
	bool addForward;
	bool addBackward;
	bool replace(std::string& str, const std::string& from, const std::string& to);
	public:
	Document();
	void text(string text);
	void p();
	void prec_p();
	void n();
	void d();
	void a();
	void i();
	void num(int number);
	void c();
	void slesh_text(string text);
	void s_slech_old_new(string oldText, string newText);
};