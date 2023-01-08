// Generated by gencpp from file roborts_msgs/ArmorDetectionFeedback.msg
// DO NOT EDIT!


#ifndef ROBORTS_MSGS_MESSAGE_ARMORDETECTIONFEEDBACK_H
#define ROBORTS_MSGS_MESSAGE_ARMORDETECTIONFEEDBACK_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <geometry_msgs/PoseStamped.h>

namespace roborts_msgs
{
template <class ContainerAllocator>
struct ArmorDetectionFeedback_
{
  typedef ArmorDetectionFeedback_<ContainerAllocator> Type;

  ArmorDetectionFeedback_()
    : detected(false)
    , error_code(0)
    , error_msg()
    , enemy_pos()  {
    }
  ArmorDetectionFeedback_(const ContainerAllocator& _alloc)
    : detected(false)
    , error_code(0)
    , error_msg(_alloc)
    , enemy_pos(_alloc)  {
  (void)_alloc;
    }



   typedef uint8_t _detected_type;
  _detected_type detected;

   typedef int32_t _error_code_type;
  _error_code_type error_code;

   typedef std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> _error_msg_type;
  _error_msg_type error_msg;

   typedef  ::geometry_msgs::PoseStamped_<ContainerAllocator>  _enemy_pos_type;
  _enemy_pos_type enemy_pos;





  typedef boost::shared_ptr< ::roborts_msgs::ArmorDetectionFeedback_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::roborts_msgs::ArmorDetectionFeedback_<ContainerAllocator> const> ConstPtr;

}; // struct ArmorDetectionFeedback_

typedef ::roborts_msgs::ArmorDetectionFeedback_<std::allocator<void> > ArmorDetectionFeedback;

typedef boost::shared_ptr< ::roborts_msgs::ArmorDetectionFeedback > ArmorDetectionFeedbackPtr;
typedef boost::shared_ptr< ::roborts_msgs::ArmorDetectionFeedback const> ArmorDetectionFeedbackConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::roborts_msgs::ArmorDetectionFeedback_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::roborts_msgs::ArmorDetectionFeedback_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::roborts_msgs::ArmorDetectionFeedback_<ContainerAllocator1> & lhs, const ::roborts_msgs::ArmorDetectionFeedback_<ContainerAllocator2> & rhs)
{
  return lhs.detected == rhs.detected &&
    lhs.error_code == rhs.error_code &&
    lhs.error_msg == rhs.error_msg &&
    lhs.enemy_pos == rhs.enemy_pos;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::roborts_msgs::ArmorDetectionFeedback_<ContainerAllocator1> & lhs, const ::roborts_msgs::ArmorDetectionFeedback_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace roborts_msgs

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::roborts_msgs::ArmorDetectionFeedback_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::roborts_msgs::ArmorDetectionFeedback_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::roborts_msgs::ArmorDetectionFeedback_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::roborts_msgs::ArmorDetectionFeedback_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::roborts_msgs::ArmorDetectionFeedback_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::roborts_msgs::ArmorDetectionFeedback_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::roborts_msgs::ArmorDetectionFeedback_<ContainerAllocator> >
{
  static const char* value()
  {
    return "8d02f36059a79608a4dff667f988ef60";
  }

  static const char* value(const ::roborts_msgs::ArmorDetectionFeedback_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x8d02f36059a79608ULL;
  static const uint64_t static_value2 = 0xa4dff667f988ef60ULL;
};

template<class ContainerAllocator>
struct DataType< ::roborts_msgs::ArmorDetectionFeedback_<ContainerAllocator> >
{
  static const char* value()
  {
    return "roborts_msgs/ArmorDetectionFeedback";
  }

  static const char* value(const ::roborts_msgs::ArmorDetectionFeedback_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::roborts_msgs::ArmorDetectionFeedback_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
"#feedback\n"
"bool detected\n"
"int32  error_code\n"
"string error_msg\n"
"geometry_msgs/PoseStamped enemy_pos\n"
"\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/PoseStamped\n"
"# A Pose with reference coordinate frame and timestamp\n"
"Header header\n"
"Pose pose\n"
"\n"
"================================================================================\n"
"MSG: std_msgs/Header\n"
"# Standard metadata for higher-level stamped data types.\n"
"# This is generally used to communicate timestamped data \n"
"# in a particular coordinate frame.\n"
"# \n"
"# sequence ID: consecutively increasing ID \n"
"uint32 seq\n"
"#Two-integer timestamp that is expressed as:\n"
"# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n"
"# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n"
"# time-handling sugar is provided by the client library\n"
"time stamp\n"
"#Frame this data is associated with\n"
"string frame_id\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Pose\n"
"# A representation of pose in free space, composed of position and orientation. \n"
"Point position\n"
"Quaternion orientation\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Point\n"
"# This contains the position of a point in free space\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Quaternion\n"
"# This represents an orientation in free space in quaternion form.\n"
"\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
"float64 w\n"
;
  }

  static const char* value(const ::roborts_msgs::ArmorDetectionFeedback_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::roborts_msgs::ArmorDetectionFeedback_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.detected);
      stream.next(m.error_code);
      stream.next(m.error_msg);
      stream.next(m.enemy_pos);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct ArmorDetectionFeedback_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::roborts_msgs::ArmorDetectionFeedback_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::roborts_msgs::ArmorDetectionFeedback_<ContainerAllocator>& v)
  {
    s << indent << "detected: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.detected);
    s << indent << "error_code: ";
    Printer<int32_t>::stream(s, indent + "  ", v.error_code);
    s << indent << "error_msg: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>::stream(s, indent + "  ", v.error_msg);
    s << indent << "enemy_pos: ";
    s << std::endl;
    Printer< ::geometry_msgs::PoseStamped_<ContainerAllocator> >::stream(s, indent + "  ", v.enemy_pos);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ROBORTS_MSGS_MESSAGE_ARMORDETECTIONFEEDBACK_H
