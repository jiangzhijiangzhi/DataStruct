#include<iostream>
#include<cctype>
using namespace std;
int factor_value();
int term_value();
int expression_value();
int main(){
	while(1){
		cout<<expression_value()<<endl;
	}
	return 0;
}
int expression_value(){
	int result=0;
	result=term_value();
	bool more=true;
	while(more){
		if(cin.peek()=='+'){
			cin.get();
			result+=term_value();
		}
		else if(cin.peek()=='-'){
			cin.get();
			result-=term_value();
		}
		else{
			more=false;
		}
	}
	return result;
}
int term_value(){
	int result=0;
	result=factor_value();
	bool more=true;
	while(more){
		if(cin.peek()=='*'){
			cin.get();
			result*=factor_value();
		}
	else if(cin.peek()=='/'){
		cin.get();
		result/=factor_value();
	}
	else{
		more=false;
 	}
  }
	return result;
  }

int factor_value(){
	int result=0;
	if(cin.peek()=='('){
		cin.get();
		result=expression_value();
		cin.get();
	}
	else{
		result=cin.get()-'0';
		while(isdigit(cin.peek())){
			result=10*result+(cin.get()-'0');
		}
	}
	return result;
}
