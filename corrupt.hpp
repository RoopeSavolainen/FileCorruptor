//This is where most of the ugly code is

#include <iostream>
#include <fstream>

#include <vector>
#include <list>
#include <map>

#include <string>
#include <algorithm>
#include <exception>

#include <random>

typedef std::string string;

bool corrupt(string input_s, string output_s, float strength, unsigned long begin, unsigned long end, bool verbose)
{
	char *read_buffer = new char;
	std::ifstream input;
	std::ofstream output;
	try
	{
		input.open(input_s, std::fstream::in | std::fstream::binary | std::fstream::ate);
		output.open(output_s, std::fstream::out | std::fstream::binary | std::fstream::trunc);
		unsigned long file_len = input.tellg();
		input.seekg(0);

		std::vector<char> output_buffer;

		std::mt19937 generator;
		{
			std::random_device device;
			generator.seed(device());
		}
		std::normal_distribution<float> offset_distribution(0.0, 35.0);
		std::uniform_real_distribution<float> corruption_chance(0.0,1.0);

		while (true)
		{
			unsigned long pos = input.tellg();
			*read_buffer = (char)input.get();

			if (input.eof())
				break;

			if (pos >= begin && pos <= file_len - end)
			{
				if (corruption_chance(generator) <= strength)
				{
					*read_buffer += (char)offset_distribution(generator);
				}
			}

			output_buffer.push_back(*read_buffer);
		}

		input.close();
		output.seekp(0);
		output.write(&output_buffer[0], file_len);
		output.close();
	}
	catch (std::exception &e)
	{
		delete read_buffer;
		std::cerr << "Failed to open the file!\n";
		input.close();
		output.close();
		return false;
	}
	delete read_buffer;

	return true;
}

std::map<string, string> parseArguments(int argc, char** argv)
{
	std::map<string, string> params;
	string s1, s2;

	//Parameters that need an additional argument
	std::vector<string> additional_req = {"-f", "--input_file", "-o", "--output-file", "-s", "--strength", "-b", "--begin", "-e", "--end"/*, "-m", "--method"*/};

	//Valid parameters
	std::vector<string> more_params = {"-h", "--help", "-v", "--verbose"};
	std::vector<string> valid_params(more_params.size() + additional_req.size());
	std::merge(additional_req.begin(), additional_req.end(),
			more_params.begin(), more_params.end(), valid_params.begin());

	for (unsigned i = 1; i < argc; i++)
	{
		s1 = string(argv[i]);
		if (std::find(valid_params.begin(), valid_params.end(), s1) != valid_params.end())
		{
			if (std::find(additional_req.begin(), additional_req.end(), s1) != additional_req.end())
			{
				i++;
				s2 = string(argv[i]);
			}
			else
			{
				s2 = "";
			}
			if (s1 == "-f" || s1 == "--input_file")		s1 = "INPUT";
			if (s1 == "-o" || s1 == "--output_file")	s1 = "OUTPUT";
			if (s1 == "-s" || s1 == "--strength")		s1 = "STRENGTH";
			if (s1 == "-b" || s1 == "--begin")			s1 = "BEGIN";
			if (s1 == "-e" || s1 == "--end")			s1 = "END";
			if (s1 == "-h" || s1 == "--help")			s1 = "HELP";
			if (s1 == "-v" || s1 == "--verbose")		s1 = "VERBOSE";
			//if (s1 == "-m" || s1 == "--method")			s1 = "METHOD";
			params[s1] = s2;
		}
		else std::cerr << "Invalid argument: " << s1 << ", skipping.\n";
	}

	return params;
}

std::string usage(char** argv)
{
	string s;
	s = "Usage:\n\n" + string(argv[0]) + " -f SOURCE [-o DESTINATION] [-m METHOD] [-s STRENGTH] [-b FIRST-BYTE] [-e LAST-BYTE] [-v]\n\n";
	s += "Options:\n\t";
	s += "-f, --input_file: File to corrupt\n\t-o, --output-file: Location to write the corrupted file to. (By default SOURCE_corrupted)\n\t";
	//s += "-m, --method"
	s += "-s, --strength: Set the probability of a byte being corrupted. Should be a floating point number between 0.0 and 1.0. Default value is 0.1.\n\t";
	s += "-b, --begin: Skip the first N bytes of a file when doing corruption.\n\t-e, --end: Same as begin, but skip trailing bytes.\n\t";
	s += "-v, --verbose: Print additional information.\n";
	return s;
}
