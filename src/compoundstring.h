#pragma once

#include <unordered_map>
#include <string>

class CompoundString {
    std::unordered_map<std::string, std::string> m_members;

    void putInternal(const std::string& identifier, const std::string& value);

    static bool endsWith(const std::string& string, const char& c);
public:
    CompoundString() = default;

    void put(const std::string &identifier, const std::string &value);

    void put(const std::string &identifier, char value);

    void put(const std::string &identifier, bool value);

    void put(const std::string &identifier, int value);

    void put(const std::string &identifier, float value);

    void put(const std::string &identifier, double value);

    void put(const std::string &identifier, long value);

    std::string getString(const std::string &identifier) const;

    char getChar(const std::string &identifier) const;

    bool getBool(const std::string &identifier) const;

    int getInt(const std::string &identifier) const;

    float getFloat(const std::string &identifier) const;

    double getDouble(const std::string &identifier) const;

    long getLong(const std::string &identifier) const;
};
