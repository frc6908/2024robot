// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include <iostream>


#include <frc/shuffleboard/Shuffleboard.h>

#include <memory>



RobotContainer::RobotContainer() : m_drivetrain(){
  // Initialize all of your commands and subsystems here

  
  

  // Configure the button bindings
  
  ConfigureButtonBindings();
  // need lambda function to capture the value of the double function for continuous data getting 
  m_drivetrain.SetDefaultCommand(ArcadeDrive(&m_drivetrain, [this] { return -m_joystick.GetY(); }, [this] { return m_joystick.GetX(); }, [this] { return m_joystick.GetThrottle(); }));
  // Configure the button bindings
  
}

void RobotContainer::ConfigureButtonBindings() {
  //drivetrain
  frc2::JoystickButton flip(&m_joystick, 8);
  flip.OnTrue(new FlipDrivetrain(&m_drivetrain));




  m_chooser.SetDefaultOption("Slow Auto", &m_slowauto);
  frc::Shuffleboard::GetTab("Autonomous").Add(m_chooser).WithWidget(frc::BuiltInWidgets::kComboBoxChooser);

  

}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return m_chooser.GetSelected();
}
