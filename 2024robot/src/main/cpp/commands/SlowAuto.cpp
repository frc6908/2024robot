// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/SlowAuto.h"

SlowAuto::SlowAuto(Drivetrain* drivetrain) : m_drivetrain{drivetrain} {
    AddRequirements(drivetrain); 
}

void SlowAuto::Initialize() {
    t = 0;
    this->m_drivetrain->stop();
}

void SlowAuto::Execute() {
    if(t <= 100) {
        this->m_shooter->setShooterMotors(1.0,1.0);
        this->m_drivetrain->setDriveMotors(0.4, 0.4);
    }
    else {
        this->m_drivetrain->setDriveMotors(0, 0);
    }
    t++;
}

void SlowAuto::End(bool interrupted) {
    this->m_drivetrain->stop();
}

bool SlowAuto::IsFinished() {
    return false;
}