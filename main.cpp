#include "corrupt.hpp"

int main(int argc, char** argv)
{
	//Set up the parameters
	std::map<string, string> input_args = parseArguments(argc, argv);

	auto input = input_args.find("INPUT");
	auto output = input_args.find("OUTPUT");
	auto strength = input_args.find("STRENGTH");
	auto begin = input_args.find("BEGIN");
	auto end = input_args.find("END");
	auto help = input_args.find("HELP");
	auto verbosity = input_args.find("VERBOSE");

	string input_s, output_s;

	//Exit and print usage info if no input file
	if (input == input_args.end())
	{
		std::cout << usage(argv);
		return 1;
	}

	//Exit and print usage info if user requested help
	if (help != input_args.end())
	{
		std::cout << usage(argv);
		return 0;
	}

	input_s = input->second;
	output_s = (output == input_args.end() ? input_s : output->second);
	bool verbose = (verbosity != input_args.end());
	float strength_f = (strength == input_args.end() ? 0.1 : atof(strength->second.c_str()));
	long begin_i = (begin == input_args.end() ? 0 : atoi(begin->second.c_str()));
	long end_i = (end == input_args.end() ? 0 : atoi(end->second.c_str()));

	//Corrupt the file
	if (corrupt(input_s, output_s, strength_f, begin_i, end_i, verbose))
	{
		std::cout << "File successfully corrupted!\n";
	}
	else
	{
		return 1;
	}
	return 0;
}
