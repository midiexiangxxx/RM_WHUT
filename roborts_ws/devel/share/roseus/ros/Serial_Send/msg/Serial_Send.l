;; Auto-generated. Do not edit!


(when (boundp 'Serial_Send::Serial_Send)
  (if (not (find-package "SERIAL_SEND"))
    (make-package "SERIAL_SEND"))
  (shadow 'Serial_Send (find-package "SERIAL_SEND")))
(unless (find-package "SERIAL_SEND::SERIAL_SEND")
  (make-package "SERIAL_SEND::SERIAL_SEND"))

(in-package "ROS")
;;//! \htmlinclude Serial_Send.msg.html


(defclass Serial_Send::Serial_Send
  :super ros::object
  :slots (_gimbal_x _gimbal_y _gimbal_z _vx_set _vy_set _wz_set ))

(defmethod Serial_Send::Serial_Send
  (:init
   (&key
    ((:gimbal_x __gimbal_x) 0.0)
    ((:gimbal_y __gimbal_y) 0.0)
    ((:gimbal_z __gimbal_z) 0.0)
    ((:vx_set __vx_set) 0.0)
    ((:vy_set __vy_set) 0.0)
    ((:wz_set __wz_set) 0.0)
    )
   (send-super :init)
   (setq _gimbal_x (float __gimbal_x))
   (setq _gimbal_y (float __gimbal_y))
   (setq _gimbal_z (float __gimbal_z))
   (setq _vx_set (float __vx_set))
   (setq _vy_set (float __vy_set))
   (setq _wz_set (float __wz_set))
   self)
  (:gimbal_x
   (&optional __gimbal_x)
   (if __gimbal_x (setq _gimbal_x __gimbal_x)) _gimbal_x)
  (:gimbal_y
   (&optional __gimbal_y)
   (if __gimbal_y (setq _gimbal_y __gimbal_y)) _gimbal_y)
  (:gimbal_z
   (&optional __gimbal_z)
   (if __gimbal_z (setq _gimbal_z __gimbal_z)) _gimbal_z)
  (:vx_set
   (&optional __vx_set)
   (if __vx_set (setq _vx_set __vx_set)) _vx_set)
  (:vy_set
   (&optional __vy_set)
   (if __vy_set (setq _vy_set __vy_set)) _vy_set)
  (:wz_set
   (&optional __wz_set)
   (if __wz_set (setq _wz_set __wz_set)) _wz_set)
  (:serialization-length
   ()
   (+
    ;; float32 _gimbal_x
    4
    ;; float32 _gimbal_y
    4
    ;; float32 _gimbal_z
    4
    ;; float32 _vx_set
    4
    ;; float32 _vy_set
    4
    ;; float32 _wz_set
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _gimbal_x
       (sys::poke _gimbal_x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _gimbal_y
       (sys::poke _gimbal_y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _gimbal_z
       (sys::poke _gimbal_z (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _vx_set
       (sys::poke _vx_set (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _vy_set
       (sys::poke _vy_set (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _wz_set
       (sys::poke _wz_set (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _gimbal_x
     (setq _gimbal_x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _gimbal_y
     (setq _gimbal_y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _gimbal_z
     (setq _gimbal_z (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _vx_set
     (setq _vx_set (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _vy_set
     (setq _vy_set (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _wz_set
     (setq _wz_set (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get Serial_Send::Serial_Send :md5sum-) "33a15562caea82466375017bafdca201")
(setf (get Serial_Send::Serial_Send :datatype-) "Serial_Send/Serial_Send")
(setf (get Serial_Send::Serial_Send :definition-)
      "float32 gimbal_x
float32 gimbal_y
float32 gimbal_z
float32 vx_set
float32 vy_set
float32 wz_set

")



(provide :Serial_Send/Serial_Send "33a15562caea82466375017bafdca201")


