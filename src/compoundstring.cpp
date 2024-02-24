#include "compoundstring.h"

#include <iostream>

void CompoundString::putInternal(const std::string& identifier, const std::string& value) {
    if(m_members.find(identifier) == m_members.end()) {
        m_members.try_emplace(identifier, value);
    } else {
        m_members.at(identifier) = value;
    }
}

bool CompoundString::endsWith(const std::string &string, const char &c) {
    if(string.back() == c) {
        return true;
    }

    std::string ctype;
    switch(c) {
        default: ctype = "bool"; break;
        case 'f': ctype = "float"; break;
        case 'd': ctype = "double"; break;
        case 'l': ctype = "long"; break;
    }

    std::string stype;
    switch(string.back()) {
        default: stype = "bool"; break;
        case 'f': stype = "float"; break;
        case 'd': stype = "double"; break;
        case 'l': stype = "long"; break;
    }

    std::cerr << "Tried to read " + ctype + " data but instead found data of type " + stype << std::endl;
    return false;
}

void CompoundString::put(const std::string &identifier, const std::string &value) {
    putInternal(identifier, "\"" + value + "\"");
}

void CompoundString::put(const std::string &identifier, const char value) {
    putInternal(identifier, std::to_string(value));
}

void CompoundString::put(const std::string &identifier, const bool value) {
    putInternal(identifier, std::to_string(value) + 'b');
}

void CompoundString::put(const std::string &identifier, const int value) {
    putInternal(identifier, std::to_string(value));
}

void CompoundString::put(const std::string &identifier, const float value) {
    putInternal(identifier, std::to_string(value) + 'f');
}

void CompoundString::put(const std::string &identifier, const double value) {
    putInternal(identifier, std::to_string(value) + 'd');
}

void CompoundString::put(const std::string &identifier, const long value) {
    putInternal(identifier, std::to_string(value) + 'l');
}

std::string CompoundString::getString(const std::string &identifier) const {
    if(m_members.find(identifier) == m_members.end()) {
        return "";
    }

    std::string str = m_members.at(identifier);
    str.pop_back();
    str.erase(str.begin());
    return str;
}

char CompoundString::getChar(const std::string &identifier) const {
    if(m_members.find(identifier) == m_members.end()) {
        return '\0';
    }

    const std::string str = m_members.at(identifier);
    if(str.size() > 1) {
        std::cerr << "Tried to read single character data from a CompoundString but instead found a string of characters" << std::endl;
    }

    return str[0];
}

bool CompoundString::getBool(const std::string &identifier) const {
    if(m_members.find(identifier) == m_members.end()) {
        std::cerr << "Could not find identifier \"" + identifier + "\" in CompoundString" << std::endl;
        return false;
    }

    if(const std::string& string = m_members.at(identifier); endsWith(string, 'b')) {
        return string.substr(0, string.size()-1) == "1";
    }

    return false;
}

int CompoundString::getInt(const std::string &identifier) const {
    if(m_members.find(identifier) == m_members.end()) {
        std::cerr << "Could not find identifier \"" + identifier + "\" in CompoundString" << std::endl;
        return 0;
    }

    return std::stoi(m_members.at(identifier));
}

float CompoundString::getFloat(const std::string &identifier) const {
    if(m_members.find(identifier) == m_members.end()) {
        std::cerr << "Could not find identifier \"" + identifier + "\" in CompoundString" << std::endl;
        return 0;
    }

    if(const std::string& string = m_members.at(identifier); endsWith(string, 'f')) {
        return std::stof(string.substr(0, string.size()-1));
    }

    return 0;
}

double CompoundString::getDouble(const std::string &identifier) const {
    if(m_members.find(identifier) == m_members.end()) {
        std::cerr << "Could not find identifier \"" + identifier + "\" in CompoundString" << std::endl;
        return 0;
    }

    if(const std::string& string = m_members.at(identifier); endsWith(string, 'd')) {
        return std::stod(string.substr(0, string.size()-1));
    }

    return 0;
}

long CompoundString::getLong(const std::string &identifier) const {
    if(m_members.find(identifier) == m_members.end()) {
        std::cerr << "Could not find identifier \"" + identifier + "\" in CompoundString" << std::endl;
        return 0;
    }

    if(const std::string& string = m_members.at(identifier); endsWith(string, 'l')) {
        return std::stol(string.substr(0, string.size()-1));
    }

    return 0;
}
