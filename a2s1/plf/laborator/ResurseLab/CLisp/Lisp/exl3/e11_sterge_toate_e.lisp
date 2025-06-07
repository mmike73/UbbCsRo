(defun sterge_e (l e)
    (cond
        ((and (atom l) (equal l e)) nil)
        ((atom l) (list l))
        (t (list (apply #'append  (mapcar #'(lambda (l) (sterge_e l e)) l))))
    )
)

;!!!! list face sa se pasreze nested formatul