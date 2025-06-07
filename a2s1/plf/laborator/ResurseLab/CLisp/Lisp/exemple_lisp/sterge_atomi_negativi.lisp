(defun sterg (l)
    (cond
        ((and (numberp l) (minusp l)) nil)
        ((atom l) (list l))
        (t (list (apply #'append (mapcar #'sterg l))))
    )
)

(defun stergere (l)
    (car (sterg L)) 
)
;; unwraps the list


