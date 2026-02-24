#pragma warning(disable : 4996)

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

string GetMaghribTime()
{
    string API = "powershell -Command \"$r = Invoke-RestMethod -Uri 'https://api.aladhan.com/v1/timingsByCity?city=Damascus&country=Syria&method=2'; $r.data.timings.Maghrib\"";

    string maghribTime;

    char buffer[16];

    FILE* pipe = _popen(API.c_str(), "r");

    if (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        maghribTime = buffer;
    }

    _pclose(pipe);

    return maghribTime;
}

void GetCurrentTime(int& hour, int& minute, int& second) {

    time_t t = time(0);
    tm* now = localtime(&t);

    hour = now->tm_hour;
    minute = now->tm_min;
    second = now->tm_sec;
}

void CalculateTimeUntilMaghrib(int maghribHour, int maghribMinute, int currentHour, int currentMinute, int currentSecond, int& hoursLeft, int& minutesLeft, int& secondsLeft)
{
    hoursLeft = maghribHour - currentHour;
    minutesLeft = maghribMinute - currentMinute;
    secondsLeft = 0 - currentSecond;

    if (secondsLeft < 0) {
        secondsLeft += 60;
        minutesLeft -= 1;
    }

    if (minutesLeft < 0) {
        minutesLeft += 60;
        hoursLeft -= 1;
    }
}

void PrintTimeRemaining(int hoursLeft, int minutesLeft, int secondsLeft)
{
    if (hoursLeft < 0)
    {
        cout << "Maghrib time has passed today in Damascus!" << endl;
    }
    else
    {
        cout << "Time remaining for Maghrib in Damascus: "
            << hoursLeft << " hours, "
            << minutesLeft << " minutes, "
            << secondsLeft << " seconds." << endl;
    }
}

int main()
{
    string maghribTime = GetMaghribTime();
    int maghribHour = stoi(maghribTime.substr(0, 2));
    int maghribMinute = stoi(maghribTime.substr(3, 2));

    int currentHour, currentMinute, currentSecond;
    GetCurrentTime(currentHour, currentMinute, currentSecond);

    int hoursLeft, minutesLeft, secondsLeft;
    CalculateTimeUntilMaghrib(maghribHour, maghribMinute, currentHour, currentMinute, currentSecond, hoursLeft, minutesLeft, secondsLeft);

    PrintTimeRemaining(hoursLeft, minutesLeft, secondsLeft);

    return 0;
}
