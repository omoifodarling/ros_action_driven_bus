#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/server/simple_action_server.h>
#include "boost/bind.hpp"
#include "gazebo/gazebo.hh"
#include "gazebo/physics/physics.hh"
#include <gazebo/common/common.hh>
#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>



/** author: Darlington Omoifo **/

using namespace std;
namespace gazebo
{
  class NavyaBusDriver : public ModelPlugin
  {
public: NavyaBusDriver(): C("move_base", *this){}	  
		  
	  
  public: void Load(physics::ModelPtr _parent, sdf::ElementPtr /*_sdf*/)
    {
      this->model = _parent;
      cout << "size of controller BEFORE WAS: " << sizeof &controller <<endl;
	  controller = this->model->GetJointController();
	  cout << "size of controller AFTER IS: " << sizeof &controller <<endl;
	  
	  //fflush(stdout);
      // Initialise the joint by name using th private procedure
      this->initJoints();

      // Listen to the update event. This event is broadcast every
      // simulation iteration.
      
      this->updateConnection = event::Events::ConnectWorldUpdateBegin(boost::bind(&NavyaBusDriver::OnUpdate, this, _1));
    }
//inner class move_base
class MoveBase
{
	private: NavyaBusDriver& navya;
protected:

  ros::NodeHandle nh_;
  actionlib::SimpleActionServer<move_base_msgs::MoveBaseAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
  std::string action_name_;
  enum What {DRIVE=0, TURN=1};
  // create messages that are used to published feedback/result
  move_base_msgs::MoveBaseFeedback feedback_;
  move_base_msgs::MoveBaseResult result_;

public:

  MoveBase(std::string name, NavyaBusDriver& d) :
    as_(nh_, name, boost::bind(&MoveBase::executeCB, this, _1), true),
    action_name_(name), navya(d)
  {
    as_.start();
  }

  ~MoveBase(void)
  {
  }

  void executeCB(const move_base_msgs::MoveBaseGoalConstPtr &goal)
  {
    // helper variables
    ros::Rate r(50);
    bool success = true;
    action_name_ = goal->target_pose.header.frame_id;
    float target_dist = goal->target_pose.pose.position.x;
    float step_size = target_dist/45; 

    // push_back the seeds for the fibonacci sequence
    
	
    // publish info to the console for the user
    ROS_INFO("%s: Executing velocity ro steering", action_name_.c_str());

    // start executing the action
    for(int pos=step_size; pos<=target_dist; pos+=step_size)
    {
      // check that preempt has not been requested by the client
      if (as_.isPreemptRequested() || !ros::ok())
      {
        ROS_INFO("%s: Preempted", action_name_.c_str());
        // set the action state to preempted
        as_.setPreempted();
        success = false;
        break;
      }
     
		  
      if(toDo(action_name_) == DRIVE && pos <= target_dist){
		navya.model->SetLinearVel(math::Vector3(step_size, 0, 0));
		navya.rotate(tan(step_size/.25));
feedback_.base_position.pose.position.x = pos;
	   }
		else {navya.turn(step_size);	feedback_.base_position.pose.position.y = pos;}
				
      
      // publish the feedback
      as_.publishFeedback(feedback_);
      // this sleep is not necessary, the sequence is computed at 1 Hz for demonstration purposes
      r.sleep();
    }

    if(success)
    {
      ROS_INFO("%s: Succeeded", action_name_.c_str());
      // set the action state to succeeded
      as_.setSucceeded(result_);
    }
  }

  private:  What toDo(string name){
	char  d[] = "drive";
	 return strcpy(d,name.c_str()) == 0 ? DRIVE: TURN;
}

public: int main(int argc, char** argv)
{
  ros::init(argc, argv, "move_base_server");

  MoveBase MoveBase("move_base",navya);
  ros::spin();

  return 0;
}

}C;


    // Called by the world update start event
  public: void OnUpdate(const common::UpdateInfo & /*_info*/)
    {
  MoveBase MoveBase("move_base",*this);
   ros::spin();
      
    }
    
    protected: void rotate(double rot){
		for(auto& j:joints)
			j->SetVelocity(0,rot);
	}
    
    
    protected: double turn(double rot){
			for(auto& rim : rims)
				controller->SetJointPosition(rim->GetName(),rot,0);
			return rims[0]->GetVelocity(0);
			
		}
		
    protected: void move(float dist_2_move,float dist_2_rot){

		this->model->SetLinearVel(math::Vector3(dist_2_move,dist_2_rot, 0));
				
		lastX = dist_2_move;
		lastY = dist_2_rot;
		if(simTime.GetWallTime().sec % 5 == 0){
			/*GetAngle(0) should be joints[1]->Position(0) in Gazebo 8 */
		 printf("Joint:%s: Degree:%.4f,Radians:%.4f, vel:%.4f, Going X:%.4lf, Y:%.4lf\t\n", 
		  ((char*)joints[1]->GetName().c_str()),joints[1]->GetAngle(0).Degree(),
		  joints[1]->GetAngle(0).Radian(),this->joints[1]->GetVelocity(0),lastX,lastY);
		}
		
	}
	
	private: void initJoints(){
		tyres_pid.Init(250.0,0.01,10.0);
		rims_pid.Init(100.0,0.01,10.0);
		for(int i = 0; i < 6; i++){
			if(i < 4){
				j_ptr = (this->joints[i] = this->model->GetJoint(j_names[i]));
				j_ptr->SetVelocityLimit(0,30.865);
				controller->AddJoint(j_ptr);
				controller->SetVelocityPID(j_ptr->GetName(),tyres_pid);
				j_ptr->SetParam("max_force",0,10000000);
			}
				
			else {
				j_ptr = (this->rims[i-5] = this->model->GetJoint(r_names[i-5]));
				j_ptr->SetVelocityLimit(0,12.567);
				controller->AddJoint(j_ptr);
				controller->SetVelocityPID(j_ptr->GetName(),rims_pid);
				j_ptr->SetParam("max_force",0,10000);
			}
			j_ptr = NULL;
		}
		this->lastX = this->lastY = 0;
	}

     // Pointer to the model
  protected: physics::ModelPtr model;
  private: common::Time simTime;
  private: common::PID tyres_pid,rims_pid;
  private: physics::JointControllerPtr controller;
  


    // Pointer to the update event connection
  private: event::ConnectionPtr updateConnection;

    // Pointers to joints
    physics::JointPtr j_ptr, joints[4], rims[2];
    std::string j_names[4] = {"front_right_wheel_joint","front_left_wheel_joint",
		"rear_right_wheel_joint","rear_left_wheel_joint"};
		std::string r_names[2] = {"front_right_wheel_rim_joint","front_left_wheel_rim_joint"};
		double lastX, lastY;
		
  };
  
  

  // Register this plugin with the simulator
  GZ_REGISTER_MODEL_PLUGIN(NavyaBusDriver)
}

