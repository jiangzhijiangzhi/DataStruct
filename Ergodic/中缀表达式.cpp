#include<iostream>
#include<stack>
#include<string>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
map<const char, int> priority;
int compare(char a, char b){
    int cmp = 0;
    if(b==')' && a=='(') cmp = 0;
    else if(a=='(') cmp = -1;
    else if(priority[a] < priority[b]) cmp = -1;
    else if(priority[a] >= priority[b]) cmp = 1;
    return cmp;
}
int cal(int a, int b, char op){
    int ans;
    if(op=='+') ans = a+b;
    else if(op=='-') ans = a-b;
    else if(op=='*') ans = a*b;
    else if(op=='/') ans = a/b;
    return ans;
}
int calculator(){
    priority['#'] = -1;
    priority[')'] = 0;
    priority['+'] = 1;
    priority['-'] = 1;
    priority['*'] = 2;
    priority['/'] = 2;
    priority['('] = 3;
    cout<<"ËãÊ½:"<<endl;
    char ch = getchar();
    stack<char> op;
    stack<int> nums;
    op.push('#');
    nums.push(0);
    bool flag = true;
    while(ch!='#' || op.top()!='#'){
        if(ch<='9' && ch>='0'){
            int number = 0;
            while(ch>='0' && ch<='9'){
                number = number*10 + (ch-'0');
                ch = getchar();
            }
            nums.push(number);
            flag = true;
        }else{
            int cmp = compare(op.top(), ch);
            if(cmp==-1){
                op.push(ch);
                flag = false;
                ch = getchar();
            }else if(cmp==0){
                op.pop();
                ch = getchar();
            }else if(cmp==1){
                int num1, num2, tempans;
                char tempop;
                num2 = nums.top();
                nums.pop();
                num1 = nums.top();
                nums.pop();
                tempop = op.top();
                op.pop();
                tempans = cal(num1, num2, tempop);
                nums.push(tempans);
            }
            if(ch=='-' && !flag) nums.push(0);
            
        }
    }
    cin.get();
    return nums.top();
}
int main(){
    int i=3;
    printf("ÇëÊäÈëËãÊ½+#\n");
    while(i--){
        cout<<calculator()<<endl;
    }
return 0;
}
