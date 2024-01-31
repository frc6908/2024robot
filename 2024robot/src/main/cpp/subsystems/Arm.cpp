#include "subsystems/Arm.h"

#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableValue.h"

Arm::Arm() {}

void Arm::setArmMotors(double speed) {
    armSpark1.Set(speed);
    armSpark2.Set(speed);
}

void Arm::stop() {
    armSpark1.Set(0);
    armSpark2.Set(0);
}