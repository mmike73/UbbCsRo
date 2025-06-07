(defun SAU (l)
    (cond
        ((null l) nil)
        (t (or (car l) (SAU (cdr l))))
    )
)

(defun apartine (e l)
    (cond
        ((and (atom l) (equal e l)) t)
        ((atom l) nil)
        (t (apply #'SAU (list (mapcar #'(lambda (l) (apartine e l)) l))))
    )
)