;; functie auxiliara - verifica daca lista e para

(defun par (l)
    (cond
        ((= 0 (mod (length l) 2)) t)
        (t nil)
    )
)

(defun NR (l)
    (cond
        ((atom l) 0)
        ((par l) (+ 1 (apply  #'+ (mapcar #'+ NR l))))
        (t (apply #'+ (mapcar #'NR l)))
    )
)