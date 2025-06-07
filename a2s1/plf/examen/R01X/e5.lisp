(defun prim_par (l)
    (cond
        ((null l) nil)
        ((numberp (car l)) (= 0 (mod (car l) 2)))
        ((atom l) nil)
        (t (prim_par(cdr l)))
    )
)

(defun ne_subliste_car_par (l)
    (cond
        ((null l) 0)
        ((atom l) 0)
        ((and (list l) (prim_par l)) 
            (+ 1 (apply #'+ (mapcar #'ne_subliste_car_par l))))
        (t (apply #'+ (mapcar #'ne_subliste_car_par l)))
    )
)
