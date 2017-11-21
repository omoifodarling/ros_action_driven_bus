/**
 * author Darlington Omoifo
 * **/

#ifndef _NavyaDriver_HH_
#define _NavyaDriver_HH_


#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/transport/transport.hh>
#include <gazebo/msgs/msgs.hh>
#include <iostream>
#include <string>

using namespace std;
namespace gazebo
{
  /// \brief A plugin to control a Velodyne sensor.
  class NavyaDriver : public ModelPlugin
  {
    /// \brief Constructor
    public: NavyaDriver() {}

    /// \brief The load function is called by Gazebo when the plugin is
    /// inserted into simulation
    /// \param[in] _model A pointer to the model that this plugin is
    /// attached to.
    /// \param[in] _sdf A pointer to the plugin's SDF element.
    private: void loadJoints(){
			for(int m = 0; m < 8; m++){
				 this->tyres[m] = this->model->GetJoint(j_names[m]);
				 if(m < 4) this->model->GetJointController()->SetVelocityPID(
				this->tyres[m] ->GetScopedName(), this->pid);
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

      // Get the first joint. We are making an assumption about the model
      // having one joint that is the rotational joint.
      
		

      // Setup a P-controller, with a gain of 0.1.
      this->pid = common::PID(0.1, 0, 0);

      // Apply the P-controller to the joint.
      /*this->model->GetJointController()->SetVelocityPID(
          this->joint->GetScopedName(), this->pid);*/
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

    /// \brief Set the velocity of the Velodyne
    /// \param[in] _vel New target velocity
    public: void SetVelocity(const double &_vel)
    {
      // Set the joint's target velocity.
      for (auto& tyre:tyres) 
			this->model->GetJointController()->SetVelocityTarget(
          tyre->GetScopedName(), _vel);
    }

    /// \brief Handle incoming message
    /// \param[in] _msg Repurpose a vector3 message. This function will
    /// only use the x component.
    private: void OnVelUpdate(ConstVector3dPtr &_msg)
    {
      this->SetVelocity(_msg->x());
    }

    /// \brief A node used for transport
    private: transport::NodePtr node;

    /// \brief A subscriber to a named topic.
    private: transport::SubscriberPtr sub;

    /// \brief Pointer to the model.
    private: physics::ModelPtr model;

    /// \brief Pointer to the joint.
    private: physics::JointPtr tyres[4];
    private: string j_names[6] ={"front_left_wheel_joint","front_right_wheel_joint",
		"rear_left_wheel_joint","rear_right_wheel_joint","front_left_wheel_rim_joint",
			"front_right_wheel_rim_joint"};
		
		

    /// \brief A PID controller for the joint.
    private: common::PID pid;
  };

  // Tell Gazebo about this plugin, so that Gazebo can call Load on this plugin.
  GZ_REGISTER_MODEL_PLUGIN(NavyaDriver)
}
#endif
