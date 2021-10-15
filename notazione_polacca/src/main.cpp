#include <cstdlib>
#include <iostream>
#include <cstdlib>
#include <stack.h>
using namespace std;

int CalcolaRis(const string&);

int main() {
    Stack<char> s;

    string espr;
    string fin = "";
    
    cout<<"Inserisci la tua espressine: ";
    cin>>espr;
    
    for(int i=0; i < espr.length(); i++) {
        switch(espr[i]) {
            case '+': case '-': case '*': case '/': {
                s.Push(espr[i]);
                break;
            }
            case '\0': case ')': {
                if (!s.IsEmpty()) {
                    fin += s.PopReturn();
                    fin += " ";
                }
                break;
            }
            case '(': case ' ':   break;
            default: {
                fin += espr[i];
                fin += " ";
                break;
            }
        }        
    }

    while (!s.IsEmpty()) {
        fin += s.PopReturn();
    }
    
    cout<<"Notazione polacca: "<<fin<<endl;
    cout << "Risultato: " << CalcolaRis(fin) << endl;
}


int CalcolaRis(const string& str)
{
    string tmp = "";
    Stack<int> s;

    for(int i=0; i<str.length(); i++)
    {
    	switch(str[i])
        {
            case '+': {
                int var1 = s.PopReturn();
                int var2 = s.PopReturn();

                int res = var2 + var1;

                s.Push(res);
                
                tmp = "";

                break;
            }
            case '-': {
                int var1 = s.PopReturn();
                int var2 = s.PopReturn();

                int res = var2 - var1;

                s.Push(res);

                tmp = "";

                break;
            }
            case '*': {
                int var1 = s.PopReturn();
                int var2 = s.PopReturn();

                int res = var2 * var1;

                s.Push(res);

                tmp = "";

                break;
            }
            case '/': {
                int var1 = s.PopReturn();
                int var2 = s.PopReturn();

                int res = var2 / var1;

                s.Push(res);

                tmp = "";

                break;
            }
            case ' ': {
                if (tmp.length() > 0) {
                    s.Push(atoi(tmp.c_str()));

                    tmp = "";
                }
                break;
            };
            default: {
                tmp += str[i];
                break;
            }
        }
    }

    return s.Top();
}
