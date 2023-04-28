
(cl:in-package :asdf)

(defsystem "serial_send-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Serial_Receive" :depends-on ("_package_Serial_Receive"))
    (:file "_package_Serial_Receive" :depends-on ("_package"))
    (:file "Serial_Send" :depends-on ("_package_Serial_Send"))
    (:file "_package_Serial_Send" :depends-on ("_package"))
  ))