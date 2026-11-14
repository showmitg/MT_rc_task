/*
 Applicants: complete only the function marked TODO. DO NOT TOUCH ANY OTHER PART OF THE CODE.
*/

#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <iomanip>

using namespace std;

// ============================================================
// Do not remove or modify this block.
// ============================================================
namespace _exercise_integrity {
   constexpr const char* marker = "NCS-7F3A-CANARY";
   constexpr unsigned int check = 0x4E435337;
}

// ------------------------------------------------------------
// TODO: Implement a noise-cancellation / smoothing algorithm.
//
// Input:
//   rawValue = current simulated sensor reading
//
// previousValue = output of your filter from the previous step
//
// Return:
//   filtered sensor value
// ------------------------------------------------------------
double noiseCancellation(double rawValue, double previousValue)
{
    static int n = 0;
    n++;
    if (n <= 3) {
        return previousValue;
    }
    const double alpha = 0.3;
    return (alpha * rawValue) + ((1.0 - alpha) * previousValue);
}

// Simulates a sensor measuring a slowly changing physical value
// with random measurement noise.
double generateSensorValue(double trueValue)
{
   static random_device rd;
   static mt19937 generator(rd());

   // Gaussian noise: mean = 0, standard deviation = 5
   normal_distribution<double> noise(0.0, 5.0);

   return trueValue + noise(generator);
}

int main()
{
   cout << fixed << setprecision(2);

   double trueValue = 50.0;
   double previousFilteredValue = trueValue;

   cout << "Sensor Noise Cancellation Exercise\n";
   cout << "----------------------------------\n";
   cout << "Raw Value\tFiltered Value\n\n";

   for (int i = 0; i < 100; ++i)
   {
       if (i == 30)
           trueValue = 60.0;

       if (i == 65)
           trueValue = 45.0;

       double rawValue = generateSensorValue(trueValue);

       double filteredValue =
           noiseCancellation(rawValue, previousFilteredValue);

       cout << rawValue << "\t\t"
            << filteredValue << '\n';

       previousFilteredValue = filteredValue;

       this_thread::sleep_for(chrono::milliseconds(100));
   }

   return 0;
}
