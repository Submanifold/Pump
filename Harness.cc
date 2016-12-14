#include <iostream>
#include <regex>
#include <string>
#include <vector>

int main( int argc, char** argv )
{
  std::vector<std::string> arguments;
  arguments.reserve( argc );

  for( int i = 0; i < argc; i++ )
    arguments.push_back( argv[i] );

  unsigned inputs  = 0;
  unsigned outputs = 1;

  std::string command;

  std::regex reInputArgument( "-i([[:digit:]]+)" );
  std::regex reCommandArgument( "-c(.+)" );

  bool descriptionRequired = false;

  for( auto&& argument : arguments )
  {
    if( argument.substr( 0, 2 ) == "-i" )
    {
      std::smatch matches;
      std::regex_match( argument, matches, reInputArgument );

      inputs = static_cast<unsigned>( std::stoul( matches[1] ) );
    }
    else if( argument.substr( 0, 2 ) == "-c" )
    {
      std::smatch matches;
      std::regex_match( argument, matches, reCommandArgument );

      command = matches[1];
    }

    // Eat all other arguments first before deciding about whether to
    // show the self-description or not.
    else if( argument == "--description" )
      descriptionRequired = true;
  }

  if( descriptionRequired )
  {
    std::cout << "name: " << command << "\n"
              << "command: " << arguments.front() << " -i" << inputs << " -c" << command << "\n";

    // FIXME: Better extraction of command name?
    for( unsigned i = 0; i < inputs; i++ )
      std::cout << "input: " << command << "_" << i << ".in\n";

    std::cout << "output: " << command << ".out\n";
    return 0;
  }

  // TODO: Execute auxiliary command, with the individual files being
  // assigned as additional parameters.
}
