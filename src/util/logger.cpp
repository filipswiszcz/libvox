#include <iostream>

#include <string>
#include <sstream>
#include <ctime>

class Logger {

    public:

        void info(const std::string& message) {

            time_t curr = time(0);
            tm* local = localtime(&curr);

            char ts[20];
            strftime(ts, sizeof(ts), "%Y/%m/%d %H:%M:%S", local);

            std::ostringstream entry;
            entry << "[libvox][" << ts << "][INFO]: " << message;

            std::cout << entry.str() << std::endl;

            // TODO save it in the file
        }

};