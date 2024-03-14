// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/Command.h>
#include <frc2/command/CommandHelper.h>

#include <frc/controller/PIDController.h>

#include "subsystems/Drivetrain.h"
#include "subsystems/Vision.h"

/**
 * An example command that uses an example subsystem.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class AlignDrivetrain : public frc2::CommandHelper<frc2::Command, AlignDrivetrain> {
 public:
  AlignDrivetrain(Drivetrain*, Vision*);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  private:
    Drivetrain* m_drivetrain;
    Vision* m_vision;
    frc::PIDController pid{0.01, 0, 0};
};