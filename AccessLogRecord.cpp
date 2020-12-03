#include "AccessLogRecord.hpp"


IPRecord::IPRecord():
    m_ip{}
{}


IPRecord::IPRecord(const IPRecord &ip)
{
    for(int i = 0; i < 4; i++)
        m_ip[i] = ip.m_ip[i];
}


IPRecord &IPRecord::operator=(const IPRecord &ip)
{
    for(int i = 0; i < 4; i++)
        m_ip[i] = ip.m_ip[i];

    return *this;
}


bool IPRecord::operator==(const IPRecord &ip) const
{
    bool res = (m_ip[0] == ip.m_ip[0] && m_ip[1] == ip.m_ip[1] 
        && m_ip[2] == ip.m_ip[2] && m_ip[3] == ip.m_ip[3]);

    return res;
}


bool IPRecord::operator!=(const IPRecord &ip) const
{
    bool res = this->operator==(ip);
    return !res;
}


void IPRecord::print() const
{
    print(stdout);
}


void IPRecord::print(FILE *file) const
{
    fprintf(file, "%u.%u.%u.%u", m_ip[0], m_ip[1], m_ip[2], m_ip[3]);
    fflush(file);
}


TimeRecord::TimeRecord():
    m_day(0),
    m_mon(0),
    m_year(0),
    m_hour(0),
    m_min(0),
    m_sec(0)
{}


bool TimeRecord::operator==(const TimeRecord &time) const
{
    bool res = (m_day == time.m_day && m_mon == time.m_mon && m_year == time.m_year
        && m_hour == time.m_hour && m_min == time.m_min && m_sec == time.m_sec);

    return res;
}


bool TimeRecord::operator!=(const TimeRecord &time) const
{
    bool res = this->operator==(time);

    return !res;
}


void TimeRecord::print() const
{
    print(stdout);
}


void TimeRecord::print(FILE *file) const
{
    fprintf(file, "%d/%d/%d:%d:%d:%d", m_day, m_mon, m_year,
        m_hour, m_min, m_sec);
    fflush(file);
}


AccessLogRecord::AccessLogRecord():
    m_clientIP(),
    m_timestamp(),
    m_request(),
    m_status_code(0),
    m_size_of_request(0),
    m_referrer_header(),
    m_user_agent()
{}


AccessLogRecord::~AccessLogRecord()
{
    m_clientIP = {};
    m_timestamp = {};
    m_status_code = 0;
    m_size_of_request = 0;
}


void AccessLogRecord::print() const
{
    m_clientIP.print();
    printf(" ");
    m_timestamp.print();
    fflush(stdout);
}

void AccessLogRecord::print(FILE *file) const
{
    m_clientIP.print(file);
    fprintf(file, " ");
    m_timestamp.print(file);
    fflush(file);
}