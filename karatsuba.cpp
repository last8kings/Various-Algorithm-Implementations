/*
* Name : Karatsuba Algorithm
* Description : This program takes in two numbers as input and outputs their product. 
*  Runs in  O(n ^ (log_3(2)) time where n is the number of digits in the larger number.
*  Compare that to standard multiplication algorithm taught in school, which is O(n ^ 2).
*  Isn't really faster unless you are dealing with numbers with a large amount of digits seen in fields such as cryptography. 
*/


#include <iostream>
#include <string>

std::string firstxdigits(std::string s, int x) {
    if (x >= s.length()) return "0";
    return s.substr(0, s.length() - x);
}
    
std::string lastxdigits(std::string s, int x) {
    if (x >= s.length()) return s;
    return s.substr(s.length() - x, s.length());
}

std::string add(std::string X, std::string Y) {
    std::string ans;
    int XLen = X.length(), YLen = Y.length();
    int carry = 0;
    int MxLen = std::max(XLen, YLen);
    
    for (int i = MxLen - 1; i >= 0; --i) {
        int sum = carry;

        if ((XLen - MxLen + i) >= 0) sum += (X[XLen - MxLen + i] - '0');
        if ((YLen - MxLen + i) >= 0) sum += (Y[YLen - MxLen + i] - '0');
        
        ans += ('0' + sum % 10);
        carry = sum / 10;
    }
    
    if (carry) ans += (carry + '0');
    
    reverse(ans.begin(), ans.end());
    return ans;
}
    
std::string subtract(std::string X, std::string Y) {
    std::string ans;
    int XLen = X.length(), YLen = Y.length();
    int carry = 0;
    for (int i = XLen - 1; i >= 0; --i) {
        int sum = X[i] - '0' - carry;
        if ((YLen - XLen + i) >= 0) sum -= (Y[YLen - XLen + i] - '0');
            
        ans += ('0' + (10 + sum ) % 10);
        if (sum < 0) carry = 1;
        else carry = 0;
    }

    reverse(ans.begin(), ans.end());
    return ans;
}  
    
std::string karatsuba(std::string X, std::string Y) {
    int XLen = X.length();
    int YLen = Y.length();

    if (XLen == 1 && YLen == 1) {
        return std::to_string((X[0] - '0') * (Y[0] - '0'));
    } 
        
    int N = std::max(XLen, YLen) / 2;
    std::string a = firstxdigits(X, N);
    std::string b = lastxdigits(X, N);
    std::string c = firstxdigits(Y, N);
    std::string d = lastxdigits(Y, N );
        
 
    std::string ac = karatsuba(a, c);
    std::string bd = karatsuba(b, d);
    std::string ad_plus_bc = subtract(subtract(karatsuba(add(a, b), add(c, d)), ac), bd);
    
    for (int i = 1; i <= N * 2; ++i) ac += "0";
    for (int i = 1; i <= N; ++i) ad_plus_bc += "0";
        
    std::string ans = add(add(ac, ad_plus_bc), bd);
    
    for (int i = 0; i < ans.size(); ++i) {
        if (ans[i] != '0') {
            return ans.substr(i);
        }
    }

    return "0";  
}

int main() {
    std::string num1, num2;
    std::cin >> num1 >> num2;
    std::cout << karatsuba(num1, num2) << '\n';   
}
