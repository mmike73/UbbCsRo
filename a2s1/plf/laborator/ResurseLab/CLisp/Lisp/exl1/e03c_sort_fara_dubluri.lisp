(defun elimina (e l)
    (cond
        ((null l) nil)
        ((atom (car l))
            (cond
                ((and (numberp (car l)) (= e (car l))) (elimina e (cdr l)))
                (t (cons (car l) (elimina e (cdr l))))
            )
        )
        (t (elimina e (cdr l)))
    )
)

(defun get_minimum (l)
    (labels ((get_minimum_helper (l crt_min)
        (cond
            ((null l) crt_min)
            ((< (car l) crt_min) (get_minimum_helper (cdr l) (car l)))
            (t (get_minimum_helper (cdr l) crt_min))
        ))
    ) (get_minimum_helper l most-positive-fixnum))
)

(defun sort_fara_dubluri (l)
    (cond
        ((null l) nil)
        ((numberp (car l)) 
            ((lambda (e l) 
                (append (list e) (sort_fara_dubluri (elimina e l))) ;; grija - trebuie eliminate doar minimele 
            ) (get_minimum l) l)                                    ;; -NU PRIMA DIN LISTA
        )   
        (t (cons (car l) (sort_fara_dubluri (cdr l))))
    )
)