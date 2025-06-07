(defun lista_at_toate_niv (l)
    (cond
        ((atom l) (list l))
        (t (mapcan #'lista_at_toate_niv l))
    )
)

;;mapcan - aplica nconc pentru fiecare lista, 
;; daca e cumva atom, se va face lsita,
;; daca e lista, va intra in mapcar si 
;; element cu element va intra in atom

(defun lista_at_toate_niv_mapcar (l)
    (cond 
        ((atom l) (list l))
        (t (apply #'append (mapcar #'lista_at_toate_niv_mapcar l)))
    )
)