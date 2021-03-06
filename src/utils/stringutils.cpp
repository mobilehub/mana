/*
 *  The Mana Client
 *  Copyright (C) 2007-2009  The Mana World Development Team
 *  Copyright (C) 2009-2010  The Mana Developers
 *
 *  This file is part of The Mana Client.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "utils/stringutils.h"

#include <string.h>
#include <algorithm>
#include <cstdarg>
#include <cstdio>

static int UTF8_MAX_SIZE = 10;

std::string &trim(std::string &str)
{
    std::string::size_type pos = str.find_last_not_of(' ');
    if (pos != std::string::npos)
    {
        str.erase(pos + 1);
        pos = str.find_first_not_of(' ');

        if (pos != std::string::npos)
            str.erase(0, pos);
    }
    else
    {
        // There is nothing else but whitespace in the string
        str.clear();
    }
    return str;
}

std::string &toLower(std::string &str)
{
    std::transform(str.begin(), str.end(), str.begin(), tolower);
    return str;
}

std::string &toUpper(std::string &str)
{
    std::transform(str.begin(), str.end(), str.begin(), toupper);
    return str;
}

unsigned int atox(const std::string &str)
{
    unsigned int value;
    sscanf(str.c_str(), "0x%06x", &value);

    return value;
}

const char *ipToString(int address)
{
    static char asciiIP[16];

    sprintf(asciiIP, "%i.%i.%i.%i",
            (unsigned char)(address),
            (unsigned char)(address >> 8),
            (unsigned char)(address >> 16),
            (unsigned char)(address >> 24));

    return asciiIP;
}

std::string strprintf(char const *format, ...)
{
    char buf[256];
    va_list(args);
    va_start(args, format);
    int nb = vsnprintf(buf, 256, format, args);
    va_end(args);
    if (nb < 256)
    {
        return buf;
    }
    // The static size was not big enough, try again with a dynamic allocation.
    ++nb;
    char *buf2 = new char[nb];
    va_start(args, format);
    vsnprintf(buf2, nb, format, args);
    va_end(args);
    std::string res(buf2);
    delete [] buf2;
    return res;
}

std::string &removeBadChars(std::string &str)
{
    std::string::size_type pos;
    do
    {
        pos = str.find_first_of("@#[]");
        if (pos != std::string::npos)
            str.erase(pos, 1);
    } while (pos != std::string::npos);

    return str;
}

std::string removeColors(std::string msg)
{
    for (unsigned int f = 0; f < msg.length() - 2 && msg.length() > 2; f++)
    {
        while (msg.length() > f + 2 && msg.at(f) == '#' && msg.at(f + 1) == '#')
        {
            msg = msg.erase(f, 3);
        }
    }
    return msg;
}

int compareStrI(const std::string &a, const std::string &b)
{
    std::string::const_iterator itA = a.begin();
    std::string::const_iterator endA = a.end();
    std::string::const_iterator itB = b.begin();
    std::string::const_iterator endB = b.end();

    for (; itA < endA, itB < endB; ++itA, ++itB)
    {
        int comp = tolower(*itA) - tolower(*itB);
        if (comp)
            return comp;
    }

    // Check string lengths
    if (itA == endA && itB == endB)
        return 0;
    else if (itA == endA)
        return -1;
    else
        return 1;
}

bool isWordSeparator(char chr)
{
    return (chr == ' ' || chr == ',' || chr == '.' || chr == '"');
}

const std::string findSameSubstring(const std::string &str1,
                                    const std::string &str2)
{
    int minLength = str1.length() > str2.length() ? str2.length() : str1.length();
    for (int f = 0; f < minLength; f ++)
    {
        if (str1.at(f) != str2.at(f))
        {
            return str1.substr(0, f);
        }
    }
    return str1.substr(0, minLength);
}

const char* getSafeUtf8String(std::string text)
{
    char* buf = new char[text.size() + UTF8_MAX_SIZE];
    memcpy(buf, text.c_str(), text.size());
    memset(buf + text.size(), 0, UTF8_MAX_SIZE);
    return buf;
}

bool getBoolFromString(const std::string &text, bool def)
{
    std::string a = text;
    toLower(trim(a));
    if (a == "true" || a == "1" || a == "on" || a == "yes" || a == "y")
        return true;
    if (a == "false" || a == "0" || a == "off" || a == "no" || a == "n")
        return false;
    else
        return def;
}

std::string autocomplete(std::vector<std::string> &candidates,
                         std::string base)
{
    std::vector<std::string>::iterator i = candidates.begin();
    toLower(base);
    std::string newName("");

    while (i != candidates.end())
    {
        if (!i->empty())
        {
            std::string name = *i;
            toLower(name);

            std::string::size_type pos = name.find(base, 0);
            if (pos == 0)
            {
                if (newName != "")
                {
                    toLower(newName);
                    newName = findSameSubstring(name, newName);
                }
                else
                {
                    newName = *i;
                }
            }
        }

        ++i;
    }

    return newName;
}

std::string normalize(const std::string &name)
{
    std::string normalized = name;
    return toLower(trim(normalized));;
}
