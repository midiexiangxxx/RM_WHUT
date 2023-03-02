; Auto-generated. Do not edit!


(cl:in-package Serial_Send-msg)


;//! \htmlinclude Serial_Send.msg.html

(cl:defclass <Serial_Send> (roslisp-msg-protocol:ros-message)
  ((gimbal_x
    :reader gimbal_x
    :initarg :gimbal_x
    :type cl:float
    :initform 0.0)
   (gimbal_y
    :reader gimbal_y
    :initarg :gimbal_y
    :type cl:float
    :initform 0.0)
   (gimbal_z
    :reader gimbal_z
    :initarg :gimbal_z
    :type cl:float
    :initform 0.0)
   (vx_set
    :reader vx_set
    :initarg :vx_set
    :type cl:float
    :initform 0.0)
   (vy_set
    :reader vy_set
    :initarg :vy_set
    :type cl:float
    :initform 0.0)
   (wz_set
    :reader wz_set
    :initarg :wz_set
    :type cl:float
    :initform 0.0))
)

(cl:defclass Serial_Send (<Serial_Send>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Serial_Send>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Serial_Send)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name Serial_Send-msg:<Serial_Send> is deprecated: use Serial_Send-msg:Serial_Send instead.")))

(cl:ensure-generic-function 'gimbal_x-val :lambda-list '(m))
(cl:defmethod gimbal_x-val ((m <Serial_Send>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader Serial_Send-msg:gimbal_x-val is deprecated.  Use Serial_Send-msg:gimbal_x instead.")
  (gimbal_x m))

(cl:ensure-generic-function 'gimbal_y-val :lambda-list '(m))
(cl:defmethod gimbal_y-val ((m <Serial_Send>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader Serial_Send-msg:gimbal_y-val is deprecated.  Use Serial_Send-msg:gimbal_y instead.")
  (gimbal_y m))

(cl:ensure-generic-function 'gimbal_z-val :lambda-list '(m))
(cl:defmethod gimbal_z-val ((m <Serial_Send>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader Serial_Send-msg:gimbal_z-val is deprecated.  Use Serial_Send-msg:gimbal_z instead.")
  (gimbal_z m))

(cl:ensure-generic-function 'vx_set-val :lambda-list '(m))
(cl:defmethod vx_set-val ((m <Serial_Send>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader Serial_Send-msg:vx_set-val is deprecated.  Use Serial_Send-msg:vx_set instead.")
  (vx_set m))

(cl:ensure-generic-function 'vy_set-val :lambda-list '(m))
(cl:defmethod vy_set-val ((m <Serial_Send>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader Serial_Send-msg:vy_set-val is deprecated.  Use Serial_Send-msg:vy_set instead.")
  (vy_set m))

(cl:ensure-generic-function 'wz_set-val :lambda-list '(m))
(cl:defmethod wz_set-val ((m <Serial_Send>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader Serial_Send-msg:wz_set-val is deprecated.  Use Serial_Send-msg:wz_set instead.")
  (wz_set m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Serial_Send>) ostream)
  "Serializes a message object of type '<Serial_Send>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'gimbal_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'gimbal_y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'gimbal_z))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vx_set))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vy_set))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'wz_set))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Serial_Send>) istream)
  "Deserializes a message object of type '<Serial_Send>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'gimbal_x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'gimbal_y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'gimbal_z) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vx_set) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vy_set) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'wz_set) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Serial_Send>)))
  "Returns string type for a message object of type '<Serial_Send>"
  "Serial_Send/Serial_Send")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Serial_Send)))
  "Returns string type for a message object of type 'Serial_Send"
  "Serial_Send/Serial_Send")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Serial_Send>)))
  "Returns md5sum for a message object of type '<Serial_Send>"
  "33a15562caea82466375017bafdca201")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Serial_Send)))
  "Returns md5sum for a message object of type 'Serial_Send"
  "33a15562caea82466375017bafdca201")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Serial_Send>)))
  "Returns full string definition for message of type '<Serial_Send>"
  (cl:format cl:nil "float32 gimbal_x~%float32 gimbal_y~%float32 gimbal_z~%float32 vx_set~%float32 vy_set~%float32 wz_set~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Serial_Send)))
  "Returns full string definition for message of type 'Serial_Send"
  (cl:format cl:nil "float32 gimbal_x~%float32 gimbal_y~%float32 gimbal_z~%float32 vx_set~%float32 vy_set~%float32 wz_set~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Serial_Send>))
  (cl:+ 0
     4
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Serial_Send>))
  "Converts a ROS message object to a list"
  (cl:list 'Serial_Send
    (cl:cons ':gimbal_x (gimbal_x msg))
    (cl:cons ':gimbal_y (gimbal_y msg))
    (cl:cons ':gimbal_z (gimbal_z msg))
    (cl:cons ':vx_set (vx_set msg))
    (cl:cons ':vy_set (vy_set msg))
    (cl:cons ':wz_set (wz_set msg))
))
