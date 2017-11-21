/**
 * author Darlington Omoifo
 * **/

#ifndef _NavyaDriver_HH_
#define _NavyaDriver_HH_


##include "boost/bind.hpp"
#include "gazebo/gazebo.hh"
#include "gazebo/physics/physics.hh"
#include "gazebo/common/common.hh"
#include "stdio.h"
#include <iostream>
#include <string>
#include <math.h>

using namespace std;
namespace gazebo
{
  
  class NavyaDriver : public ModelPlugin
  {
   
    public: NavyaDriver() {}

   
    private: void loadJoints(){
			for(int m = 0; m < 4; m++){
				 this->tyres[m] = _model->GetJoint(j_names[m]);
				 this->model->GetJointController()->SetVelocityPID(
				this->tyres[m] ->GetName(), this->pid);
			 }
		}
		
    public: virtual void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf)
    {
      // Safety check
      if (_model->GetJointCount() == 0)
      {
        std::cerr << "Invalid joint count, Velodyne plugin not loaded\n";
        return;
      }

      // Store the model pointer for convenience.
      this->model = _model;

      
      this->pid = common::PID(0.1, 0, 0);

      
      loadJoints();

      // Default to zero velocity
      double velocity = 0;

      // Check that the velocity element exists, then read the value
      if (_sdf->HasElement("velocity"))
        velocity = _sdf->Get<double>("velocity");

      this->SetVelocity(velocity);

      // Create the node
      this->node = transport::NodePtr(new transport::Node());
      #if GAZEBO_MAJOR_VERSION < 8
      this->node->Init(this->model->GetWorld()->GetName());
      #else
      this->node->Init(this->model->GetWorld()->Name());
      #endif

      // Create a topic name
      std::string topicName = "~/" + this->model->GetName() + "/vel_cmd";

      // Subscribe to the topic, and register a callback
      this->sub = this->node->Subscribe(topicName,
         &NavyaDriver::OnVelUpdate, this);
    }

   
    public: void SetVelocity(const double &_vel)
    {
      // Set the joint's target velocity.
      for (auto& tyre:tyres) 
			this->model->GetJointController()->SetVelocityTarget(
          tyre->GetScopedName(), _vel);
    }

    
    private: void OnVelUpdate(ConstVector3dPtr &_msg)
    {
      this->SetVelocity(_msg->x());
    }

   
    private: transport::NodePtr node;
			transport::SubscriberPtr sub;
			physics::ModelPtr model;
			physics::JointPtr tyres[4];
			std::string j_names[4] = {"front_right_wheel_joint","front_left_wheel_joint",
		"rear_right_wheel_joint","rear_left_wheel_joint"};
			common::PID pid;
  };

  // Tell Gazebo about this plugin, so that Gazebo can call Load on this plugin.
  GZ_REGISTER_MODEL_PLUGIN(NavyaDriver)
}
#endif
