;; Se cere să se determine înălțimea unui nod în arbore. Se va folosi o funcție MAP.

(defun sau (l)
    (cond
        ((null l) nil)
        (t (or (car l) (sau (cdr l))))
    )
)

(defun apartine (nod arb)
    (cond
        ((and (atom arb) (equal arb nod)) t)
        ((atom arb) nil)
        (t (apply #'sau (list (mapcar #'(lambda (subarb) (apartine nod subarb)) arb))))
    )
)

(defun inaltime_nod_arbore (nod arb)
    (cond
        ((null arb) 0)                            ;; Tree is empty, height is 0
        ((and (atom arb) (equal arb nod)) 1)      ;; Tree is an atom and matches node, height is 1
        ((atom arb) 0)                            ;; Tree is an atom but doesn't match node, height is 0
        ((apartine nod arb) 
        (+ 1 (apply #'+
                    (mapcar #'(lambda (subarb)
                                (inaltime_nod_arbore nod subarb)) 
                            (cdr arb)))))
        (t 0)
    )
)                                 