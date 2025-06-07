(defun subst_e_l1 (l e l1)
    (cond
        ((equal l e) (list l1))
        ((atom l) (list l))
        (t (apply #'append (mapcar #'(lambda (l) (subst_e_l1 l e l1)) l)))
    )
)

