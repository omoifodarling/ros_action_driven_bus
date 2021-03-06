;; Auto-generated. Do not edit!


(when (boundp 'navya_control::DriveFeedback)
  (if (not (find-package "NAVYA_CONTROL"))
    (make-package "NAVYA_CONTROL"))
  (shadow 'DriveFeedback (find-package "NAVYA_CONTROL")))
(unless (find-package "NAVYA_CONTROL::DRIVEFEEDBACK")
  (make-package "NAVYA_CONTROL::DRIVEFEEDBACK"))

(in-package "ROS")
;;//! \htmlinclude DriveFeedback.msg.html


(defclass navya_control::DriveFeedback
  :super ros::object
  :slots (_percent_complete ))

(defmethod navya_control::DriveFeedback
  (:init
   (&key
    ((:percent_complete __percent_complete) 0.0)
    )
   (send-super :init)
   (setq _percent_complete (float __percent_complete))
   self)
  (:percent_complete
   (&optional __percent_complete)
   (if __percent_complete (setq _percent_complete __percent_complete)) _percent_complete)
  (:serialization-length
   ()
   (+
    ;; float32 _percent_complete
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _percent_complete
       (sys::poke _percent_complete (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _percent_complete
     (setq _percent_complete (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get navya_control::DriveFeedback :md5sum-) "d342375c60a5a58d3bc32664070a1368")
(setf (get navya_control::DriveFeedback :datatype-) "navya_control/DriveFeedback")
(setf (get navya_control::DriveFeedback :definition-)
      "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
# Define a feedback message
float32 percent_complete


")



(provide :navya_control/DriveFeedback "d342375c60a5a58d3bc32664070a1368")


