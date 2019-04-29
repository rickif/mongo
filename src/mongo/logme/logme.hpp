#ifndef LOGME_HPP__
#define LOGME_HPP__

#include <fstream>
#include <ctime>
#include <chrono>

class Logme {
    friend Logme& Glogme();
    public:
        ~Logme() {
            _ofs.close();
        }
        template <typename T>
        Logme& operator<<(const T& x) {
            _ofs << x;
            return *this;
        }
        Logme& operator<<(std::ostream& (*manip)(std::ostream&)) {
            _ofs << manip;
            return *this;
        }
    private:
        Logme() {
            _ofs.open("logme.log", std::ofstream::app);
        }
        std::ofstream _ofs;
};

inline Logme &Glogme() {
    static Logme logme;
    auto now = std::chrono::system_clock::now();
    auto milli = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    time_t t = std::chrono::system_clock::to_time_t(now);
    char buf[100];
    std::strftime(buf, sizeof(buf), "%F %T.", localtime(&t));
    logme._ofs << buf;
    logme._ofs << (milli % 1000) << "\t";
    return logme;
}

#endif
