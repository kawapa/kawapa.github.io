#include <boost/lexical_cast.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class SingletonDatabase {
    SingletonDatabase() {
        std::ifstream ifs("./users.txt");

        std::string s, s2;
        while (getline(ifs, s)) {
            getline(ifs, s2);
            int pop = boost::lexical_cast<int>(s2);
            users[s] = pop;
        }
    }

    std::map<std::string, int> users;

public:
    SingletonDatabase(SingletonDatabase const&) = delete;
    void operator=(SingletonDatabase const&) = delete;

    static SingletonDatabase& get() {
        static SingletonDatabase db;
        return db;
    }

    int getUserId(const std::string& mail) {
        return users[mail];
    }
};

class UserFinder {
public:
    int getUserId(const std::string& mail) {
        return SingletonDatabase::get().getUserId(mail);
    }
};

main() {
    // std::string city = "abc@yahoo.com";
    // std::cout << SingletonDatabase::get().getUserId(city)
    //           << std::endl;

    UserFinder uf;
    std::cout << uf.getUserId("abc@yahoo.com");

    return 0;
}