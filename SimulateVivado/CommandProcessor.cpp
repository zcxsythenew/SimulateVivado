#include "CommandProcessor.h"
#include "Vivado.h"

CommandProcessor *CommandProcessor::instence = NULL;

CommandProcessor::CommandProcessor() : vivado(NULL)
{
	PrintWelcome();
}

CommandProcessor *CommandProcessor::GetInstence()
{
	if (instence == NULL)
	{
		instence = new CommandProcessor();
	}
	return instence;
}

void CommandProcessor::DestoryInstence()
{
	if (instence != NULL)
	{
		delete instence;
	}
	instence = NULL;
}

void CommandProcessor::SetVivado(Vivado *vivado)
{
	this->vivado = vivado;
}

void CommandProcessor::PrintWelcome()
{
	cout << "SVivado, a project for finishing homework by TA" << endl;
	cout << "Copyright 2018, by Zcxsythenew" << endl;
	PrintHints();
}

void CommandProcessor::PrintHints(const string &command)
{
	if (command == "gate")
	{
		cout << "Retype command \"gate\" with" << endl
			<< "\"-add\" to add gates from the library" << endl
			<< "\"-v\" to view gates added to the pane" << endl
			<< "\"-rm\" to delete a gate from the pane" << endl;
	}
	else if (command == "view")
	{
		cout << "Type command \"view\" to view the current list of ports and detailed info." << endl
			<< "Add \"-e\" to execute the circuit and view the value of every port." << endl;
	}
	else if (command == "help")
	{
		cout << "All of available commands are listed below." << endl
			<< "quit       - To exit the application" << endl
			<< "gate       - To add, view or remove gates by adding -add, -v or -rm command" << endl
			<< "connect    - To connect two ports together" << endl
			<< "disconnect - To disconnect one port off the net it has been attached to" << endl
			<< "watch      - To execute the circuit and observe a port's value" << endl
			<< "             if no exception occurs, " << endl
			<< "             otherwise to see what kind of exception appears" << endl
			<< "view       - To see all ports' connection status. " << endl
			<< "             When the ports are connected, they share the same \"Net\" value." << endl
			<< "             add -e to execute the circuit and watch each port's value." << endl
			<< "             If an exception occurs, the value will be replaced by '*' and" << endl
			<< "             you may use \"watch\" command to see the type of exception" << endl;
	}
}

void CommandProcessor::PrintHints()
{
	cout << "Type \"help\" for more information." << endl;
}

bool CommandProcessor::ParseCommand(const string &command)
{
	stringstream ss;
	string cmd;
	ss << command;
	ss >> cmd;
	if (cmd == "quit")
	{
		return true;
	}
	else if (cmd == "gate")
	{
		if (ss >> cmd)
		{
			if (cmd == "-add")
			{
				vivado->AddGate();
			}
			else if (cmd == "-v")
			{
				vivado->ViewGates();
			}
			else if (cmd == "-rm")
			{
				vivado->DeleteGate();
			}
			else
			{
				PrintHints("gate");
			}
		}
		else
		{
			PrintHints(cmd);
		}
		return true;
	}
	else if (cmd == "connect")
	{
		vivado->ConnectPort();
		return true;
	}
	else if (cmd == "disconnect")
	{
		vivado->DisConnectPort();
		return true;
	}
	else if (cmd == "watch")
	{
		vivado->Watch();
		return true;
	}
	else if (cmd == "view")
	{
		if (ss >> cmd)
		{
			if (cmd == "-e")
			{
				vivado->View(true);
			}
			else
			{
				PrintHints("view");
			}
			return true;
		}
		else
		{
			vivado->View();
			return true;
		}
	}
	else if (cmd == "help")
	{
		PrintHints(cmd);
		return true;
	}
	else
	{
		return false;
	}
}

void CommandProcessor::PrintFail(const string &command)
{
	cout << "Invalid command \"" << command << "\"." << endl;
	PrintHints();
}

bool CommandProcessor::InputCommand()
{
	string command;
	cout << "(SVivado) ";
	if (getline(cin, command))
	{
		if (!ParseCommand(command))
		{
			PrintFail(command);
		}
		return !(command == "quit");
	}
	else
	{
		cout << endl;
		return false;
	}
}

CommandProcessor::~CommandProcessor()
{

}
