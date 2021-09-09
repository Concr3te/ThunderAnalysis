#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>
#include <ios>

class CommitAnalyzer
{

public:
    CommitAnalyzer(std::string file) : commits_file(file)
    {
    }

    void Run()
    {
        std::string line;

        std::fstream inputfile(commits_file);
        std::vector<std::string> to_write;

        while (getline(inputfile, line))
        {
            to_write.push_back(line);
        }
        std::reverse(to_write.begin(), to_write.end());

        std::ofstream outputfile(std::string("reversedcommits.txt"),
                                 std::ios_base::out | std::ios_base::app);

        for (std::vector<std::string>::iterator it = to_write.begin(); it < to_write.end(); ++it)
        {
            outputfile << *it << std::endl;
        }

        inputfile.close();

        outputfile.close();

        inputfile.open("reversedcommits.txt");

        while (getline(inputfile, line))
        {
            if (line.find("date:") != std::string::npos)
            {
                //we found a date line which should represent a commit

                std::vector<std::string> tokens;

                std::istringstream iss(line);
                copy(std::istream_iterator<std::string>(iss),
                     std::istream_iterator<std::string>(),
                     std::back_inserter(tokens));

                if (tokens[0] != "date:")
                {
                    continue;
                }

                size_t first_space = line.find(" ");
                char current;
                current = line.at(first_space);

                while (current == ' ')
                {
                    first_space++;
                    current = line.at(first_space);
                }

                current = line.at(first_space);

                while (current != ' ')
                {
                    first_space++;
                    current = line.at(first_space);
                }

                // extract the month
                current = line.at(first_space);

                //remove the space first and foremost
                while (current == ' ')
                {
                    first_space++;
                    current = line.at(first_space);
                }

                size_t end = first_space;
                current = line.at(first_space);

                while (current != ' ')
                {
                    end++;
                    current = line.at(end);
                }

                //get the month
                std::string month = line.substr(first_space, end - first_space);
                int month_as_int;
                //represent the month as an integer
                if (month == "Jan")
                {
                    month_as_int = 1;
                }
                else if (month == "Feb")
                {
                    month_as_int = 2;
                }
                else if (month == "Mar")
                {
                    month_as_int = 3;
                }
                else if (month == "Apr")
                {
                    month_as_int = 4;
                }
                else if (month == "May")
                {
                    month_as_int = 5;
                }
                else if (month == "Jun")
                {
                    month_as_int = 6;
                }
                else if (month == "Jul")
                {
                    month_as_int = 7;
                }
                else if (month == "Aug")
                {
                    month_as_int = 8;
                }
                else if (month == "Sep")
                {
                    month_as_int = 9;
                }
                else if (month == "Oct")
                {
                    month_as_int = 10;
                }
                else if (month == "Nov")
                {
                    month_as_int = 11;
                }
                else if (month == "Dec")
                {
                    month_as_int = 12;
                }
                //strip another space and extra date in that month
                first_space += end - first_space;

                while (current == ' ')
                {
                    first_space++;
                    current = line.at(first_space);
                }

                end = first_space;
                current = line.at(first_space);

                while (current != ' ')
                {
                    end++;
                    current = line.at(end);
                }

                //get the date
                std::string date = line.substr(first_space, end - first_space);
                int date_as_int = atoi(date.c_str());

                //skip yet another space
                first_space += end - first_space;

                while (current == ' ')
                {
                    first_space++;
                    current = line.at(first_space);
                }

                //discard the time
                end = first_space;
                current = line.at(first_space);

                while (current != ' ')
                {
                    end++;
                    current = line.at(end);
                }
                //skip yet another space
                first_space += end - first_space;

                while (current == ' ')
                {
                    first_space++;
                    current = line.at(first_space);
                }
                //extract the year
                end = first_space;
                current = line.at(first_space);

                while (current != ' ')
                {
                    end++;
                    current = line.at(end);
                }

                std::string year = line.substr(first_space, end - first_space);
                int year_as_int = atoi(year.c_str());

                std::string commit_date = std::to_string(year_as_int) + "-" +
                                          std::to_string(month_as_int) + '-' +
                                          std::to_string(date_as_int);

                //std::cout << commit_date << std::endl;

                if (commits_per_date.find(commit_date) == commits_per_date.end())
                {

                    commits_per_date[commit_date] == 1;
                }
                else
                {

                    commits_per_date[commit_date] += 1;
                }
            }
        }
    }

    void Save()
    {
        std::ofstream outputfile("analyzedcommits.txt");

        std::map<std::string, int>::iterator it;

        for (it = commits_per_date.begin(); it != commits_per_date.end(); it++)
        {
            outputfile << it->first << "," << it->second << std::endl;
        }

        outputfile.close();
    }

private:
    std::string commits_file;
    std::map<std::string, int> commits_per_date;
};

int main(int argc, char *argv[])
{
    CommitAnalyzer *Analyzer = new CommitAnalyzer(std::string(argv[1]));

    Analyzer->Run();

    Analyzer->Save();

    return 0;
}