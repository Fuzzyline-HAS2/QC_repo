 ;/**
 * @file Done_ItemBox_code.ino
 * @author 김병준 (you@domain.com)
 * @brief
 * @version 1.0
 * @date 2022-11-29
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "itembox_random_add.h"
#include "QC/QC_Engine.h"
#include "QC/QC_Rules.h"

void setup() 
{
    Serial.begin(115200);
    has2wifi.Setup("badland");
    NeopixelInit();
    //RfidInit();
    //MotorInit();
    //EncoderInit();
    //NextionInit();
    TimerInit();
    // has2wifi.Setup();
    // has2wifi.Setup("KT_GiGA_6C64","ed46zx1198");
    DataChanged();

    // QC System Initialization
    QCEngine::getInstance().begin(1000);
    QCEngine::getInstance().addRule(new QCRule_WifiConnection());
    QCEngine::getInstance().addRule(new QCRule_WifiSignal());
    QCEngine::getInstance().addRule(new QCRule_HeapMemory());
    QCEngine::getInstance().addRule(new QCRule_GameState());
    //QCEngine::getInstance().addRule(new QCRule_RfidStatus());
    QCEngine::getInstance().addRule(new QCRule_EncoderRange());
    QCEngine::getInstance().addRule(new QCRule_StateConsistency());
    Serial.println("QC System Started");
}
void loop() 
{
    ptrCurrentMode();
    WifiTimer.run();
    GameTimer.run();
    BlinkTimer.run();

    // QC Check
    QCEngine::getInstance().tick();
}
