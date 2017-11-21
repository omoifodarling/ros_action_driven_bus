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
  class VehicleDriver : public ModelPlugin
  {
public: VehicleDriver(): C("move_base", *this){cout << "NAVYA BUS CONSTRUCTED\n"<<endl;}	  
		  
	  
  public: void Load(physics::ModelPtr _parent, sdf::ElementPtr /*_sdf*/)
    {
      this->model = _parent;
      cout << "Address of controller BEFORE WAS: " << controller <<" \n"<<flush;
	  controller = this->model->GetJointController();
	  cout << "Address of controller AFTER IS: " << controller <<" \n"<<flush;
	  fflush(stdout);
	  
	  //fflush(stdout);
      // Initialise the joint by name using th private procedure
      this->initJoints();

      // Listen to the update event. This event is broadcast every
      // simulation iteration.
     MoveBase MoveBase("move_base",*this);
      //this->updateConnection = event::Events::ConnectWorldUpdateBegin(boost::bind(&VehicleDriver::OnUpdate, this, _1));
    }
//inner class move_base
private: class MoveBase
{
	private: VehicleDriver& navya;
protected:

  ros::NodeHandle nh_;
  actionlib::SimpleActionServer<move_base_msgs::MoveBaseAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
  std::string action_name_;
  enum What {DRIVE=0, TURN=1};
  // create messages that are used to published feedback/result
  move_base_msgs::MoveBaseFeedback feedback_;
  move_base_msgs::MoveBaseResult result_;

public:

  MoveBase(std::string name, VehicleDriver& d) :
    as_(nh_, name, boost::bind(&MoveBase::executeCB, this, _1), false),
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
    bool success = true,
    accel = true;
    const float T_PI = 3.14159265*2;
    string what  = goal->target_pose.header.frame_id;
    float target_dist = goal->target_pose.pose.position.x;
    navya.target_global_vel = target_dist;
    float step_dist = target_dist/50.0; 
    float tot_rot = navya.target_global_vel*180;
    float step_rot = tot_rot/50.0;
    float turn_angle = goal->target_pose.pose.orientation.z;
    float u_turn_angle = turn_angle/50.0;
	
    // push_back the seeds for the fibonacci sequence
  
	
	
    // publish info to the console for the user
    //ROS_INFO("%s: Executing velocity ros steering with orientation:%.2f\n", action_name_.c_str(),turn_angle);

    // start executing the action
    for(float pos=step_dist; pos<=target_dist; pos+=step_dist)
    {
		
      // check that preempt has not been requested by the client
      if (as_.isPreemptRequested() || !ros::ok())
      {
        //ROS_INFO("%s: Preempted", action_name_.c_str());
        // set the action state to preempted
        as_.setPreempted();
        success = false;
        break;
      }
     
		  
      if(toDo(what) == DRIVE && pos <= target_dist){
			//ROS_INFO("WE ARE DRIVING In LOOP\n");
			navya.global_pose.pos.x +=step_dist;
			navya.global_pose.rot.z +=step_rot;
			/*The right velocity is 2.5*the taget velocity using the vehicle velocity as engine*/
			//navya.rotate(step_rot*10.0);
			navya.move(step_dist,navya.iteration_counter);
			feedback_.base_position.pose.position.x = navya.global_pose.pos.x;
	   }
		else {
			//ROS_INFO("WE ARE TURNING In LOOP\n");
			navya.turn(u_turn_angle);	feedback_.base_position.pose.position.y += u_turn_angle;
			}  
      // publish the feedback
      as_.publishFeedback(feedback_);
      // this sleep is not necessary, the sequence is computed at 1 Hz for demonstration purposes
      r.sleep();
    }

    if(success)
    {
      ROS_INFO("%s: Succeeded. iteraction:%d", action_name_.c_str(),++navya.iteration_counter);
      // set the action state to succeeded
      as_.setSucceeded(result_);
    }
  }

  private:  What toDo(string name){
	char  d[] = "turn";
	 return strncmp(d,name.c_str(),strlen(name.c_str())) == 0 ? TURN: DRIVE;
}

/*public: int main(int argc, char** argv)
{
  ros::init(argc, argv, "move_base_server");

  MoveBase MoveBase("move_base",navya);
  ros::spin();

  return 0;
}*/

}C;


    // Called by the world update start event
  public: void OnUpdate(const common::UpdateInfo & /*_info*/)
    {
  MoveBase MoveBase("move_base",*this);
   ros::spin();
      
    }
    
    protected: void rotate(double rot){
		//ROS_INFO("ROTATING IN ROTATE tyre rotated %.2f rad/sec\n",rot);
		//It seems multiplexing causes context switch too quickly making either three
		// or one joint to be rotated. Also, when any front rotates the adjacent does same
		//Now, let's try rotated the front_left and rear_right only to possibly beat context switch
		/*for(auto& j:joints)
			j->SetVelocity(0,rot);*/
		for(int a = 0; a < 4; a+=3){
			joints[a]->SetVelocity(0,rot);
		}
		/*if(simTime.GetWallTime().sec % 5 == 0){
		for(int i=0; i< 4; i++)
				printf("Tyre with Joint:%s rotated %.2f Degrees\n", 
					((char*)joints[i]->GetScopedName().c_str()),joints[i]->GetAngle(0).Degree());
		printf("\tTotal distance to have been covered is covered:%.2f meters at %.2f rad/s.\n",global_pose.pos.x,rot);
		}*/
		
	}
    
    
    protected: double turn(double rot){
			for(auto& rim : rims)
				controller->SetJointPosition(rim->GetName(),rot,0);
			return rims[0]->GetVelocity(0);
			
		}
		
    protected: void move(float dist_2_move,int how_2_accel){
		if(this->model->GetWorldLinearVel().x == 0.000) iteration_counter = 0;
		
		
		this->model->SetLinearVel(ignition::math::Vector3d(accelerate(dist_2_move),0, 0));
		//this->model->SetLinearVel(ignition::math::Vector3d(1.0,0, 0));
		/*if(how_2_accel > 5)this->model->SetLinearVel(ignition::math::Vector3d(accelerate(dist_2_move),0, 0));
		else {
			this->global_vel += dist_2_move;
			this->model->SetLinearVel(ignition::math::Vector3d(1.0,0, 0)); 
			}*/
		if(simTime.GetWallTime().sec % 12 == 0){
			/*GetAngle(0) should be joints[1]->Position(0) in Gazebo 8 */
		 printf("Tyre:%s: Degree:%.4f,Radians:%.4f, vel:%.4f, distance covered:%.2f\t\nVehicle moving at %.2f m/s & GLOBAL VEL:%.2fm/s. ITER:%d\t\n", 
		  ((char*)joints[1]->GetScopedName().c_str()),joints[1]->GetAngle(0).Degree(),
		  joints[1]->GetAngle(0).Radian(),this->joints[1]->GetVelocity(0),global_pose.pos.x,this->model->GetWorldLinearVel().x,global_vel,iteration_counter);
		}
		
	}
	
	private: float accelerate(float dist){
		float speed = this->model->GetWorldLinearVel().x;
		if(iteration_counter > 5) { 
			if(speed < target_global_vel*2.5 - (dist*2))global_vel += speed +dist*.05;
			else global_vel = target_global_vel*2.5;
		}else if(global_vel == 0.0) global_vel = dist;
		else global_vel +=dist/1.02500;
		return global_vel < (target_global_vel*2.5 - (dist*2))  ? this->global_vel: target_global_vel*2.5;
		}
	
	private: void initJoints(){
		printf("Address of controller in INITJOINTS IS: %p\n",*controller);
		global_pose = math::Pose(0,0,0,0,0,0);
		global_vel = 0.0;
		iteration_counter = 0;
		tyres_pid = common::PID(250.0,0.01,10.0);
		rims_pid = common::PID(100.0,0.01,10.0);
		for(int i = 0; i < 6; i++){
			if(i < 4){
				j_ptr = (this->joints[i] = this->model->GetJoint(j_names[i]));
				j_ptr->SetVelocityLimit(0,30.865);
				//controller->AddJoint(j_ptr);
				controller->SetVelocityPID(j_ptr->GetScopedName(),tyres_pid);
				j_ptr->SetParam("max_force",0,10000000);
			}
				
			else {
				j_ptr = (this->rims[i-5] = this->model->GetJoint(r_names[i-5]));
				j_ptr->SetVelocityLimit(0,12.567);
				//controller->AddJoint(j_ptr);
				controller->SetVelocityPID(j_ptr->GetScopedName(),rims_pid);
				j_ptr->SetParam("max_force",0,10000);
			}
			j_ptr = NULL;
		}
		this->lastX = this->lastY = 0;
		printf("ADDRESS AFTER FINISHED INITIALIZING JOINTS: %p\n",*controller);
		fflush(stdin);
	}

     // Pointer to the model
  protected: physics::ModelPtr model;
  private: common::Time simTime;
  private: math::Pose global_pose;
  private: common::PID tyres_pid,rims_pid;
  private: physics::JointControllerPtr controller;
  private: float global_vel;
			float target_global_vel;
	private: int iteration_counter;
  


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
  GZ_REGISTER_MODEL_PLUGIN(VehicleDriver)
}

