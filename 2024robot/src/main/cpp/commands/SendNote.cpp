#include "commands/SendNote.h"

SendNote::SendNote(Intake* intake) : m_intake{intake} {
    AddRequirements(intake);
    t = 0;
}

void SendNote::Initialize() {
    this->m_intake->stop();
}

void SendNote::Execute() {

    if (t < 200){
        this->m_intake->stop();
    }
    else{
        this->m_intake->setIntakeMotor(1.0);
    }
    t++;
}

void SendNote::End(bool interrupted) {
    this->m_intake->stop();
}

bool SendNote::IsFinished() {
    return false;
}