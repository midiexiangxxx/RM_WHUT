;; Auto-generated. Do not edit!


(when (boundp 'serial_send::Serial_Send)
  (if (not (find-package "SERIAL_SEND"))
    (make-package "SERIAL_SEND"))
  (shadow 'Serial_Send (find-package "SERIAL_SEND")))
(unless (find-package "SERIAL_SEND::SERIAL_SEND")
  (make-package "SERIAL_SEND::SERIAL_SEND"))

(in-package "ROS")
;;//! \htmlinclude Serial_Send.msg.html


(defclass serial_send::Serial_Send
  :super ros::object
  :slots (_vx_set _vy_set _wz_set _yaw_add _pitch_add _mode ))

(defmethod serial_send::Serial_Send
  (:init
   (&key
    ((:vx_set __vx_set) 0.0)
    ((:vy_set __vy_set) 0.0)
    ((:wz_set __wz_set) 0.0)
    ((:yaw_add __yaw_add) 0.0)
    ((:pitch_add __pitch_add) 0.0)
    ((:mode __mode) 0)
    )
   (send-super :init)
   (setq _vx_set (float __vx_set))
   (setq _vy_set (float __vy_set))
   (setq _wz_set (float __wz_set))
   (setq _yaw_add (float __yaw_add))
   (setq _pitch_add (float __pitch_add))
   (setq _mode (round __mode))
   self)
  (:vx_set
   (&optional __vx_set)
   (if __vx_set (setq _vx_set __vx_set)) _vx_set)
  (:vy_set
   (&optional __vy_set)
   (if __vy_set (setq _vy_set __vy_set)) _vy_set)
  (:wz_set
   (&optional __wz_set)
   (if __wz_set (setq _wz_set __wz_set)) _wz_set)
  (:yaw_add
   (&optional __yaw_add)
   (if __yaw_add (setq _yaw_add __yaw_add)) _yaw_add)
  (:pitch_add
   (&optional __pitch_add)
   (if __pitch_add (setq _pitch_add __pitch_add)) _pitch_add)
  (:mode
   (&optional __mode)
   (if __mode (setq _mode __mode)) _mode)
  (:serialization-length
   ()
   (+
    ;; float32 _vx_set
    4
    ;; float32 _vy_set
    4
    ;; float32 _wz_set
    4
    ;; float32 _yaw_add
    4
    ;; float32 _pitch_add
    4
    ;; uint8 _mode
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _vx_set
       (sys::poke _vx_set (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _vy_set
       (sys::poke _vy_set (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _wz_set
       (sys::poke _wz_set (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _yaw_add
       (sys::poke _yaw_add (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _pitch_add
       (sys::poke _pitch_add (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; uint8 _mode
       (write-byte _mode s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _vx_set
     (setq _vx_set (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _vy_set
     (setq _vy_set (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _wz_set
     (setq _wz_set (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _yaw_add
     (setq _yaw_add (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _pitch_add
     (setq _pitch_add (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; uint8 _mode
     (setq _mode (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get serial_send::Serial_Send :md5sum-) "73de9545dab8a1f88fa0fdc921aa3bba")
(setf (get serial_send::Serial_Send :datatype-) "serial_send/Serial_Send")
(setf (get serial_send::Serial_Send :definition-)
      "float32 vx_set
float32 vy_set
float32 wz_set
float32 yaw_add
float32 pitch_add
uint8 mode
")



(provide :serial_send/Serial_Send "73de9545dab8a1f88fa0fdc921aa3bba")


