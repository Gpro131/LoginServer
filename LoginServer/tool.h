#pragma once
#include <string>
#include <locale.h>
#include <intsafe.h>
std::string SubString(std::string str,char start, char end);

bool IsDigital(std::string& str);

bool chars2wchars(const char* srcChar,wchar_t* dstChar,int size);
bool wchars2chars(const wchar_t* ch,  char* dstWChar, int size);

// wstring=&gt;string
std::string WString2String(const std::wstring& ws);

// string =&gt; wstring
std::wstring String2WString(const std::string& s);

std::string UnicodeToAscii(wchar_t* src);

std::wstring Utf82Unicode(const std::string& utf8string);

std::wstring Chars2WChars(UINT type, std::string& str);

std::string WChars2Chars(UINT type, std::wstring& wstr);
