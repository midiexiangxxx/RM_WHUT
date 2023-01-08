;; Auto-generated. Do not edit!


(when (boundp 'roborts_msgs::SupplierStatus)
  (if (not (find-package "ROBORTS_MSGS"))
    (make-package "ROBORTS_MSGS"))
  (shadow 'SupplierStatus (find-package "ROBORTS_MSGS")))
(unless (find-package "ROBORTS_MSGS::SUPPLIERSTATUS")
  (make-package "ROBORTS_MSGS::SUPPLIERSTATUS"))

(in-package "ROS")
;;//! \htmlinclude SupplierStatus.msg.html


(intern "*CLOSE*" (find-package "ROBORTS_MSGS::SUPPLIERSTATUS"))
(shadow '*CLOSE* (find-package "ROBORTS_MSGS::SUPPLIERSTATUS"))
(defconstant roborts_msgs::SupplierStatus::*CLOSE* 0)
(intern "*PREPARING*" (find-package "ROBORTS_MSGS::SUPPLIERSTATUS"))
(shadow '*PREPARING* (find-package "ROBORTS_MSGS::SUPPLIERSTATUS"))
(defconstant roborts_msgs::SupplierStatus::*PREPARING* 1)
(intern "*SUPPLYING*" (find-package "ROBORTS_MSGS::SUPPLIERSTATUS"))
(shadow '*SUPPLYING* (find-package "ROBORTS_MSGS::SUPPLIERSTATUS"))
(defconstant roborts_msgs::SupplierStatus::*SUPPLYING* 2)
(defclass roborts_msgs::SupplierStatus
  :super ros::object
  :slots (_status ))

(defmethod roborts_msgs::SupplierStatus
  (:init
   (&key
    ((:status __status) 0)
    )
   (send-super :init)
   (setq _status (round __status))
   self)
  (:status
   (&optional __status)
   (if __status (setq _status __status)) _status)
  (:serialization-length
   ()
   (+
    ;; uint8 _status
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _status
       (write-byte _status s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _status
     (setq _status (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get roborts_msgs::SupplierStatus :md5sum-) "81f3d032e85b689acf259876e6f8d051")
(setf (get roborts_msgs::SupplierStatus :datatype-) "roborts_msgs/SupplierStatus")
(setf (get roborts_msgs::SupplierStatus :definition-)
      "#supplier status
uint8 CLOSE = 0
uint8 PREPARING = 1
uint8 SUPPLYING = 2
uint8 status


")



(provide :roborts_msgs/SupplierStatus "81f3d032e85b689acf259876e6f8d051")


