#include "solution.h"

long long Hash(std::string str) {

    int constInt = 5;
    int largePrime = 1e9 + 9;
    long long toReturn = 0;
    long long toPow = (long long)pow(constInt, str.length() - 1);

    for (size_t i = 0; i < str.length(); i++)
    {
        if (str[i] == ' ') {
            toReturn = (toReturn + 1 * toPow) % largePrime;
        }
        else if (str[i] == '.') {
            toReturn = (toReturn + 2 * toPow) % largePrime;
        }
        else if (str[i] >= 'A' && str[i] <= 'Z') {
            toReturn = (toReturn + (str[i] - '>') * toPow) % largePrime;
        }
        else {
            toReturn = (toReturn + (str[i] - 'D') * toPow) % largePrime;
        }

        toPow /= constInt;
    }
    return toReturn;
}

long long RollingHash(std::string prev, long long H, char nxt) {

    int constInt = 5;
    int largePrime = 1e9 + 9;

    if (prev[0] == ' ') {
        if (nxt >= 'A' && nxt <= 'Z') {
            return ((H - (prev[0] - 31) * (long long)pow(constInt, prev.length() - 1)) * constInt + (nxt - '>')) % largePrime;
        }
        else {
            return ((H - (prev[0] - 31) * (long long)pow(constInt, prev.length() - 1)) * constInt + (nxt - 'D')) % largePrime;
        }
    }
    else if (prev[0] == '.') {
        if (nxt >= 'A' && nxt <= 'Z') {
            return ((H - (prev[0] - 44) * (long long)pow(constInt, prev.length() - 1)) * constInt + (nxt - '>')) % largePrime;
        }
        else {
            return ((H - (prev[0] - 44) * (long long)pow(constInt, prev.length() - 1)) * constInt + (nxt - 'D')) % largePrime;
        }
    }
    else if (prev[0] >= 'A' && prev[0] <= 'Z') {
        if (nxt == ' ') {
            return ((H - (prev[0] - '>') * (long long)pow(constInt, prev.length() - 1)) * constInt + (nxt - 31)) % largePrime;
        }
        else if (nxt == '.') {
            return ((H - (prev[0] - '>') * (long long)pow(constInt, prev.length() - 1)) * constInt + (nxt - 44)) % largePrime;
        }
        else if (nxt >= 'a' && nxt <= 'z') {
            return ((H - (prev[0] - '>') * (long long)pow(constInt, prev.length() - 1)) * constInt + (nxt - 'D')) % largePrime;
        }
        else {
            return ((H - (prev[0] - '>') * (long long)pow(constInt, prev.length() - 1)) * constInt + (nxt - '>')) % largePrime;
        }
    }
    else {
        if (nxt == ' ') {
            return ((H - (prev[0] - 'D') * (long long)pow(constInt, prev.length() - 1)) * constInt + (nxt - 31)) % largePrime;
        }
        else if (nxt == '.') {
            return ((H - (prev[0] - 'D') * (long long)pow(constInt, prev.length() - 1)) * constInt + (nxt - 44)) % largePrime;
        }
        else if (nxt >= 'a' && nxt <= 'z') {
            return ((H - (prev[0] - 'D') * (long long)pow(constInt, prev.length() - 1)) * constInt + (nxt - 'D')) % largePrime;
        }
        else {
            return ((H - (prev[0] - 'D') * (long long)pow(constInt, prev.length() - 1)) * constInt + (nxt - '>')) % largePrime;
        }
    }
    
}


int rabinKarp(const char* s, const char* in) {
    int i = 0;
    std::string newS;
    std::string newIn;
    while (s[i] != '\0')
    {
        newS.push_back(s[i]);
        i++;
    }
    i = 0;
    while (in[i] != '\0')
    {
        newIn.push_back(in[i]);
        i++;
    }

    int j = 0;
    std::string prev = newIn.substr(j, newS.length());
    j++;
    //std::map<long long, long long> toCheck;
    long long InHash = Hash(newS);

    long long cur = Hash(prev);

    if (cur == InHash) {
        return 0;
    }

    for (size_t k = newS.length(); k < newIn.length(); k++)
    {
        //if (newIn[k] == '.' || newIn[k] == ' ') {
        //    continue;
        //}
        cur = RollingHash(prev, cur, newIn[k]);
        if (cur == InHash) {

            return k - newS.length() + 1;

        }
        prev = newIn.substr(j, newS.length());
        j++;
    }
    return -1;
}