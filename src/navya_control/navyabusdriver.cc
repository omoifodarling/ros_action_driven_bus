#include "boost/bind.hpp"
#include "gazebo/gazebo.hh"
#include "gazebo/physics/physics.hh"
#include "gazebo/common/common.hh"
#include "stdio.h"
#include <iostream>
#include <string>
#include <math.h>



/** author: Darlington Omoifo **/

namespace gazebo
{
  class NavyaBusDriver : public ModelPlugin
  {
  public: void Load(physics::ModelPtr _parent, sdf::ElementPtr /*_sdf*/)
    {
      this->model = _parent;

      // Initialise the joint by name using th private procedure
      this->initJoints();

      // Listen to the update event. This event is broadcast every
      // simulation iteration.
      this->updateConnection = event::Events::ConnectWorldUpdateBegin(boost::bind(&NavyaBusDriver::OnUpdate, this, _1));
    }

    // Called by the world update start event
  public: void OnUpdate(const common::UpdateInfo & /*_info*/)
    {
		this->rotate();
		this->move();
      
    }
    
    private: void rotate(){
		for(auto& j:joints)
			j->SetVelocity(0,(3.142*0.75));
		// controller->SetJointPosition(j,0,(3.142*0.75));
	}
    
    private: void move(){
		
		double disX = sin(joints[1]->GetAngle(0).Degree())*0.25,
		 disY = cos(joints[1]->GetAngle(0).Degree())*0.25;
		this->model->SetLinearVel(math::Vector3((disX-lastX), (disY-lastY), 0));
		
		if(simTime.GetWallTime().sec % 5 == 0){
		 printf("Joint:%s: Degree:%.4f,Radians:%.4f, vel:%.4f, Going X:%.4lf, Y:%.4lf\t\n", 
		  ((char*)joints[1]->GetName().c_str()),joints[1]->GetAngle(0).Degree(),
		  joints[1]->GetAngle(0).Radian(),this->joints[1]->GetVelocity(0),disX,disY);
		  }
		lastX = disX;
		lastY = disY;
	}
	
	private: void initJoints(){
		for(int i =0; i< 4; i++){
			this->joints[i] = this->model->GetJoint(j_names[i]);
			this->joints[i]->SetVelocityLimit(0,5.865);
			this->joints[i]->SetParam("max_force",0,10000000);
			controller->AddJoint(this->joints[i]);	
		}
		this->lastX = this->lastY = 0;
	}

     // Pointer to the model
  private: physics::ModelPtr model;
  private: common::Time simTime;
  private: physics::JointController * controller;


    // Pointer to the update event connection
  private: event::ConnectionPtr updateConnection;

    // Pointers to joints
    physics::JointPtr joints[4];
    std::string j_names[4] = {"front_right_wheel_joint","front_left_wheel_joint",
		"rear_right_wheel_joint","rear_left_wheel_joint"};
		double lastX, lastY;
  };

  // Register this plugin with the simulator
  GZ_REGISTER_MODEL_PLUGIN(NavyaBusDriver)
}
