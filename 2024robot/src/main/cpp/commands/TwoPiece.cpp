// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/TwoPiece.h"

TwoPiece::TwoPiece(Drivetrain* drivetrain, Shooter* shooter, Arm* arm, Intake* intake) : m_drivetrain{drivetrain}, m_shooter{shooter}, m_arm{arm}, m_intake{intake} {
    AddRequirements(drivetrain); 
    AddRequirements(shooter);
    AddRequirements(arm);
    AddRequirements(intake);
}

void TwoPiece::Initialize() {
    t = 0;
    this->m_drivetrain->stop();
}

void TwoPiece::Execute() {
    if(t <= 200) {
        
        this->m_shooter->setShooterMotors(1, 1);
        if(t > 100){
             this->m_intake->stop();;
        }
        else{
            this->m_intake->setIntakeMotor(1);
        }
       
    }
    else if(t>200 && t<= 500){
        this->m_drivetrain->setDriveMotors(0.4, 0.4);
        this->m_shooter->stop();
        this->m_intake->setIntakeMotor(1);

       /* 
        if(t>100 && t<= 200){
            //this->m_arm->setArmMotors(1);
        }

        else{
            this->m_arm->stop();
        }
        */
    }

    else(t>500){
        this->m_intake->setIntakeMotors(1);
    }

    
    t++;
}

void TwoPiece::End(bool interrupted) {
    this->m_drivetrain->stop();
    this->m_shooter->stop();
    this->m_arm->stop();
    this->m_intake->stop();
}

bool TwoPiece::IsFinished() {
    return false;
}