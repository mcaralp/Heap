
#include "path.h"

#include <sstream>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <list>
#include <functional>
#include <sstream>

#define NS heap::Path

#ifdef _WIN32

#include <windows.h>


std::string NS::getAbsolutePath(const std::string & path)
{
	char *fileExt;
	char szDir[1024]; //dummy buffer
	GetFullPathName(path.c_str(), 1024, szDir, &fileExt); 

	std::string res (szDir);
	if(res[res.size() - 1] == '\\') res.pop_back();

	for(char & c : res)
		if(c == '\\') c = '/';

	return res;
}


const char NS::delimiter = '\\';

#else

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>


std::string NS::getAbsolutePath(const std::string & path)
{
    char tmp[1024];
    if(realpath(path.c_str(), tmp) == nullptr) return "";

	std::string res (tmp);
	if(res[res.size() - 1] == '/') res.pop_back();
		return res;
}


const char NS::delimiter = '/';


#endif

void NS::init(const std::string & argv0)
{
    execDir = getAbsolutePath(dirName(argv0));
}


std::string NS::baseName(const std::string & path, bool ext)
{
	std::size_t begin = path.find_last_of('/');
	if(begin == std::string::npos)
		begin = 0;
	else
		begin++;

	std::size_t end = path.find_last_of('.');
	// if true then the file is of the form .something or /some.thing/file
	if(ext || end == 0 || begin > end) end = path.size();

	return path.substr(begin, end - begin);


}


std::string NS::dirName(const std::string & path)
{
	std::size_t end = path.find_last_of('/');
	if(end == std::string::npos)
		end = 0;

	return path.substr(0, end);
}


std::string NS::joinRec()
{
    return ".";
}

std::string NS::normalize(const std::string & path)
{
     static auto split = [] (const std::string & str, const std::string & delim, std::list<std::string> & parts) -> void
     {
        std::size_t start = 0, end = 0;
        while (end < str.size()) 
        {
            while (end < str.size() && (delim.find(str[end]) == std::string::npos))
                end++;
                    
            parts.push_back(std::string(str, start, end - start));

            ++end;
            start = end;
        
        }
    };

    std::list<std::string> parts;
    split(path, "/\\", parts);

    // remove ".", ".." and empty parts, except if at the first position.
    for(auto it = parts.begin(); it != parts.end(); )
    {
        if(*it == ".")
            it = parts.erase(it);

        else if(*it == "" && it != parts.begin())
            it = parts.erase(it);

        else if(*it == ".." && it != parts.begin())
        {
            --it;
            if(*it == "..")
            {
                ++it;
                ++it;            
            }
            else if(*it != "")
            {
                it = parts.erase(it);
                it = parts.erase(it);
            }
            else
            {
                ++it;
                it = parts.erase(it);
            }
            
        }
        else
            ++it;
    }

    if(parts.size() == 0) return ".";
    if(parts.size() == 1 && parts.front() == "") return "/";

    std::ostringstream res;

    for(auto it = parts.begin(); it != parts.end(); )
    {
        res << *it;

        if(++it != parts.end()) 
            res << delimiter;
    }


    return res.str();

}

std::string NS::getExecDir()
{
    return execDir;
}

std::string NS::execDir;


#undef NS