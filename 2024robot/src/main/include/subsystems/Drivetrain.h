// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <cmath>

#include <frc2/command/SubsystemBase.h>

#include <CANVenom.h>
#include <ctre/phoenix/motorcontrol/can/TalonFX.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include <rev/CANSparkMax.h>
#include <rev/CANSparkLowLevel.h>
#include <rev/CANSparkBase.h>
#include <rev/SparkRelativeEncoder.h>
#include <frc/motorcontrol/MotorControllerGroup.h>

#include <frc/SPI.h>
#include <AHRS.h>

#include <frc/geometry/Rotation2d.h>

#include <frc/drive/DifferentialDrive.h>

#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/shuffleboard/ShuffleboardTab.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <iostream>

#include "Constants.h"

class Drivetrain : public frc2::SubsystemBase {
 public:
  Drivetrain();

  void setDriveMotors(double, double);

  void arcadeDrive(double, double);

  void stop();
  
  void flipDT();

  frc::Rotation2d getHeading();

  double getHeadingAsAngle();

  void resetEncoders();

  frc::Rotation2d getPitch();

  double getPitchAsAngle();

  double getLeftEncoderDistance();

  double getRightEncoderDistance();

  double neoTicksToInches(double);

  void resetGyro();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

 private:
  //TalonSRX leftDrive1 = new TalonSRX(drivetrain::kLeftDriveTalonPort);
  //frc::CANVenom leftDrive2{drivetrain::kLeftDriveVenomPort};

  rev::CANSparkMax leftSpark1{drivetrain::kLeftDriveSparkPort1, rev::CANSparkLowLevel::MotorType::kBrushless};
  rev::CANSparkMax leftSpark2{drivetrain::kLeftDriveSparkPort2, rev::CANSparkLowLevel::MotorType::kBrushless};

  //TalonSRX rightDrive1 = new TalonSRX(drivetrain::kRightDriveTalonPort);
  //frc::CANVenom rightDrive2(drivetrain::kRightDriveVenomPort);

  rev::CANSparkMax rightSpark1{drivetrain::kLeftDriveSparkPort1, rev::CANSparkLowLevel::MotorType::kBrushless};
  rev::CANSparkMax rightSpark2{drivetrain::kLeftDriveSparkPort2, rev::CANSparkLowLevel::MotorType::kBrushless};
  frc::MotorControllerGroup leftMotors{rightSpark1, leftSpark1};
  frc::MotorControllerGroup rightMotors{rightSpark2, leftSpark2};

  rev::SparkRelativeEncoder leftEncoder = leftSpark1.GetEncoder(rev::SparkRelativeEncoder::Type::kQuadrature, 4096);
  rev::SparkRelativeEncoder rightEncoder = rightSpark1.GetEncoder(rev::SparkRelativeEncoder::Type::kQuadrature, 4096);
 // rev::SparkRelativeEncoder::leftEncoder(SparkRelativeEncoder && rhs);
 // rev::SparkRelativeEncoder rightEncoder = rightSpark1.GetEncoder();
  frc::DifferentialDrive drive{leftMotors, rightMotors};

  AHRS gyro{frc::SPI::Port::kMXP};

  bool flipped = false;

  frc::ShuffleboardTab& tab = frc::Shuffleboard::GetTab("Test");

  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};