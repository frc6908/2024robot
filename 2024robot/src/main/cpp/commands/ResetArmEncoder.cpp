// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ResetArmEncoder.h"

ResetArmEncoder::ResetArmEncoder(Arm* arm)
    : m_arm{arm} {

    AddRequirements(arm); 
}

void ResetArmEncoder::Initialize() {
    prev = this->m_arm->getEncoderDist();
    this->m_arm->stop();
}

void ResetArmEncoder::Execute() {
    frc::SmartDashboard::PutNumber("Encoder", this->m_arm->getEncoderDist());
    this->m_arm->setArmMotors(0.3);
}

void ResetArmEncoder::End(bool interrupted) {
    this->m_arm->resetEncoder();
    this->m_arm->stop();
}

bool ResetArmEncoder::IsFinished() {
    if(abs(prev - this->m_arm->getEncoderDist()) <= 1) {
        return true;
    }
    else {
        return false;
    }
}
