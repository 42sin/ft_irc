#include "Command.hpp"
#include "Server.hpp"

std::string Command::executePass()
{
    
    if (Command::checkPass(_params.first()) == TRUE)
        AUTHENTICATED = TRUE;

    else {
        AUTHENTICATED = FASE;
        return (ERR_NOTREGISTERED());
    }
    
    

}

bool Command::checkPass(std::string input_pass)
{
    if (input_pass.compare(Server::getPassword()) == TRUE)
        return (TRUE);
    else
        return (FALSE);
}
