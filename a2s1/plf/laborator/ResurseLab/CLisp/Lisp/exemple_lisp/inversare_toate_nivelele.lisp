(defun invers (l)
    (cond
        ((atom l) l)
        (t (append (invers (cdr l)) (list (car l))))
    )
)

(defun invers_col (l)
    (invers_col_aux l nil)
)

(defun invers_col_aux (l Col)
    (cond
        ((null l) Col)
        (t (invers_col_aux (cdr l) (cons (car l) Col)))
    )
)

(defun inversare (l)
    (cond
        ((atom l) (list l))
        (t (mapcan #'inversare (invers_col l)))
    )
)