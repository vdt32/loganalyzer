#include "LogAnalyzer.hpp"


void LogAnalyzer::analyze(const std::vector<AccessLogRecord> &records)
{
    TimeRecord currentTime = records[0].m_timestamp;
    IPRecord currentIP = records[0].m_clientIP;
    unsigned reqNumb = 0;

    bool isSuspicious = false;

    /*FILE *res_file = fopen("res.txt", "w");
	if(errno != 0)
    {
        printf("error: failed to open res\n");
	    exit(EXIT_FAILURE);
    }*/

    for(unsigned i = 0; i < records.size(); i++)
    {
        reqNumb++;

        if(records[i].m_timestamp != currentTime || records[i].m_clientIP != currentIP)
        {
            currentTime = records[i].m_timestamp;
            currentIP = records[i].m_clientIP;
            reqNumb = 0;
        }
        

        //records[i].print();
        //std::cout << " " << reqNumb << std::endl;

        if(reqNumb == reqMax)
        {
            std::cout << "Suspicious activity detected: probably vulnerability scanner" << std::endl;
            std::cout << "    IP address: "; 
            currentIP.print();
            std::cout << "\n    Timestamp: ";
            currentTime.print();
            std::cout << std::endl << std::endl;

            isSuspicious = true;
        }        
    }

    if(!isSuspicious)
        std::cout << "No suspicious activity was found" << std::endl;

    //fclose(res_file);
}
