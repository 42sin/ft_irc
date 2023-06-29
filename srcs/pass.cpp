#include "Command.hpp"
#include "Server.hpp"

void Command::executePass()
{
    if (Command::checkPass(_params.first()) == TRUE)
        AUTHENTICATED = TRUE;
    else   
        AUTHENTICATED = FASE;
    

}

bool Command::checkPass(std::string input_pass)
{
    if (input_pass.compare(getPassword()) == TRUE)
        return (TRUE);
    else
        return (FALSE);
}