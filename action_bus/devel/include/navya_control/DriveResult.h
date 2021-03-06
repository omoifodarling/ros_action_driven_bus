// Generated by gencpp from file navya_control/DriveResult.msg
// DO NOT EDIT!


#ifndef NAVYA_CONTROL_MESSAGE_DRIVERESULT_H
#define NAVYA_CONTROL_MESSAGE_DRIVERESULT_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace navya_control
{
template <class ContainerAllocator>
struct DriveResult_
{
  typedef DriveResult_<ContainerAllocator> Type;

  DriveResult_()
    : total_dishes_cleaned(0.0)  {
    }
  DriveResult_(const ContainerAllocator& _alloc)
    : total_dishes_cleaned(0.0)  {
  (void)_alloc;
    }



   typedef double _total_dishes_cleaned_type;
  _total_dishes_cleaned_type total_dishes_cleaned;




  typedef boost::shared_ptr< ::navya_control::DriveResult_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::navya_control::DriveResult_<ContainerAllocator> const> ConstPtr;

}; // struct DriveResult_

typedef ::navya_control::DriveResult_<std::allocator<void> > DriveResult;

typedef boost::shared_ptr< ::navya_control::DriveResult > DriveResultPtr;
typedef boost::shared_ptr< ::navya_control::DriveResult const> DriveResultConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::navya_control::DriveResult_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::navya_control::DriveResult_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace navya_control

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'navya_control': ['/home/darling/Desktop/navya_working_copy/devel/share/navya_control/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::navya_control::DriveResult_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::navya_control::DriveResult_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::navya_control::DriveResult_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::navya_control::DriveResult_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::navya_control::DriveResult_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::navya_control::DriveResult_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::navya_control::DriveResult_<ContainerAllocator> >
{
  static const char* value()
  {
    return "d5197ab31647d52f52a19e26a5a69498";
  }

  static const char* value(const ::navya_control::DriveResult_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xd5197ab31647d52fULL;
  static const uint64_t static_value2 = 0x52a19e26a5a69498ULL;
};

template<class ContainerAllocator>
struct DataType< ::navya_control::DriveResult_<ContainerAllocator> >
{
  static const char* value()
  {
    return "navya_control/DriveResult";
  }

  static const char* value(const ::navya_control::DriveResult_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::navya_control::DriveResult_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
# Define the result\n\
float64 total_dishes_cleaned\n\
";
  }

  static const char* value(const ::navya_control::DriveResult_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::navya_control::DriveResult_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.total_dishes_cleaned);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct DriveResult_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::navya_control::DriveResult_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::navya_control::DriveResult_<ContainerAllocator>& v)
  {
    s << indent << "total_dishes_cleaned: ";
    Printer<double>::stream(s, indent + "  ", v.total_dishes_cleaned);
  }
};

} // namespace message_operations
} // namespace ros

#endif // NAVYA_CONTROL_MESSAGE_DRIVERESULT_H
