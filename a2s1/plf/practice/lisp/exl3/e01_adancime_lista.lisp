(defun adancime_lista (l)
    (cond
        ((null l) 0)
        ((not (listp l)) 0)
        (t 
            (+ 1 (apply #'max (mapcar #'adancime_lista l)))
        )
    )
)
