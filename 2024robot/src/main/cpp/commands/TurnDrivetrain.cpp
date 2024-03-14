// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/TurnDrivetrain.h"

TurnDrivetrain::TurnDrivetrain(Drivetrain* drivetrain, double angle)
    : m_drivetrain{drivetrain}, turn{angle} {

    AddRequirements(drivetrain); 
}

void TurnDrivetrain::Initialize() {
    this->m_drivetrain->stop();
    this->pid.SetTolerance(2);
}

void TurnDrivetrain::Execute() {
    frc::SmartDashboard::PutNumber("Gyro", this->m_drivetrain->getHeadingAsAngle());
    
    this->m_drivetrain->arcadeDrive(0, -this->pid.Calculate(this->m_drivetrain->getHeadingAsAngle(), turn));
}

void TurnDrivetrain::End(bool interrupted) {
    this->m_drivetrain->stop();
}

bool TurnDrivetrain::IsFinished() {
    return this->pid.AtSetpoint();
}
