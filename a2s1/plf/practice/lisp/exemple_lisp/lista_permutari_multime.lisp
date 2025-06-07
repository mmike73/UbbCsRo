(defun permutari (l)
    (cond
        ((null (cdr l)) (list l))
        (t (mapcan #'(lambda (e)
            (mapcar #'(lambda (p)
                         (cons e p)
                      ) (permutari (remove e L)))
                
                     ) l))
    )
)