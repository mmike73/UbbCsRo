(defun get_minim_niv_impar (l niv)
    (cond
        ((null l) most-positive-fixnum)
        ((and (= 0 (mod niv 2)) (numberp l)) l)
        ((atom l) most-positive-fixnum)
        (t (apply #'min (mapcar #'(lambda (lst) (get_minim_niv_impar lst (+ niv 1))) l)))
    )
)

(defun cnt_propr (l niv)
    (cond
        ((null l) 0)
        ((atom l) 0)
        ((and (= 0 (mod (get_minim_niv_impar l niv) 2))) 
            (+ 1 (apply #'+ (mapcar #'(lambda (lst) (cnt_propr lst (+ niv 1))) l))))
        (t (apply #'+ (mapcar #'(lambda (lst) (cnt_propr lst (+ niv 1))) l)))
    )
)
