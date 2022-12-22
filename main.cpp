#include "Dictionary.h"
#define NUM 0
#define CONST 1
#define FUU 2
#define ACTION 3
#define VAR 4
#define BKT 5

struct Token{
    string value;
    int type;
};

string build_num(const string& expr, int i){
    string num = "";
    while((expr[i] == '0' || expr[i] == '1' || expr[i] == '2' || expr[i] == '3' || expr[i] == '4'
    || expr[i] == '5' || expr[i] == '6' || expr[i] == '7' || expr[i] == '8' || expr[i] == '9')
    && i < expr.length()){
        num+=expr[i];
        i++;
    }
    return num;
}
bool check_if_letter(char C){
    for(int i = 0; i < 26; i++){
        if(C == 'a' + i){
            return true;
        }
        return false;
    }
}
string build_word(const string& expr,int i){
    string word = "";
    while(check_if_letter(expr[i]) && i < expr.length()){
        word += expr[i];
        i++;
    }
    return word;
}


vector<Token> arr;
string calculation(const string& expr){
    // decide whteher it is function, num, variable, or const
    Dictionary dictionary;
    int j = 0;
    string buf;
    Token to_add;
    for(int i = 0; i < expr.length();){
        buf = build_num(expr,i);
        if(buf.length() > 0){
            to_add.value = buf;
            to_add.type = NUM;
            arr.push_back(to_add);
            i += buf.length();
            continue;
        }

        buf = build_word(expr,i);
        if(buf.length() > 0){
            i += buf.length();
            if(expr[i+1] == '('){
                to_add.type = FUU;
                dictionary.add(buf,buf);
            }
            else {
                to_add.type = CONST;
            }
            to_add.value = buf;
            arr.push_back(to_add);
            continue;
        }

        if(expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/' || expr[i] == '^'){
            to_add.value = expr[i];
            to_add.type = ACTION;
            arr.push_back(to_add);
            i++;
            continue;
        }

        if(expr[i] == 'X'){
            to_add.value = expr[i];
            to_add.type = VAR;
            arr.push_back(to_add);
            i++;
            continue;
        }

        if(expr[i] == '(' || expr[i] == ')'){
            to_add.value = expr[i];
            to_add.type = BKT;
            arr.push_back(to_add);
            i++;
            continue;
        }
    }
}

string turn_to_string(int l, int r){
    string expr = "";
    for(int i = l; i <= r; i++){
        expr += arr[i].value;
    }
    return expr;
}

vector <char> brackets;
bool check_BKT(int l, int r){
    for(int i = l; i <= r; i++){
        if(arr[i].value == "("){
            brackets.push_back('(');
        }
        if(arr[i].value == ")"){
            if(arr.empty() == true){
                arr.erase();
                return false;
            }
            brackets.pop_back();
        }
    }
    if(brackets.empty()){
        return true;
    }
    return false;
}

string fuu(int l, int r){
    for(int i = l; i <= r; i++){
        if(arr[i].type == ACTION){
            if(arr[i].value == "+" && check_BKT(i,r)){
                return fuu(l,i-1) + '+' + fuu(i+1,r);
            }
            if(arr[i].value == "-" && check_BKT(i,r)){
                return fuu(l,i-1) + '+' + fuu(i+1,r);
            }
        }
    }
    for(int i = l; i <= r; i++){
        if(arr[i].type == ACTION){
            if(arr[i].value == "*" && check_BKT(i,r)){
                return fuu(l,i-1) + '*' + turn_to_string(i+1,r) + '+' + fuu(i+1,r) + '*' + turn_to_string(l,i-1);
            }
            if(arr[i].value == "/" && check_BKT(i,r)){
                return '('+fuu(l,i-1)+'*'+turn_to_string(i+1,r)+
                '-'+fuu(i+1,r)+'*'+turn_to_string(l,i-1)+')'+'/'+'('+turn_to_string(i+1,r)+')'+'^'+'2';
            }
        }
    }
    if()

}

int main() {




    return 0;
}
