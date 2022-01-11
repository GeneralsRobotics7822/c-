// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc/XboxController.h>
#include <frc/TimedRobot.h>
#include <frc/Timer.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/motorcontrol/PWMSparkMax.h>

class Robot : public frc::TimedRobot {
 public:
  
  bool going = true;

  void RobotInit() override{
    rightMotor.SetInverted(true);
  }
  void RobotPeriodic() override{}

  void AutonomousInit() override{
    timer.Reset();
    timer.Start();
  }
  void AutonomousPeriodic() override{
    if(timer.Get() < 2_s){
      robotDrive.ArcadeDrive(-0.5,0);
    }
    else{
      robotDrive.StopMotor();
    }
  }

  void TeleopInit() override{}
  void TeleopPeriodic() override{
    if(going){
      robotDrive.ArcadeDrive(-xboxController.GetLeftY(), xboxController.GetLeftX());
    }
    if(xboxController.GetBButtonPressed()){
      robotDrive.StopMotor();
      going = false;
    }
    if(xboxController.GetAButtonPressed()){
      going = true;
    }
  }

  void DisabledInit() override{}
  void DisabledPeriodic() override{}

  void TestInit() override{}
  void TestPeriodic() override{}

  private:
    // Robot drive system
    frc::PWMSparkMax leftMotor{0};
    frc::PWMSparkMax rightMotor{1};
    frc::DifferentialDrive robotDrive{leftMotor, rightMotor};

    frc::XboxController xboxController{0};
    frc::Timer timer;

};


#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
