// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/Command.h>
#include <frc2/command/CommandHelper.h>
#include <frc/controller/PIDController.h>

#include "subsystems/Drivetrain.h"

/**
 * An example command that uses an example subsystem.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class TurnDrivetrain : public frc2::CommandHelper<frc2::Command, TurnDrivetrain> {
 public:
  TurnDrivetrain(Drivetrain*, double);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  private:
    Drivetrain* m_drivetrain;
    double turn;
    frc::PIDController pid{frc::SmartDashboard::GetNumber("kP", 0.01), frc::SmartDashboard::GetNumber("kI", 0), frc::SmartDashboard::GetNumber("kD", 0)};
    //0.12, 0, 0.0006
};