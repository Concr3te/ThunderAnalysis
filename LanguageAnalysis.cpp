#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <filesystem>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <magic.h>

enum class LanguageType
{
    Cpp,
    Python,
    Javascript,
    Idl,
    Rust,
    Go,
    Bash,
    Perl,
    HTML,
    Other,
    All
};

/* 
   TODO 
   i) clean this up to remove redundancy
   ii) Possibly make use of threads to make the analysis run even more faster
*/
class Analyzer
{
public:
    Analyzer(std::string directory) : directory(directory)
    {
        results[LanguageType::Cpp] = 0;
        results[LanguageType::Python] = 0;
        results[LanguageType::Javascript] = 0;
        results[LanguageType::Idl] = 0;
        results[LanguageType::Rust] = 0;
        results[LanguageType::Go] = 0;
        results[LanguageType::Bash] = 0;
        results[LanguageType::Perl] = 0;
        results[LanguageType::Other] = 0;
        results[LanguageType::All] = 0;
    }

    void Languages()
    {
        std::string line;

        size_t line_count = 0;

        magic_t cookie = magic_open(MAGIC_MIME);

        magic_load(cookie, NULL);

        for (auto &p : std::filesystem::recursive_directory_iterator(directory))
        {
            std::string file_type(magic_file(cookie, p.path().string().c_str()));

            if (file_type.find("text") != std::string::npos && p.path().string().find(".hg") == std::string::npos)
            {

                if (p.path().string().find(".cpp") != std::string::npos)
                {
                    std::ifstream current_file(p.path().string());

                    current_file.unsetf(std::ios_base::skipws);

                    line_count = std::count(std::istream_iterator<char>(current_file),
                                            std::istream_iterator<char>(),
                                            '\n');

                    results[LanguageType::Cpp] += line_count;
                    results[LanguageType::All] += line_count;
                }
                if (p.path().string().find(".idl") != std::string::npos)
                {
                    std::ifstream current_file(p.path().string());

                    current_file.unsetf(std::ios_base::skipws);

                    line_count = std::count(std::istream_iterator<char>(current_file),
                                            std::istream_iterator<char>(),
                                            '\n');

                    results[LanguageType::Idl] += line_count;
                    results[LanguageType::All] += line_count;
                }
                else if (p.path().string().find(".js") != std::string::npos)
                {
                    std::ifstream current_file(p.path().string());

                    current_file.unsetf(std::ios_base::skipws);

                    line_count = std::count(std::istream_iterator<char>(current_file),
                                            std::istream_iterator<char>(),
                                            '\n');

                    results[LanguageType::Javascript] += line_count;
                    results[LanguageType::All] += line_count;
                }
                //javascript modules but they actually get analyzed in the above
                else if (p.path().string().find(".jsm") != std::string::npos)
                {
                    std::ifstream current_file(p.path().string());

                    current_file.unsetf(std::ios_base::skipws);

                    line_count = std::count(std::istream_iterator<char>(current_file),
                                            std::istream_iterator<char>(),
                                            '\n');

                    results[LanguageType::Javascript] += line_count;
                    results[LanguageType::All] += line_count;
                }
                else if (p.path().string().find(".py") != std::string::npos)
                {
                    std::ifstream current_file(p.path().string());

                    current_file.unsetf(std::ios_base::skipws);

                    line_count = std::count(std::istream_iterator<char>(current_file),
                                            std::istream_iterator<char>(),
                                            '\n');

                    results[LanguageType::Python] += line_count;
                    results[LanguageType::All] += line_count;
                }
                else if (p.path().string().find(".rs") != std::string::npos)
                {
                    std::ifstream current_file(p.path().string());

                    current_file.unsetf(std::ios_base::skipws);

                    line_count = std::count(std::istream_iterator<char>(current_file),
                                            std::istream_iterator<char>(),
                                            '\n');

                    results[LanguageType::Rust] += line_count;
                    results[LanguageType::All] += line_count;
                }
                else if (p.path().string().find(".h") != std::string::npos)
                {
                    std::ifstream current_file(p.path().string());

                    current_file.unsetf(std::ios_base::skipws);

                    line_count = std::count(std::istream_iterator<char>(current_file),
                                            std::istream_iterator<char>(),
                                            '\n');

                    results[LanguageType::Cpp] += line_count;
                    results[LanguageType::All] += line_count;
                }
                else if (p.path().string().find(".pl") != std::string::npos)
                {
                    std::ifstream current_file(p.path().string());

                    current_file.unsetf(std::ios_base::skipws);

                    line_count = std::count(std::istream_iterator<char>(current_file),
                                            std::istream_iterator<char>(),
                                            '\n');
                    results[LanguageType::Perl] += line_count;
                    results[LanguageType::All] += line_count;
                }
                else if (p.path().string().find(".sh") != std::string::npos)
                {
                    std::ifstream current_file(p.path().string());

                    current_file.unsetf(std::ios_base::skipws);

                    line_count = std::count(std::istream_iterator<char>(current_file),
                                            std::istream_iterator<char>(),
                                            '\n');

                    results[LanguageType::Bash] += line_count;
                    results[LanguageType::All] += line_count;
                }
                else if (p.path().string().find(".go") != std::string::npos)
                {
                    std::ifstream current_file(p.path().string());

                    current_file.unsetf(std::ios_base::skipws);

                    line_count = std::count(std::istream_iterator<char>(current_file),
                                            std::istream_iterator<char>(),
                                            '\n');

                    results[LanguageType::Go] += line_count;
                    results[LanguageType::All] += line_count;
                }

                else if (p.path().string().find(".html") != std::string::npos)
                {
                    std::ifstream current_file(p.path().string());

                    current_file.unsetf(std::ios_base::skipws);

                    line_count = std::count(std::istream_iterator<char>(current_file),
                                            std::istream_iterator<char>(),
                                            '\n');

                    results[LanguageType::HTML] += line_count;
                    results[LanguageType::All] += line_count;
                }
                else if (p.path().string().find(".xhtml") != std::string::npos)
                {
                    std::ifstream current_file(p.path().string());

                    current_file.unsetf(std::ios_base::skipws);

                    line_count = std::count(std::istream_iterator<char>(current_file),
                                            std::istream_iterator<char>(),
                                            '\n');

                    results[LanguageType::HTML] += line_count;
                    results[LanguageType::All] += line_count;
                }
                else
                {
                    std::ifstream current_file(p.path().string());

                    current_file.unsetf(std::ios_base::skipws);

                    line_count = std::count(std::istream_iterator<char>(current_file),
                                            std::istream_iterator<char>(),
                                            '\n');

                    results[LanguageType::Other] += line_count;
                    results[LanguageType::All] += line_count;
                }

            }
        }
        magic_close(cookie);
    }

    void PrintLanguageResults()
    {
        for (auto const &[key, val] : results)
        {
            switch (key)
            {
            case LanguageType::Cpp:
                std::cout << " Total C++ lines of code " << results[LanguageType::Cpp] << std::endl;
                break;
            case LanguageType::Python:
                std::cout << " Total Python lines of code " << results[LanguageType::Python] << std::endl;
                /* code */
                break;
            case LanguageType::Javascript:
                std::cout << " Total Javascript lines of code " << results[LanguageType::Javascript] << std::endl;
                /* code */
                break;
            case LanguageType::Idl:
                std::cout << " Total Idl lines of code " << results[LanguageType::Idl] << std::endl;
                /* code */
                break;
            case LanguageType::Rust:
                std::cout << " Total Rust lines of code " << results[LanguageType::Rust] << std::endl;
                /* code */
                break;
            case LanguageType::Go:
                std::cout << " Total Go lines of code " << results[LanguageType::Go] << std::endl;
                /* code */
                break;
            case LanguageType::Bash:
                std::cout << " Total Bash lines of code " << results[LanguageType::Bash] << std::endl;
                /* code */
                break;
            case LanguageType::Perl:
                std::cout << " Total Perl lines of code " << results[LanguageType::Perl] << std::endl;
                /* code */
                break;
            case LanguageType::Other:
                std::cout << " Other lines of code " << results[LanguageType::Other] << std::endl;
                /* code */
                break;
            case LanguageType::All:
                std::cout << " Total lines of code " << results[LanguageType::All] << std::endl;
                /* code */
                break;

            default:
                break;
            }
        }
    }
    void Save()
    {
        std::ofstream csv_file(std::string("results.csv"));

        for (auto const &[key, val] : results)
        {
            switch (key)
            {
            case LanguageType::Cpp:
                 csv_file << "C++, " << results[LanguageType::Cpp] << std::endl;
                break;
            case LanguageType::Python:
                 csv_file << "Python, " << results[LanguageType::Python] << std::endl;
                /* code */
                break;
            case LanguageType::Javascript:
                csv_file << "Javascript, " << results[LanguageType::Javascript] << std::endl;
                /* code */
                break;
            case LanguageType::Idl:
                csv_file << "Idl, " << results[LanguageType::Idl] << std::endl;
                /* code */
                break;
            case LanguageType::Rust:
                csv_file << "Rust, " << results[LanguageType::Rust] << std::endl;
                /* code */
                break;
            case LanguageType::Go:
                csv_file << "Go, " << results[LanguageType::Go] << std::endl;
                /* code */
                break;
            case LanguageType::Bash:
                csv_file << "Bash, " << results[LanguageType::Bash] << std::endl;
                /* code */
                break;
            case LanguageType::Perl:
                csv_file << "Perl, " << results[LanguageType::Perl] << std::endl;
                /* code */
                break;
            case LanguageType::Other:
                csv_file << "Other, " << results[LanguageType::Other] << std::endl;
                /* code */
                break;
            case LanguageType::All:
                csv_file << "Total, " << results[LanguageType::All] << std::endl;
                /* code */
                break;

            default:
                break;
            }
        }
    }

private:
    std::string directory;
    std::map<LanguageType, int> results;
};

int main(int argc, char *argv[])
{

    if (argc <= 1)
    {
        std::cout << "Usage : " << argv[0] << " directory" << std::endl;

        return -1;
    }

    Analyzer *analysis = new Analyzer(std::string(argv[1]));

    analysis->Languages();

    analysis->PrintLanguageResults();

    analysis->Save();
}