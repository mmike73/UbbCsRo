(defun suma_at_num (l)
    (cond
        ((numberp l) l)
        ((atom l) 0)
        (t (apply #'+ (mapcar #'suma_at_num l)))
    )
)