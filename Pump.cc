#include "Node.hh"
#include "Pump.hh"
#include "Processes.hh"

#include <fstream>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>

namespace pump
{

void Pump::load( const std::string& filename )
{
  std::ifstream in( filename );
  if( !in )
    throw std::runtime_error( "Unable to read input file" );

  std::regex reNode( "[[:space:]]*node:[[:space:]]+([^[:space:]]+)" );
  std::regex reEdge( "[[:space:]]*([^[:space:]]+)[[:space:]]*->[[:space:]]*([^[:space:]]+)" );

  std::string line;

  while( std::getline( in, line ) )
  {
    if( line.empty() || line.front() == '#' )
      continue;

    std::smatch matches;

    if( std::regex_match( line, matches, reNode ) )
    {
      std::string name        = matches[1];
      std::string description = get_stdout( name + " --description" );

      std::cerr << "* Line contains node: " << name << "\n"
                << "* Description length: " << description.size() << "\n";

      auto node = Node::fromDescription( description );
    }
    else if( std::regex_match( line, matches, reEdge ) )
      std::cerr << "* Line contains edge: " << line << "\n";
    else
      std::cerr << "* Unknown line: " << line << "\n";
  }
}

void Pump::save( const std::string& filename )
{
  throw std::runtime_error( "Not yet implemented" );
}

} // namespace pump

int main( int argc, char** argv )
{
  // Sounds like the beginning of a motivational video...
  pump::Pump pump;
  pump.load( "../examples/simple.workflow" );
}
