;; Auto-generated. Do not edit!


(when (boundp 'Serial_Send::Serial_Receive)
  (if (not (find-package "SERIAL_SEND"))
    (make-package "SERIAL_SEND"))
  (shadow 'Serial_Receive (find-package "SERIAL_SEND")))
(unless (find-package "SERIAL_SEND::SERIAL_RECEIVE")
  (make-package "SERIAL_SEND::SERIAL_RECEIVE"))

(in-package "ROS")
;;//! \htmlinclude Serial_Receive.msg.html


(defclass Serial_Send::Serial_Receive
  :super ros::object
  :slots (_vx _vy _wz ))

(defmethod Serial_Send::Serial_Receive
  (:init
   (&key
    ((:vx __vx) 0.0)
    ((:vy __vy) 0.0)
    ((:wz __wz) 0.0)
    )
   (send-super :init)
   (setq _vx (float __vx))
   (setq _vy (float __vy))
   (setq _wz (float __wz))
   self)
  (:vx
   (&optional __vx)
   (if __vx (setq _vx __vx)) _vx)
  (:vy
   (&optional __vy)
   (if __vy (setq _vy __vy)) _vy)
  (:wz
   (&optional __wz)
   (if __wz (setq _wz __wz)) _wz)
  (:serialization-length
   ()
   (+
    ;; float32 _vx
    4
    ;; float32 _vy
    4
    ;; float32 _wz
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _vx
       (sys::poke _vx (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _vy
       (sys::poke _vy (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _wz
       (sys::poke _wz (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _vx
     (setq _vx (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _vy
     (setq _vy (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _wz
     (setq _wz (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get Serial_Send::Serial_Receive :md5sum-) "b2020d2d07e276a9930049ea7b96eb7a")
(setf (get Serial_Send::Serial_Receive :datatype-) "Serial_Send/Serial_Receive")
(setf (get Serial_Send::Serial_Receive :definition-)
      "float32 vx
float32 vy
float32 wz

")



(provide :Serial_Send/Serial_Receive "b2020d2d07e276a9930049ea7b96eb7a")


