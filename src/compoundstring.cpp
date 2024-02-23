#include "compoundstring.h"

#include <iostream>

void CompoundString::putInternal(const std::string& identifier, const std::string& value) {
    if(m_members.find(identifier) == m_members.end()) {
        m_members.try_emplace(identifier, value);
    } else {
        m_members.at(identifier) = value;
    }
}

void CompoundString::put(const std::string &identifier, const std::string &value) {
    putInternal(identifier, "\"" + value + "\"");
}

void CompoundString::put(const std::string &identifier, const char value) {
    putInternal(identifier, std::to_string(value));
}

void CompoundString::put(const std::string &identifier, const bool value) {
    putInternal(identifier, std::to_string(value));
}

void CompoundString::put(const std::string &identifier, const int value) {
    putInternal(identifier, std::to_string(value));
}

void CompoundString::put(const std::string &identifier, const float value) {
    putInternal(identifier, std::to_string(value));
}

void CompoundString::put(const std::string &identifier, const double value) {
    putInternal(identifier, std::to_string(value));
}

void CompoundString::put(const std::string &identifier, const long value) {
    putInternal(identifier, std::to_string(value));
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

    return m_members.at(identifier) == "1";
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

    return std::stof(m_members.at(identifier));
}

double CompoundString::getDouble(const std::string &identifier) const {
    if(m_members.find(identifier) == m_members.end()) {
        std::cerr << "Could not find identifier \"" + identifier + "\" in CompoundString" << std::endl;
        return 0;
    }

    return std::stod(m_members.at(identifier));
}

long CompoundString::getLong(const std::string &identifier) const {
    if(m_members.find(identifier) == m_members.end()) {
        std::cerr << "Could not find identifier \"" + identifier + "\" in CompoundString" << std::endl;
        return 0;
    }

    return std::stol(m_members.at(identifier));
}
