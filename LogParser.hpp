#pragma once
#include "AccessLogRecord.hpp"
#include "vector"
#include <fstream>
#include <streambuf>
#include <iostream>
#include <sys/stat.h>



class LogParser
{
public:
    LogParser() = default;
    ~LogParser() = default;

    LogParser(const LogParser &) = delete;
    LogParser(LogParser &&) = default;
    LogParser &operator=(const LogParser &) = delete;
    LogParser &operator=(LogParser &&) = delete;

    void parse(const std::string &path, std::vector<AccessLogRecord> *records);


private:
    void parse(char **strs, int size, std::vector<AccessLogRecord> *records);
    void parse(const char *str, AccessLogRecord &logRecord);
    void parseIP(const char *str, AccessLogRecord &logRecord);
    void parseDate(const char *str, AccessLogRecord &logRecord);

    void exitErr(const char *s);
    int calcNumbOfStr(char *bigString);
    char *readText(FILE *file);
    char **formatText(char *bigString, int nStr);
    char **getText(FILE *file, int *nStrings);
    void memfree(char **text, char *bigString);

    int getMonthNumb(const char *str);

    FILE *m_res;

    int m_index;
};
