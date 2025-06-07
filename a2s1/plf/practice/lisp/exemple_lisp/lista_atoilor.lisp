(defun atomi (l)
    (cond
        ((atom l) (list l))
        (t (mapcan #'atomi l))
    )
)

(defun atomi_mapcar (l)
    (cond
        ((atom l) (list l))
        (t (apply #'append (mapcar #'atomi l)))
    )
)