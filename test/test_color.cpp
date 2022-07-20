// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED
#include <unity.h>
#include "base.h"
#include "BlinkActivity.h"
#include "Benchmark.h"

void testColorHsvSteps();
void testColorDetails();
void testHSVFunctions();

glow::PinDevice blinkPin;
glow::BlinkSettings blink(&blinkPin);
glow::BlinkMonitor monitor(&blink);
glow::BlinkActivity blinker(&monitor, &blink);

void run()
{
    UNITY_BEGIN();
    testColorDetails();
    testColorHsvSteps();
    testHSVFunctions();
    UNITY_END();
}

#ifdef ARDUINO

void setup()
{
#ifdef ARDUINO
    Serial.begin(115200);
#endif
    delay(2000);
    glow::Benchmark::Setup();
    run();
    blinkPin.Setup();
    blinker.Reset();
    blink.On(50);
    blink.Off(400);
}

void loop()
{
    glow::Monitor::Cycle();
    blinker.Pulse();
}

#else
int main(int argc, char **argv)
{
    run();
}
#endif // ARDUINO
