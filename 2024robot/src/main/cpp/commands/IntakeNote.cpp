#include "commands/IntakeNote.h"

IntakeNote::IntakeNote(Intake* intake) : m_intake{intake} {
    AddRequirements(intake);
}