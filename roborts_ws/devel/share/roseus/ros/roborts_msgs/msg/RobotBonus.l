;; Auto-generated. Do not edit!


(when (boundp 'roborts_msgs::RobotBonus)
  (if (not (find-package "ROBORTS_MSGS"))
    (make-package "ROBORTS_MSGS"))
  (shadow 'RobotBonus (find-package "ROBORTS_MSGS")))
(unless (find-package "ROBORTS_MSGS::ROBOTBONUS")
  (make-package "ROBORTS_MSGS::ROBOTBONUS"))

(in-package "ROS")
;;//! \htmlinclude RobotBonus.msg.html


(defclass roborts_msgs::RobotBonus
  :super ros::object
  :slots (_bonus ))

(defmethod roborts_msgs::RobotBonus
  (:init
   (&key
    ((:bonus __bonus) nil)
    )
   (send-super :init)
   (setq _bonus __bonus)
   self)
  (:bonus
   (&optional __bonus)
   (if __bonus (setq _bonus __bonus)) _bonus)
  (:serialization-length
   ()
   (+
    ;; bool _bonus
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _bonus
       (if _bonus (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _bonus
     (setq _bonus (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get roborts_msgs::RobotBonus :md5sum-) "22365d98c104f9d16cae777ed759cbfe")
(setf (get roborts_msgs::RobotBonus :datatype-) "roborts_msgs/RobotBonus")
(setf (get roborts_msgs::RobotBonus :definition-)
      "#robot bonus
bool bonus

")



(provide :roborts_msgs/RobotBonus "22365d98c104f9d16cae777ed759cbfe")


