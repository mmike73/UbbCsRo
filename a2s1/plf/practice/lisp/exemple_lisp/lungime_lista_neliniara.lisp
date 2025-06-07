(defun LG (l)
    (cond
        ((atom l) 1)
        (t (apply #'+ (mapcar #'LG l)))
    )
)
