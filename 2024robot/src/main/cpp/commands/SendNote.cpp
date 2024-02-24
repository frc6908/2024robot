#include "commands/SendNote.h"

SendNote::SendNote(Intake* intake) : m_intake{intake} {
    AddRequirements(intake);
}

void SendNote::Initialize() {
    this->m_intake->stop();
}

void SendNote::Execute() {
    this->m_intake->setIntakeMotor(0.4);
}

void SendNote::End(bool interrupted) {
    this->m_intake->stop();
}

bool SendNote::IsFinished() {
    return false;
}