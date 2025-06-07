(defun m (L)
    (cond
        ((numberp L) L)
        ((atom L) most-negative-fixnum)
        (t (apply #'max (mapcar #'m L)))
    )
)

(defun lista (L)
    (mapcan #'(lambda (L)
                ((lambda (v)
                    (cond
                        ((= 0 (mod v 2)) (list v))
                        (t nil)
                    )
                 ) (m L)
              )) L )
)

;; likely numerele maxime din ficare sublista, care sunt pare