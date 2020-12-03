#pragma once
#include <vector>
#include <iostream>
#include "AccessLogRecord.hpp"


const unsigned reqMax = 30;


class LogAnalyzer
{
public:
    LogAnalyzer() = default;
    ~LogAnalyzer() = default;

    LogAnalyzer(const LogAnalyzer &) = delete;
    LogAnalyzer(LogAnalyzer &&) = delete;
    LogAnalyzer &operator=(const LogAnalyzer &) = delete;
    LogAnalyzer &operator=(LogAnalyzer &&) = delete;

    void analyze(const std::vector<AccessLogRecord> &records);
};