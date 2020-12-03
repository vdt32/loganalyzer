#pragma once
#include <string>


class IPRecord
{
public:
    IPRecord();
    ~IPRecord() = default;

    IPRecord(const IPRecord &);
    IPRecord &operator=(const IPRecord &);

    bool operator==(const IPRecord &) const;
    bool operator!=(const IPRecord &) const;

    void print() const;
    void print(FILE *file) const;

    unsigned char m_ip[4];
};


class TimeRecord
{
public:
    TimeRecord();
    ~TimeRecord() = default;

    TimeRecord(const TimeRecord &) = default;
    TimeRecord &operator=(const TimeRecord &) = default;
    bool operator==(const TimeRecord &) const;
    bool operator!=(const TimeRecord &) const;
    
    void print() const;
    void print(FILE *file) const;

    int m_day;
    int m_mon;
    int m_year;
    int m_hour;
    int m_min;
    int m_sec;
};


class AccessLogRecord
{
public:
    AccessLogRecord();
    ~AccessLogRecord();

    AccessLogRecord(const AccessLogRecord &) = delete;
    AccessLogRecord(AccessLogRecord &&) = default;
    AccessLogRecord &operator=(const AccessLogRecord &) = delete;
    AccessLogRecord &operator=(AccessLogRecord &&) = delete;

    void print() const;
    void print(FILE *file) const;

    IPRecord m_clientIP;
    TimeRecord m_timestamp;
    std::string m_request;
    unsigned m_status_code;
    unsigned m_size_of_request;
    std::string m_referrer_header;
    std::string m_user_agent;
};