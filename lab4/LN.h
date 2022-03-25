#ifndef _LN_H
#define _LN_H

#include <string>

class LN {
public:
    int *a_;
    int len_;
    bool sign_;

    LN(int *a_val, int len_val, bool sign) {
        setValues(a_val, len_val, sign);
    }

    LN(const LN &obj);

    LN(LN &&obj);

    LN(const char *str);

    LN(std::string_view s);

    LN(long long x = 0);

    LN(std::string s);

    ~LN() {
        free(a_);
    }

    LN operator+(const LN &b) const;

    LN operator-(const LN &b) const;

    LN operator*(const LN &b) const;

    LN operator>(const LN &b) const;

    LN operator<(const LN &b) const;

    LN operator<=(const LN &b) const;

    LN operator>=(const LN &b) const;

    LN operator==(const LN &b) const;

    LN operator!=(const LN &b) const;

    LN operator+=(LN &b);

    LN &operator=(LN &obj);

    LN &operator=(LN &&obj);

    operator long long();

    operator bool();



    void setValues(int *a_val, int len_val, bool sign);

private:
    LN add(int *a, int *b, int len_, int len1_) const;

    LN subtract(int *a, int *b, int len_, int len1_) const;

    char comp(int *a, int len_, int *b, int len1_, bool sign_a, bool sign_b) const;

};
LN operator "" _ln(const char *s);

#endif