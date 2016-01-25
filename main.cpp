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
	auto verbose = input_args.find("VERBOSE");

	string input_s, output_s;

	//Exit and print usage info if no input file
	if (input == input_args.end())
	{
		std::cout << usage(argv);
		return 1;
	}

	//Exit and print usage info if user requested help
	if (help == input_args.end())
	{
		std::cout << usage(argv);
		return 0;
	}

	input_s = input->second;
	output_s = (output == input_args.end() ? input_s : output->second);

	//Open the file for corruption
	try
	{
		
	}
	catch (std::runtime_error &e)
	{

	}
}
