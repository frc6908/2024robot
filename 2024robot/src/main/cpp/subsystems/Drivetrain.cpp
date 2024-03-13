// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Drivetrain.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableValue.h"

#include <pathplanner/lib/auto/AutoBuilder.h>
#include <pathplanner/lib/util/HolonomicPathFollowerConfig.h>
#include <pathplanner/lib/util/PIDConstants.h>
#include <pathplanner/lib/util/ReplanningConfig.h>
#include <frc/geometry/Pose2d.h>
#include <frc/geometry/Rotation2d.h>
#include <frc/geometry/Translation2d.h>
#include <frc/kinematics/ChassisSpeeds.h>
#include <frc/kinematics/DifferentialDriveKinematics.h>
#include <frc/DriverStation.h>

#include <units/velocity.h>


using namespace pathplanner;
Drivetrain::Drivetrain() {

    
    rightSpark1.SetInverted(1); 
    rightSpark2.SetInverted(1);// inverts the right drive motors
    resetGyro();

    AutoBuilder::configureRamsete(
    [this]() -> frc::Pose2d { return getPose(); },              // Lambda for Robot pose supplier
    [this](frc::Pose2d pose) { resetPose(pose); },              // Lambda for resetting odometry
    [this]() -> frc::ChassisSpeeds { return getRobotRelativeSpeeds(); },  // Lambda for ChassisSpeeds supplier (MUST BE ROBOT RELATIVE)
    [this](frc::ChassisSpeeds speeds) { driveRobotRelative(speeds); },   // Lambda for driving the robot given ROBOT RELATIVE ChassisSpeeds
    ReplanningConfig(),                                         // Default path replanning config
        []() {
            // Boolean supplier that controls when the path will be mirrored for the red alliance
            // This will flip the path being followed to the red side of the field.
            // THE ORIGIN WILL REMAIN ON THE BLUE SIDE

            auto alliance = frc::DriverStation::GetAlliance();
            if (alliance) {
                return alliance.value() == frc::DriverStation::Alliance::kRed;
            }
            return false;
        },
    this    
                                                    // Reference to this subsystem to set requirements
);
}

void Drivetrain::setDriveMotors(double left, double right) {
    //tab.Add("Left Motor", left);
    //tab.Add("Right Motor", right);
    
    if (flipped) {
        leftSpark1.Set(-right);
        leftSpark2.Set(-right);
        rightSpark1.Set(-left);
        rightSpark2.Set(-left);
    } else {
        leftSpark1.Set(left);
        leftSpark2.Set(left);
        rightSpark1.Set(right);
        rightSpark2.Set(right);
    }
    //NetworkTableEntry testTab = Shuffleboard.getTab("Test").add("Pi", 3.14);
}

void Drivetrain::arcadeDrive(double throttle, double turn) {
    setDriveMotors(throttle + turn, throttle - turn);
}

void Drivetrain::stop() {
    leftSpark1.Set(0);
    leftSpark2.Set(0);
    rightSpark1.Set(0);
    rightSpark2.Set(0);
}

void Drivetrain::flipDT() {
    flipped = !flipped;
}

frc::Rotation2d Drivetrain::getHeading() {
    units::degree_t deg{-gyro.GetAngle()};
    return frc::Rotation2d(deg);
}

double Drivetrain::getHeadingAsAngle() {
    return getHeading().Degrees().value();
}

frc::Rotation2d Drivetrain::getPitch() {
    units::degree_t deg{gyro.GetPitch()};
    return frc::Rotation2d(deg);
}


double Drivetrain::getPitchAsAngle() {
    return getPitch().Degrees().value();
}



void Drivetrain::resetEncoders() {
    rightSpark2.SetSelectedSensorPosition(0.0);
    leftSpark2.SetSelectedSensorPosition(0.0);
}

double Drivetrain::getLeftEncoderDistance() {
    return leftSpark2.GetActiveTrajectoryPosition();
}

double Drivetrain::getRightEncoderDistance() {
    return rightSpark2.GetActiveTrajectoryPosition();
}

double Drivetrain::venomTicksToInches(double revolutions) {
    return 3.14159265358979323846 * drivetrain::wheelDiameter * revolutions / 10.71;
}

void Drivetrain::resetGyro() {
    gyro.Reset();
}

frc::Pose2d Drivetrain::getPose(){
    return m_odometry.GetPose();
}


void Drivetrain::resetPose(frc::Pose2d pose){
    m_odometry.ResetPosition(gyro.GetRotation2d(), units::length::meter_t(leftSpark2.GetActiveTrajectoryPosition()), units::length::meter_t(rightSpark2.GetActiveTrajectoryPosition()), 
    m_pose);
}

frc::ChassisSpeeds Drivetrain::getRobotRelativeSpeeds(){

    units::meters_per_second_t speedX{gyro.GetVelocityX()};
    units::meters_per_second_t speedY{gyro.GetVelocityY()};

    frc::ChassisSpeeds speeds{speedX, -speedY,
    units::radians_per_second_t(std::numbers::pi)};
    return frc::ChassisSpeeds(speeds);
}

void Drivetrain::driveRobotRelative(frc::ChassisSpeeds speeds){
    frc::DifferentialDriveKinematics kinematics{23_in}; //Change for KOP

// Convert to wheel speeds. Here, we can use C++17's structured bindings
// feature to automatically split the DifferentialDriveWheelSpeeds
// struct into left and right velocities.
    auto [left,right] = kinematics.ToWheelSpeeds(speeds);

    rightSpark1.Set(double(right));
    rightSpark2.Set(double(right));
    leftSpark1.Set(double(left));
    leftSpark2.Set(double(left));
}



// This method will be called once per scheduler run
void Drivetrain::Periodic() {
    m_odometry.Update(gyro.GetRotation2d(), units::length::meter_t(leftSpark2.GetActiveTrajectoryPosition()), units::length::meter_t(rightSpark2.GetActiveTrajectoryPosition()));
}

