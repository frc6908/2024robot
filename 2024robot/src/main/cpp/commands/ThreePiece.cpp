#include "commands/ThreePiece.h"

ThreePiece::ThreePiece(Drivetrain* drivetrain) : m_drivetrain{drivetrain} {
    AddRequirements(drivetrain); 
}

void ThreePiece::Initialize() {}

void ThreePiece::Execute() {}

void ThreePiece::End(bool interrupted) {}

bool ThreePiece::IsFinished() {
    return true;
}