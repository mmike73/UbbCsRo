(defun sau (l)
    (cond
        ((null l) nil)
        (t (or (car l) (sau (cdr l))))
    )
)

(defun apartine(e l) 
    (cond
        ((null l) nil)
        ((and (atom l) (equal e l)) t)
        ((atom l) nil)
        (t (apply #'sau (list (mapcar #'(lambda (l1) (apartine e l1)) l))))
    )
)

(defun find_path (e l)
    (cond
        ((null l) nil)
        ((atom l) nil)
        ((apartine e l) 
            (append (list (car l)) (apply #'append (mapcar #'(lambda (l1) (find_path e l1) ) l)))
        )
        (t 
            (apply #'append (mapcar #'(lambda (l1) (find_path e l1) ) l))
        )
    )
)