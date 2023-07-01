#ifndef COMMAND_HPP
#define COMMAND_HPP

class User {
    
    public:
        User();
        User(int UserClientId, std::string nickname, modes userMode)
        ~User();


    private:

        int userClientId;

};

#endif