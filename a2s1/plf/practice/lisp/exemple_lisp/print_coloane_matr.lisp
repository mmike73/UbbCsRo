(defun coloane (L)
    (cond
        ((null (car L)) nil)
        (t (cons
            (mapcar #'car L)
            (coloane (mapcar #'cdr L))        
           )
        )
    )
)