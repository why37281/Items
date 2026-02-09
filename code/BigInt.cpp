#include <bits/stdc++.h>
using namespace std;
struct Bigint{
    int len, a[10000];
    bool d = 0;
    Bigint(){
        memset(a,0,sizeof(a));
        len = 0;
    }
    Bigint(long long x = 0){
        memset(a,0,sizeof(a));
        if (x < 0){
            d = 1;
            x = abs(x);
        }
        for(len = 1; x; len++){
            a[len] = x % 10, x /= 10;
        }
        len--;
    }
    Bigint(string x = "0"){
        memset(a, 0, sizeof(a));
        int len1 = x.size();
        if (x == "0") { len = 0; return;}
        if (x[0] == '-'){
            d = 1;
            for(len = 1;len1 > 1;len++, len1--){
                a[len] = x[len1 - 1] - '0';
            }
            return;
        }
        for(len = 1;len1 != 0;len++, len1--){
            a[len] = x[len1 - 1] - '0';
        }
        len--;
    }
    int &operator[](int i){
        return a[i];
    }
    bool operator<(Bigint x){
        if (d == 0 && x.d == 1) return false;
        if (d == 1 && x.d == 0) return true;
        int lstr = -1;
        for(int i = max(len, x.len);i > 0;i--){
            if (a[i] != x[i]){
                if (a[i] < x[i]) lstr = 1;
                if (a[i] > x[i]) lstr = 0;
                break;
            }
        }
        if (lstr == -1) return false;
        if (lstr == 1 && d == 1) return false;
        if (lstr == 1 && d == 0) return true;
        if (lstr == 0 && d == 1) return true;
        if (lstr == 0 && d == 0) return false;
    }
    bool operator>(Bigint x){
        if (d == 0 && x.d == 1) return true;
        if (d == 1 && x.d == 0) return false;
        int lstr = -1;
        for(int i = max(len, x.len);i > 0;i--){
            if (a[i] != x[i]){
                if (a[i] < x[i]) lstr = 1;
                if (a[i] > x[i]) lstr = 0;
            }
        }
        if (lstr == -1) return false;
        if (lstr == 0 && d == 0) return true;
        if (lstr == 1 && d == 1) return true;
        if (lstr == 0 && d == 1) return false;
        if (lstr == 1 && d == 0) return false;
    }
    bool operator==(Bigint x){
        if (d != x.d)return false;
        for(int i = 1;i < max(len, x.len);i++){
            if (x[i] != a[i]) return false;
        }
        return true;
    }
    void flatten(int L){
        len = L;
        for(int i = 1; i <= len; i++){
            a[i+1] += a[i] / 10, a[i] %= 10;
        }
        for(;!a[len];){
            len--;
        }
    }
    void print(){
        if (d == 1) printf("%c", '-');
        for(int i = max(len,1); i >= 1; i--){
            printf("%d", a[i]);
        }
    }
};
Bigint operator-(Bigint a, Bigint b);
Bigint operator+(Bigint a, Bigint b){
    Bigint c(0), d(0), e(0);
    d = a;
    e = b;
    d.d = 0;
    e.d = 0;
    if (a.d == b.d){
        c.d = a.d;
    }
    else if (d == e){
        return c;
    }else{
        if (d > e)c = d - e;
        else c = e - d;
        if (d > e)c.d = a.d;
        else c.d = b.d;
        return c;
    }
    int len = max(a.len, b.len);
    for(int i = 1; i <= len; i++){
        c[i] += a[i] + b[i];
    }
    c.flatten(len+1);
    return c;
}
Bigint operator-(Bigint a, Bigint b){
    Bigint c(0);
    if (a.d == 1 && b.d == 0) {
        Bigint d(0), e(0);
        d = a;
        d.d = 0;
        c = d + b;
        c.d = 1;
        return c;
    }
    if(a.d == 1 && b.d == 1){
        b.d = 0;
        c = a + b;
        return c;
    }
    if (a.d == 0 && b.d == 1){
        b.d = 0;
        c = a + b;
        return c;
    }
    if (a.d == 0 && b.d == 0 && a < b){
        c = b - a;
        c.d = 1;
        return c;
    }
    for(int i = 1;i <= max(a.len, b.len);i++){
        c[i] = a[i] - b[i];
        if (c[i] <  0){
            c[i] += 10;
            c[i + 1] -= 1;
        }
    }
    c.flatten(max(a.len, b.len));
    return c;
}
Bigint operator*(Bigint a, int b){
    Bigint c(0);
    if ((a.d == 0 && b > 0) || (a.d == 1 && b < 0)) c.d = 0;
    else c.d = 1;
    int len = a.len;
    for(int i = 1; i <= len; i++){
        c[i] = a[i] * b;
    }
    c.flatten(len + 11);
    return c;
}
Bigint operator*(Bigint a, Bigint b){
    Bigint c(0);
    if (a.len == 0 || b.len == 0) return c;
    if (a.d == b.d)c.d = 0;
    else c.d = 1;
    for(int i = 1;i <= a.len;i++){
        for(int j = 1;j <= b.len;j++){
            c[i + j - 1] += a[i] * b[j];
            c[i + j] += c[i + j - 1] / 10;
            c[i + j - 1] %= 10;
        }
    }
    c.flatten(a.len + b.len);
    return c;
}