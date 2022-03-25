#include "LN.h"
#include <iostream>


char LN::comp(int *a_, int al, int *b, int bl, bool sign_a_, bool sign_b) const {
    if (sign_a_ == false && sign_b == true) {
        return '<';
    }
    if (sign_a_ == true && sign_b == false) {
        return '>';
    }
    if (al > bl) {
        return '>';
    }
    if (al < bl) {
        return '<';
    }
    for (int i = 0; i < al; i++) {
        if (a_[i] > b[i]) {
            return '>';
        }
        if (a_[i] < b[i]) {
            return '<';
        }
    }
    return '=';
}

LN LN::add(int *a_, int *b, int al, int bl) const {
    int cl;
    int *c;
    c = (int *) malloc(cl * sizeof(int));
    for (int i = 0; i < cl; i++) {
        c[i] = 0;
    }
    if (al > bl) {
        cl = al + 1;
    } else {
        cl = bl + 1;
    }
    int al1 = al;
    int bl1 = bl;
    for (int i = cl - 1; i > 0; i--) {
        if (al1 > 0 && bl1 > 0) {
            c[i] += (a_[al1 - 1] + b[bl1 - 1]);
            c[i - 1] += (c[i] / 10);
            c[i] %= 10;
        } else if (al1 <= 0 && bl1 > 0) {
            c[i] += (b[bl1 - 1]);
            c[i - 1] += (c[i] / 10);
            c[i] %= 10;
        } else if (bl1 <= 0 && al1 > 0) {
            c[i] += (a_[al1 - 1]);
            c[i - 1] += (c[i] / 10);
            c[i] %= 10;
        } else {
            c[i - 1] += (c[i] / 10);
            c[i] %= 10;
        }
        al1--;
        bl1--;
    }
    if (c[0] == 0) {
        cl--;
        int *c1;
        c1 = (int *) malloc(cl * sizeof(int));
        for (int i = 0; i < cl; i++) {
            c1[i] = c[i + 1];
        }
        LN res(c1, cl, true);
        return res;
    }
    LN res(c, cl, true);
    return res;
}

LN &LN::operator=(LN &obj) {
    free(a_);
    a_ = (int *) malloc(len_ * sizeof(int));
    for (int i = 0; i < obj.len_; i++) {
        a_[i] = obj.a_[i];
    }
    len_ = obj.len_;
    sign_ = obj.sign_;
    return *this;
}

LN::LN(long long x) {
    std::string s = std::to_string(x);
    sign_ = true;
    if (s[0] == '-') {
        sign_ = false;
    }
    len_ = sign_ ? s.length() : s.length() - 1;
    a_ = (int *) malloc(len_ * sizeof(int));
    int u = 0;
    for (int i = sign_ ? 0 : 1; i < s.length(); i++) {
        a_[u] = s[i] - '0';
        u++;
    }
}

LN::LN(std::string_view s) {
    std::string{s};
    sign_ = true;
    if (s[0] == '-') {
        sign_ = false;
    }
    len_ = sign_ ? s.length() : s.length() - 1;
    a_ = (int *) malloc(len_ * sizeof(int));
    int u = 0;
    for (int i = sign_ ? 0 : 1; i < s.length(); i++) {
        a_[u] = s[i] - '0';
        u++;
    }
}

LN::LN(const char *str) {
    std::string s = str;
    sign_ = true;
    if (s[0] == '-') {
        sign_ = false;
    }
    len_ = sign_ ? s.length() : s.length() - 1;
    a_ = (int *) malloc(len_ * sizeof(int));
    int u = 0;
    for (int i = sign_ ? 0 : 1; i < s.length(); i++) {
        a_[u] = s[i] - '0';
        u++;
    }
}

LN::LN(LN &&obj) {
    a_ = obj.a_;
    len_ = obj.len_;
    sign_ = obj.sign_;
    obj.a_ = nullptr;
}

LN::LN(const LN &obj) {
    len_ = obj.len_;
    a_ = (int *) malloc(len_ * sizeof(int));
    for (int i = 0; i < obj.len_; i++) {
        a_[i] = obj.a_[i];
    }
//    len_ = obj.len_;
    sign_ = obj.sign_;
}

LN::operator long long() {
    long long res = 0;
    int k = 1;
    for (int i = len_ - 1; i >= 0; i--) {
        res += a_[i] * k;
        k *= 10;
    }
    if (!sign_) {
        return -res;
    }
    return res;
}

LN::operator bool() {
    if (len_ == 1 && a_[0] == 0) {
        return true;
    }
    return false;
}

LN operator "" _ln(const char *s) {
    return LN(s);
}

LN &LN::operator=(LN &&obj) {
    a_ = obj.a_;
    len_ = obj.len_;
    sign_ = obj.sign_;
    obj.a_ = nullptr;
    return *this;
}

LN LN::subtract(int *a_, int *b, int al, int bl) const {
    int cl = al;
    int *c;
    c = (int *) malloc(cl * sizeof(int));
    for (int i = 0; i < cl; i++) {
        c[i] = 0;
    }
    int al1 = al;
    int bl1 = bl;
    for (int i = cl - 1; i >= 0; i--) {
        if (al1 > 0 && bl1 > 0) {
            if (a_[al1 - 1] >= b[bl1 - 1]) {
                c[i] = a_[al1 - 1] - b[bl1 - 1];
            } else {
                c[i] = 10 + a_[al1 - 1] - b[bl1 - 1];
                a_[al1 - 2]--;
            }
        } else if (al1 > 0) {
            c[i] = a_[al1 - 1];
        }
        al1--;
        bl1--;
    }
    LN res(c, cl, true);
    return res;
}

void LN::setValues(int *a_val, int len_val, bool sign_val) {
    a_ = a_val;
    len_ = len_val;
    sign_ = sign_val;
}

LN LN::operator*(const LN &b) const {
    int cl = len_ + b.len_;
    int *c;
    int al1 = len_ - 1;
    int bl1 = b.len_ - 1;
    c = (int *) malloc(cl * sizeof(int));
    for (int i = 0; i < cl; i++) {
        c[i] = 0;
    }
    bool sign_c = true;
    if (sign_ == false && b.sign_ == true || sign_ == true && b.sign_ == false) {
        sign_c = false;
    }
    int r = 0;
    int y;
    for (int i = bl1; i >= 0; i--) {
        y = bl1 - i;
        for (int j = al1; j >= 0; j--) {
            c[y] += ((a_[j] * b.a_[i]) % 10 + r) % 10;
            r = (a_[j] * b.a_[i] + r) / 10;
            y++;
        }
        c[y] = r;
    }
    int g = cl - 1;
    int o = 0;
    while (c[g] == 0) {
        o++;
    }
    int dl = cl - o;
    int *d;
    d = (int *) malloc(dl * sizeof(int));
    for (int i = 0; i < dl; i++) {
        d[i] = 0;
    }
    for (int i = 0; i < dl; i++) {
        d[i] = c[i + o];
    }
    LN res(d, dl, sign_c);
    return res;
}

LN LN::operator+=(LN &b) {
    return this->operator+(b);
}

LN LN::operator>(const LN &b) const {
    if (comp(a_, len_, b.a_, b.len_, sign_, b.sign_) == '>') {
        int arr[] = {1};
        LN res(arr, 1, true);
        return res;
    } else {
        int arr[] = {0};
        LN res(arr, 1, true);
        return res;
    }
}

LN LN::operator<(const LN &b) const {
    if (comp(a_, len_, b.a_, b.len_, sign_, b.sign_) == '<') {
        int arr[] = {1};
        LN res(arr, 1, true);
        return res;
    } else {
        int arr[] = {0};
        LN res(arr, 1, true);
        return res;
    }
}

LN LN::operator<=(const LN &b) const {
    char ch = comp(a_, len_, b.a_, b.len_, sign_, b.sign_);
    if (ch == '<' || ch == '=') {
        int arr[] = {1};
        LN res(arr, 1, true);
        return res;
    } else {
        int arr[] = {0};
        LN res(arr, 1, true);
        return res;
    }
}

LN LN::operator>=(const LN &b) const {
    char ch = comp(a_, len_, b.a_, b.len_, sign_, b.sign_);
    if (ch == '>' || ch == '=') {
        int arr[] = {1};
        LN res(arr, 1, true);
        return res;
    } else {
        int arr[] = {0};
        LN res(arr, 1, true);
        return res;
    }
}

LN LN::operator==(const LN &b) const {
    char ch = comp(a_, len_, b.a_, b.len_, sign_, b.sign_);
    if (ch == '=') {
        int arr[] = {1};
        LN res(arr, 1, true);
        return res;
    } else {
        int arr[] = {0};
        LN res(arr, 1, true);
        return res;
    }
}

LN LN::operator!=(const LN &b) const {
    char ch = comp(a_, len_, b.a_, b.len_, sign_, b.sign_);
    if (ch != '=') {
        int arr[] = {1};
        LN res(arr, 1, true);
        return res;
    } else {
        int arr[] = {0};
        LN res(arr, 1, true);
        return res;
    }
}

LN::LN(std::string s) {
    sign_ = true;
    if (s[0] == '-') {
        sign_ = false;
    }
    len_ = sign_ ? s.length() : s.length() - 1;
    a_ = (int *) malloc(len_ * sizeof(int));
    int u = 0;
    for (int i = sign_ ? 0 : 1; i < s.length(); i++) {
        a_[u] = s[i] - '0';
        u++;
    }
}

LN LN::operator+(const LN &b) const {
    int cl;
    int *c;
    c = (int *) malloc(cl * sizeof(int));
    for (int i = 0; i < cl; i++) {
        c[i] = 0;
    }
    if (sign_ == false || b.sign_ == false) {
        if (sign_ == false && b.sign_ == false) {
            LN x = add(a_, b.a_, len_, b.len_);
            LN res(x.a_, x.len_, false);
            return res;
        } else if (sign_ == false) {
            if (comp(a_, len_, b.a_, b.len_, sign_, b.sign_) == '>') {
                LN x = subtract(a_, b.a_, len_, b.len_);
                LN res(x.a_, x.len_, false);
                return res;
            } else if (comp(a_, len_, b.a_, b.len_, sign_, b.sign_) == '<') {
                LN x = subtract(b.a_, a_, b.len_, len_);
                LN res(x.a_, x.len_, true);
                return res;
            } else {
                LN res({}, 0, true);
                return res;
            }
        } else {
            if (comp(a_, len_, b.a_, b.len_, sign_, b.sign_) == '>') {
                LN x = subtract(a_, b.a_, len_, b.len_);
                LN res(x.a_, x.len_, true);
                return res;
            } else if (comp(a_, len_, b.a_, b.len_, sign_, b.sign_) == '<') {
                LN x = subtract(b.a_, a_, b.len_, len_);
                LN res(x.a_, x.len_, false);
                return res;
            } else {
                LN res({}, 0, true);
                return res;
            }
        }
    } else {
        LN x = add(a_, b.a_, len_, b.len_);
        LN res(x.a_, x.len_, true);
        return res;
    }
}

LN LN::operator-(const LN &b) const {
    int cl;
    int *c;
    c = (int *) malloc(cl * sizeof(int));
    for (int i = 0; i < cl; i++) {
        c[i] = 0;
    }
    if (sign_ == false || b.sign_ == false) {
        if (sign_ == true && b.sign_ == false) {
            LN x = add(a_, b.a_, len_, b.len_);
            LN res(x.a_, x.len_, true);
            return res;
        } else if (sign_ == false && b.sign_ == true) {
            LN x = add(a_, b.a_, len_, b.len_);
            LN res(x.a_, x.len_, false);
            return res;
        } else {
            if (comp(a_, len_, b.a_, b.len_, sign_, b.sign_) == '<') {
                LN x = subtract(b.a_, a_, b.len_, len_);
                LN res(x.a_, x.len_, true);
                return res;
            } else if (comp(a_, len_, b.a_, b.len_, sign_, b.sign_) == '>') {
                LN x = subtract(a_, b.a_, len_, b.len_);
                LN res(x.a_, x.len_, false);
                return res;
            } else {
                LN res({}, 0, true);
                return res;
            }
        }
    } else {
        if (comp(a_, len_, b.a_, b.len_, sign_, b.sign_) == '<') {
            LN x = subtract(b.a_, a_, b.len_, len_);
            LN res(x.a_, x.len_, false);
            return res;
        } else if (comp(a_, len_, b.a_, b.len_, sign_, b.sign_) == '>') {
            LN x = subtract(a_, b.a_, len_, b.len_);
            LN res(x.a_, x.len_, true);
            return res;
        } else {
            LN res({}, 0, true);
            return res;
        }
    }
}