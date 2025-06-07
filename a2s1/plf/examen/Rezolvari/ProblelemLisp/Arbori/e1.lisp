;;; arbore n-ar se reprezintă în LISP astfel ( nod subarbore1 subarbore2 .....). 
;;; Se cere să se determine calea de la radăcină către un nod dat. Se va folosi o funcție MAP.
(defun sau (l)
    (cond
        ((null l) nil)
        (t (or (car l) (sau (cdr l))))
    )
)

(defun apartine (nod arb)
    (cond
        ((and (atom arb) (equal nod arb)) t)
        ((atom arb) nil)
        (t (apply #'sau (list (mapcar #'(lambda (subarb) (apartine nod subarb)) arb))))
    )
)

(defun drum_rad_nod (nod arb)
    (cond
        ((null arb) nil)
        ((and (atom arb) (equal nod arb)) (list nod))
        ((apartine nod arb)
            (cons (car arb)
                (apply #'append (mapcar #'(lambda (subarb) (drum_rad_nod nod subarb)) (cdr arb)))
            )
        )
        (t nil)
    )
)

