(defun f(l)
    (cond
        ((atom l) -1)
        (((lambda (k) 
            (cond
                ((> k 0) (+ (car l) k (f (cdr l))))
                (t (f (cdr l)))
            )
        ) (f (car l))))
    )
)

(defun fi(l)
    (cond
        ((atom l) -1)
        ((> (fi (car l)) 0) (+ (car l) (fi (car l)) (fi (cdr l))))
        (t (fi (cdr l)))
    )
)