(defun adancime_lista (l)
    (cond
        ((null l) 0)
        ((atom (car l)) (adancime_lista (cdr l)))
        (t (max (+ 1 (adancime_lista (car l))) (adancime_lista (cdr l))))
    )
)

;; atentie la paranteze