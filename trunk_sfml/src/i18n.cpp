#include "i18n.h"

#include <string>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <cwchar>
#include <cerrno>

// This is from http://stackoverflow.com/questions/7141260/compare-stdwstring-and-stdstring/7159944#7159944
// Real worker
std::wstring get_wstring(const std::string & s)
{
    const char * cs = s.c_str();
    const size_t wn = std::mbsrtowcs(NULL, &cs, 0, NULL);

    if (wn == size_t(-1))
    {
        //std::cout << "Error in mbsrtowcs(): " << errno << std::endl;
        return L"";
    }

    std::vector<wchar_t> buf(wn + 1);
    const size_t wn_again = std::mbsrtowcs(buf.data(), &cs, wn + 1, NULL);

    if (wn_again == size_t(-1))
    {
        //std::cout << "Error in mbsrtowcs(): " << errno << std::endl;
        return L"";
    }

    assert(cs == NULL); // successful conversion

    return std::wstring(buf.data(), wn);
}


std::wstring _(const char * c){
    std::string s = gettext(c);
    return get_wstring(s);
}
