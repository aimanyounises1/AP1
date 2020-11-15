#include <string>
#include <iostream>
#include <vector>
using namespace std;
class Document{
	private:
	bool addForward;
	bool addBackward;
	public:
	int currentLine;
	vector<string>lines;
	bool replace(std::string& str, const std::string& from, const std::string& to);
	Document();
	void init(ifstream& is);
	void text(string text);
	void p();
	void prec_p();
	void d();
	void a();
	void i();
	void append(string &);
	void n();
	void num(int);
	void num2(int);
	void c();
	void slesh_text(string text);
	void s_slech_old_new(string oldText, string newText);
	void j();
	void w(string &);
	void load();
	void handle(string& );
	void e(string &);
	void dollar();
};