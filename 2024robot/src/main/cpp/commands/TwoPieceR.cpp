#include "commands/TwoPieceR.h"

TwoPieceR::TwoPieceR(Drivetrain* drivetrain, Shooter* shooter, Arm* arm, Intake* intake) : m_drivetrain{drivetrain}, m_shooter{shooter}, m_arm{arm}, m_intake{intake} {
    AddRequirements(drivetrain); 
    AddRequirements(shooter);
    AddRequirements(arm);
    AddRequirements(intake);
}

void TwoPieceR::Initialize() {
    t = 0;
    this->m_drivetrain->stop();
    this->m_arm->stop();
    this->m_intake->stop();
    this->m_shooter->stop();
}

void TwoPieceR::Execute() {
    if(t <= 100) {

        this->m_arm->setArmMotors(0.5);
        this->m_shooter->setShooterMotors(1, 1);
        if(t > 50){
             this->m_intake->setIntakeMotor(1);;
        }
        else{
            this->m_intake->stop();
        }
       
    }
    else if(t>100 && t<= 150){
        this->m_drivetrain->setDriveMotors(1, 1);
        this->m_shooter->stop();
        this->m_intake->setIntakeMotor(0.5);
    }

    else if(t<150 & t<=200){
        this->m_drivetrain->setDriveMotors(-1.0,-1.0);
    }

    else if(t>200 && t <= 300){
        this->m_drivetrain->stop();
        this->m_shooter->setShooterMotors(1,1);
        if(t > 250){
             this->m_intake->setIntakeMotor(1);;
        }
        else{
            this->m_intake->stop();
        }
    }

    else if(t>300 && t<=350){
        this->m_arm->setArmMotors(-0.4);
        this->m_drivetrain->setDriveMotors(1,1);
        this->m_shooter->setShooterMotors(1,1);
        this->m_intake->setIntakeMotor(1);
    }
    else{
        this->m_arm->setArmMotors(-0.1);
        this->m_drivetrain->stop();
        this->m_shooter->stop();
        this->m_intake->stop();
    }

}
void TwoPieceR::End(bool interrupted) {
    this->m_drivetrain->stop();
    this->m_shooter->stop();
    this->m_intake->stop();
    this->m_arm->stop();
}

bool TwoPieceR::IsFinished() {
    return false;
}