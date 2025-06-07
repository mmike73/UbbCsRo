(defun prim_impar (l)
    (cond
        ((null l) nil)
        ((numberp l) (list l))
        ((atom l) nil)
        (t (apply #'append (mapcar #'prim_impar l)))
    )
)

(defun nr_sub (l)
    (cond
        ((null l) 0)
        ((atom l) 0)
        ((and (listp l) (= 1 (mod (car (prim_impar l)) 2)) (+ 1 (apply #'+ (mapcar #'nr_sub l)))))
        (t (apply #'+ (mapcar #'nr_sub l)))
    )
)