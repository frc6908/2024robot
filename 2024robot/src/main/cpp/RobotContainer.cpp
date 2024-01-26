// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include <pathplanner/lib/auto/NamedCommands.h>
#include <pathplanner/lib/commands/PathPlannerAuto.h>
#include <iostream>

#include <frc/shuffleboard/Shuffleboard.h>

#include <memory>

using namespace pathplanner;


RobotContainer::RobotContainer() : m_drivetrain(){
  // Initialize all of your commands and subsystems here

  m_chooser.SetDefaultOption("Slow Auto", &m_slowauto);
  frc::Shuffleboard::GetTab("Autonomous").Add(m_chooser).WithWidget(frc::BuiltInWidgets::kComboBoxChooser);
  

  // Configure the button bindings
  configureButtonBindings();
  // need lambda function to capture the value of the double function for continuous data getting 
  m_drivetrain.SetDefaultCommand(ArcadeDrive(&m_drivetrain, [this] { return -m_joystick.GetY(); }, [this] { return m_joystick.GetX(); }, [this] { return m_joystick.GetThrottle(); }));

  // Configure the button bindings


  //pathplannertest
  
}

void RobotContainer::ConfigureBindings() {
  // Configure your trigger bindings here

  // Schedule `ExampleCommand` when `exampleCondition` changes to `true`
  /*frc2::Trigger([this] {
    return m_subsystem.ExampleCondition();
  }).OnTrue(ExampleCommand(&m_subsystem).ToPtr());
  */

  // Schedule `ExampleMethodCommand` when the Xbox controller's B button is
  // pressed, cancelling on release.
  frc2::JoystickButton flipDriveTrain(&m_joystick, 8);
  FlipDrivetrain.WhenPressed(new FlipDrivetrain(&m_drivetrain));
}

frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  //return m_chooser.GetSelected();
  return PathPlannerAuto("Example Auto").ToPtr();
}
