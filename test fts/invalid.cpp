#include <iostream>

bool    invalidChars(std::string str, std::string chars)
{
	size_t pos;
	for (size_t i = 0; i < chars.size(); i++)
	{
		pos = str.find(chars[i]);
		if (pos < str.size())
			return (true);
	}
	
	return (false);
}

int main(int argc, char **argv)
{
    if (argc == 3)
    {
        if (invalidChars(argv[1], argv[2]))
            std::cout<<"invalid character"<<std::endl;
        else
            std::cout<<"no invalid character"<<std::endl;
    }

    return (0);
}