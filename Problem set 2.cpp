#include <iostream>
#include <stack>
#include <conio.h>
#include <string>
using namespace std;

void idle() {
	int input;
	cout << "\n\nEnter any key to exit the program" << endl;
	input = getch();
	if (input == 13) {
		system("cls");
	}

}

bool isMathOperator(char token) {
// math operator checker
    switch (token) {
        case '+': 
        case '-': 
        case '*': 
        case '/': 
            return true;
            break;
        default:
            return false;
            break;
    }
}

int orderOfOperations(char token) {
// Priority of operation
    int priority = 0;
    switch (token) {
        case '*': 
        case '/': 
            priority = 2;
            break;
        case '-': 
        case '+':
            priority = 1;
            break;
    }
    return priority;
}

int evaluate(string postfix){
    stack<int> ns; //bikin stack dulu buat masukin angka2nya
    for (int i = 0; i < postfix.length(); i++){
        char c = postfix[i];
        if (c == ' '){ //kalo spasi diskip aja
            continue; 
        }else if(isdigit(c)){
            int n = 0;
            while (isdigit(c)){
                n = n * 10 + (int)(c - '0'); 
                // Konsepnya angka yang lebih depan itu nanti dikali 10
                // Misal 121, nanti 
                // iterasi ke-1 => n = 0 * 10 + 1
                //                 n = 1
                // iterasi ke-2 => n = 1 * 10 + 2
                //                 n = 12
                // iterasi ke-3 => n = 12 * 10 + 1
                //                 n = 121
                i++;
                c = postfix[i];
            }
            i--; 
            ns.push(n); //push angkanya ke stack
            
        }else{
            int val1 = ns.top(); ns.pop(); //Ambil 2 angka paling pucuk buat dioperasiin
            int val2 = ns.top(); ns.pop();
            switch (c){
            case '+':
                ns.push(val2 + val1);
                break;
            case '-':
                ns.push(val2 - val1);
                break;
            case '*':
                ns.push(val2 * val1);
                break;
            case '/':
                ns.push(val2 / val1);
                break;
            default:
                throw invalid_argument{
                    "ERROR: UNKNOWN OPERATOR"
                };
                break;
            }
        }
    }
    return ns.top();
}

string convertInfixToPostfix(string infix) {
    string postfix;
    stack<char> charStack;
 
    for (int i = 0; i < infix.length(); i++) {
        // Masukin angka ke string 'postfix' 
        if (isdigit(infix[i])) { 
            if (postfix.length() > 0 && !isdigit(postfix.back())) { 
                //Cek kalo karakter di postfix paling belakang bukan angka / bukan digit
                if (!isspace(postfix.back())) { 
                    //cek kalo karakter postfix paling belakang bukan space
                    postfix += " "; //Dikasih space setelah digit selesai
                }
            }
            postfix += infix[i]; // misal postfix.back() nya bukan suatu digit, langsung push ke string
        }else if (isMathOperator(infix[i])) {  //Dicek apakah ekspresinya berupa math operator
            if (postfix.length() > 0 && !isspace(postfix.back())) { //Kalo setelah operator gaada spasi, dikasih spasi
                postfix += " ";
            }
            // while nya ngecek, selama stacknya ga kosong dan
            // math operator di pucuk stack, apakah lebih besar sama dengan dari
            // math operator pada tranversing sekarang
            while ((!charStack.empty()) && (orderOfOperations(charStack.top()) >= orderOfOperations(infix[i]))) {
                // Kalo bener lebih besar
                // math operator di pucuk stack dipush ke string postfix
                
                if (postfix.length() > 0 && !isspace(postfix.back())) { //Kalo setelah operator gaada spasi, dikasih spasi
                    postfix += " ";
                }
                postfix += charStack.top();
                charStack.pop(); //Jangan lupa dipop
            }
            // push sisa operator yang belum ke stack
            charStack.push(infix[i]);
        }else if (infix[i] == '(') { //Kurung buka dipush tersendiri ke stack
            charStack.push(infix[i]);
 
        }else if (infix[i] == ')') { //kalo ketemu kurung tutup..
            //while ngecek selama ga empty, dan pucuk stack nya bukan kurung buka
            while ((!charStack.empty()) && (charStack.top() != '(')) {
                if (postfix.length() > 0 && !isspace(postfix.back())) { //Kalo setelah operator gaada spasi, dikasih spasi
                    postfix += " ";
                }
                
                postfix += charStack.top(); //Operator sebelum '(' push semua
                charStack.pop(); //Jangan lupa dipop
            }
 
            // pop '(' symbol off the stack
            if (!charStack.empty()) {
                charStack.pop();
            } else {
                //Misal ga ketemu '(' sampe akhir
                throw invalid_argument {
                    "ERROR: INVALID PARENTHESIS"
                };
            }
        } else {
            throw invalid_argument {
                "ERROR: INVALID INPUT"
            };
        }
    }
 
    //Masukin sisanya ke string postfix
    while (!charStack.empty()) {
        if (postfix.length() > 0 && !isspace(postfix.back())) { //Kalo setelah operator gaada spasi, dikasih spasi
            postfix += " ";
        }
        postfix += charStack.top(); //Masukin lagi
        charStack.pop(); //Jangan lupa dipop
    }
    return postfix;
}


int main(){
    string number;
	cin >> number;
    string postfix = convertInfixToPostfix(number);
    cout << evaluate(postfix);
    
	idle();

    return 0;
}