// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <cmath>

#include <frc2/command/SubsystemBase.h>

#include <rev/CANSparkMax.h>
#include <rev/CANSparkLowLevel.h>
#include <rev/CANSparkBase.h>
#include <rev/SparkRelativeEncoder.h>
#include <frc/motorcontrol/MotorControllerGroup.h>


#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/shuffleboard/ShuffleboardTab.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <iostream>

#include "Constants.h"

class Arm : public frc2::SubsystemBase {
    public:
        Arm();

        void setRotationMotor(double);

        void stop();
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
        void Periodic() override;

    private:
        rev::CANSparkMax rightArmSpark{arm::kRightArmSparkPort, rev::CANSparkLowLevel::MotorType::kBrushless};
        rev::CANSparkMax leftArmSpark{arm::kLeftArmSparkPort, rev::CANSparkLowLevel::MotorType::kBrushless};

        rev::SparkRelativeEncoder leftArmEncoder = leftArmSpark.GetEncoder(rev::SparkRelativeEncoder::Type::kQuadrature, 4096);
        rev::SparkRelativeEncoder rightArmEncoder = rightArmSpark.GetEncoder(rev::SparkRelativeEncoder::Type::kQuadrature, 4096);

        
        frc::MotorControllerGroup RotationMotor{rightArmSpark, leftArmSpark};

        frc::ShuffleboardTab& tab = frc::Shuffleboard::GetTab("Test");
        // Components (e.g. motor controllers and sensors) should generally be
            // declared private and exposed only through public methods.
};