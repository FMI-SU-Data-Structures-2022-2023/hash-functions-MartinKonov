#ifndef WEEK11_HASH_H
#include<string>
#include <map>

long long Hash(std::string str);
long long RollingHash(std::string prev, long long H, char nxt);
int rabinKarp(const char* s, const char* in);

#endif //WEEK11_HASH_H
