#include "commands/TwoPieceR.h"

TwoPieceR::TwoPieceR(Drivetrain* drivetrain) : m_drivetrain{drivetrain} {
    AddRequirements(drivetrain); 
}

void TwoPieceR::Initialize() {}

void TwoPieceR::Execute() {}

void TwoPieceR::End(bool interrupted) {}

bool TwoPieceR::IsFinished() {return true;}