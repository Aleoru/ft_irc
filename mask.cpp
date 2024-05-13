#include <iostream>
#include <vector>

bool maskMacht(std::string mask, std::string name)
{
	size_t pos = 0;
	pos = mask.find("*");
	std::string	sub;  
	if (pos <= mask.size() && (mask.size()-1) <= name.size())
	{
		if (pos == 0)
		{
			mask.erase(mask.begin());
			sub = name.substr((name.size() - mask.size()), (mask.size()));
			if (!sub.compare(mask))
				return (true);
		}
		else if (pos == mask.size()-1)
		{
			mask.erase(mask.end()-1);
			sub = name.substr(0, mask.size());
			if (!sub.compare(mask))
				return (true);
		}
		else
		{
			std::string maskIni = mask.substr(0, pos);
			std::string maskEnd = mask.substr(pos + 1, mask.size() -1);
			sub = name.substr(0, maskIni.size());
			if (!sub.compare(maskIni))
			{
				sub = name.substr((name.size() - maskEnd.size()), (maskEnd.size()));
				if (!sub.compare(maskEnd))
					return (true);
			}
		}
	}
	else
	{
		if (!name.compare(mask))
			return (true);
	}
	return (false);  
}

int main(int argc, char **argv)
{
	if (argc >= 2)
	{ 
		std::vector<std::string> names;
		names.reserve(5);
		names.push_back("Juan");        
		names.push_back("Juanito");        
		names.push_back("Pepe");        
		names.push_back("Pepito");        
		names.push_back("Paco");
		for (size_t i = 2; i < argc; i++)
			names.push_back(argv[i]);

		for (size_t i = 0; i < names.size(); i++)
		{
			if (maskMacht(argv[1], names[i]))
				std::cout<<names[i]<<std::endl;
		}
	}
	return (0);
}