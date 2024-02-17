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
    //this->m_shooter->setShooterMotors(1,1); (UNTESTED)
}

void TwoPiece::Execute() {
    if(t <= 20) {
        this->m_drivetrain->setDriveMotors(0.8, 0.8);
        //this->m_shooter->setShooterMotors(0,0); (UNTESTED)
    }
    else if(t > 20 && t < 40) {
        this->m_drivetrain->setDriveMotors(-0.8, -0.8);
    }
    else if(t >= 40 && t< 45){
        this-> m_drivetrain-> setDriveMotors(0.0,0.0);
        //this-> m_shooter->setShooterMotors(1,1); (UNTESTED)
    }

    else if (t>=45 && t< 100){
        this-> m_drivetrain-> setDriveMotors(0.4,0.45);
        //this-> m_shooter->setShooterMotors(0,0); (UNTESTED)
    }
    else {
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