#include "LogParser.hpp"


void LogParser::parse(const std::string &path, std::vector<AccessLogRecord> *records)
{
    FILE *file = fopen(path.c_str(), "r");
	if(errno != 0)
		exitErr("failed to open file");

    /*m_res = fopen("res.txt", "w");
	if(errno != 0)
		exitErr("failed to open res");
	*/
	int nStrings;
	char **text = getText(file, &nStrings);
	char *bigString = text[0]; 


    parse(text, nStrings-1, records);


    fclose(file);
	if(errno != 0)
		exitErr("file fclose() failed");

	/*fclose(m_res);
	if(errno != 0)
		exitErr("res fclose() failed");*/

    memfree(text, bigString);
}


void LogParser::parse(char **strs, int size, std::vector<AccessLogRecord> *records)
{
    for(int i = 0; i < size; i++)
    {
        unsigned long ulI = static_cast<unsigned long>(i);
        records->emplace_back();
        parse(strs[i], (*records)[ulI]);
    }
}


void LogParser::parse(const char *str, AccessLogRecord &logRecord)
{
    parseIP(str, logRecord);

    while(str[m_index] != '[')
        m_index++;

    m_index++;

    parseDate(str, logRecord);
}


void LogParser::parseIP(const char *str, AccessLogRecord &logRecord)
{
    char str1[4] = ""; 
    char str2[4] = "";
    char str3[4] = "";
    char str4[4] = "";

    int i = 0;
    while(str[i] != '.')
    {
        str1[i] = str[i];
        i++;
    }

    i++;
    int oldI = i;

    while(str[i] != '.')
    {
        str2[i-oldI] = str[i];
        i++;
    }

    i++;
    oldI = i;

    while(str[i] != '.')
    {
        str3[i-oldI] = str[i];
        i++;
    }

    i++;
    oldI = i;

    while(str[i] != ' ')
    {
        str4[i-oldI] = str[i];
        i++;
    }

    i++;

    int a1, a2, a3, a4;

    a1 = atoi(str1);
    a2 = atoi(str2);
    a3 = atoi(str3);
    a4 = atoi(str4);

    logRecord.m_clientIP.m_ip[0] = static_cast<unsigned char>(a1);
    logRecord.m_clientIP.m_ip[1] = static_cast<unsigned char>(a2);
    logRecord.m_clientIP.m_ip[2] = static_cast<unsigned char>(a3);
    logRecord.m_clientIP.m_ip[3] = static_cast<unsigned char>(a4);

    //logRecord.m_clientIP.print();
    //std::cout << " ";

    m_index = i;
}


void LogParser::parseDate(const char *str, AccessLogRecord &logRecord)
{
    int i = m_index;
    int oldI = m_index;

    char strDay[5] = "";
    char strMonth[5] = "";
    char strYear[5] = "";
    char strHour[5] = "";
    char strMinute[5] = "";
    char strSecond[5] = "";

    while(str[i] != '/')
    {
        strDay[i - oldI] = str[i];
        i++;
    }

    i++;
    oldI = i;

    while(str[i] != '/')
    {
        strMonth[i-oldI] = str[i];
        i++;
    }

    i++;
    oldI = i;

    while(str[i] != ':')
    {
        strYear[i-oldI] = str[i];
        i++;
    }

    i++;
    oldI = i;

    while(str[i] != ':')
    {
        strHour[i-oldI] = str[i];
        i++;
    }

    i++;
    oldI = i;

    while(str[i] != ':')
    {
        strMinute[i-oldI] = str[i];
        i++;
    }

    i++;
    oldI = i;

    while(str[i] != ' ')
    {
        strSecond[i-oldI] = str[i];
        i++;
    }

    logRecord.m_timestamp.m_day = atoi(strDay);
    logRecord.m_timestamp.m_mon = getMonthNumb(strMonth);
    logRecord.m_timestamp.m_year = atoi(strYear);
    logRecord.m_timestamp.m_hour = atoi(strHour);
    logRecord.m_timestamp.m_min = atoi(strMinute);
    logRecord.m_timestamp.m_sec = atoi(strSecond);

    //logRecord.m_timestamp.print();
    //std::cout << std::endl;
}


void LogParser::exitErr(const char *s)
{
	printf("error: %s\n", s);
	exit(EXIT_FAILURE);
}


int LogParser::calcNumbOfStr(char *bigString)
{
	int i = 0;
	int nStr = 1;	
	while(bigString[i] != 0)
	{
		if(bigString[i] == '\n')
			nStr++;
		i++;
	}
	
	return nStr;
}


char *LogParser::readText(FILE *file)
{
	struct stat tmp;
	fstat(fileno(file), &tmp);
	long int size = tmp.st_size;
    size_t uSize = static_cast<size_t>(size);

	char *bigString = (char *)calloc(uSize + 1, sizeof(char));
	if((errno != 0) || bigString == nullptr)
		exitErr("Memory cannot be allocated");
	
	if(fread(bigString, uSize, 1, file) != 1)
		exitErr("reading error");

	return bigString;
}


char **LogParser::formatText(char *bigString, int nStr)
{
	char **text = (char **)calloc(static_cast<size_t>(nStr), sizeof(char *));
	if(errno != 0)
		exitErr("Memory cannot be allocated");

	text[0] = bigString;
	int n = 1;
	int i = 0;
	while(bigString[i] != 0)
	{
		if(bigString[i] == '\n')
		{
			bigString[i] = 0;
			text[n] = &bigString[i + 1];
			n++;
		}		
		i++;
	}

	return text;
}


char **LogParser::getText(FILE *file, int *nStrings)
{
	char *bigString = readText(file);

	int nStr = calcNumbOfStr(bigString);
	if(nStrings)
		*nStrings = nStr;
		
	char **text = formatText(bigString, nStr);

	return text;
}


void LogParser::memfree(char **text, char *bigString)
{
	free(bigString);
	free(text);
}


int LogParser::getMonthNumb(const char *str)
{
    if(str[0] == 'J' && str[1] == 'a')
        return 1;

    if(str[0] == 'F')
        return 2;

    if(str[0] == 'M' && str[2] == 'r')
        return 3;

    if(str[0] == 'A' && str[1] == 'p')
        return 4;

    if(str[0] == 'M' && str[2] == 'y')
        return 5;

    if(str[0] == 'J' && str[1] == 'u' && str[2] == 'n')
        return 6;

    if(str[0] == 'J' && str[2] == 'l')
        return 7;

    if(str[0] == 'A' && str[1] == 'u')
        return 8;

    if(str[0] == 'S')
        return 9;

    if(str[0] == 'O')
        return 10;

    if(str[0] == 'N')
        return 11;

    if(str[0] == 'D')
        return 12;

    return 13;
}