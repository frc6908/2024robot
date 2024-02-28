// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include <pathplanner/lib/auto/NamedCommands.h>
#include <pathplanner/lib/auto/AutoBuilder.h>
#include <pathplanner/lib/commands/PathPlannerAuto.h>
#include <pathplanner/lib/util/ReplanningConfig.h>
#include <frc/geometry/Pose2d.h>
#include <frc/kinematics/ChassisSpeeds.h>
#include <iostream>


#include <frc/shuffleboard/Shuffleboard.h>

#include <memory>

using namespace pathplanner;


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

  //Intake
  frc2::JoystickButton Intake(&m_joystick, 1);
  Intake.WhileTrue(new IntakeNote(&m_intake));

  //Outtake
  frc2::JoystickButton Outtake(&m_joystick, 4);
  Outtake.WhileTrue(new OuttakeNote(&m_intake));



  //Shooter
  frc2::JoystickButton Shooter(&m_joystickArm, 1);
  Shooter.WhileTrue(new ShootNote(&m_shooter));
  Shooter.WhileTrue(new SendNote(&m_intake));
  

  //Arm Manual UNTESTED
  frc2::JoystickButton armUp(&m_joystickArm, 3);
  armUp.WhileTrue(new MoveArm(&m_arm, false, m_joystickArm.GetThrottle())); 
  frc2::JoystickButton armDown(&m_joystickArm, 6);
  armDown.WhileTrue(new MoveArm(&m_arm, true, m_joystickArm.GetThrottle()));

  // Alignment

  /*
  frc2::JoystickButton alignArm(&m_joystick, 7);
  alignArm.WhileTrue(new AlignArm(&m_arm, &m_vision));
  frc2::JoystickButton alignDT(&m_joystick, 8);
  alignDT.WhileTrue(new AlignDrivetrain(&m_drivetrain, &m_vision));
  frc2::JoystickButton alignAmp(&m_joystick, 5);
  alignAmp.WhileTrue(new MoveArmAngle(&m_arm, 106));
  */



  m_chooser.SetDefaultOption("Slow Auto", &m_slowauto);
  m_chooser.AddOption("Preloaded Mobility", &m_preloaded);
  m_chooser.AddOption("Two Piece Auto- Center", &m_twopiece);
  // m_chooser.AddOption("Amp Auton", &m_ampauto);
  // m_chooser.AddOption("Two Piece Auto- Right", &m_twopieceR);
  // m_chooser.AddOption("Three Piece Auto- Center", &m_threepiece);

  frc::Shuffleboard::GetTab("Autonomous").Add(m_chooser).WithWidget(frc::BuiltInWidgets::kComboBoxChooser);
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return m_chooser.GetSelected();
}
