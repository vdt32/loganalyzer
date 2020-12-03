#include "LogParser.hpp"
#include "LogAnalyzer.hpp"


//const std::string path = "/var/log/apache2/access.log";


int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./a.out file_path\n");
        return EXIT_FAILURE;
    }

    LogParser parser;
    std::vector<AccessLogRecord> records;
    parser.parse(argv[1], &records);

    LogAnalyzer analyzer;
    analyzer.analyze(records);

    return EXIT_SUCCESS;
}