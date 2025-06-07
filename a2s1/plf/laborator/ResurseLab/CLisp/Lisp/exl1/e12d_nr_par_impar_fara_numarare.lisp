(defun verif_paritate_no_count (l)
    (cond
        ((null l) t)
        ((and (not (null l)) (null (cdr l))) nil)
        (t (verif_paritate_no_count (cddr l)))
    )
)