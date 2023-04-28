; Auto-generated. Do not edit!


(cl:in-package serial_send-msg)


;//! \htmlinclude Serial_Send.msg.html

(cl:defclass <Serial_Send> (roslisp-msg-protocol:ros-message)
  ((vx_set
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
    :initform 0.0)
   (yaw_add
    :reader yaw_add
    :initarg :yaw_add
    :type cl:float
    :initform 0.0)
   (pitch_add
    :reader pitch_add
    :initarg :pitch_add
    :type cl:float
    :initform 0.0)
   (mode
    :reader mode
    :initarg :mode
    :type cl:fixnum
    :initform 0))
)

(cl:defclass Serial_Send (<Serial_Send>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Serial_Send>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Serial_Send)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name serial_send-msg:<Serial_Send> is deprecated: use serial_send-msg:Serial_Send instead.")))

(cl:ensure-generic-function 'vx_set-val :lambda-list '(m))
(cl:defmethod vx_set-val ((m <Serial_Send>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader serial_send-msg:vx_set-val is deprecated.  Use serial_send-msg:vx_set instead.")
  (vx_set m))

(cl:ensure-generic-function 'vy_set-val :lambda-list '(m))
(cl:defmethod vy_set-val ((m <Serial_Send>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader serial_send-msg:vy_set-val is deprecated.  Use serial_send-msg:vy_set instead.")
  (vy_set m))

(cl:ensure-generic-function 'wz_set-val :lambda-list '(m))
(cl:defmethod wz_set-val ((m <Serial_Send>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader serial_send-msg:wz_set-val is deprecated.  Use serial_send-msg:wz_set instead.")
  (wz_set m))

(cl:ensure-generic-function 'yaw_add-val :lambda-list '(m))
(cl:defmethod yaw_add-val ((m <Serial_Send>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader serial_send-msg:yaw_add-val is deprecated.  Use serial_send-msg:yaw_add instead.")
  (yaw_add m))

(cl:ensure-generic-function 'pitch_add-val :lambda-list '(m))
(cl:defmethod pitch_add-val ((m <Serial_Send>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader serial_send-msg:pitch_add-val is deprecated.  Use serial_send-msg:pitch_add instead.")
  (pitch_add m))

(cl:ensure-generic-function 'mode-val :lambda-list '(m))
(cl:defmethod mode-val ((m <Serial_Send>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader serial_send-msg:mode-val is deprecated.  Use serial_send-msg:mode instead.")
  (mode m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Serial_Send>) ostream)
  "Serializes a message object of type '<Serial_Send>"
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
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'yaw_add))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'pitch_add))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'mode)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Serial_Send>) istream)
  "Deserializes a message object of type '<Serial_Send>"
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
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'yaw_add) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'pitch_add) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'mode)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Serial_Send>)))
  "Returns string type for a message object of type '<Serial_Send>"
  "serial_send/Serial_Send")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Serial_Send)))
  "Returns string type for a message object of type 'Serial_Send"
  "serial_send/Serial_Send")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Serial_Send>)))
  "Returns md5sum for a message object of type '<Serial_Send>"
  "73de9545dab8a1f88fa0fdc921aa3bba")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Serial_Send)))
  "Returns md5sum for a message object of type 'Serial_Send"
  "73de9545dab8a1f88fa0fdc921aa3bba")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Serial_Send>)))
  "Returns full string definition for message of type '<Serial_Send>"
  (cl:format cl:nil "float32 vx_set~%float32 vy_set~%float32 wz_set~%float32 yaw_add~%float32 pitch_add~%uint8 mode~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Serial_Send)))
  "Returns full string definition for message of type 'Serial_Send"
  (cl:format cl:nil "float32 vx_set~%float32 vy_set~%float32 wz_set~%float32 yaw_add~%float32 pitch_add~%uint8 mode~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Serial_Send>))
  (cl:+ 0
     4
     4
     4
     4
     4
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Serial_Send>))
  "Converts a ROS message object to a list"
  (cl:list 'Serial_Send
    (cl:cons ':vx_set (vx_set msg))
    (cl:cons ':vy_set (vy_set msg))
    (cl:cons ':wz_set (wz_set msg))
    (cl:cons ':yaw_add (yaw_add msg))
    (cl:cons ':pitch_add (pitch_add msg))
    (cl:cons ':mode (mode msg))
))
