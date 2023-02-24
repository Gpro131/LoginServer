#include "tool.h"
#include "BaseInc.h"

using namespace std;
std::string SubString(std::string str, char start, char end)
{
	size_t posS = str.find_first_of(start);
	size_t posE = str.find_last_of(end);
	return  str.substr(posS + 1, posE - posS - 1);
}

bool IsDigital(string& str)
{
	auto it = str.begin();
	while (it != str.end() && std::isdigit(*it)) {
		it++;
	}
	return !str.empty() && it == str.end();
}


bool chars2wchars(const char* srcChar, wchar_t* dstChar, int size)
{
	std::string strLocale = setlocale(LC_ALL, "");
	size_t nDestSize = mbstowcs(NULL, srcChar, 0) + 1;
	if (nDestSize > size)
	{
		printf("chars2wchars not enough space,required %d bytes,buf in fact %d bytes.", nDestSize, size);
		return false;
	}

	//wchar_t* wchDest = new wchar_t[nDestSize];
	wmemset(dstChar, 0, size);
	mbstowcs(dstChar, srcChar, nDestSize);
	/*std::wstring wstrResult = wchDest;
	delete[] wchDest;*/
	setlocale(LC_ALL, strLocale.c_str());
	return true;
}
bool wchars2chars(const wchar_t* wchSrc, char* dstChar, int size)
{
	std::string strLocale = setlocale(LC_ALL, "");
	size_t nDestSize = wcstombs(NULL, wchSrc, 0) + 1;
	if (nDestSize > size)
	{
		printf("wchars2chars not enough space,required %d bytes,buf in fact %d bytes.", nDestSize, size);
		return false;
	}

	//char* chDest = new char[nDestSize];
	memset(dstChar, 0, size);
	wcstombs(dstChar, wchSrc, nDestSize);
	/*std::string strResult = chDest;
	delete[] chDest;*/
	setlocale(LC_ALL, strLocale.c_str());
	return true;
}


std::string WString2String(const std::wstring& ws)
{
	std::string strLocale = setlocale(LC_ALL, "");
	const wchar_t* wchSrc = ws.c_str();
	size_t nDestSize = wcstombs(NULL, wchSrc, 0) + 1;
	char* chDest = new char[nDestSize];
	memset(chDest, 0, nDestSize);
	wcstombs(chDest, wchSrc, nDestSize);
	std::string strResult = chDest;
	delete[] chDest;
	setlocale(LC_ALL, strLocale.c_str());
	return strResult;

}

std::wstring String2WString(const std::string& s)
{
	std::string strLocale = setlocale(LC_ALL, "");
	const char* chSrc = s.c_str();
	size_t nDestSize = mbstowcs(NULL, chSrc, 0) + 1;
	wchar_t* wchDest = new wchar_t[nDestSize];
	wmemset(wchDest, 0, nDestSize);
	mbstowcs(wchDest, chSrc, nDestSize);
	std::wstring wstrResult = wchDest;
	delete[] wchDest;
	setlocale(LC_ALL, strLocale.c_str());
	return wstrResult;

}

std::string UnicodeToAscii(wchar_t* src)
{
	std::string strLocale = setlocale(LC_ALL, "");
	const char* chSrc = strLocale.c_str();
	size_t nDestSize = mbstowcs(NULL, chSrc, 0) + 1;
	wchar_t* wchDest = new wchar_t[nDestSize];
	wmemset(wchDest, 0, nDestSize);
	mbstowcs(wchDest, chSrc, nDestSize);
	std::wstring wstrResult = wchDest;
	delete[] wchDest;
	setlocale(LC_ALL, strLocale.c_str());
	return chSrc;
}

std::wstring Utf82Unicode(const std::string& utf8string)
{
	int widesize = ::MultiByteToWideChar(CP_ACP, 0, utf8string.c_str(), -1, NULL, 0);
	if (widesize == ERROR_NO_UNICODE_TRANSLATION)
	{
		throw std::exception("Invalid UTF-8 sequence.");
	}
	if (widesize == 0)
	{
		throw std::exception("Error in conversion.");
	}

	std::vector<wchar_t> resultstring(widesize);
	int convresult = ::MultiByteToWideChar(CP_ACP, 0, utf8string.c_str(), -1, &resultstring[0], widesize);
	if (convresult != widesize)
	{
		throw std::exception("La falla!");
	}

	return std::wstring(&resultstring[0]);
}
std::wstring Chars2WChars(UINT type, std::string& str)
{
	int widesize = ::MultiByteToWideChar(type, 0, str.c_str(), -1, NULL, 0);
	if (widesize == ERROR_NO_UNICODE_TRANSLATION)
	{
		throw std::exception("Invalid UTF-8 sequence.");
	}
	if (widesize == 0)
	{
		throw std::exception("Error in conversion.");
	}

	std::vector<wchar_t> resultstring(widesize);
	int convresult = ::MultiByteToWideChar(type, 0, str.c_str(), -1, &resultstring[0], widesize);
	if (convresult != widesize)
	{
		throw std::exception("La falla!");
	}

	return std::wstring(&resultstring[0]);
}

std::string WChars2Chars(UINT type, std::wstring& wstr)
{
	int widesize = ::WideCharToMultiByte(type, 0, wstr.c_str(), -1, NULL, 0, 0, 0);
	if (widesize == ERROR_NO_UNICODE_TRANSLATION)
	{
		throw std::exception("Invalid UTF-8 sequence.");
	}
	if (widesize == 0)
	{
		throw std::exception("Error in conversion.");
	}

	std::vector<char> resultstring(widesize);
	int convresult = ::WideCharToMultiByte(type, 0, wstr.data(), -1, &resultstring[0], widesize, 0, 0);
	if (convresult != widesize)
	{
		throw std::exception("La falla!");
	}

	return std::string(&resultstring[0]);
}
// wstring=&gt;string
//std::string WString2String(const std::wstring&  ws)
//{
//	
//}
//
//
//std::wstring String2WString(const std::string& s)
//{
//	
//
//}
