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
    m_right.SetInverted(true);
  }
  void RobotPeriodic() override{}

  void AutonomousInit() override{
    m_timer.Reset();
    m_timer.Start();
  }
  void AutonomousPeriodic() override{
    if(m_timer.Get() < 2_s){
      m_robotDrive.ArcadeDrive(0.5,0);
    }
    else{
      m_robotDrive.StopMotor();
    }
  }

  void TeleopInit() override{}
  void TeleopPeriodic() override{
    if(going){
      m_robotDrive.ArcadeDrive(-m_stick.GetRightX(), m_stick.GetRightY());
    }
    if(m_stick.GetBButtonPressed()){
      m_robotDrive.StopMotor();
      going = false;
    }
    if(m_stick.GetAButtonPressed()){
      going = true;
    }
  }

  void DisabledInit() override{}
  void DisabledPeriodic() override{}

  void TestInit() override{}
  void TestPeriodic() override{}

  private:
    // Robot drive system
    frc::PWMSparkMax m_left{0};
    frc::PWMSparkMax m_right{1};
    frc::DifferentialDrive m_robotDrive{m_left, m_right};

    frc::XboxController m_stick{0};
    frc::Timer m_timer;

};


#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
