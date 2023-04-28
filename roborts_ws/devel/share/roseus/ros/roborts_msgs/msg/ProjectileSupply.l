;; Auto-generated. Do not edit!


(when (boundp 'roborts_msgs::ProjectileSupply)
  (if (not (find-package "ROBORTS_MSGS"))
    (make-package "ROBORTS_MSGS"))
  (shadow 'ProjectileSupply (find-package "ROBORTS_MSGS")))
(unless (find-package "ROBORTS_MSGS::PROJECTILESUPPLY")
  (make-package "ROBORTS_MSGS::PROJECTILESUPPLY"))

(in-package "ROS")
;;//! \htmlinclude ProjectileSupply.msg.html


(defclass roborts_msgs::ProjectileSupply
  :super ros::object
  :slots (_number ))

(defmethod roborts_msgs::ProjectileSupply
  (:init
   (&key
    ((:number __number) 0)
    )
   (send-super :init)
   (setq _number (round __number))
   self)
  (:number
   (&optional __number)
   (if __number (setq _number __number)) _number)
  (:serialization-length
   ()
   (+
    ;; uint8 _number
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _number
       (write-byte _number s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _number
     (setq _number (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get roborts_msgs::ProjectileSupply :md5sum-) "29e94f7568510a2f9241abcc8f191b4f")
(setf (get roborts_msgs::ProjectileSupply :datatype-) "roborts_msgs/ProjectileSupply")
(setf (get roborts_msgs::ProjectileSupply :definition-)
      "#projectile supply
uint8 number

")



(provide :roborts_msgs/ProjectileSupply "29e94f7568510a2f9241abcc8f191b4f")


