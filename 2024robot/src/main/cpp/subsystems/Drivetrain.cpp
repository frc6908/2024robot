// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Drivetrain.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableValue.h"

Drivetrain::Drivetrain() {
    rightSpark1.SetInverted(1); 
    rightSpark2.SetInverted(1);// inverts the right drive motors
    resetGyro();
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
    leftEncoder.SetPosition(0.0);
    rightEncoder.SetPosition(0.0);
}

double Drivetrain::getLeftEncoderDistance() {
    return leftEncoder.GetPosition();
}

double Drivetrain::getRightEncoderDistance() {
    return rightEncoder.GetPosition();
}

double Drivetrain::neoTicksToInches(double revolutions) {
    return M_PI * drivetrain::wheelDiameter * revolutions / 10.71;
}

void Drivetrain::resetGyro() {
    gyro.Reset();
}
// This method will be called once per scheduler run
void Drivetrain::Periodic() {}
