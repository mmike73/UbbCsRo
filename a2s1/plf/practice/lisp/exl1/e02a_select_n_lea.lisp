(defun n_th (l n)
    (cond
        ((= 0 n) (car l))
        ((null l) nil)
        ((atom (car l)) (n_th (cdr l) (- n 1)))
        (t (cond
                ((lambda (elem)
                    (cond
                        ((not (= nil elem)) (n_th (cdr l) (- n 1))
                        (t nil)
                    )
                 ) (n_th (car l) n)
           )
        )
    )
)

;; transforma in lista liniara si dupa e simplu