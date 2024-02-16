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
  

  //pathplannertest
  NamedCommands::registerCommand("marker1", frc2::cmd::Print("Passed marker 1"));
  NamedCommands::registerCommand("marker2", frc2::cmd::Print("Passed marker 2"));

  
    // Configure the AutoBuilder last
    
}

void RobotContainer::ConfigureButtonBindings() {
  //drivetrain
  frc2::JoystickButton flip(&m_joystick, 8);
  flip.OnTrue(new FlipDrivetrain(&m_drivetrain));



  //register Autons on PathPlanner

  exampleAuto = PathPlannerAuto("Example Auto").ToPtr().Unwrap();
  frc::SmartDashboard::PutData("Example Auto", exampleAuto.get());

  //exampleAuto = PathPlannerAuto("Example Auto").ToPtr().Unwrap();
  //pieceAuto = PathPlannerAuto("pieceAuto").ToPtr().Unwrap();
  //m_chooser.SetDefaultOption("Example Auto", &m_slowauto);
  /*
  //m_chooser.AddOption("pieceAuto",pieceAuto.get());
  frc::Shuffleboard::GetTab("Autonomous").Add(m_chooser).WithWidget(frc::BuiltInWidgets::kComboBoxChooser);


  // Create a vector of bezier points from poses. Each pose represents one waypoint.
  // The rotation component of the pose should be the direction of travel. Do not use holonomic rotation.
  std::vector<frc::Pose2d> poses{
    frc::Pose2d(1.0_m, 1.0_m, frc::Rotation2d(0_deg)),
    frc::Pose2d(3.0_m, 1.0_m, frc::Rotation2d(0_deg)),
    frc::Pose2d(5.0_m, 3.0_m, frc::Rotation2d(90_deg))
};
  std::vector<frc::Translation2d> bezierPoints = PathPlannerPath::bezierFromPoses(poses);

  // Create the path using the bezier points created above
  // We make a shared pointer here since the path following commands require a shared pointer
  auto path = std::make_shared<PathPlannerPath>(
      bezierPoints,
      PathConstraints(3.0_mps, 3.0_mps_sq, 360_deg_per_s, 720_deg_per_s_sq), // The constraints for this path. If using a differential drivetrain, the angular constraints have no effect.
      GoalEndState(0.0_mps, frc::Rotation2d(-90_deg)) // Goal end state. You can set a holonomic rotation here. If using a differential drivetrain, the rotation will have no effect.
  );

  // Prevent the path from being flipped if the coordinates are already correct
  path->preventFlipping = true;
*/


}

frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  //return m_chooser.GetSelected();
  return PathPlannerAuto("Example Auto").ToPtr();
}

