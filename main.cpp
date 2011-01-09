
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <getopt.h>



/*
	what needs to be done:
		create testmod
			write test widget there
			write modinfo.lua there
		run

	create a dynamic mutator

params:
	maxtime		maximum time it is run (in frames)
	game		game to use (for example "Zero-K 0.5.1)
	exec		executable of spring (usally /usr/bin/spring)
	script		script
	test		test (subfolder) to run

*/

enum{
	OPT_GAME=0,
	OPT_SPRING,
	OPT_ARGS,
	OPT_SPEED,
	OPT_MAXFRAMES,
	OPT_SIZE
};

static struct option long_options[] = {
	{ "game"      , 1, 0, OPT_GAME },
	{ "spring"    , 1, 0, OPT_SPRING },
	{ "args"      , 1, 0, OPT_ARGS },
	{ "speed"     , 1, 0, OPT_SPEED },
	{ "maxframes" , 1, 0, OPT_MAXFRAMES },
	{0            , 0, 0, 0},
};

int main(int argc, char **argv){

	std::string game = "Zero-K v0.5.1";
	std::string exec = "spring-headless";
	std::string args = "";
	std::string script = "script.txt";
	int speed = 200;
	int frames = 9000;

	while(true){
		int option_index = 0;
		int c = getopt_long(argc, argv, "",long_options, &option_index);
		if (c == -1)
			break;
		switch(c){
			case OPT_GAME:{
				game = optarg;
				break;
			}
			case OPT_SPRING:{
				exec = optarg;
				break;
			}
			case OPT_ARGS:{
				args = optarg;
				break;
			}
			case OPT_SPEED:{
				sscanf(optarg,"%d",&speed);
				break;
			}
			case OPT_MAXFRAMES:{
				sscanf(optarg,"%d",&frames);
				break;
			}
		}
	}

	std::cout << "Creating testmod... \n";
	std::ofstream testmod;
	testmod.open("testmod.sdd/modinfo.lua");

	testmod << "return {\n";
	testmod << "	name='" << game << "',\n";
	testmod << "	description='Moooooo!',\n";
	testmod << "	shortname='BA',\n";
	testmod << "	version='testmod',\n";
	testmod << "	mutator='Official',\n";
	testmod << "	game='Total Annihilation',\n";
	testmod << "	shortGame='TA',\n";
	testmod << "	modtype=1,\n";
	testmod << "	depend= {\n";
	testmod << "		'"<< game <<"'\n";
	testmod << "	},\n";
	testmod << "}\n";

	testmod.close();
//	ostringstream s;
//	s << frames;
	testmod.open("testmod.sdd/luarules/gadgets/test.lua");
	testmod << "-- warning, don't edit this file, it will be overwritten!\n";
	testmod << "function gadget:GetInfo()\n";
	testmod << "return {\n";
	testmod << "	name    = \"Test-Gadget\",\n";
	testmod << "	desc    = \"Runs tests specified in config-file\",\n";
	testmod << "	author  = \"abma\",\n";
	testmod << "	date    = \"Sep. 2010\",\n";
	testmod << "	license = \"GNU GPL, v2 or later\",\n";
	testmod << "	layer   = 0,\n";
	testmod << "	enabled = true,\n";
	testmod << "}\n";
	testmod << "end\n";

	testmod << "if (gadgetHandler:IsSyncedCode()) then\n";
	testmod << "function gadget:GameFrame(n)\n";
	testmod << "	if n==0 then\n";
	testmod << "		Spring.Echo(\"Going to test...\")\n";
	testmod << "		Spring.SendCommands(\"cheat\")\n";
	testmod << "		Spring.SendCommands(\"setmaxspeed "<< speed <<"\")\n";
	testmod << "		Spring.SendCommands(\"setminspeed "<< speed <<"\")\n";
	testmod << "		Spring.SendCommands(\"setminspeed 0.1\")\n"; //allow lower speeds if cpu is to slow
	testmod << "	end\n";
	testmod << "	if n==10 then\n";
	testmod << "		Spring.SendCommands(\"give all 0\")\n";
	testmod << "		Spring.SendCommands(\"give all 1\")\n";
	testmod << "	end\n";
	testmod << "	if n==" << frames << " then\n";
	testmod << "		Spring.Echo(\"Tests finished after "<< frames << "!\")\n";
	testmod << "		Spring.SendCommands(\"quit\")\n";
	testmod << "	end\n";
	testmod << "end\n";
	testmod << "end\n";
	testmod.close();

	std::cout << "Creating Script.txt...\n";
	
	char buf[1024]; 
	getcwd(buf, sizeof(buf));
	args = buf;
	args += "/script.txt";

	std::cout << "Starting spring\n";
	
	std::string command;
	command = exec + " ";
	command += args;
	
	std::cout << "Running \""<< command << "\"\n";
	system(command.c_str());

}

