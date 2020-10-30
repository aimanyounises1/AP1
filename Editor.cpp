#include <string>
#include <iostream>
#include <sstream>
#include <bits/stdc++.h>
#include "Editor.h"
using namespace std;
Editor::Editor(): document(){}

void Editor::loop(){
	string a;
	while(1){
		getline(cin, a);
		if (!a.compare("Q"))
			break;
		handle(a);
	}
}
//handle a text line from the user
void Editor::handle(string line){
	
	//in case of 'a', 'i' or 'c', call "text" function, until '.' recived.
	static bool waitForDot = false;
	if(waitForDot){
		document.text(line);
		if(!line.compare("."))
			waitForDot = false;
		return;
	}
	
	if(!line.compare("p")){
		document.p();
		return;
	}
	if(!line.compare("n")){
		document.n();
		return;
	}
	if(!line.compare("%p")){
		document.prec_p();
		return;
	}
	if(!line.compare("a")){
		waitForDot = true;
		document.a();
		return;
	}
	if(!line.compare("i")){
		document.i();
		waitForDot = true;
		return;
	}
	if(!line.compare("c")){
		waitForDot = true;
		document.c();
		return;
	}
	if(!line.compare("d")){
		document.d();
		return;
	}
	
	//check if the text is a number
	int num = 0;
	bool isAnumber;
	string s = line;
	try{
		num = stoi(s);
		isAnumber=true;
	}
	catch (std::invalid_argument const &e){
		isAnumber=false;
	}
	catch (std::out_of_range const &e){
		isAnumber=false;
	}
	if(isAnumber){
		document.num(num);
		return;
	}
	
	//empty text
	if(line.size()==0){
		document.text(line);
		return;
	}
	
	// '/text'
	if(line.at(0) == '/'){
		document.slesh_text(split(line, '/')[1]);
		return;		
	}
	// 's/old/new/'
	if(line.at(0) == 's'){
		vector<string> arr = split(line, '/');
		if(arr.size() >= 3){
			document.s_slech_old_new(arr[1], arr[2]);
			return;
		}
	}
	
	//text
	//document.text(line);
	
}
//split text by char and return a vector of words
vector<string> Editor::split(string str, char splitBy){
	vector<string> words;
   string word = ""; 
   for (auto x : str) { 
       if (x == splitBy) {  
		   words.push_back(word);
           word = ""; 
       } 
       else{ 
           word = word + x; 
       } 
   }  
   words.push_back(word);
   return words;
} 
