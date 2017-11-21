#include <thread>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include "ros/ros.h"
#include "ros/callback_queue.h"
#include "ros/subscribe_options.h"
#include "geometry_msgs/Twist.h"
namespace gazebo {
    class BusPlugin : public ModelPlugin {
        private: physics::ModelPtr model;
        private: physics::JointPtr joint_1l;
        private: physics::JointPtr joint_1r;
        private: physics::JointPtr joint_3l;
        private: common::PID pid;
        private: common::PID pid2;
        private: common::PID pid3;
        private: std::unique_ptr<ros::NodeHandle> node;
        private: ros::Subscriber subscriber;
        private: ros::CallbackQueue queue;
        private: std::thread thread;
        public: void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf) {
            model = _model;
            joint_1l = model->GetJoint("j.1.left");
            joint_1r = model->GetJoint("j.1.right");
            joint_3l = model->GetJoint("j.3.left");
            pid = common::PID(0.1, 0, 0);
            model->GetJointController()->SetVelocityPID(
                joint_1l->GetScopedName(),
                pid);
            pid2 = common::PID(0.1, 0, 0);
            model->GetJointController()->SetVelocityPID(
                joint_1r->GetScopedName(),
                pid2);
            pid3 = common::PID(0.1, 0, 0);
            model->GetJointController()->SetPositionPID(
                joint_3l->GetScopedName(),
                pid3);
            if (!ros::isInitialized()) {
                int argc = 0;
                char ** argv = NULL;
                ros::init(argc, argv, "bus");
            }
            node.reset(new ros::NodeHandle("bus"));
            ros::SubscribeOptions so =
                ros::SubscribeOptions::create<geometry_msgs::Twist>(
                "/" + model->GetName() + "/vel",
                1,
                boost::bind(&BusPlugin::OnVelMsg, this, _1),
                ros::VoidPtr(),
                &queue);
            subscriber = node->subscribe(so);
            thread = std::thread(std::bind(&BusPlugin::Thread, this));
        }
        public: void OnVelMsg(const geometry_msgs::TwistConstPtr & _msg) {
            model->GetJointController()->SetVelocityTarget(
                joint_1l->GetScopedName(),
                _msg->linear.x);
            model->GetJointController()->SetVelocityTarget(
                joint_1r->GetScopedName(),
                _msg->linear.x);
            model->GetJointController()->SetPositionTarget(
                joint_3l->GetScopedName(),
                _msg->angular.z);
        }
        private: void Thread() {
            static const double timeout = 0.01;
            while (node->ok()) {
                queue.callAvailable(ros::WallDuration(timeout));
            }
        }
    };
    GZ_REGISTER_MODEL_PLUGIN(BusPlugin)
}

