// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/TwoPiece.h"

TwoPiece::TwoPiece(Drivetrain* drivetrain) : m_drivetrain{drivetrain} {
    AddRequirements(drivetrain); 
}

void TwoPiece::Initialize() {
    t = 0;
    this->m_drivetrain->stop();
}

void TwoPiece::Execute() {
    if(t <= 50 && t > 15) {
        this->m_drivetrain->setDriveMotors(0.4, 0.4);
    }
    else if(t > 50 && t<=75){
        this->m_drivetrain->setDriveMotors(-0.8,-0.8);
    }

    else if(t > 75 && 80){
        this->m_drivetrain->setDriveMotors(0,0);
    }

    else if(t>80 && 88){
        this->m_drivetrain->setDriveMotors(0, 1);

    }

    else if(t>88 && t<100){
        this->m_drivetrain->setDriveMotors(0.4,0.4);
    }
    else{
        this->m_drivetrain->setDriveMotors(0, 0);
    }
    t++;
}

void TwoPiece::End(bool interrupted) {
    this->m_drivetrain->stop();
    /*
    this->m_shooter->setTopMotorVoltage(stopVoltage);
    this->m_shooter->setBottomMotorVoltage(stopVoltage);
    this->m_uptake->setTopFeederMotor(0);
    this->m_uptake->setUptakeMotor(0);
    */
}

bool TwoPiece::IsFinished() {
    return false;
}