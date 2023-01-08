// Generated by gencpp from file roborts_msgs/RobotDamage.msg
// DO NOT EDIT!


#ifndef ROBORTS_MSGS_MESSAGE_ROBOTDAMAGE_H
#define ROBORTS_MSGS_MESSAGE_ROBOTDAMAGE_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace roborts_msgs
{
template <class ContainerAllocator>
struct RobotDamage_
{
  typedef RobotDamage_<ContainerAllocator> Type;

  RobotDamage_()
    : damage_type(0)
    , damage_source(0)  {
    }
  RobotDamage_(const ContainerAllocator& _alloc)
    : damage_type(0)
    , damage_source(0)  {
  (void)_alloc;
    }



   typedef uint8_t _damage_type_type;
  _damage_type_type damage_type;

   typedef uint8_t _damage_source_type;
  _damage_source_type damage_source;



// reducing the odds to have name collisions with Windows.h 
#if defined(_WIN32) && defined(ARMOR)
  #undef ARMOR
#endif
#if defined(_WIN32) && defined(OFFLINE)
  #undef OFFLINE
#endif
#if defined(_WIN32) && defined(EXCEED_HEAT)
  #undef EXCEED_HEAT
#endif
#if defined(_WIN32) && defined(EXCEED_POWER)
  #undef EXCEED_POWER
#endif
#if defined(_WIN32) && defined(FORWARD)
  #undef FORWARD
#endif
#if defined(_WIN32) && defined(LEFT)
  #undef LEFT
#endif
#if defined(_WIN32) && defined(BACKWARD)
  #undef BACKWARD
#endif
#if defined(_WIN32) && defined(RIGHT)
  #undef RIGHT
#endif

  enum {
    ARMOR = 0u,
    OFFLINE = 1u,
    EXCEED_HEAT = 2u,
    EXCEED_POWER = 3u,
    FORWARD = 0u,
    LEFT = 1u,
    BACKWARD = 2u,
    RIGHT = 3u,
  };


  typedef boost::shared_ptr< ::roborts_msgs::RobotDamage_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::roborts_msgs::RobotDamage_<ContainerAllocator> const> ConstPtr;

}; // struct RobotDamage_

typedef ::roborts_msgs::RobotDamage_<std::allocator<void> > RobotDamage;

typedef boost::shared_ptr< ::roborts_msgs::RobotDamage > RobotDamagePtr;
typedef boost::shared_ptr< ::roborts_msgs::RobotDamage const> RobotDamageConstPtr;

// constants requiring out of line definition

   

   

   

   

   

   

   

   



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::roborts_msgs::RobotDamage_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::roborts_msgs::RobotDamage_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::roborts_msgs::RobotDamage_<ContainerAllocator1> & lhs, const ::roborts_msgs::RobotDamage_<ContainerAllocator2> & rhs)
{
  return lhs.damage_type == rhs.damage_type &&
    lhs.damage_source == rhs.damage_source;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::roborts_msgs::RobotDamage_<ContainerAllocator1> & lhs, const ::roborts_msgs::RobotDamage_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace roborts_msgs

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::roborts_msgs::RobotDamage_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::roborts_msgs::RobotDamage_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::roborts_msgs::RobotDamage_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::roborts_msgs::RobotDamage_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::roborts_msgs::RobotDamage_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::roborts_msgs::RobotDamage_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::roborts_msgs::RobotDamage_<ContainerAllocator> >
{
  static const char* value()
  {
    return "effef5d3b7e81a8189f62bb1e64ada64";
  }

  static const char* value(const ::roborts_msgs::RobotDamage_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xeffef5d3b7e81a81ULL;
  static const uint64_t static_value2 = 0x89f62bb1e64ada64ULL;
};

template<class ContainerAllocator>
struct DataType< ::roborts_msgs::RobotDamage_<ContainerAllocator> >
{
  static const char* value()
  {
    return "roborts_msgs/RobotDamage";
  }

  static const char* value(const ::roborts_msgs::RobotDamage_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::roborts_msgs::RobotDamage_<ContainerAllocator> >
{
  static const char* value()
  {
    return "#robot damage\n"
"uint8 ARMOR = 0\n"
"uint8 OFFLINE = 1\n"
"uint8 EXCEED_HEAT = 2\n"
"uint8 EXCEED_POWER = 3\n"
"uint8 damage_type\n"
"uint8 FORWARD = 0\n"
"uint8 LEFT = 1\n"
"uint8 BACKWARD = 2\n"
"uint8 RIGHT = 3\n"
"uint8 damage_source\n"
"\n"
"\n"
;
  }

  static const char* value(const ::roborts_msgs::RobotDamage_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::roborts_msgs::RobotDamage_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.damage_type);
      stream.next(m.damage_source);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct RobotDamage_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::roborts_msgs::RobotDamage_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::roborts_msgs::RobotDamage_<ContainerAllocator>& v)
  {
    s << indent << "damage_type: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.damage_type);
    s << indent << "damage_source: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.damage_source);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ROBORTS_MSGS_MESSAGE_ROBOTDAMAGE_H
