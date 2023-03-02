; Auto-generated. Do not edit!


(cl:in-package Serial_Send-msg)


;//! \htmlinclude Serial_Receive.msg.html

(cl:defclass <Serial_Receive> (roslisp-msg-protocol:ros-message)
  ((vx
    :reader vx
    :initarg :vx
    :type cl:float
    :initform 0.0)
   (vy
    :reader vy
    :initarg :vy
    :type cl:float
    :initform 0.0)
   (wz
    :reader wz
    :initarg :wz
    :type cl:float
    :initform 0.0))
)

(cl:defclass Serial_Receive (<Serial_Receive>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Serial_Receive>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Serial_Receive)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name Serial_Send-msg:<Serial_Receive> is deprecated: use Serial_Send-msg:Serial_Receive instead.")))

(cl:ensure-generic-function 'vx-val :lambda-list '(m))
(cl:defmethod vx-val ((m <Serial_Receive>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader Serial_Send-msg:vx-val is deprecated.  Use Serial_Send-msg:vx instead.")
  (vx m))

(cl:ensure-generic-function 'vy-val :lambda-list '(m))
(cl:defmethod vy-val ((m <Serial_Receive>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader Serial_Send-msg:vy-val is deprecated.  Use Serial_Send-msg:vy instead.")
  (vy m))

(cl:ensure-generic-function 'wz-val :lambda-list '(m))
(cl:defmethod wz-val ((m <Serial_Receive>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader Serial_Send-msg:wz-val is deprecated.  Use Serial_Send-msg:wz instead.")
  (wz m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Serial_Receive>) ostream)
  "Serializes a message object of type '<Serial_Receive>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vx))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vy))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'wz))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Serial_Receive>) istream)
  "Deserializes a message object of type '<Serial_Receive>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vx) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vy) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'wz) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Serial_Receive>)))
  "Returns string type for a message object of type '<Serial_Receive>"
  "Serial_Send/Serial_Receive")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Serial_Receive)))
  "Returns string type for a message object of type 'Serial_Receive"
  "Serial_Send/Serial_Receive")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Serial_Receive>)))
  "Returns md5sum for a message object of type '<Serial_Receive>"
  "b2020d2d07e276a9930049ea7b96eb7a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Serial_Receive)))
  "Returns md5sum for a message object of type 'Serial_Receive"
  "b2020d2d07e276a9930049ea7b96eb7a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Serial_Receive>)))
  "Returns full string definition for message of type '<Serial_Receive>"
  (cl:format cl:nil "float32 vx~%float32 vy~%float32 wz~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Serial_Receive)))
  "Returns full string definition for message of type 'Serial_Receive"
  (cl:format cl:nil "float32 vx~%float32 vy~%float32 wz~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Serial_Receive>))
  (cl:+ 0
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Serial_Receive>))
  "Converts a ROS message object to a list"
  (cl:list 'Serial_Receive
    (cl:cons ':vx (vx msg))
    (cl:cons ':vy (vy msg))
    (cl:cons ':wz (wz msg))
))
