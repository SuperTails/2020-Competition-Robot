/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Hopper.h"
#include <rev/CANSparkMaxLowLevel.h>
#include <rev/CANSparkMax.h>
#include <rev/ControlType.h>

using MotorType = rev::CANSparkMax::MotorType;
using hopper_consts::INTAKE_MOTOR_ID;
using hopper_consts::AGITATE_MOTOR_ID;

Hopper::Hopper() :
    intakeMotor(INTAKE_MOTOR_ID, MotorType::kBrushless),
    agitateMotor(AGITATE_MOTOR_ID, MotorType::kBrushless)
{
    intakeMotor.SetSmartCurrentLimit(15);
    agitateMotor.SetSmartCurrentLimit(15);

    intakeMotor.SetInverted(false);
    agitateMotor.SetInverted(true);
}

// This method will be called once per scheduler run
void Hopper::Periodic() {}

void Hopper::setIntake(bool intake) {
    if (!outtakeOverride) {
        intakeMotor.Set(intake * 0.75);
    }
}

void Hopper::setOuttake(bool outtake) {
    outtakeOverride = outtake;

    agitateMotor.Set(outtake * 0.75);
    intakeMotor.Set(outtake * 0.75);
}