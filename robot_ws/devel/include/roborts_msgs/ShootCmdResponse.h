// Generated by gencpp from file roborts_msgs/ShootCmdResponse.msg
// DO NOT EDIT!


#ifndef ROBORTS_MSGS_MESSAGE_SHOOTCMDRESPONSE_H
#define ROBORTS_MSGS_MESSAGE_SHOOTCMDRESPONSE_H


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
struct ShootCmdResponse_
{
  typedef ShootCmdResponse_<ContainerAllocator> Type;

  ShootCmdResponse_()
    : received(false)  {
    }
  ShootCmdResponse_(const ContainerAllocator& _alloc)
    : received(false)  {
  (void)_alloc;
    }



   typedef uint8_t _received_type;
  _received_type received;





  typedef boost::shared_ptr< ::roborts_msgs::ShootCmdResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::roborts_msgs::ShootCmdResponse_<ContainerAllocator> const> ConstPtr;

}; // struct ShootCmdResponse_

typedef ::roborts_msgs::ShootCmdResponse_<std::allocator<void> > ShootCmdResponse;

typedef boost::shared_ptr< ::roborts_msgs::ShootCmdResponse > ShootCmdResponsePtr;
typedef boost::shared_ptr< ::roborts_msgs::ShootCmdResponse const> ShootCmdResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::roborts_msgs::ShootCmdResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::roborts_msgs::ShootCmdResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::roborts_msgs::ShootCmdResponse_<ContainerAllocator1> & lhs, const ::roborts_msgs::ShootCmdResponse_<ContainerAllocator2> & rhs)
{
  return lhs.received == rhs.received;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::roborts_msgs::ShootCmdResponse_<ContainerAllocator1> & lhs, const ::roborts_msgs::ShootCmdResponse_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace roborts_msgs

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::roborts_msgs::ShootCmdResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::roborts_msgs::ShootCmdResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::roborts_msgs::ShootCmdResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::roborts_msgs::ShootCmdResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::roborts_msgs::ShootCmdResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::roborts_msgs::ShootCmdResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::roborts_msgs::ShootCmdResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "dd4152e077925db952c78baadb1e48b7";
  }

  static const char* value(const ::roborts_msgs::ShootCmdResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xdd4152e077925db9ULL;
  static const uint64_t static_value2 = 0x52c78baadb1e48b7ULL;
};

template<class ContainerAllocator>
struct DataType< ::roborts_msgs::ShootCmdResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "roborts_msgs/ShootCmdResponse";
  }

  static const char* value(const ::roborts_msgs::ShootCmdResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::roborts_msgs::ShootCmdResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool received\n"
"\n"
;
  }

  static const char* value(const ::roborts_msgs::ShootCmdResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::roborts_msgs::ShootCmdResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.received);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct ShootCmdResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::roborts_msgs::ShootCmdResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::roborts_msgs::ShootCmdResponse_<ContainerAllocator>& v)
  {
    s << indent << "received: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.received);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ROBORTS_MSGS_MESSAGE_SHOOTCMDRESPONSE_H
