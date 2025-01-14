#include <random>
#include <iostream>
#include <ctime>
#include <chrono>
#include "XoshiroCpp.hpp"
#include <iomanip>
using namespace std;
using namespace XoshiroCpp;
        bool rezero = false;
        int roll = 0;
        int space = 0;
        int highest = 0;
        int rollcall = 0;
        int highroll = 0;
        double totalroll = 0;
        unsigned long rps = 0;
        unsigned long cps = 0;
        bool end = false;
        bool ctrlCPressed = false;
        long endcount = 0;
        const int startNum = 1;
        const int endNum = 6;
        double rollcount = 0;
        double guage;
        unsigned long timewasted = 0;
        random_device rd;
        uint64_t seed = rd();
        Xoshiro256PlusPlus rng(seed);
        uniform_int_distribution<> dist(1,6);
class Timer
{
public:
    void start()
    {
        m_StartTime = std::chrono::system_clock::now();
        m_bRunning = true;
    }
    
    void stop()
    {
        m_EndTime = std::chrono::system_clock::now();
        m_bRunning = false;
    }
    
    double elapsedMilliseconds()
    {
        std::chrono::time_point<std::chrono::system_clock> endTime;
        
        if(m_bRunning)
        {
            endTime = std::chrono::system_clock::now();
        }
        else
        {
            endTime = m_EndTime;
        }
        
        return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
    }
    
    double elapsedSeconds()
    {
        return elapsedMilliseconds() / 1000.0;
    }

private:
    std::chrono::time_point<std::chrono::system_clock> m_StartTime;
    std::chrono::time_point<std::chrono::system_clock> m_EndTime;
    bool                                               m_bRunning = false;
};

long fibonacci(unsigned n)
{
    if (n < 2) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}
void Clear()
{
#if defined _WIN32
        system("cls");
        //clrscr(); // including header file : conio.h
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        system("clear");
        //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
    #elif defined (__APPLE__)
               system("clear");
    #endif
}

unsigned long minuteswasted = 0;
unsigned long hourswasted = 0;

void drawcall(){
    guage = rollcount / totalroll;
    Clear();
    cout << "highest: " << highest << endl << "highest roll: " << highroll << endl << "total roll: " << totalroll << endl << "total runs: " << endcount << endl << "rolls/s: " << rps << endl << "runs/s: " << cps << endl << "average roll: " << setprecision(500) << guage << endl << "total sum of rolls: " << rollcount << endl << "time wasted: " << timewasted << " seconds " << minuteswasted << " minutes " << hourswasted << " hours" << endl;
    rps = 0;
    cps = 0;
    timewasted++;
    if(timewasted == 60){
        minuteswasted++;
        timewasted = 0;
        if(minuteswasted == 60){
            hourswasted++;
            minuteswasted = 0;
        }
    }
    return;
};

int main(){
    Timer timer1;

    time_t now = time(0); // current time in seconds since epoch
    tm* local_time = localtime(&now);

    int hour = local_time->tm_hour;
    int minute = local_time->tm_min;
    int second = local_time->tm_sec;

    bool running = true;

    long iteration = 0;

    double seconds;

    bool loop = true;
    bool timerset;
    double timerlength;
    double timerrun;
    Timer timer2;


    //std::signal(SIGINT, signalHandler);

    cout << "starting " << hour << ":" << minute << ":" << second << endl;
    timer1.start();

    cout << "Do you want to set a timer? (y=1/n=0)";
    cin >> timerset;
    if(timerset){

        cout << "how long will the timer be set for? (seconds)";

        cin >> timerlength;
        timer2.start();
    }

    while(loop){ // primary loop
                    if(!rezero){
                roll = dist(rng); // safe gamble
                rollcall++; totalroll++; rps++; rollcount = rollcount + roll;
                if(roll == 3){
                    roll = dist(rng); // risky gamble
                    rollcall++; totalroll++; rps++; rollcount = rollcount + roll;
                    if(roll == 3){
                        space++;
                    }
                    else{
                        rezero = true;
                    };
                }
                else{};
            };

            if(rezero){
                if(space > highest){
                    highest = space;
                }
                else{};
                if(rollcall > highroll){
                    highroll = rollcall;
                };
                
                rollcall = 0;
                space = 0;
                rezero = false;
                endcount++;
                cps++;
            
            
        seconds = timer1.elapsedSeconds();
        if(seconds > 1){
            drawcall();
            timer1.stop();
            timer1.start();
        };
        if(timerset){
            timerrun = timer2.elapsedSeconds();
            if(timerrun == timerlength){
                loop = false;
            }
        }
            }else{};
    };
    now = time(0); // current time in seconds since epoch
    local_time = localtime(&now);

    hour = local_time->tm_hour;
    minute = local_time->tm_min;
    second = local_time->tm_sec;
    cout << "complete " << hour << ":" << minute << ":" << second << endl;
;}